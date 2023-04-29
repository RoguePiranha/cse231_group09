#include <set>     // for STD::SET
#include <string>  // for STRING

class ChessBoard {
public:
    explicit ChessBoard(const std::string& initialBoardState);
    std::set<int> getPossibleMoves(int location) const;

private:
    bool isNotWhite(int row, int col) const;
    bool isWhite(int row, int col) const;
    bool isNotBlack(int row, int col) const;
    bool isBlack(int row, int col) const;

    const std::string board;
};

inline bool ChessBoard::isNotWhite(int row, int col) const
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return piece == ' ' || (piece >= 'A' && piece <= 'Z');
}

inline bool ChessBoard::isWhite(int row, int col) const
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return (piece >= 'a' && piece <= 'z');
}

inline bool ChessBoard::isNotBlack(int row, int col) const
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return piece == ' ' || (piece >= 'a' && piece <= 'z');
}

inline bool ChessBoard::isBlack(int row, int col) const
{
    if (row < 0 || row >= 8 || col < 0 || col >= 8)
        return false;
    char piece = board[row * 8 + col];

    return (piece >= 'A' && piece <= 'Z');
}

ChessBoard::ChessBoard(const std::string& initialBoardState) : board(initialBoardState)
{
}

std::set<int> ChessBoard::getPossibleMoves(int location) const
{
    std::set<int> possible;

    if (location < 0 || location >= 64 || board[location] == ' ')
        return possible;
    int row = location / 8;
    int col = location % 8;
    int r;
    int c;
    bool amBlack = isBlack(row, col);

    if (board[location] == 'P')
    {
        c = col;
        r = row - 2;
        if (row == 6 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);
        r = row - 1;
        if (r >= 0 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);
        c = col - 1;
        if (isWhite(r, c))
            possible.insert(r * 8 + c);
        c = col + 1;
        if (isWhite(r, c))
            possible.insert(r * 8 + c);
    }
    if (board[location] == 'p')
    {
        c = col;
        r = row + 2;
        if (row == 1 && board[r * 8 + c] == ' ')
            possible.insert(r * 8 + c);
        r = row + 1;
        if (r < 8 && board[r * 8 + c] == ' ')
            possible
