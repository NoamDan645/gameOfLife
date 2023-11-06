

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef void (*func)(int **board, int row, int col);

func lut[2][9];


int **BoardCreate(int row, int col);
void initLut();
void GetRandom(int **board, int n, int m);
void TurnOn(int **board, int row, int col);
void TurnOff(int **board, int row, int col);
void SwapBoards(int ***board_a, int ***board_b);
void PrintBoard(int **board, int rows, int cols);
int IsAlive(int **board, int x, int y);
int CountNeb(int **board, int n, int m, int rows, int cols);
void Play(int **board_a, int **board_b, int n, int m);

int main(int argc, char **argv)
{
    int row = 2;
    int col = 4;

    int **board1 = BoardCreate(row, col);
    int **board2 = BoardCreate(row, col);

    initLut();

    GetRandom(board1, row, col);
    PrintBoard(board1, row, col);
     /*Play(board1, board2, row, col);
*/
    return 0;
}

int **BoardCreate(int row, int col)
{
    int i = 0;
    int **board = (int **)malloc(row * sizeof(int *));
    if (NULL == board)
    {
        return NULL;
    }
    for (i = 0; i < row; ++i)
    {
        board[i] = malloc(col * sizeof(int));
    }
    return board;
}

void initLut()
{
    lut[0][0] = TurnOff;
    lut[0][1] = TurnOff;
    lut[0][2] = TurnOff;
    lut[0][3] = TurnOn;
    lut[0][4] = TurnOff;
    lut[0][5] = TurnOff;
    lut[0][6] = TurnOff;
    lut[0][7] = TurnOff;
    lut[0][8] = TurnOff;

    lut[1][0] = TurnOff;
    lut[1][1] = TurnOff;
    lut[1][2] = TurnOn;
    lut[1][3] = TurnOn;
    lut[1][4] = TurnOff;
    lut[1][5] = TurnOff;
    lut[1][6] = TurnOff;
    lut[1][7] = TurnOff;
    lut[1][8] = TurnOff;
}

void SwapBoards(int ***board_a, int ***board_b)
{
    int **temp = NULL;

    temp = *board_a;
    *board_a = *board_b;
    *board_b = temp;
}
void TurnOn(int **board, int row, int col)
{
    board[row][col] = 1;
}
void TurnOff(int **board, int row, int col)
{
    board[row][col] = 0;
}
void GetRandom(int **board, int n, int m)
{
    int i = 0, j = 0;

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; ++j)
        {
            board[i][j] = rand() % 2;
        }
    }
}

int IsAlive(int **board, int x, int y)
{
    return board[x][y];
}

void PrintBoard(int **board, int rows, int cols)
{
    int i = 0, j = 0;

    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < cols; ++j)
        {
            if (1 == IsAlive(board, i, j))
            {
                printf(" * ");
            }
        }
        printf("\n");
    }
}
int CountNeb(int **board, int n, int m, int rows, int cols)
{
    int counter = 0;

    counter += board[(rows - 1 + n) % (n)][(cols - 1 + m) % m];
    counter += board[(rows - 1 + n) % (n)][(cols + m) % m];
    counter += board[(rows - 1 + n) % (n)][(cols + 1 + m) % m];

    counter += board[(rows + n) % (n)][(cols - 1 + m) % m];
    counter += board[(rows + n) % (n)][(cols + 1 + m) % m];

    counter += board[(rows + 1 + n) % (n)][(cols - 1 + m) % m];
    counter += board[(rows + 1 + n) % (n)][(cols + m) % m];
    counter += board[(rows + 1 + n) % (n)][(cols + 1 + m) % m];

    return counter;
}

void Play(int **boardIn, int **boardOut, int row, int col)
{
    int i = 0, j = 0;

    while (1)
    {

        PrintBoard(boardIn, row, col);

        for (i = 0; i < row; ++i)
        {
            for (j = 0; j < col; ++j)
            {
                int count = CountNeb(boardIn, row, col, i, j);
                lut[IsAlive(boardIn, i, j)][count](boardOut, i, j);
            }
            PrintBoard(boardIn, row, col);
        }

        SwapBoards(&boardIn, &boardOut);
        sleep(2);
    }
}
