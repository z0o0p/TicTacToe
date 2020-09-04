#ifndef DECISION_H
#define DECISION_H
#include "game.h"

int min_value(Game game, int alpha, int beta);
int max_value(Game game, int alpha, int beta);

// Makes a decision of best move among all posible moves
int alpha_beta(Game game)
{
    int decision;
    int maximum_score = std::numeric_limits<int>::min();
    int alpha = std::numeric_limits<int>::min();
    int beta = std::numeric_limits<int>::max();
    std::vector<int> actions = game.actions();
    for (auto i = actions.begin(); i != actions.end(); i++)
    {
        int m_val = min_value(game.result(*i), alpha, beta);
        alpha = std::max(alpha, m_val);
        if (m_val > maximum_score)
        {
            maximum_score = m_val;
            decision = *i;
        }
    }
    return decision;
}

// Minimizing function
int min_value(Game game, int alpha, int beta)
{
    if (game.reached_terminal())
        return game.utility(0);
    int v = std::numeric_limits<int>::max();
    auto actions = game.actions();
    for (auto i = actions.begin(); i != actions.end(); i++)
    {
        v = std::min(v, max_value(game.result(*i), alpha, beta));
        if (v <= alpha)
            return v;
        beta = std::min(beta, v);
    }
    return v;
}

// Maximizing function
int max_value(Game game, int alpha, int beta)
{
    if (game.reached_terminal())
        return game.utility(0);
    int v = std::numeric_limits<int>::min();
    auto actions = game.actions();
    for (auto i = actions.begin(); i != actions.end(); i++)
    {
        v = std::max(v, min_value(game.result(*i), alpha, beta));
        if (v >= beta)
            return v;
        alpha = std::max(alpha, v);
    }
    return v;
}

#endif