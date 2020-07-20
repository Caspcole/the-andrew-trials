/*
Must have a proper board
- 2d array
- 9x9 grid with 3x3 subdivisions (regions)

Must have the ability to fill in squares with numbers
- numbers can only appear once each row, collum, and region
- validate user input so I don't have to check at the end if everything is correct
	- 3 validation funtions:
	1. row
	2. collum
	3. region

Must automatically pass the user if user�s current solution is valid
- check to see if all elements contain numbers
- congratulate user if

One square cannot hold more than one number
User able to empty a selected square
- use an array of pointers, set to nullptr if user enters -1

*/
#include <iostream>
#include <vector>
using namespace std;

const int T_ROW = 9, T_COL = 9; // the total number of rows and collums

void display(const vector<vector<int> >& board)
{
	cout << "   ";
	for (int i = 0; i < board.size(); i++)
	{
		cout << i + 1 << " ";
	}
	cout << endl;
	
	for (int i = 0; i < board.size(); i++)
	{
		cout << i + 1 << ".|"; // number the rows
		for (int x = 0; x < board[i].size(); x++)
		{
			if (board[i][x] > 0)
			{
				cout << board[i][x] << "|";
			}
			else
			{
				cout << " |";
			}
			
		}
		cout << endl;
	}
}


void change(int row, int col, int new_num, vector<vector<int> >& board)
{
	if (new_num == -1)
	{
		board[row].erase(board[row].begin() + col);
		board[row].insert(board[row].begin() + col, new_num);
	}
	else
	{
		board[row][col] = new_num;
	}
}

bool chk_row(int row, int new_num, vector<vector<int> >& board)
{
	bool isValid = true;
	if (!(new_num == -1))
	{
		for (int i = 0; i < board.size(); i++)
		{
			if (new_num == board[row][i])
			{
				isValid = false;
			}
		}
	}
	return isValid;
}

bool chk_col(int col, int new_num, vector<vector<int> >& board)
{
	bool isValid = true;
	if (!(new_num == -1))
	{
		for (int i = 0; i < board.size(); i++)
		{
			if (new_num == board[i][col])
			{
				isValid = false;
			}
		}
	}
	return isValid;
}

/*
regions are 3x3 in the 9x9, 3 regions per row.
divide col and row by 3, if either is 9 then subtract 1
if(i == (row / 3))
*/

bool chk_region(int row, int col, int new_num, vector<vector<int> >& board)
{
	bool isValid = true;
	int row_region = row / 3;
	int col_region = col / 3;
	if (!(new_num == -1))
	{
		for (int i = 0; i < board.size(); i++)
		{
			if ((i / 3) == row_region)
			{
				for (int x = 0; x < board[i].size(); x++)
				{
					if ((x / 3) == col_region)
					{
						if (new_num == board[i][x])
						{
							isValid = false;
						}
					}
				}
			}
		}
	}
	return isValid;
}

bool chk_win(vector<vector<int> >& board)
{
	bool isWin = true;
	for (int i = 0; i < board.size(); i++)
	{
		for (int x = 0; x < board[i].size(); x++)
		{
			if (board[i][x] < 1)
			{
				isWin = false;
			}
		}
	}
	return isWin;
}

int main()
{
	// initializing 2d vectors: http://www.dcs.bbk.ac.uk/~roger/cpp/week13.htm
	vector<int> board_row(T_ROW);
	vector<vector<int> > board(T_COL,board_row);
	

	int input_row, 
		input_col,
		input_num;
	bool win = false;
	while (!win)
	{
		// Display the board at the beginning of each loop
		display(board);

		// get positional data from user and validate
		do
		{
			cout << "Please enter the row and collum (x y) you would like to edit (1-9): ";
			cin >> input_row >> input_col;
		} while ((((input_row < 1) || (input_row > 9)) || ((input_col < 1) || (input_col > 9))));

		// get new number from user and validate
		do
		{
			cout << "Please enter the new number (-1 for blank): ";
			cin >> input_num;
		}
		while ( !((input_num > 1) || (input_num < 9)) && !(input_num == -1) ); 

		// change number in the array
		bool valid_row = true,
			 valid_col = true,
			 valid_region = true;
		if (!chk_row(input_row - 1, input_num, board))
		{
			valid_row = false;
			cout << "\n Invalid row. \n";	
		}
		if (!chk_col(input_col - 1, input_num, board))
		{
			valid_col = false;
			cout << "\n Invalid col. \n";
		}
		if (!chk_region(input_row - 1, input_col - 1, input_num, board))
		{
			valid_region = false;
			cout << "\n Invalid region. \n";
		}
		if (valid_row && valid_col && valid_region)
		{
			change(input_row - 1, input_col - 1, input_num, board);
		}
		win = chk_win(board);
	}
	cout << "\n You win. Good job, kid.\n";

	return 0;
}