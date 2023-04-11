#include "Board.h"

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
	return;
}


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

	// nếu số ký tự mỗi loại
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
	
	// random vị trí của bảng nếu vị trí đó chưa được chọn thì gán giá trị mới cho nó 
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
	// Xét từng cặp 2 ô trong bảng xem có thể nối với nhau được không sau đó gán vào start và end
    std::vector<std::pair<int,int> > Path; 
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_column; j++)
		{
			start = {i, j};
			if (_board[i][j] == -1)
				continue;
			else
			{
				for (int ii = 0; ii < n_row; ii++)
				{
					for (int jj = 0; jj < n_column; jj++)
					{
						end = {ii, jj};
						if (start == end) continue;
						
						if (Board::canConnect(start, end, Path))
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


// Hàm kiểm tra logic game
bool Board::canConnect(std::pair<int,int> start, std::pair<int,int> end, std::vector<std::pair<int,int> > &path)
{
	if (start == end) return false;
	if (_board[start.first][start.second] != _board[end.first][end.second])
		return false;

    path = Board::findPath(start, end);
	// do hàm path trả về các ô tại những lần đổi hướng và 2 đầu mút
	// do đó nếu số lượng của path là 2, 3, 4 thì 2 ô nối với nhau hợp lệ
	if (2 <= path.size() && path.size() <= 4) return true; 
	return false;
}

std::vector<std::pair<int,int>> Board::findPath(std::pair<int,int> start, std::pair<int,int> end)
{
	// thảm khảo từ nguồn "https://codelearn.io/sharing/huong-dan-lam-game-bang-cocos2d-x-phan-2"

	// nâng tọa độ của start và end lên 1 do trong bảng mới các vị trí của mảng cũ tăng 1
	start.first += 1;
	start.second += 1;
	end.first += 1;
	end.second += 1;
	
	// khởi tạo mảng bao lên extra_board[n_row+2][n_column+2]
	int **extra_board = new int*[n_row + 2];
	for (int i = 0; i < n_row + 2; i++)
		extra_board[i] = new int [n_column + 2];
	for (int i = 0; i < n_row + 2; i++)
		for (int j = 0; j < n_column + 2;j++)	
			extra_board[i][j] = -1;
	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_column;j++)
		{
			if (_board[i][j] != -1)
				extra_board[i+1][j+1] = _board[i][j];
		}
		
	// BFS
	// 2 mảng const thể hiện 4 hướng di chuyển trên bảng
	const int dx[4] = {-1, 0, 1, 0};
	const int dy[4] = {0, 1, 0, -1};
	


	// khởi tạo mảng backtrack đường đi
	std::pair<int,int> **trace = new std::pair<int,int> *[n_row + 2];
	for (int i = 0; i < n_row + 2; i++)
		trace[i] = new std::pair<int,int> [n_column + 2];
	for (int i = 0; i < n_row + 2; i++)
		for (int j = 0; j < n_column + 2;j++)
			trace[i][j] = {-1, -1};
			
	// Đặt giá trị ban đầu của start = {-2,-2} để đánh dấu vị trí bắt đầu tìm được đường đi khi quay ngược lại
	trace[start.first][start.second] = {-2, -2}; 

	// Cho 2 ô start và end có thể đi được
	extra_board[start.first][start.second] = -1;
	extra_board[end.first][end.second] = -1;

	std::deque<std::pair<int,int>> q;
	q.push_back(start);
	while(!q.empty())
	{
		std::pair<int,int> cur = q.front();
		q.pop_front();

		if (cur == end) break;// Nếu có đường đi tới ô end thì thoát vòng while

		for (int i = 0; i < 4; i++)
		{
			int nx = cur.first + dx[i];
			int ny = cur.second + dy[i];
			// nếu vị trí mới (nx, ny) nằm trong bảng extra_board và ô (nx, ny) có thể đi được thì lặp vòng while)
			while (0 <= nx && nx < n_row + 2 && 0 <= ny && ny < n_column + 2 && extra_board[nx][ny] == -1)
			{
				// nếu ô (nx, ny) chưa được đi tới thì tiếp tục
				if (trace[nx][ny].first == -1)
				{
					q.push_back({nx, ny});
					trace[nx][ny] = cur;
				}
				// tiếp tục đi tới theo cho tới khi không đi được nữa 
				nx += dx[i];
				ny += dy[i];
			}
		}
	}
	
	// Tìm đường đi
	std::pair<int,int> cur = end;
	std::vector<std::pair<int,int>> res;
	// nếu mà có đường đi tới end vì thực hiện
	if (trace[end.first][end.second].first != -1)
	{
		// thực hiện tới khi cur = start do start.first = -2;
		while (cur.first != -2) 
		{
			res.push_back({cur.first - 1, cur.second - 1});
			cur = trace[cur.first][cur.second];
		}
	}
	
	for (int i = 0; i < n_row + 2; i++)
	{
		delete [] extra_board[i];	
		delete [] trace[i];	
	}
	delete [] extra_board;
	delete [] trace;
	
	return res;
}

bool Board::checkBoard()
{	
	// kiểm tra từng cặp 2 ô xem nó có thể nối với nhau không 
	// nếu có thì trả về true
    std::vector<std::pair<int,int> > Path;
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
				for (int ii = 0; ii < n_row; ii++)
				{
					for (int jj = 0; jj < n_column; jj++)
					{
						end = {ii, jj};
						if (start == end) continue;
						if (Board::canConnect(start, end, Path))
							return true;
					}
				}
			}
		}
	}
	return false;
}


void Board::drawCells(int type, int y, int x, bool isVisible){
    if(type == -1)
        return;
	
	int textcolor = type % 16;
	if(!textcolor) textcolor++;

    int RowCell = 5, ColCell = 11; // kích thước ô

    for(int i = 0; i < RowCell; i++)
        for(int j = 0; j < ColCell; j++){
            if((i == 0 || i == RowCell - 1) && j != 0 && j != ColCell -1){
                SettingGame::gotoXY(x * ColCell + j + left, y * RowCell + i + top);
				putchar('-');
            }

            else if((j == 0 || j == ColCell - 1) && i != 0 && i != RowCell - 1){
                SettingGame::gotoXY(x * ColCell + j + left, y * RowCell + i + top);
				putchar('|');
            }
            else{
                SettingGame::gotoXY(x * ColCell + j + left, y * RowCell + i + top);
                putchar(' ');
            }
        }
    SettingGame::gotoXY(x * ColCell + ColCell / 2 + left, y * RowCell + RowCell / 2 + top);
    SettingGame::setColor(BLACK, textcolor);
	if (isVisible)
		putchar(type + 32);
	SettingGame::setColor(BLACK, WHITE);
    
}

void Board::drawBoard(bool isVisible){
        SettingGame::setColor(BLACK, WHITE);
        for(int i = 0; i < n_row; i++){
            for(int j = 0; j < n_column; j++)
                drawCells(_board[i][j], i, j, isVisible);
        }
}

void Board::drawLine(std::vector<std::pair<int,int>> path)
{
	int n = path.size();
	int RowCell = 5, ColCell = 11; // kích thước ô
	for (int i = 0; i < n - 1; i ++)
	{
		std::pair<int,int> start = path[i], end = path[i+1];
		if (start.first == end.first)
		{
			if (start.second > end.second)
				swap(start, end);
			int dis2Cell = (end.second - start.second) * ColCell;
			for (int j = 1; j < dis2Cell; j+=2)
			{
				SettingGame::gotoXY(left + start.second * ColCell + (ColCell/2) + j, top + start.first * RowCell + (RowCell/2));
				SettingGame::setColor(BLACK, RED);
				putchar('*');
			}
		}
		
		else
		{
			if (start.first > end.first)
				swap(start, end);
				int dis2Cell = (end.first - start.first) * RowCell;
			for (int j = 1; j < dis2Cell; j++)
			{
				SettingGame::gotoXY(left + start.second * ColCell + (ColCell/2), top + start.first * RowCell + (RowCell/2) + j);
				SettingGame::setColor(BLACK, RED);
				putchar('*');			
			}
		}
	}
	SettingGame::setColor(BLACK, WHITE);
}