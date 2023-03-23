#include "Board.h"


//////////////////////////////////////////////
// constructor và destructor

Board::Board(int _n_row, int _n_column, int n_type)
{
	n_row = _n_row;
	n_column = _n_column;
	
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

void Board::initBoard(int _n_row, int _n_column, int n_type)
{
	// tham khảo từ PhVanMin "https://github.com/PhVanMin/Pikachuuu/blob/master/NormalMode.cpp"
	
	srand((unsigned int)time(NULL));
	int n_flag = _n_row *_n_column / 2;
	while (n_flag--)
	{
		int i, j, time = 2;
		int type = rand() % n_type;
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
	std::vector<std::vector<int>> extra_board(n_row + 2, std::vector<int>(n_column + 2, 0));
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
	
	extra_board[start.first][start.second] = 0;
	extra_board[end.first][end.second] = 0;
	
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
			while (0 <= nx && nx < n_row + 2 && 0 <= ny && ny < n_column + 2 && extra_board[nx][ny] == 0)
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
