//Author Yecheng Liang
#include <iostream>

using namespace std;

const int DIRECTION[8][2] = { {1, 0}, {0, 1}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, 1}, {-1, -1} };

//Ask user for a number
//Repeat until a vaild number greater than 0
int InputNumber(int min, int max) {
    int result = min -1;
    while (result < min || result > max) {
        cin >> result;
        if (cin.fail() || result < min || result > max) {
            cout << "Please enter a valid number!" << endl;
            std::cin.clear();
            std::cin.ignore(256, '\n');
        }
    }
    return result;
}

//wait and check for player input
void playerMove(int** board, int row, int column) {
    cout << "Player's Turn:" << endl;
    while (true) {
        int input = InputNumber(0, column - 1);
        for (int i = row - 1; i >= 0; i--) {
            if (board[i][input] == 0) {
                board[i][input] = 1;
                cout << "Setting:" << i << " " << input << endl;
                return;
            }
        }
        cout << "Please enter a valid Move!" << endl;
    }
}

//Gu
void AIMove() {
}

//Check wether we have a winner
bool CheckWin(int** board, int row, int column, int x, int y, int d, int step) {
    if (step >= 4) return true;
    int dx = x + DIRECTION[d][0];
    int dy = y + DIRECTION[d][1];
    if (dx >= 0 && dx < row && dy >= 0 && dy < column && board[dx][dy] == board[x][y])
        return CheckWin(board, row, column, dx, dy, d, step + 1);
    return false;
}

int CheckWin(int** board, int row, int column, int player) {
    for (int i = 0; i < row; i ++)
        for (int j = 0; j < column; j++) {
            if (board[i][j] == player) {
                for (int k = 0; k < 8; k++) {
                    if (CheckWin(board, row, column, i, j, k, 1))
                        return board[i][j];
                }
            }
        }
    return 0;
}


//number of digit
//Useful when there are more than 10 column
int NumberOfDigits(int number) {
    int i = 0;
    if (number == 0) return 1;
    while (number > 0) {
        number /= 10;
        i++;
    }
    return i;
}

void PrintBoard(int** board, int row, int column) {
    cout << endl;

    int length = 0;
    for (int i = 0; i < column; i++) {
        cout << i;
        for (int k = 0; k < (NumberOfDigits(column) - NumberOfDigits(i) + 1); k++) {
            length++;
            cout << " ";
        }
    }
    cout << endl;

    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << endl;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < column; j++) {
            cout << board[i][j];
            for (int k = 0; k < (NumberOfDigits(column)); k++)
                cout << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void ResetBoard(int** board, int row, int column) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            board[i][j] = 0;

}

int main()
{
    cout << "Push Four!" << endl;

    cout << "Please enter the number of Row:" << endl;
    int row = InputNumber(4, 20);

    cout << "Please enter the number of column:" << endl;
    int column = InputNumber(3, 20);


    int** board;
    board = new int*[row];
    for (int i = 0; i < row; i++)
        board[i] = new int[column];

    ResetBoard(board, row, column);

    bool gameOver = false;
    int winner = 0;
    
    while (!gameOver) {

        PrintBoard(board, row, column);
        playerMove(board, row, column);
        winner = CheckWin(board, row, column, 1);
        if (winner != 0) {
            gameOver = true;
            PrintBoard(board, row, column);
            cout << "Human Player Won" << endl;
        }

        if (!gameOver) {
            AIMove();
            winner = CheckWin(board, row, column, 2);
            if (winner != 0) {
                gameOver = true;
                PrintBoard(board, row, column);
                cout << "AI Player Won" << endl;
            }
        }

        if (gameOver) {
            cout << "Play Again? Y/N" << endl;
            while (true) {
                char input = ' ';
                cin >> input;
                if (input == 'y' || input == 'Y') {
                    ResetBoard(board, row, column);
                    gameOver = false;
                    break;
                }
                else if (input == 'n' || input == 'N'){
                    break;
                }
            }
        }
    }

    for (int i = 0; i < row; i++) {
        delete[] board[i];
        board[i] = NULL;
    }
    delete[] board;
    board = NULL;

    return 0;
}
