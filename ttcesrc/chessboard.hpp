#include <string>

const std::string defaultFen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

class Chessboard {

    private:
        std::string inputFen;

    public:
        Chessboard(const std::string& fenString);

        float add(float arg1, float arg2);
};
