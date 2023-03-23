#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

const int ROW = 5;
const int COL = 4;

void gotoxy(int x, int y)
{
  static HANDLE h = NULL;  
  if(!h)
    h = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD c = { x, y };  
  SetConsoleCursorPosition(h,c);
}

void drawCells(char a, int y, int x)// đưa vào kí tự a, đưa vào hàng i (y), cột j (x)
{
	int nRow = 5, mCol = 11; 
	for (int i = 1; i <= nRow; i++) // hàng -> y
	{
		for (int j = 1; j <= mCol; j++)// cột -> x
		{
			if ((i == (nRow/2+1)) && (j == (mCol/2+1)))
			{
				gotoxy(x*mCol+j , y*nRow+i);// đi tới ô (x*mCol+j, y*nRow+i)
				cout << a;
			}
			else if ((i == 1 || i == nRow) && (1 < j) && (j < mCol))
			{
				gotoxy(x*mCol+j , y*nRow+i );
				cout << "-";
			}
			else if ((j == 1 || j == mCol) && (1 < i) && (i < nRow))
			{
				gotoxy(x*mCol+j , y*nRow+i );
				cout << "|";
			}
		}
	}
}

int main()
{
	srand(time(0));
	char board[ROW][COL];
	for (int i = 0; i < ROW; i++)
		for (int j = 0; j < COL; j++)
			board[i][j] = rand() % 26 + 'A';
	
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)	
			drawCells(board[i][j], i, j);
	}
	cout << "\n\n";
	for (int i = 0; i < ROW; i++)
	{
		for (int j = 0; j < COL; j++)	
			cout << board[i][j] << " ";
		cout << "\n";	
	}			
}