#include "agent.hpp"

int agent::get_move(int state_no, state st)
{
    return 0;
}

int simple_agent::get_move(int state_no, state st)
{
    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            return i;
        }
    }
    cout << "Warning: simple agent could not select move." << endl;
    return 0;
}

int random_agent::get_move(int state_no, state st)
{
    int index = rand() % (st.no_of_valid_actions);
    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (index == 0)
            {
                return i;
            }
            index--;
        }
    }
    cout << "Warning: random agent could not select move." << endl;
    return 0;
}

int q_agent::get_move(int state_no, state st)
{
    if (this->last_state != -1)
    {
        this->give_feedback(boxes_diff, st);
    }

    //EXPLORATION 1:
    /*int base = state_no * st.actions.size();
    double max = -DBL_MAX;
    int move = 0;
    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (q_values[base + i] == 0.0)
            {
                move = i;
                break;
            }
            else if (q_values[base + i] > max)
            {
                max = q_values[base + i];
                move = i;
            }
        }
    }
    this->last_state = state_no;
    this->last_action = move;
    return move;*/

    //EXPLORATION 2:
    int base = state_no * st.actions.size();
    double max = -DBL_MAX;
    int move = 0;
    int chance = rand() % 10;
    bool explore;
    if ((chance < (10 - epsilon)) || (no_of_actions <= 1))
    {
        explore = false;
    }
    else
    {
        explore = true;
    }
    int choose = rand() % st.no_of_valid_actions;

    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (explore)
            {
                if (choose == 0)
                {
                    move = i;
                    break;
                }
                choose--;
            }
            else if (q_values[base + i] > max)
            {
                max = q_values[base + i];
                move = i;
            }
        }
    }
    this->last_state = state_no;
    this->last_action = move;
    return move;

    //EXPLORATION 3:
    /*int move = 0;

    int index = rand() % st.no_of_valid_actions;

    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (index == 0)
            {
                move = i;
            }
            index--;
        }
    }
    this->last_state = state_no;
    this->last_action = move;
    return move;*/
}

int agent::get_move_trained(int state_no, state st)
{
    return this->get_move(state_no, st);
}

int simple_agent::get_move_trained(int state_no, state st)
{
    return this->get_move(state_no, st);
}

int random_agent::get_move_trained(int state_no, state st)
{
    return this->get_move(state_no, st);
}

int q_agent::get_move_trained(int state_no, state st)
{
    int base = state_no * st.actions.size();
    double max = -DBL_MAX;
    int move = 0;

    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (q_values[base + i] > max)
            {
                max = q_values[base + i];
                move = i;
            }
        }
    }

    this->last_state = state_no;
    this->last_action = move;
    return move;
    /*int base = state_no * st.actions.size();
    double max = -DBL_MAX;
    int move = 0;
    int epsilon = 1;
    int chance = rand() % 10;
    bool explore;
    if ((chance < (10 - epsilon)) || (no_of_actions <= 1))
    {
        explore = false;
    }
    else
    {
        explore = true;
    }
    int choose = rand() % st.no_of_valid_actions;

    for (int i = 0; i < st.actions.size(); i++)
    {
        if (st.actions[i])
        {
            if (explore)
            {
                if (choose == 0)
                {
                    move = i;
                    break;
                }
                choose--;
            }
            else if (q_values[base + i] > max)
            {
                max = q_values[base + i];
                move = i;
            }
        }
    }
    this->last_state = state_no;
    this->last_action = move;
    return move;*/
}

void agent::give_feedback(int feedback, state new_state)
{
    return;
}

void simple_agent::give_feedback(int feedback, state new_state)
{
    return;
}

void random_agent::give_feedback(int feedback, state new_state)
{
    return;
}

void q_agent::give_feedback(int feedback, state new_state)
{
    double prev_q = q_values[last_state * no_of_actions + last_action];
    double max = 0;
    if (new_state.no_of_valid_actions != 0)
    {
        int max_action = -1;
        max = -DBL_MAX;
        int new_state_no = last_state + pow(2, last_action);
        for (int i = 0; i < no_of_actions; i++)
        {
            if (new_state.actions[i])
            {
                if (q_values[new_state_no + i] > max)
                {
                    max = q_values[new_state_no + i];
                    max_action = i;
                }
            }
        }
    }
    double new_q = prev_q + learning_rate * (feedback + discount_factor * max - prev_q);
    q_values[last_state * no_of_actions + last_action] = new_q;
    //cout << "New q: " << new_q << endl;
    return;
}

void agent::set(int rows, int columns, double discount_factor, double learning_rate, int epsilon)
{
    return;
}

void random_agent::set(int rows, int columns, double discount_factor, double learning_rate, int epsilon)
{
    return;
}

void simple_agent::set(int rows, int columns, double discount_factor, double learning_rate, int epsilon)
{
    return;
}

void q_agent::set(int rows, int columns, double discount_factor, double learning_rate, int epsilon)
{
    no_of_actions = (columns - 1) * (rows) + (rows - 1) * columns;
    int no_of_states = pow(2, no_of_actions);
    q_values.resize(no_of_states * no_of_actions, 0.0);
    this->discount_factor = discount_factor;
    this->learning_rate = learning_rate;
    this->epsilon = epsilon;
}

void q_agent::print_q_values()
{
    for (auto d : q_values)
    {
        if (d == 0.0)
        {
            continue;
        }
        cout << d << endl;
    }
}

void agent::reset()
{
    return;
}

void simple_agent::reset()
{
    return;
}

void random_agent::reset()
{
    return;
}

void q_agent::reset()
{
    last_state = -1;
    last_action = -1;
}

void agent::set_boxes_diff(double boxes_diff)
{
    return;
}

void simple_agent::set_boxes_diff(double boxes_diff)
{
    return;
}
void random_agent::set_boxes_diff(double boxes_diff)
{
    return;
}

void q_agent::set_boxes_diff(double boxes_diff)
{
    this->boxes_diff = boxes_diff;
}

void agent::add_boxes_diff(double boxes_diff)
{
    return;
}

void simple_agent::add_boxes_diff(double boxes_diff)
{
    return;
}

void random_agent::add_boxes_diff(double boxes_diff)
{
    return;
}

void q_agent::add_boxes_diff(double boxes_diff)
{
    this->boxes_diff += boxes_diff;
    return;
}

void agent::write_file(ofstream &fout)
{
    return;
}
void agent::read_file(ifstream &fin)
{
    return;
}

void simple_agent::write_file(ofstream &fout)
{
    return;
}
void simple_agent::read_file(ifstream &fin)
{
    return;
}

void random_agent::write_file(ofstream &fout)
{
    return;
}
void random_agent::read_file(ifstream &fin)
{
    return;
}

void q_agent::write_file(ofstream &fout)
{
    fout << this->no_of_actions << " " << this->discount_factor << " " << this->learning_rate << " " << this->epsilon << " ";
    fout << q_values.size() << " ";
    for (auto d : q_values)
    {
        fout << d << " ";
    }
    return;
}
void q_agent::read_file(ifstream &fin)
{
    fin >> this->no_of_actions;
    fin >> this->discount_factor;
    fin >> this->learning_rate;
    fin >> this->epsilon;
    int vec_size;
    fin >> vec_size;
    for (int i = 0; i < vec_size; i++)
    {
        double temp;
        fin >> temp;
        q_values.push_back(temp);
    }
    last_state = -1;
    last_action = -1;
    boxes_diff = 0;
    return;
}

agent::~agent()
{
}