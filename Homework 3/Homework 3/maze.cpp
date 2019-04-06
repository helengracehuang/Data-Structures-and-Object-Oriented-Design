//
//  maze.cpp
//  Homework 3
//
//  Created by Xin Huang on 2/11/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//
/*
#include <iostream>
#include <string>

using namespace std;
*/
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    // Stopping condition:
    // If the start location is equal to the ending location, then we've solved the maze, so return true.
    if (sr == er && sc == ec)
        return true;               
    
    // Simplifying step:
    maze[sr][sc] = 'Y';             // mark visited
    
    if (maze[sr - 1][sc] == '.')    //unvisited to the NORTH
        if (pathExists(maze, nRows, nCols, sr - 1, sc, er, ec))
            return true;
    if (maze[sr][sc + 1] == '.')    //unvisited to the EAST
        if (pathExists(maze, nRows, nCols, sr, sc + 1, er, ec))
            return true;
    if (maze[sr + 1][sc] == '.')    //unvisited to the SOUTH
        if (pathExists(maze, nRows, nCols, sr + 1, sc, er, ec))
            return true;
    if (maze[sr][sc - 1] == '.')    //unvisited to the WEST
        if (pathExists(maze, nRows, nCols, sr, sc - 1, er, ec))
            return true;
    
    return false;                   //no solution
}

/*
int main()
{
    string maze[10] = {
        "XXXXXXXXXX",
        "X...X..X.X",
        "X..XX....X",
        "X.X.XXXX.X",
        "XXX......X",
        "X...X.XX.X",
        "X.X.X..X.X",
        "X.XXXX.X.X",
        "X..X...X.X",
        "XXXXXXXXXX"
    };
    
    if (pathExists(maze, 10,10, 4,3, 1,8))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
}
*/
