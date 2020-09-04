#include "game.h"
#include "decision.h"
using namespace std;

void play_game(Game game);
void show_rules();

int main()
{
    cout << "----------------------TIC TAC TOE----------------------" << endl;
    cout << "              Developed by Taqmeel Zubeir              " << endl;
    cout << "-------------------------------------------------------" << endl;
    show_rules();
    cout << "-------------------------------------------------------" << endl;
    int player;
    cout << "Who is going first? (AI -> 0, HUMAN -> 1) :";
    cin >> player;
    Game game(player);
    play_game(game);
    return 0;
}

// Alternates the turn between players until the game ends
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
        move = alpha_beta(game);
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

void show_rules()
{
    cout << "How to play?" << endl;
    cout << "1. The objective of the game is get three of your marks in a row (vertically, horizontally, or diagonally)." << endl
         << "The first to do so wins." << endl;
    cout << "2. Each cell in the game board is denoted with a value as shown below. " << endl
         << "Enter the cell value to make your move while playing." << endl;
    cout << "0 | 1 | 2" << endl;
    cout << "--+---+--" << endl;
    cout << "3 | 4 | 5" << endl;
    cout << "--+---+--" << endl;
    cout << "6 | 7 | 8" << endl;
}