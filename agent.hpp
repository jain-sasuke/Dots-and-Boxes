#pragma once
#include "state.hpp"

class agent
{
public:
    virtual int get_move(int state_no, state st);
    virtual int get_move_trained(int state_no, state st);
    virtual void give_feedback(int feedback, state new_state);
    virtual void set(int rows, int columns, double discount_factor, double learning_rate, int epsilon);
    virtual void reset();
    virtual void set_boxes_diff(double boxes_diff);
    virtual void add_boxes_diff(double boxes_diff);
    virtual void write_file(ofstream &fout);
    virtual void read_file(ifstream &fin);
    virtual ~agent();
};

class simple_agent : public agent
{
public:
    int get_move(int state_no, state st);
    int get_move_trained(int state_no, state st);
    void give_feedback(int feedback, state new_state);
    void set(int rows, int columns, double discount_factor, double learning_rate, int epsilon);
    void reset();
    void set_boxes_diff(double boxes_diff);
    void add_boxes_diff(double boxes_diff);
    void write_file(ofstream &fout);
    void read_file(ifstream &fin);
};

class random_agent : public agent
{
public:
    int get_move(int state_no, state st);
    int get_move_trained(int state_no, state st);
    void give_feedback(int feedback, state new_state);
    void set(int rows, int columns, double discount_factor, double learning_rate, int epsilon);
    void reset();
    void set_boxes_diff(double boxes_diff);
    void add_boxes_diff(double boxes_diff);
    void write_file(ofstream &fout);
    void read_file(ifstream &fin);
};

class q_agent : public agent
{
    vector<double> q_values;
    int last_state;
    int last_action;
    int no_of_actions;
    double discount_factor;
    double learning_rate;
    double boxes_diff;
    int epsilon;

public:
    int get_move(int state_no, state st);
    int get_move_trained(int state_no, state st);
    void give_feedback(int feedback, state new_state);
    void set(int rows, int columns, double discount_factor, double learning_rate, int epsilon);
    void reset();
    void print_q_values();
    void set_boxes_diff(double boxes_diff);
    void add_boxes_diff(double boxes_diff);
    void write_file(ofstream &fout);
    void read_file(ifstream &fin);
};