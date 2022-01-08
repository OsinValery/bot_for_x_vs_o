
#include <iostream>
#include "game.hpp"

using namespace std;

void help()
{
    cout << "there is shown the full list with commands for this game:\n";
    cout << "1) help       - current help list\n";
    cout << "2) fill x,y   - it is your move. Fill field (x,y) with your figure\n";
    cout << "3) game size,who   - start new game with board size x size, who = 1,2\n";
    cout << "4) close      - exit programm\n";
    cout << "5) leave      - leave this game and start new";
    cout << "6) show       - show current board\n";
}

void print(string frase)
{
    cout << frase << "\n"
         << ">>> ";
}

int main()
{
    bool play = true;
    bool game_active = false;
    int player = 1;

    std::string command;
    auto game = Game(3);
    std::vector<int> empty = {};

    print("start game");
    while (play)
    {
        cin >> command;
        if (command == "close")
        {
            play = false;
        }
        else if (command == "help"){
            help();
            cout << ">>> ";
        }

        else if (command == "leave")
        {
            if (game_active)
            {
                game_active = false;
                print("");
            }
            else
            {
                print("you are not playing now!");
            }
        }

        else if (command == "show")
        {
            if (game_active)
                print(game.print());
            else
                print("you are not plaing now! ");
        }

        else if (command == "game")
        {
            int size = 3;
            int who = 1;
            cin >> size >> who;
            if (game_active)
                print("right now you are plaing!");
            else if (size <= 0)
                print("size should be > 0");
            else if (who <= 0 || who > 2)
                print("who should be in {1,2}");
            else
            {
                game = Game(size);
                player = who;
                game_active = true;
                if (player == 2)
                {
                    auto best = game.best_move(1);
                    game.fill(best[0], best[1], 1);
                }
                cout << game.print();
                print("your move");
            }
        }

        else if (command == "fill")
        {
            int x = 0;
            int y = 0;
            cin >> x >> y;
            int check = game.can_fill(x, y);
            if (!game_active)
                print("you do not playing now!");
            else if (check == 1)
                print("x,y out of range!!!");
            else if (check == 2)
                print("choose another field! ");
            else
            {
                game.fill(x, y, player);
                if (game.check_results() == player)
                {
                    cout << game.print();
                    print("you won!!");
                    game_active = false;
                }
                else
                {
                    auto bot_move = game.best_move(3 - player);
                    if (bot_move == empty)
                    {
                        cout << game.print();
                        print("draw!!");
                        game_active = false;
                    }
                    else
                    {
                        game.fill(bot_move[0], bot_move[1], 3 - player);
                        cout << game.print();
                        auto res = game.check_results();
                        if (res == 3 - player)
                        {
                            print("fail!!");
                            game_active = false;
                        }
                        else if (game.gen_moves().size() == 0)
                        {
                            print("draw!!!");
                            game_active = false;
                        }
                        else
                            print("your move");
                    }
                }
            }
        }

        else
        {
            print("write \"help\" for help");
        }
    }
    print("bye!");
    return 0;
}
