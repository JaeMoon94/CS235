#ifndef PATHFINDER_H
#define PATHFINDER_H

#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include <algorithm> 

#include "PathfinderInterface.h"

using namespace std;

class Pathfinder: public PathfinderInterface
{

	protected:
	const int BACKGROUND = 1;
	const int WALL = 0;
	const int TEMPORARY = 2; // Used to show this path has been explored
	const int PATH = 3;
	const int ROW_SIZE = 5;
	const int COL_SIZE = 5;
	const int MAZE_SIZE = 5;
	

	// int myMaze[MAZE_SIZE][ROW_SIZE][COL_SIZE]; 
	

	private:
		vector <int> saveInt;
		int myMaze [5][5][5]; // To hold values
		int cloneMaze[5][5][5];
		vector<string> solution;
	

    public:
	// Implement
		Pathfinder() {
			initalizeMaze();
			
		}
		virtual ~Pathfinder() {}



    //Part 1-----------------------------------------------------------------------------------
	/*
	* toString
	*
	* Returns a string representation of the current maze. Returns a maze of all 1s if no maze
	* has yet been generated or imported.
	*
	* A valid string representation of a maze consists only of 125 1s and 0s (each separated
	* by spaces) arranged in five 5x5 grids (each separated by newlines) with no trailing newline. A valid maze must
	* also have 1s in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).
	*
	* Cell (0, 0, 0) is represented by the first number in the string representation of the
	* maze. Increasing in x means moving toward the east, meaning cell (1, 0, 0) is the second
	* number. Increasing in y means moving toward the south, meaning cell (0, 1, 0) is the
	* sixth number. Increasing in z means moving downward to a new grid, meaning cell
	* (0, 0, 1) is the twenty-sixth cell in the maze. Cell (4, 4, 4) is represented by the last number.
	*
	* Returns:		string
	*				A single string representing the current maze
	*/
	string toString() const
	{
		stringstream ss;
		for(int size = 0; size < MAZE_SIZE; size++)
		{
			for(int row = 0; row < ROW_SIZE; row++)
			{
				for (int col = 0; col < COL_SIZE; col++)
				{
					ss << myMaze[size][row][col];
					if(col < COL_SIZE-1) ss << " ";
				}
				ss << endl;
			}
			if(size < MAZE_SIZE-1) ss << endl;
		}
		//use stringstream
		return ss.str();
	}


	/*
	* createRandomMaze
	*
	* Generates a random maze and stores it as the current maze.
	*
	* The generated maze must contain a roughly equal number of 1s and 0s and must have a 1
	* in the entrance cell (0, 0, 0) and in the exit cell (4, 4, 4).  The generated maze may be
	* solvable or unsolvable, and this method should be able to produce both kinds of mazes.
	*/
	void createRandomMaze()
	{
		for(int size = 0; size < MAZE_SIZE; size++)
		{
			for(int row = 0; row < ROW_SIZE; row++)
			{
				for(int col = 0; col < COL_SIZE; col++)
				{
					myMaze[size][row][col] = rand()%2;
				}
			}
		}
	}


	//Part 2-----------------------------------------------------------------------------------
	/*
	* importMaze
	*
	* Reads in a maze from a file with the given file name and stores it as the current maze.
	* Does nothing if the file does not exist or if the file's data does not represent a valid
	* maze.
	*
	* The file's contents must be of the format described above to be considered valid.
	*
	* Parameter:	file_name
	*				The name of the file containing a maze
	* Returns:		bool
	*				True if the maze is imported correctly; false otherwise
	*/
	bool importMaze(string file_name)
	{
		if(isValid(file_name))
		{
			resetMaze(myMaze);
			resetMaze(cloneMaze);
			int index = 0;
			for(int i = 0; i < MAZE_SIZE; i++)
			{
				for(int j = 0; j < ROW_SIZE; j++)
				{
					for(int k = 0; k < COL_SIZE; k++)
					{
						cout << saveInt.at(index);
						myMaze[i][j][k] = saveInt.at(index);
						cloneMaze[i][j][k] = saveInt.at(index);
						index++;
					}
				}
			}
			saveInt.clear();
			// toString();

			solution.clear();
			isSolvable(0,0,0, cloneMaze);
			return true;
			// if(isSolvable(0,0,0, cloneMaze)) 
			// {
			// 	cout << "VALID" << endl;
			// 	cout << "MAZE SOLVABLE " << endl;
			// 	return true;
			// }
			// else 
			// {
			// 	cout << "VALID" << endl;
			// 	cout << "MAZE NOT SOLVABLE " << endl;
			// 	return true;
			// }
			// cout << toString() << endl;
		}
		else
		{

			cout << "MAZE NOT VALID" << endl;
			return false;
		}
	}

	//Part 3-----------------------------------------------------------------------------------
	/*
	* solveMaze
	*
	* Attempts to solve the current maze and returns a solution if one is found.
	*
	* A solution to a maze is a list of coordinates for the path from the entrance to the exit
	* (or an empty vector if no solution is found). This list cannot contain duplicates, and
	* any two consecutive coordinates in the list can only differ by 1 for only one
	* coordinate. The entrance cell (0, 0, 0) and the exit cell (4, 4, 4) should be included
	* in the solution. Each string in the solution vector must be of the format "(x, y, z)",
	* where x, y, and z are the integer coordinates of a cell.
	*
	* Understand that most mazes will contain multiple solutions
	*
	* Returns:		vector<string>
	*				A solution to the current maze, or an empty vector if none exists
	*/
	vector<string> solveMaze()
	{
		reverse(solution.begin(),solution.end());
		for(auto s: solution)
		{
			cout << s << endl;
		}
		// reverse(solution.begin(),solution.end());
		return solution;
	}

	//Helper Method check wether maze is valid or not
	bool isSolvable(int z, int x, int y, int maze[5][5][5])
	{
		//baseCases
		// cout << z << ", " << x << ", " << y << endl; 
		// cout << "location: " << z <<", " << x <<", " << y << ": " << maze[z][x][y] << endl;
		if((z < 0) || (z > MAZE_SIZE-1) || (x < 0) || (x > ROW_SIZE-1) || (y < 0) || (y > COL_SIZE-1))
			return false;
		if(maze[y][x][z] != 1)
			return false;
		// if(maze[y][x][z] == 3)
		// 	return false;
		// if(maze[z][x][y] == 2)
		// 	return true;
		// if(maze[4][4][4] == 1)
		// {
		if(x == 4 && y == 4 && z== 4)
		{
			maze[y][x][z] = 3;
			string path = "(" + to_string(z) + ", " + to_string(x) + ", " + to_string(y) + ")";
			solution.push_back(path);
			return true;
		}
		// }
			

		// inductive step
		maze[y][x][z] = 3;
		bool right = isSolvable(z, x+1, y, maze);
		bool left = isSolvable(z, x-1, y, maze);
		bool up = isSolvable(z, x, y-1, maze);
		bool down = isSolvable(z, x, y+1, maze);
		bool sink = isSolvable(z+1, x, y, maze);
		bool hover = isSolvable(z-1, x, y, maze);

		if(right || left || up || down || sink || hover) 
		{
			string path = "(" + to_string(z) + ", " + to_string(x) + ", " + to_string(y) + ")";
			solution.push_back(path);
			return true;
		}

		return false;
	}

	//Another helper Method
	bool isValid(string fileName)
	{
		int countOnes = 0;
		int countZeros = 0;
		int value = 0;
		ifstream ifs;
		string line;
		ifs.open(fileName.c_str());
		if(ifs)
		{
			while(getline(ifs,line))
			{
				// cout << line << endl;
				stringstream ss(line);
				while(ss >> value) 
				{
					if(isalpha(value))
					{ 
						saveInt.clear();
						return false;
					}
					saveInt.push_back(value);
					if(value == 1) countOnes++;
					else if(value == 0) countZeros++;
				}
			}
			// cout << "Number of 1's: " << countOnes << endl;
			// cout << "Number of 0: " << countZeros << endl;
			if(saveInt.back() != 1) 
			{
				saveInt.clear();
				return false; 
			}
			if(countOnes + countZeros == 125) return true;
			else if(countOnes + countZeros != 125)
			{
				saveInt.clear();
				return false;
			} 
		}
		else
		{
			cout << "File not exist" << endl;
			return false;
		}
		ifs.close(); 
	}	

	void initalizeMaze()
	{
		for(int size = 0; size < MAZE_SIZE; size++)
		{
			for(int row = 0; row < ROW_SIZE; row++)
			{
				for(int col = 0; col < COL_SIZE; col++)
				{
					myMaze[size][row][col] = 1;
				}
			}
		}
			
	}

	void resetMaze(int maze[5][5][5])
	{
		for(int size = 0; size < MAZE_SIZE; size++)
		{
			for(int row = 0; row < ROW_SIZE; row++)
			{
				for(int col = 0; col < COL_SIZE; col++)
				{
					maze[size][row][col] = 0;
				}
			}
		}
	}
};




#endif