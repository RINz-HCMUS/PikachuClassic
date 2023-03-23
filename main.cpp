#include "Board.h"
#include <iostream>


int main()
{
	int n = 5, m = 4;
	Board A(n,m,26);
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)	
			std::cout << char(A.getCell(i, j) + 'A') << " ";
		std::cout << "\n";	
	}
	std::cout << "\n";
	int x, y, _x, _y;
	std::cin >> _x >> _y >> x >> y;
	
	if (A.Board::canConnect(std::make_pair(_x, _y), std::make_pair(x, y)))
		std::cout << "ok";
	else
		std:: cout << "no";
	A.~Board();
}