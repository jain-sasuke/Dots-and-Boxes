#include <bits/stdc++.h>
#include "state.hpp"

using namespace std;
void state_matrix::set(int rows, int columns)
{
    current_state = 0;
    if (rows < 2)
    {
        cout << "Insufficient row size. Aborting." << endl;
        return;
    }
    else if (columns < 2)
    {
        cout << "Insufficient column size. Aborting." << endl;
        return;
    }
    no_of_rows = rows;
    no_of_columns = columns;
    no_of_actions = (columns - 1) * (rows) + (rows - 1) * columns;
    no_of_states = pow(2, no_of_actions);
    states.resize(no_of_states);
    for (int i = 0; i < no_of_states; i++)
    {
        states[i].set(i, no_of_states, no_of_actions, no_of_rows, no_of_columns);
    }
}

void state_matrix::print()
{
    state cur = states[current_state];
    int gl_count = 0;
    for (int i = 0; i < no_of_rows; i++)
    {
        for (int j = 0; j < no_of_columns - 1; j++)
        {
            cout << ".";
            if (cur.actions[gl_count])
            {
                cout << "  ";
            }
            else
            {
                cout << "——";
            }
            gl_count++;
        }
        cout << "." << endl;
        if (i == no_of_rows - 1)
        {
            break;
        }
        for (int j = 0; j < no_of_columns; j++)
        {
            if (cur.actions[gl_count])
            {
                cout << " ";
            }
            else
            {
                cout << "|";
            }
            gl_count++;
            cout << "  ";
        }
        cout << endl;
    }
}

void state::set(int index, int no_of_states, int no_of_actions, int rows, int columns)
{
    no_of_valid_actions = no_of_actions;
    this->actions.resize(no_of_actions, 1);
    no_of_states /= 2;
    for (int i = no_of_actions - 1; i >= 0; i--)
    {
        if (no_of_states <= index)
        {
            no_of_valid_actions--;
            actions[i] = 0;
            index -= no_of_states;
        }
        no_of_states /= 2;
    }
    no_of_boxes = 0;
    int precal = columns * 2 - 1;
    for (int i = 0; i < rows - 1; i++)
    {
        int mul = i * precal;
        for (int j = 0; j < columns - 1; j++)
        {
            if ((!actions[mul + j]) && (!actions[mul + j + columns]) && (!actions[mul + j + columns - 1]) && (!actions[mul + j + precal]))
            {
                no_of_boxes++;
            }
        }
    }
}

void state_matrix::set_state(int state_no)
{
    current_state = state_no;
}

state state_matrix::get_state()
{
    return states[current_state];
}

bool state_matrix::is_over()
{
    if (current_state == (no_of_states - 1))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool state::is_valid_move(int move)
{
    if (move >= actions.size())
    {
        return false;
    }
    else if (move < 0)
    {
        return false;
    }
    else if (!actions[move])
    {
        return false;
    }
    return true;
}

void state_matrix::play_move(int move)
{
    current_state += pow(2, move);
}

int state_matrix::get_state_no()
{
    return current_state;
}
//array of states, each line has a value, add values to get array value