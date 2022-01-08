#pragma once
#include <string>
#include <vector>

class Game
{
private:
    int line;
    std::vector<std::vector<int>> board;
    int estimate_move(std::vector<int> const &move, int player);

public:
    Game(int n);
    std::string print();
    void fill(int x, int y, int player);
    // 0 - can
    // 1 - x,y is out of board size
    // 2 - bourd[x][y] filled earlyer
    int can_fill(int x, int y);
    std::vector<int> best_move(int player);
    int check_results();
    std::vector<std::vector<int>> gen_moves();
};
