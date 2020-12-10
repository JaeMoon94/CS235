
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Pathfinder.h"

int main()
{
    Pathfinder myPath;
    // myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Solvable1.txt");
    myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Solvable2.txt");
    // myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Solvable3.txt");
    // if(myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Invalid1.txt"))
    // if(myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Invalid3.txt"))
    // if(myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Invalid4.txt"))
    // if(myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Invalid5.txt"))
    // myPath.importMaze("/Users/seungjaemoon/CS235/Lab4-Maze/Mazes/Unsolvable1.txt");
    // // 
    // // 
    // // 
    // // 
    // int maze[5][5][5] =
    //         {
    //             {
    //                 1, 1, 0, 1, 0,
    //                 0, 0, 0, 1, 0,
    //                 1, 1, 1, 1, 0,
    //                 1, 0, 0, 0, 0,
    //                 1, 0, 0, 0, 0
    //             },

    //             {
    //                 0, 1, 0, 1, 0,
    //                 0, 0, 0, 0, 0,
    //                 0, 0, 0, 0, 0,
    //                 0, 0, 0, 0, 0,
    //                 1, 0, 0, 0, 0
    //             },

    //             {
    //                 0, 1, 0, 1, 0,
    //                 0, 1, 0, 0, 0,
    //                 0, 1, 1, 1, 0,
    //                 0, 0, 0, 0, 0,
    //                 1, 0, 0, 0, 0
    //             },

    //             {
    //                 0, 0, 0, 1, 0,
    //                 0, 0, 0, 0, 0,
    //                 0, 0, 0, 1, 0,
    //                 0, 0, 0, 0, 0,
    //                 1, 0, 0, 0, 0
    //             },

    //             {
    //                 0, 0, 0, 1, 0,
    //                 0, 0, 0, 1, 0,
    //                 0, 0, 0, 1, 0,
    //                 0, 0, 0, 0, 0,
    //                 1, 1, 1, 1, 1
    //             }
    //         };

    // if( myPath.isSolvable(0,0,0,maze))
    // {
    //     cout << "it Works!" << endl;
    // }
    // else
    // {
    //     cout <<"Not working" << endl;
    // }

    // myPath.createRandomMaze();


    cout << myPath.toString() << endl;
    myPath.solveMaze();



    return 0;
};