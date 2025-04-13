#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <iostream>
#include <string>
#include <vector>
#include "view.hpp"

namespace tictactoe {
std::pair<Coordinates, ResultOfParsing> PrettyView::parse_input(
    std::string input
) {
    Coordinates game_step = {0, 0};
    if (input.find("view-") != std::string::npos) {
        return std::make_pair(game_step, ResultOfParsing::CHANGEVIEW);
    } else {
        if (input.length() != 2) {
            return std::make_pair(game_step, ResultOfParsing::BADINPUT);
        }
        try {
            game_step.y = input[0] - 97;
            game_step.x = 9 - stoi(input.substr(1, 1));
            return std::make_pair(game_step, ResultOfParsing::OK);
        } catch (...) {
            return std::make_pair(game_step, ResultOfParsing::BADINPUT);
        }
    }
}

void PrettyView::print_wall_line(int length) {
    std::cout << "  ";
    for (int i = 0; i < length * 5 + 1; i++) {
        std::cout << ((i % 5 == 0) ? "+" : "-");
    }
    std::cout << "\n";
}

void PrettyView::print_cell_line(
    int length,
    const std::vector<OptionalPlayer> &board_line,
    bool is_upper
) {
    for (int i = 0; i < length; i++) {
        std::cout << "|";
        switch (board_line[i]) {
            case OptionalPlayer::NOTHING:
                std::cout << "    ";
                break;
            case OptionalPlayer::NOUGHT:
                std::cout << " @@ ";
                break;
            case OptionalPlayer::CROSS:
                std::cout << ((is_upper) ? " \\/ " : " /\\ ");
                break;
            default:
                break;
        }
    }
    std::cout << "|\n";
}

void PrettyView::print_board(tictactoe::Game &game) {
    std::vector<std::vector<OptionalPlayer>> board = game.get_board();
    // NOLINTNEXTLINE(modernize-loop-convert,-warnings-as-errors)
    for (int i = game.height() * 3; i >= 0; i--) {
        switch (i % 3) {
            case 0:
                print_wall_line(game.width());
                break;
            case 2:
                std::cout << i / 3 << " ";
                print_cell_line(game.width(), board[9 - i / 3], true);
                break;
            case 1:
                std::cout << "  ";
                print_cell_line(game.width(), board[9 - i / 3], false);
                break;
            default:
                break;
        }
    }
    std::cout << "  ";
    const char symbol = 'a';
    for (int i = 0; i < game.width() * 5 + 1; i++) {
        std::cout << ((i % 5 == 2) ? static_cast<char>(symbol + i / 5) : ' ');
    }
    std::cout << "\n";
}
}  // namespace tictactoe

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,-warnings-as-errors)
extern "C" BOOST_SYMBOL_EXPORT tictactoe::PrettyView plugin;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,-warnings-as-errors)
tictactoe::PrettyView plugin;
