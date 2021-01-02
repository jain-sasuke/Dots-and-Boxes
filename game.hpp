#pragma once
#include "agent.hpp"
#include "state.hpp"

class game
{
    state_matrix stm;

public:
    void play(agent *ag);
    void play();
    pair<int, int> train(agent *training_agent, agent *adversary);
    void set(int rows, int columns);
    void reset();
    vector<int> train_stats(agent *training_agent, agent *adversary);

    pair<int, int> test(agent *training_agent, agent *adversary);
};