#include "game.hpp"
#include <vector>

namespace tictactoe {
bool Game::check_coordinates(int x, int y) {
    return (x >= 0 && x < HEIGHT_ && y >= 0 && y < WIDTH_)
               ? (board_[x][y] == OptionalPlayer::NOTHING)
               : false;
}

bool Game::has_winner(int x, int y) {
    int horizontal_line = 0;
    int vertical_line = 0;
    for (int i = 0; i < WIDTH_; i++) {
        horizontal_line =
            (board_[x][i] == current_player_) ? horizontal_line + 1 : 0;
        vertical_line =
            (board_[i][y] == current_player_) ? vertical_line + 1 : 0;
        if (horizontal_line == NUMBER_TO_WIN_ ||
            vertical_line == NUMBER_TO_WIN_) {
            return true;
        }
    }
    int left_diagonal = 0;
    int right_diagonal = 0;
    for (int dx = x - std::min(x, y), dy = y - std::min(x, y);
         dx < WIDTH_ && dy < HEIGHT_; dx++, dy++) {
        left_diagonal =
            (board_[dx][dy] == current_player_) ? left_diagonal + 1 : 0;
        if (left_diagonal == NUMBER_TO_WIN_) {
            return true;
        }
    }
    for (int dx = x - WIDTH_, dy = y + HEIGHT_; dx < WIDTH_ && dy >= 0;
         dx++, dy--) {
        if (dx >= 0 && dy < HEIGHT_) {
            right_diagonal =
                (board_[dx][dy] == current_player_) ? right_diagonal + 1 : 0;
        }
        if (right_diagonal == NUMBER_TO_WIN_) {
            return true;
        }
    }
    return false;
}

ResultOfTheMove Game::make_move(int x, int y) {
    if (!check_coordinates(x, y)) {
        return ResultOfTheMove::BADMOVE;
    }
    board_[x][y] = current_player_;
    remaining_cells_--;
    if (has_winner(x, y)) {
        return ResultOfTheMove::WIN;
    }
    if (remaining_cells_ == 0) {
        return ResultOfTheMove::FINISH;
    }
    current_player_ = (current_player_ == OptionalPlayer::NOUGHT)
                          ? OptionalPlayer::CROSS
                          : OptionalPlayer::NOUGHT;
    return ResultOfTheMove::NOTHING;
}

}  // namespace tictactoe
