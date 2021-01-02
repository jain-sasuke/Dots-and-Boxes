#pragma once
#include <bits/stdc++.h>

using namespace std;
class state
{
public:
    int no_of_valid_actions;
    int no_of_boxes;
    //int no_of_rows;
    //int no_of_columns;
    vector<int> actions;
    bool is_valid_move(int move);
    void set(int index, int no_of_states, int no_of_actions, int rows, int columns);
};

class state_matrix
{
    int no_of_rows;
    int no_of_columns;
    int no_of_states;
    int no_of_actions;
    vector<state> states;
    int current_state;

public:
    void set(int rows, int columns);
    void set_state(int state_no);
    int get_state_no();
    state get_state();
    void print();
    bool is_over();
    void play_move(int move);
};