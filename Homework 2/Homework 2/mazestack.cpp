//
//  main.cpp
//  Homework 2
//
//  Created by Xin Huang on 2/1/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include <iostream>
#include <stack>

using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise
{
    stack<Coord> coordStack;
    coordStack.push(Coord(sr, sc));
    maze[sr][sc] = 'Y';
    
    while (!coordStack.empty())
    {
        int r = coordStack.top().r();
        int c = coordStack.top().c();
        if (r == er && c == ec)
            return true;
        coordStack.pop();
        
        if (maze[r][c+1] == '.')
        {
            coordStack.push(Coord(r, c+1));
            maze[r][c+1] = 'Y';
        }
        if (maze[r+1][c] == '.')
        {
            coordStack.push(Coord(r+1, c));
            maze[r+1][c] = 'Y';
        }
        if (maze[r][c-1] == '.')
        {
            coordStack.push(Coord(r, c-1));
            maze[r][c-1] = 'Y';
        }
        if (maze[r-1][c] == '.')
        {
            coordStack.push(Coord(r-1, c));
            maze[r-1][c] = 'Y';
        }
    }
    return false;
}

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

