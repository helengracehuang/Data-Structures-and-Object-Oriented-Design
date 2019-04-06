//
//  History.cpp
//  Project 1
//
//  Created by Xin Huang on 1/10/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include <iostream>
#include "History.h"

using namespace std;

History::History(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols;
    for (int i = 1; i <= m_row; i++)   //Creates a grid of dots
    {
        for (int k = 1; k <= m_col; k++)
        {
            unconvertedFlatulans[i][k] = '.';
        }
    }
}

bool History::record(int r, int c)
// the function returns false if row r, column c is not within the City; otherwise, it returns true after recording what it needs to
{
    if ((r >= 0 && r <= m_row) && (c >= 0 && c <= m_col))
        //dot means 0, a letter character A through Y means 1 through 25 (A means 1, B means 2, etc.) and Z means 26 or more
    {
        if (unconvertedFlatulans[r][c] >= 'A' && unconvertedFlatulans[r][c] <= 'Y')
            unconvertedFlatulans[r][c] ++;
        else if (unconvertedFlatulans[r][c] == 'Z')
            ;
        else
            unconvertedFlatulans[r][c] = 'A';
        return true;
    }
    else
        return false;
}

void History::display() const
// clears the screen and displays the history grid as the posted programs do
// the only member function of the History class that may write to cout
{
    clearScreen();
    for (int r = 1; r <= m_row; r++)   //Creates a grid of dots
    {
        for (int c = 1; c <= m_col; c++)
        {
            cout << unconvertedFlatulans[r][c];
        }
        cout << endl;
    }
    cout << endl;
}
