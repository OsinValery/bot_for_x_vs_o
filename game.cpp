#include "game.hpp"
#include <string>

const std::vector<std::vector<int>> empty = {};

void Game::fill(int x, int y, int player)
{
    board[x][y] = player;
}

int Game::can_fill(int x, int y)
{
    if (x < 0 || y < 0)
        return 1;
    if (x >= line || y >= line)
        return 1;
    if (board[x][y] == 0)
        return 0;
    return 2;
}

Game::Game(int n)
{
    board = {};
    line = n;
    std::vector<int> digits = {};
    for (int i = 0; i < n; i++)
    {
        digits.push_back(0);
    }
    for (int i = 0; i < n; i++)
    {
        board.push_back(digits);
    }
};

std::string Game::print()
{
    std::string empty = ".";
    std::string first = "x";
    std::string second = "o";
    std::string result = "";
    for (int y = line - 1; y >= 0; y--)
    {
        for (int x = 0; x < line; x++)
        {
            switch (board[x][y])
            {
            case 0:
                result += empty;
                break;
            case 1:
                result += first;
                break;
            case 2:
                result += second;
                break;
            default:
                result += "?";
                break;
            }
        }
        result += "\n";
    }
    return result;
}

std::vector<std::vector<int>> Game::gen_moves()
{
    std::vector<std::vector<int>> potentional_moves = {};
    for (int x = 0; x < line; x++)
        for (int y = 0; y < line; y++)
            if (board[x][y] == 0)
                potentional_moves.push_back({x, y});
    return potentional_moves;
}

int Game::check_results()
{
    bool line_filed = true;
    int cur_player = board[0][0];
    for (int i = 0; i < line; i++)
    {
        if (board[i][i] != cur_player)
        {
            line_filed = false;
            break;
        }
    }
    if (line_filed && cur_player != 0)
        return cur_player;

    line_filed = true;
    cur_player = board[0][line - 1];
    for (int i = 0; i < line; i++)
        if (board[i][line - 1 - i] != cur_player)
        {
            line_filed = false;
            break;
        }
    if (line_filed && cur_player != 0)
        return cur_player;

    for (int x = 0; x < line; x++)
    {
        line_filed = true;
        cur_player = board[x][0];
        for (int y = 0; y < line; y++)
        {
            if (board[x][y] != cur_player)
            {
                line_filed = false;
            }
        }
        if (line_filed && cur_player != 0)
            return cur_player;
    }

    for (int y = 0; y < line; y++)
    {
        line_filed = true;
        cur_player = board[0][y];
        for (int x = 0; x < line; x++)
        {
            if (board[x][y] != cur_player)
            {
                line_filed = false;
            }
        }
        if (line_filed && cur_player != 0)
            return cur_player;
    }
    return 0;
}

std::vector<int> Game::best_move(int player)
{
    auto potentional_moves = gen_moves();
    long long points = -line * line;
    std::vector<int> best;
    for (auto move : potentional_moves)
    {
        long long val = estimate_move(move, player);
        if (val > points)
        {
            points = val;
            best = move;
        }
    }
    return best;
}

int Game::estimate_move(std::vector<int> const &move, int player)
{
    Game temp = *this;
    temp.fill(move[0], move[1], player);
    long long res = temp.check_results();
    if (res == player)
        return line * line;
    if (res != 0)
        return -line * line;
    long long worst = line * line;
    auto potentional_moves = gen_moves();

    if (potentional_moves == empty)
        return 0;
    for (auto move : potentional_moves)
    {
        res = -temp.estimate_move(move, 3 - player);
        if (res < worst)
            worst = res;
    }
    return worst;
}
