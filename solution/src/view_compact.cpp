#include <boost/algorithm/string.hpp>
#include <boost/config.hpp>
#include <boost/dll/alias.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "view.hpp"

namespace tictactoe {
std::pair<Coordinates, ResultOfParsing> CompactView::parse_input(
    // NOLINTNEXTLINE(-Werror=unused-parameter)
    std::string input
) {
    Coordinates game_step = {0, 0};
    if (input.find("view-") != std::string::npos) {
        return std::make_pair(game_step, ResultOfParsing::CHANGEVIEW);
    } else {
        std::vector<std::string> splited_data;
        std::vector<std::string> input_data;
        boost::split(
            splited_data, input, boost::is_any_of(" "), boost::token_compress_on
        );
        for (auto &part : splited_data) {
            if (part.find_first_not_of(" ") != std::string::npos) {
                input_data.push_back(std::move(part));
            }
        }
        if (input_data.size() != 2) {
            return std::make_pair(game_step, ResultOfParsing::BADINPUT);
        }
        try {
            game_step.x = stoi(input_data[0]);
            game_step.y = stoi(input_data[1]);
            if (game_step.x == -1 && game_step.y == -1) {
                return std::make_pair(game_step, ResultOfParsing::FINISH);
            }
            return std::make_pair(game_step, ResultOfParsing::OK);
        } catch (...) {
            return std::make_pair(game_step, ResultOfParsing::BADINPUT);
        }
    }
}

void CompactView::print_board(tictactoe::Game &game) {
    std::vector<std::vector<OptionalPlayer>> board = game.get_board();
    // NOLINTNEXTLINE(modernize-loop-convert,-warnings-as-errors)
    for (size_t i = 0; i < board.size(); i++) {
        for (size_t j = 0; j < board[i].size(); j++) {
            if (board[i][j] == OptionalPlayer::NOUGHT) {
#ifdef VIEW_COMPACT_USE_ZERO
                std::cout << "0";
#else
                std::cout << "O";
#endif
            } else {
                std::cout
                    << ((board[i][j] == OptionalPlayer::NOTHING) ? "." : "X");
            }
        }
        std::cout << "\n";
    }
}
}  // namespace tictactoe

// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,-warnings-as-errors)
extern "C" BOOST_SYMBOL_EXPORT tictactoe::CompactView plugin;
// NOLINTNEXTLINE(cppcoreguidelines-avoid-non-const-global-variables,-warnings-as-errors)
tictactoe::CompactView plugin;
