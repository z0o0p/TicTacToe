#ifndef GAME_H
#define GAME_H
#include <bits/stdc++.h>

class Game
{
private:
    int player;
    std::vector<int> filled;

public:
    Game(int p)
    {
        player = p; // Denotes player id (AI -> 0, HUMAN -> 1)
        filled.resize(9);
        std::fill(filled.begin(), filled.end(), -1); // Game board is initialized with -1 to denote empty cell
    }

    // Returns the current player id
    int current_player()
    {
        return player;
    }

    // Returns possible legal moves
    std::vector<int> actions()
    {
        std::vector<int> a;
        for (int i = 0; i < filled.size(); i++)
            if (filled.at(i) == -1)
            {
                a.push_back(i);
            }
        return a;
    }

    // Returns a "Transistion Model" which defines the result of an action
    Game result(int action)
    {
        Game result_model(0);
        result_model.player = player;
        result_model.filled = filled;
        result_model.filled[action] = result_model.player;
        result_model.player ^= 1;
        return result_model;
    }

    // Terminal test, which returns true when the game is over or any when player has won
    bool reached_terminal()
    {
        if (count(filled.begin(), filled.end(), -1))
        {
            if (utility(player))
                return true;
            return false;
        }
        return true;
    }

    // Defines the score (WIN -> 1, LOSS -> -1, DRAW -> 0)
    int utility(int p)
    {
        if (win_situation(p))
            return 1;
        else if (win_situation(p ^ 1))
            return -1;
        else
            return 0;
    }

    // Determines whether the player has any winning combination in the game board
    bool win_situation(int p)
    {
        // TODO: Implement an intelligent approach here
        bool win_1 = (filled[0] == p && filled[1] == p && filled[2] == p);
        bool win_2 = (filled[3] == p && filled[4] == p && filled[5] == p);
        bool win_3 = (filled[6] == p && filled[7] == p && filled[8] == p);
        bool win_4 = (filled[0] == p && filled[3] == p && filled[6] == p);
        bool win_5 = (filled[1] == p && filled[4] == p && filled[7] == p);
        bool win_6 = (filled[2] == p && filled[5] == p && filled[8] == p);
        bool win_7 = (filled[0] == p && filled[4] == p && filled[8] == p);
        bool win_8 = (filled[2] == p && filled[4] == p && filled[6] == p);
        return (win_1 || win_2 || win_3 || win_4 || win_5 || win_6 || win_7 || win_8);
    }

    // Makes appropriate changes in the game board for the given action
    void move_player(int action)
    {
        filled[action] = player;
        player ^= 1;
    }

    // Determines the validity of the given action
    bool valid_action(int action)
    {
        return filled[action] == -1;
    }

    // Displays the game board onto the console
    void display_board()
    {
        int filled_index = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = filled_index; j < filled_index + 3; j++)
            {
                if (filled[j] == -1)
                {
                    std::cout << " ";
                }
                else if (filled[j] == 1)
                {
                    std::cout << "X";
                }
                else
                {
                    std::cout << "O";
                }
                if ((j + 1) % 3 != 0)
                {
                    std::cout << " | ";
                }
                else
                {
                    std::cout << std::endl;
                }
            }
            if (i != 2)
            {
                std::cout << "--+---+--" << std::endl;
            }
            filled_index += 3;
        }
        std::cout << std::endl;
    }
};

#endif