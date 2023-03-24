#include "Board.h"


//////////////////////////////////////////////
// constructor và destructor

Board::Board(int _n_row, int _n_column, int _n_type)
{
	n_row = _n_row;
	n_column = _n_column;
	n_type = _n_type;
	
	_board = new int*[n_row];
	for (int i = 0; i < n_row; i++)
		_board[i] = new int [n_column];
	
	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_column; j++)
			Board::setCell(i, j, -1);
	
	Board::initBoard(n_row, n_column, n_type);
}

Board::~Board()
{
	for (int i = 0; i < n_row; i++)
		delete [] _board[i];
	delete [] _board;
}

//////////////////////////////////////////////
// Các hàm lấy giá trị

int Board::getnRow()
{
	return n_row;
}

int Board::getnCol()
{
	return n_column;
}

int Board::getCell(int _x, int _y)
{
	return _board[_x][_y];
}
//////////////////////////////////////////////
// Các hàm thực thi

void Board::removeCell(int _x, int _y)
{
	// Khi xóa bỏ 1 ô nào đó thì đặt giá trị ô đó là -1
	_board[_x][_y] = -1;
}

void Board::setCell(int _x, int _y, int type)
{
	// Gán giá trị cho 1 ô trong bảng là type (loại pokemon)
	_board[_x][_y] = type;
}

void Board::initBoard(int _n_row, int _n_column, int _n_type)
{
	// tham khảo từ PhVanMin "https://github.com/PhVanMin/Pikachuuu/blob/master/NormalMode.cpp"
	
	srand((unsigned int)time(NULL));
	int n_flag = _n_row *_n_column / 2;
	while (n_flag--)
	{
		int i, j, time = 2;
		int type = rand() % _n_type;
		while (time)
		{
			i = rand() % _n_row;
			j = rand() % _n_column;
			if (_board[i][j] == -1)
			{
				_board[i][j] = type;
				time--;
			}
		}
	}
}

void Board::suffleBoard()
{
	// Tạo ra mảng count đếm số phần tử mỗi loại
	int *count = new int [n_type];
	for (int i = 0; i < n_type; i++)
		count[i] = 0;	
	
	// Tạo ra mảng 2 chiều để xem ô (i,j) đã được chọn hay chưa
	int **mark = new int* [n_row];
	for (int i = 0; i < n_row; i++)
		mark[i] = new int[n_column];
	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_column; j++)
			mark[i][j] = 0;
	
	int type;
	
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_column; j++)
		{
			if (_board[i][j] != -1)
			{
				type = _board[i][j];
				count[type]++;				
			}

		}
	}

	int x, y;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < n_type; i++)
	{
		while (count[i] != 0)
		{
			x = rand() % n_row;
			y = rand() % n_column;
			if (_board[x][y] != -1 && mark[x][y] == 0)
			{
				mark[x][y] = 1;
				_board[x][y] = i;
				count[i]--;
			}
		}
	}
	delete [] count;
	for (int i = 0; i < n_row; i++)
		delete [] mark[i];
	delete [] mark;
}

void Board::suggestBoard(std::pair <int,int> &start, std::pair <int,int> &end)
{
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_column; j++)
		{
			start = {i, j};
			if (_board[i][j] == -1) 
				continue;
			else
			{
				for (int ii = i; ii < n_row; ii++)
				{
					for (int jj = j; jj < n_column; jj++)
					{
						end = {ii, jj};
						if (start == end) continue;
						if (Board::canConnect(start, end))
							return;
					}
				}
			}
		}
	}
	return;	
}

void Board::removeBoard_0(std::pair <int,int> start, std::pair <int,int> end)
{
	Board::removeCell(start.first, start.second);
	Board::removeCell(end.first, end.second);
}

void Board::removeBoard_1(std::pair <int,int> start, std::pair <int,int> end)
{
	
	Board::removeCell(start.first, start.second);
	Board::removeCell(end.first, end.second);
	
	if (start.first == end.first && start.second > end.second)
		std::swap(start, end);
	// thụt qua trái 
	for (int i = end.second; i < n_column - 1; i++)
		_board[end.first][i] = _board[end.first][i+1];
	_board[end.first][n_column-1] = -1;
	
	for (int i = start.second; i < n_column - 1; i++)
		_board[start.first][i] = _board[start.first][i+1];
	_board[start.first][n_column-1] = -1;		 
}

void Board::removeBoard_2(std::pair <int,int> start, std::pair <int,int> end)
{
	Board::removeCell(start.first, start.second);
	Board::removeCell(end.first, end.second);
	
	if (start.second == end.second && start.first > end.first)
		std::swap(start, end);
	// thụt lên trên
	for (int i = end.first; i < n_row - 1; i++)
		_board[i][end.second] = _board[i+1][end.second];
	_board[n_row-1][end.second] = -1;
	
	for (int i = start.first; i < n_row - 1; i++)
		_board[i][start.second] = _board[i+1][start.second];
	_board[n_row-1][start.second] = -1;
	
}

void Board::removeBoard_3(std::pair <int,int> start, std::pair <int,int> end)
{
	Board::removeCell(start.first, start.second);
	Board::removeCell(end.first, end.second);
	
	if (start.first == end.first && start.second > end.second)
		std::swap(start, end);
	
	//thụt phải
	for (int i = start.second; i >= 1; i--)
		_board[start.first][i] = _board[start.first][i-1];
	_board[start.first][0] = -1;

	for (int i = end.second; i >= 1; i--)
		_board[end.first][i] = _board[end.first][i-1];
	_board[end.first][0] = -1;	
	
}

void Board::removeBoard_4(std::pair <int,int> start, std::pair <int,int> end)
{
	Board::removeCell(start.first, start.second);
	Board::removeCell(end.first, end.second);
	
	// đi xuống 
	if (start.second == end.second && start.first > end.first)
		std::swap(start, end);
	
	for (int i = start.first; i >= 1; i--)
		_board[i][start.second] = _board[i-1][start.second];
	_board[0][start.second] = -1;

	for (int i = end.first; i >= 1; i--)
		_board[i][end.second] = _board[i-1][end.second];
	_board[0][end.second] = -1;	
}



//////////////////////////////////////////
// Hàm kiểm tra logic game

bool Board::canConnect(std::pair<int,int> start, std::pair<int,int> end)
{
	if (start == end) return false;
	if (_board[start.first][start.second] != _board[end.first][end.second]) 
		return false;
	
	std::vector<std::pair<int,int>> path = Board::findPath(start, end);
	
	if (2 <= path.size() && path.size() <= 4) return true;
	return false;
}

std::vector<std::pair<int,int>> Board::findPath(std::pair<int,int> start, std::pair<int,int> end)
{
	
	// thảm khảo từ nguồn "https://codelearn.io/sharing/huong-dan-lam-game-bang-cocos2d-x-phan-2"
	std::vector<std::vector<int>> extra_board(n_row + 2, std::vector<int>(n_column + 2, -1));
	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_column;j++)
		{
			if (_board[i][j] != -1)
				extra_board[i+1][j+1] = _board[i][j];
		}
	// BFS
	const int dx[4] = {-1, 0, 1, 0};
	const int dy[4] = {0, 1, 0, -1};
	std::deque<std::pair<int,int>> q;
	
	// nâng tọa độ của start và end lên 1
	start.first += 1; 
	start.second += 1;
	end.first += 1;
	end.second += 1;
	
	// khởi tạo mảng lưu đường đi
	std::vector<std::vector<std::pair<int,int>>> trace(n_row + 2, std::vector<std::pair<int,int>>(n_column + 2, std::make_pair(-1,-1)));
	trace[start.first][start.second] = {-2, -2};
	
	extra_board[start.first][start.second] = -1;
	extra_board[end.first][end.second] = -1;
	
	q.push_back(start);
	while(!q.empty())
	{
		std::pair<int,int> cur = q.front();
		q.pop_front();
		
		if (cur == end) break;
		
		for (int i = 0; i < 4; i++)
		{
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			while (0 <= nx && nx < n_row + 2 && 0 <= ny && ny < n_column + 2 && extra_board[nx][ny] == -1)
			{
				if (trace[nx][ny].first == -1)
				{
					q.push_back({nx, ny});	
					trace[nx][ny] = cur;				
				}
				nx += dx[i];
				ny += dy[i];				
			}
		}
	}
	// Tìm đường đi 
	
	std::pair<int,int> cur = end;
	std::vector<std::pair<int,int>> res;
	if (trace[end.first][end.second].first != -1)
	{
		while (cur.first != -2)
		{
			res.push_back(cur);
			cur = trace[cur.first][cur.second];
		}
	}
	return res;
}

bool Board::checkBoard()
{
	std::pair <int,int> start, end;
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_column; j++)
		{
			start = {i, j};
			if (_board[i][j] == -1) 
				continue;
			else
			{
				for (int ii = i; ii < n_row; ii++)
				{
					for (int jj = j; jj < n_column; jj++)
					{
						end = {ii, jj};
						if (start == end) continue;
						if (Board::canConnect(start, end))
							return true;
					}
				}
			}
		}
	}
	return false;
}
