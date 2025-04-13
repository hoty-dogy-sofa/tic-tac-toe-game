#ifndef GAME_FWD_HPP_
#define GAME_FWD_HPP_

#include <iostream>

namespace tictactoe {
enum class OptionalPlayer { NOTHING, NOUGHT, CROSS };
enum class ResultOfTheMove { BADMOVE, WIN, FINISH, NOTHING };
enum class ResultOfParsing { BADINPUT, CHANGEVIEW, OK, FINISH };

struct Coordinates {
    int x = 0;
    int y = 0;
};
}  // namespace tictactoe

#endif
