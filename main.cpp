#include "Stack.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Cell
{
private:
	int x, y;
	bool walls[4]; // l,r,u,d

public:

	Cell() {
		x = -1;
		y = -1;
		for (int i = 0; i < 4; i++) {
			walls[i] = true;
		}
	}

	Cell(int x1, int y1)
	{
		x = x1;
		y = y1;
		
		for (int i = 0; i < 4; i++)
		{
			walls[i] = 1; // Initialize all walls to 1
		}
	}

	Cell& operator=(const Cell& other) {
		if (this != &other) {  // Check for self-assignment
			x = other.x;
			y = other.y;
			for (int i = 0; i < 4; i++) {
				walls[i] = other.walls[i];
			}
		}
		return *this;
	}


	const bool* getWalls() const {
		return walls;
	}


	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	void DestructWall(int dir)
	{
		if ((dir < 4) && (dir > -1))
		{
			walls[dir] = 0;
		}
	}

	int ChoseNeighbour(vector<vector<bool>> Matrix)
	{
		int Rows = Matrix.size();
		int Columns = Matrix[0].size();

		vector<int> AvailableCells;
		if (x > 0)
			if(!Matrix[x-1][y])
			AvailableCells.push_back(0); // left

		if (x < Rows - 1)
			if(!Matrix[x + 1][y])
			AvailableCells.push_back(1); // right

		if (y > 0)
			if(!Matrix[x][y - 1])
			AvailableCells.push_back(3); // down

		if (y < Columns - 1)
			if(!Matrix[x][y + 1])
			AvailableCells.push_back(2); // up

		int Size = AvailableCells.size();
		if (Size == 0)
		{
			return -1;
		}

		else
		{
			int dir = AvailableCells[rand() % Size];
			return dir;
		}
	}

	Cell NextCell(int dir)
	{
		if (dir == 0)
		{
			Cell Left(x - 1, y);
			return Left;
		}
		else if (dir == 1)
		{
			Cell Right(x + 1, y);
			return Right;
		}
		else if(dir == 2)
		{
			Cell Up(x, y + 1);
			return Up;
		}
		else if(dir == 3)
		{
			Cell Down(x, y - 1);
			return Down;
		}
	}

	void print()
	{
		cout << endl;
		cout << "x=" << x << " y=" << y;
		cout << " l=" << walls[0];
		cout << " r=" << walls[1];
		cout << " u=" << walls[2];
		cout << " d=" << walls[3];
		cout << endl;
	}

	void FilePrint(ofstream& File)
	{
		File << "x=" << x << " y=" << y;
		File << " l=" << walls[0];
		File << " r=" << walls[1];
		File << " u=" << walls[2];
		File << " d=" << walls[3];
		File << endl;
	}
};

//This Function get 1 maze and 2 cell parameters then destroy appropriate walls of given cells in Maze
void DestructWalls(Cell cell1, Cell cell2, vector<vector<Cell>>& Maze)
{
	if (cell1.getX() == cell2.getX())
	{
		if (cell1.getY() == cell2.getY() + 1)
		{
			//Cell2 is in Down direction
			Maze[cell1.getX()][cell1.getY()].DestructWall(3);
			Maze[cell2.getX()][cell2.getY()].DestructWall(2);
		}

		else if (cell1.getY() == cell2.getY() - 1)
		{
			//Cell2 is in Up direction
			Maze[cell1.getX()][cell1.getY()].DestructWall(2);
			Maze[cell2.getX()][cell2.getY()].DestructWall(3);
		}

	}

	else if (cell1.getY()== cell2.getY())
	{
		if (cell1.getX() == cell2.getX() + 1)
		{
			//Cell2 is in Left direction
			Maze[cell1.getX()][cell1.getY()].DestructWall(0);
			Maze[cell2.getX()][cell2.getY()].DestructWall(1);
		}

		else if (cell1.getX() == cell2.getX() - 1)
		{
			//Cell2 is in Right direction
			Maze[cell1.getX()][cell1.getY()].DestructWall(1);
			Maze[cell2.getX()][cell2.getY()].DestructWall(0);
		}
	}

}

int main()
{
	srand(time(0));

	//-------MAZE GENERATOR-------

	int Rows, Columns, NumMaze;

	cout << "Enter the number of mazes: " << endl;
	cin >> NumMaze;

	cout << "Enter the number of rows and columns (M and N): " << endl;
	cin >> Rows >> Columns;

	vector<vector<vector<Cell>>> Mazes; //All of the mazes are stored here

	for (int i = 0; i < NumMaze; i++)
	{
		vector<vector<Cell>> Maze(Columns, vector<Cell>(Rows)); // Maze is stored here 

		for (int i = 0; i < Columns; i++)
		{
			for (int j = 0; j < Rows; j++)
			{
				Maze[i][j] = Cell(i, j);
			}
		}
		Stack<Cell> TempStack; //Stack for pushing and poping cells inorderto generateMaze
		vector<vector<bool>> Matrix(Columns, vector<bool>(Rows, false));// matrix for checking cells visited or not

		Cell FirstCell(0, 0);
		TempStack.push(FirstCell);
		Matrix[0][0] = true;
		int VisitedCellCount = 1;

		while (VisitedCellCount < Rows * Columns)
		{
			Cell top = TempStack.top();
			int direction = top.ChoseNeighbour(Matrix);// chose the direction to advance

			if (direction != -1) //if there is available cell
			{
				
				Cell NextCell = top.NextCell(direction);
				DestructWalls(top, NextCell, Maze); // Destruct walls between top and NextCell and update Maze
				Matrix[NextCell.getX()][NextCell.getY()] = true; // Check previous cell (top) as visited in Matrix
				TempStack.push(NextCell);//Push NextCell into TempStack

				VisitedCellCount++;
			}
			else
			{
				TempStack.pop();
			}
		}

		Mazes.push_back(Maze);
	}

	cout << "All mazes are generated." << endl;

	for (int i = 0; i < Mazes.size(); i++)
	{
		ofstream MazeFile;
		string str = "maze_" + to_string(i + 1) + ".txt";
		MazeFile.open(str);
		MazeFile << Rows << " " << Columns << endl;
		for (int j = 0; j < Mazes[i].size(); j++)
		{
			for (int k = 0; k < Mazes[i][j].size(); k++)
			{
				Mazes[i][j][k].FilePrint(MazeFile);
			}

		}
	}

	//------PATH FINDER-------

	int MazeID;
	cout << "Enter a maze ID between 1 to " << NumMaze << " inclusive to find a path: " << endl;
	cin >> MazeID;

	int EntryX, EntryY;
	cout << "Enter x and y coordinates of the entry points (x,y) or (column,row): " << endl;
	cin >> EntryX >> EntryY;

	int ExitX, ExitY;
	cout << "Enter x and y coordinates of the exit points (x,y) or (column,row): " << endl;
	cin >> ExitX >> ExitY;

	Stack<Cell> Path;
	vector<vector<Cell>> ChosenMaze = Mazes[MazeID - 1];
	vector<vector<bool>> Matrix(ChosenMaze.size(), vector<bool>(ChosenMaze[0].size(), false));

	Cell StartCell = ChosenMaze[EntryX][EntryY];
	Matrix[EntryX][EntryY] = true;
	Path.push(StartCell);
	Cell top = Path.top();

	while ((top.getX() != ExitX) || (top.getY() != ExitY))
	{
		int direction = -1;
		const bool* cellWalls = top.getWalls();
		for (int i = 0; i < 4; i++)
		{
			if (!cellWalls[i]) //If not visited check if the cell has wall in that direction
			{
				if (!Matrix[top.NextCell(i).getX()][top.NextCell(i).getY()]) // Check if the cell in that direction is visited
				{
				direction = i; //If all conditions satisfied that direction is suitable for advancing
				break;
				}
			}
		}
		if (direction != -1)
		{
			int X = (top.NextCell(direction)).getX();
			int Y = (top.NextCell(direction)).getY();
			Matrix[X][Y] = true;
			Path.push(ChosenMaze[X][Y]);
		}
		else 
		{
			Path.pop();
		}
		top = Path.top();
	}

	ofstream PathFile;
	string str2 = "maze_" + to_string(MazeID) + "_path_" + to_string(EntryX) + "_" + to_string(EntryY)
		+ "_" + to_string(ExitX) + "_" + to_string(ExitY) + ".txt";
	PathFile.open(str2);
	
	while (!Path.isEmpty())
	{
		Path.topAndPop().FilePrint(PathFile);
	}

	return 0;
}

