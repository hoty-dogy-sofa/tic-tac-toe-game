#ifdef _MSC_VER
#include <crtdbg.h>
#endif
#include <boost/dll/import.hpp>
#include <boost/version.hpp>
#include <game.hpp>
#include <game_fwd.hpp>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <view.hpp>

#if BOOST_VERSION >= 107600
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import_symbol
#else
// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define boost_dll_import_symbol ::boost::dll::import
#endif

int main(int argc, char *argv[]) {
#ifdef _MSC_VER
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDERR);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE | _CRTDBG_MODE_DEBUG);
    _CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDERR);
#endif
    if (argc == 2) {
        tictactoe::Game game;
        boost::shared_ptr<tictactoe::View> view = boost_dll_import_symbol<
            tictactoe::View>(
            // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic,-warnings-as-errors)
            argv[1], "plugin", boost::dll::load_mode::append_decorations
        );
        std::cout << "\n";
        view->print_board(game);
        view->invitation(game);
        while (true) {
            std::string input = {};
            if (!std::getline(std::cin, input)) {
                return 0;
            }
            const std::pair<tictactoe::Coordinates, tictactoe::ResultOfParsing>
                result = view->parse_input(input);
            switch (result.second) {
                case tictactoe::ResultOfParsing::BADINPUT:
                    std::cout << "Bad move!\n";
                    view->invitation(game);
                    break;
                case tictactoe::ResultOfParsing::CHANGEVIEW:
                    view = boost_dll_import_symbol<tictactoe::View>(
                        input, "plugin",
                        boost::dll::load_mode::append_decorations
                    );
                    view->print_board(game);
                    view->invitation(game);
                    break;
                case tictactoe::ResultOfParsing::FINISH:
                    return 0;
                case tictactoe::ResultOfParsing::OK:
                    const tictactoe::ResultOfTheMove result_of_move =
                        game.make_move(result.first.x, result.first.y);
                    switch (result_of_move) {
                        case tictactoe::ResultOfTheMove::BADMOVE:
                            std::cout << "Bad move!\n";
                            view->invitation(game);
                            break;
                        case tictactoe::ResultOfTheMove::NOTHING:
                            std::cout << "\n";
                            view->print_board(game);
                            view->invitation(game);
                            break;
                        case tictactoe::ResultOfTheMove::FINISH:
                            std::cout << "\n";
                            view->print_board(game);
                            std::cout << "Draw.\n";
                            return 0;
                        case tictactoe::ResultOfTheMove::WIN:
                            std::cout << "\n";
                            view->print_board(game);
                            if (game.get_current_player() ==
                                tictactoe::OptionalPlayer::CROSS) {
                                std::cout << "X wins!\n";
                            } else {
                                std::cout << "O wins!\n";
                            }
                            return 0;
                        default:
                            break;
                    }
            }
        }
    } else {
        return 0;
    }
}
