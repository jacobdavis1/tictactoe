#include <iostream>
#include <random>
#include <functional>

using namespace std;

/*
    Description:
    This program runs a tic-tac-toe game against a
    computer-controlled player that wants to lose.
    In other words, it will:
      a) avoid winning by not completing a set of 3
      b) never prevent a completion of the set by the player
    NOTE: first version picks a random free space.

    Usage:
    Moves are given as coordinates, which start from 0 and go
    to 2 for both x and y. 0 0 would give the top-left corner.
    If there is a set of 3 in a row, column, or diagonal,
    the game stops immediately and the winner declared. A
    draw is called if all spaces are filled.
*/

default_random_engine e;
uniform_int_distribution<int> d(0, 2);
auto randSpace = bind(d, e);

class Board
{
public:
    Board() { resetBoard(); };
    ~Board() { };

    void printBoard();
    void resetBoard();
    bool positionEmpty(int x, int y); // returns true if space is unused
    int checkWin(); // returns 0 for no win, 1 for player win, 2 for ai win
    void setPosition(int x, int y, int player); // sets position as owned by given player, does nothing if position taken

private:
    int positions[3][3];
};

class AIPlayer
{
public:
    AIPlayer(Board& nboard) : board(nboard) { };

    void makeMove();

    Board& board;
};

int main()
{
    int currentPlayer = 1;
    Board board;
    AIPlayer aiPlayer(board);

    while(true)
    {
        board.printBoard();

        if (currentPlayer == 1)
        {
            int x, y;
            cout << "Input move: ";
            cin >> x >> y;
            board.setPosition(x, y, 1);
            currentPlayer = 2;
        }
        else
        {
            aiPlayer.makeMove();
            currentPlayer = 1;
        }

        if (board.checkWin() > 0)
        {
            cout << "Player " << board.checkWin() << " wins! Resetting." << endl;
            board.resetBoard();
        }
    }
}

void Board::printBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            cout << " " << positions[j][i];
        }

        cout << endl;
    }
}

void Board::resetBoard()
{
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            positions[j][i] = 0;
        }
    }
}

bool Board::positionEmpty(int x, int y)
{
    if (positions[x][y] == 0)
        return true;
    else return false;
}

void Board::setPosition(int x, int y, int player)
{
    if (positionEmpty(x, y))
        positions[x][y] = player;
}

int Board::checkWin()
{
    // Check top-left, middle, and bottom-right for 3-sets

    // Top-left: - \ |
    if (positions[0][0] > 0)
    {
        if ( ( (positions[0][0] == positions[1][0]) && (positions[0][0] == positions[2][0]) )
            || ( (positions[0][0] == positions[1][1]) && (positions[0][0] == positions[2][2]) )
            || ( (positions[0][0] == positions[0][1]) && (positions[0][0] == positions[0][2]) ) )
                return positions[0][0];
    }

    // Middle: | - /
    if (positions[1][1] > 0)
    {
        if ( ( (positions[1][0] == positions[1][1]) && (positions[1][1] == positions[1][2]) )
            || ( (positions[0][1] == positions[1][1]) && (positions[1][1] == positions[2][1]) )
            || ( (positions[0][2] == positions[1][1]) && (positions[2][0] == positions[1][1])) )
                return positions[1][1];
    }

    // Bottom right: | -
    if (positions[2][2] > 0)
    {
        if ( ( (positions[2][0] == positions[2][2]) && (positions[2][1] == positions[2][2]) )
            || ( (positions[0][2] == positions[2][2]) && (positions[1][2] == positions[2][2]) ) )
                return positions[2][2];
    }

    return 0;
}

void AIPlayer::makeMove()
{
    int tx = randSpace(), ty = randSpace();

    while (!board.positionEmpty(tx, ty))
    {
        tx = randSpace();
        ty = randSpace();
    }

    board.setPosition(tx, ty, 2);
}
