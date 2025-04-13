#ifndef GAME_HPP_
#define GAME_HPP_

#include <vector>
#include "game_fwd.hpp"

namespace tictactoe {

class Game {
public:
    Game() {
        board_.resize(
            HEIGHT_,
            std::vector<OptionalPlayer>(WIDTH_, OptionalPlayer::NOTHING)
        );
    }

    Game(const Game &) = delete;
    Game(Game &&) = delete;
    Game &operator=(const Game &) = delete;
    Game &operator=(Game &&) = delete;
    ~Game() = default;

    std::vector<std::vector<OptionalPlayer>> get_board() {
        return board_;
    }

    [[nodiscard]] int width() const {
        return WIDTH_;
    }

    [[nodiscard]] int height() const {
        return HEIGHT_;
    }

    OptionalPlayer get_current_player() {
        return current_player_;
    }

    bool check_coordinates(int x, int y);
    ResultOfTheMove make_move(int x, int y);
    bool has_winner(int x, int y);

private:
    std::vector<std::vector<OptionalPlayer>> board_ = {};
    OptionalPlayer current_player_ = OptionalPlayer::NOUGHT;
    int remaining_cells_ = 100;
    const int WIDTH_ = 10;
    const int HEIGHT_ = 10;
    const int NUMBER_TO_WIN_ = 5;
};

}  // namespace tictactoe
#endif
