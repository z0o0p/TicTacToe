#include "game.h"
#include "decision.h"
using namespace std;

void play_game(Game game);

int main()
{
    Game game;
    cout << "----------------------TIC TAC TOE----------------------" << endl;
    cout << "              Developed by Taqmeel Zubeir              " << endl;
    cout << "-------------------------------------------------------" << endl;
    play_game(game);
    return 0;
}

void play_game(Game game)
{
    if (game.reached_terminal())
    {
        int result = game.utility(0);
        string message = (result == 1) ? "AI Wins. You Lose" : (result == 0) ? "Draw Match" : "Wait! What?";
        cout << "-------------------------------------------------------" << endl;
        cout << message << endl;
        cout << "-------------------------------------------------------" << endl;
        return;
    }
    int move;
    if (!game.current_player())
    {
        cout << "AI TURN" << endl;
        move = minimax(game);
    }
    else
    {
        cout << "HUMAN TURN" << endl;
    human_move:
        cout << "Available Moves -> ";
        auto a = game.actions();
        for (auto i = a.begin(); i != a.end(); i++)
            cout << *i << "/";
        cout << endl;
        cout << "Enter Your Move: ";
        cin >> move;
        if (!game.valid_action(move))
        {
            cout << "ERROR: Invalid Move" << endl;
            goto human_move;
        }
    }
    game.move_player(move);
    game.display_board();
    play_game(game);
}