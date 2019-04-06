//
//  History.h
//  Project 1
//
//  Created by Xin Huang on 1/10/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_row;
    int m_col;
    char unconvertedFlatulans[MAXROWS][MAXCOLS];
};

#endif /* History_h */
