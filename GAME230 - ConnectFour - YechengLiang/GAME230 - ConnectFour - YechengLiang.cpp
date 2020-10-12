//Author Yecheng Liang
#include <iostream>

using namespace std;

void playerMove() {
    cout << "Player's Turn:" << endl;
    int input = -1;
    while (input == -1) {
        cin >> input;
    }
}

void AIMove() {
}

int NumberOfDigits(int number) {
    int i = 0;
    if (number == 0) return 1;
    while (number > 0) {
        number /= 10;
        i++;
    }
    return i;
}

void PrintBoard(int* board, int row, int column) {
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
            cout << board[i, j];
            for (int k = 0; k < (NumberOfDigits(column)); k++)
                cout << " ";
        }
        cout << endl;
    }

    cout << endl;
}

void ResetBoard(int* board, int row, int column) {
    for (int i = 0; i < row; i++)
        for (int j = 0; j < column; j++)
            board[i, j] = 0;

}

int main()
{
    cout << "Push Four!" << endl;

    cout << "Please enter the number of Row:" << endl;
    int row = 0;
    while (row == 0) {
        cin >> row;
        if (row == 0)
            cout << "The input isn't a number!" << endl;
    }

    cout << "Please enter the number of column:" << endl;
    int column = 0;
    while (column == 0) {
        cin >> column;
        if (column == 0)
            cout << "The input isn't a number!" << endl;
    }


    int* board;
    board = new int[row, column];
    ResetBoard(board, row, column);

    bool gameOver = false;
    
    while (!gameOver) {

        PrintBoard(board, row, column);
        playerMove();

        if (gameOver) {
            cout << "Play Again? Y/N" << endl;
            while (true) {
                char input = ' ';
                cin >> input;
                if (input == 'y' || input == 'Y') {
                    ResetBoard(board, row, column);
                    gameOver = true;
                    break;
                }
                else if (input == 'n' || input == 'N'){
                    break;
                }
            }
        }
    }

    delete [] board;
    board = NULL;
}
