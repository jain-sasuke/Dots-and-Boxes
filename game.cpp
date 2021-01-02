#include "game.hpp"

void game::play(agent *ag)
{
    int player_points = 0;
    int agent_points = 0;
    int no_of_boxes = 0;
    while (!stm.is_over())
    {
        int move;
        stm.print();
        cout << "Enter your move: ";
        cin >> move;
        while (!stm.get_state().is_valid_move(move))
        {
            cout << "The move you entered was invalid. Try again: ";
            cin >> move;
        }
        no_of_boxes = stm.get_state().no_of_boxes;
        stm.play_move(move);
        player_points += stm.get_state().no_of_boxes - no_of_boxes;
        if (stm.is_over())
        {
            break;
        }
        stm.print();
        move = ag->get_move(stm.get_state_no(), stm.get_state());
        cout << "Agent's move: " << endl;
        no_of_boxes = stm.get_state().no_of_boxes;
        stm.play_move(move);
        agent_points += stm.get_state().no_of_boxes - no_of_boxes;
    }
    stm.print();
    if (agent_points > player_points)
    {
        cout << "The agent won.\n";
    }
    else
    {
        cout << "You won.\n";
    }
    cout << "Player points: " << player_points << endl;
    cout << "Agent points: " << agent_points << endl;
}

void game::play()
{
    int player_one_points = 0;
    int player_two_points = 0;
    int no_of_boxes = 0;
    int cur_player = 0;
    while (!stm.is_over())
    {
        int move;
        stm.print();
        if (cur_player == 0)
        {
            cout << "Player 1, Enter your move: ";
        }
        else
        {
            cout << "Player 2, Enter your move: ";
        }
        cin >> move;
        while (!stm.get_state().is_valid_move(move))
        {
            cout << "The move you entered was invalid. Try again: ";
            cin >> move;
        }
        no_of_boxes = stm.get_state().no_of_boxes;
        stm.play_move(move);
        if (cur_player == 0)
        {
            player_one_points += (stm.get_state().no_of_boxes - no_of_boxes);
            cur_player = 1;
        }
        else
        {
            player_two_points += (stm.get_state().no_of_boxes - no_of_boxes);
            cur_player = 0;
        }
    }
    stm.print();
    if (player_one_points > player_two_points)
    {
        cout << "Player one wins!" << endl;
    }
    else if (player_two_points > player_one_points)
    {
        cout << "Player two wins!" << endl;
    }
    else
    {
        cout << "Player one wins!" << endl;
    }
    cout << "Player one points: " << player_one_points << endl;
    cout << "Player two points: " << player_two_points << endl;
}

pair<int, int> game::train(agent *training_agent, agent *adversary)
{
    int training_agent_points = 0;
    int adversary_points = 0;
    int no_of_boxes = 0;
    //stm.set(3, 3);
    //int player = rand() % 2;
    int player = 0;
    int start = player;
    int move = 0;
    while (!stm.is_over())
    {
        //stm.print();
        //cout << "No of boxes: " << stm.get_state().no_of_boxes << endl;
        if (player == 0)
        {
            move = training_agent->get_move(stm.get_state_no(), stm.get_state());
            //cout << "Training agent's move: " << move << endl;
            no_of_boxes = stm.get_state().no_of_boxes;
            stm.play_move(move);
            training_agent_points += stm.get_state().no_of_boxes - no_of_boxes;
            //training_agent->give_feedback(stm.get_state().no_of_boxes - no_of_boxes, stm.get_state());
            training_agent->set_boxes_diff(stm.get_state().no_of_boxes - no_of_boxes);
            adversary->add_boxes_diff((-stm.get_state().no_of_boxes + no_of_boxes) / 2.0);
            player = 1;
        }
        else
        {
            move = adversary->get_move(stm.get_state_no(), stm.get_state());
            //cout << "Adversary agent's move: " << move << endl;
            no_of_boxes = stm.get_state().no_of_boxes;
            stm.play_move(move);
            adversary_points += stm.get_state().no_of_boxes - no_of_boxes;
            //adversary->give_feedback(stm.get_state().no_of_boxes - no_of_boxes, stm.get_state());
            adversary->set_boxes_diff(stm.get_state().no_of_boxes - no_of_boxes);
            training_agent->add_boxes_diff((-stm.get_state().no_of_boxes + no_of_boxes) / 2.0);
            player = 0;
        }
    }
    //stm.print();
    pair<int, int> ret;
    int feedback_adversary = 0;
    int feedback_training_agent = 0;
    if (adversary_points > training_agent_points)
    {
        feedback_adversary = 10;
        feedback_training_agent = -10;
        ret.first = 0;
        ret.second = 1;
    }
    else if (training_agent_points > adversary_points)
    {
        feedback_training_agent = 10;
        feedback_adversary = -10;
        ret.first = 1;
        ret.second = 0;
    }
    else if (start == 0)
    {
        feedback_training_agent = 10;
        feedback_adversary = -10;
        ret.first = 1;
        ret.second = 0;
    }
    else
    {
        feedback_adversary = 10;
        feedback_training_agent = -10;
        ret.first = 0;
        ret.second = 1;
    }
    training_agent->give_feedback(feedback_training_agent, stm.get_state());
    adversary->give_feedback(feedback_adversary, stm.get_state());
    return ret;
    //cout << "No of boxes: " << stm.get_state().no_of_boxes << endl;
    //cout << "Training agent points: " << training_agent_points << endl;
    //cout << "Adversary points: " << adversary_points << endl;
    //cout << "Game over." << endl;
}

void game::set(int rows, int columns)
{
    stm.set(rows, columns);
}

void game::reset()
{
    stm.set_state(0);
}

pair<int, int> game::test(agent *training_agent, agent *adversary)
{
    int training_agent_points = 0;
    int adversary_points = 0;
    int no_of_boxes = 0;
    //int player = rand() % 2;
    int player = 0;
    int start = player;
    int move = 0;
    while (!stm.is_over())
    {
        if (player == 0)
        {
            move = training_agent->get_move_trained(stm.get_state_no(), stm.get_state());
            no_of_boxes = stm.get_state().no_of_boxes;
            stm.play_move(move);
            training_agent_points += stm.get_state().no_of_boxes - no_of_boxes;
            player = 1;
        }
        else
        {
            move = adversary->get_move_trained(stm.get_state_no(), stm.get_state());
            no_of_boxes = stm.get_state().no_of_boxes;
            stm.play_move(move);
            adversary_points += stm.get_state().no_of_boxes - no_of_boxes;
            player = 0;
        }
    }
    pair<int, int> ret;

    if (adversary_points > training_agent_points)
    {
        ret.first = 0;
        ret.second = 1;
    }
    else if (training_agent_points > adversary_points)
    {
        ret.first = 1;
        ret.second = 0;
    }
    else if (start == 0)
    {
        ret.first = 1;
        ret.second = 0;
    }
    else
    {
        ret.first = 0;
        ret.second = 1;
    }
    return ret;
}

vector<int> game::train_stats(agent *training_agent, agent *adversary)
{
    vector<int> wins;
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
        {
            training_agent->reset();
            adversary->reset();
            this->train(training_agent, adversary);
            this->reset();
        }
        int local_wins = 0;
        for (int k = 0; k < 100; k++)
        {
            training_agent->reset();
            adversary->reset();
            auto p = this->test(training_agent, adversary);
            local_wins += p.first;
            this->reset();
        }
        wins.push_back(local_wins);
    }
    return wins;
}