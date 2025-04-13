#ifndef VIEW_HPP_
#define VIEW_HPP_

#include <boost/config.hpp>
#include <string>
#include <unordered_map>
#include "game.hpp"
#include "game_fwd.hpp"

namespace tictactoe {

class BOOST_SYMBOL_VISIBLE View {
public:
    View() = default;

    View(const View &) = delete;
    View(View &&) = delete;
    View &operator=(const View &) = delete;
    View &operator=(View &&) = delete;

    virtual ~View() = default;

    virtual void print_board(Game &game) = 0;
    virtual std::pair<Coordinates, ResultOfParsing> parse_input(
        std::string input
    ) = 0;

    static void invitation(Game &game) {
        const OptionalPlayer current_player = game.get_current_player();
        if (current_player == OptionalPlayer::NOUGHT) {
            std::cout << "O move: ";
        } else {
            std::cout << "X move: ";
        }
    }
};

class CompactView : View {
public:
    void print_board(Game &game) override;
    std::pair<Coordinates, ResultOfParsing> parse_input(std::string input
    ) override;
};

class PrettyView : View {
public:
    static void print_wall_line(int length);
    static void print_cell_line(
        int length,
        const std::vector<OptionalPlayer> &board_line,
        bool is_upper
    );
    void print_board(Game &game) override;
    std::pair<Coordinates, ResultOfParsing> parse_input(std::string input
    ) override;
};

}  // namespace tictactoe
#endif
