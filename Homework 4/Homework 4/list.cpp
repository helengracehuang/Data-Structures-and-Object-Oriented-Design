//
//  list.cpp
//  Homework 4
//
//  Created by Xin Huang on 3/4/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//


void listAll(const Class* c, string path)  // two-parameter overload
{
    cout << path << c->name() << endl;
    
    const vector<Class*> sc = c->subclasses();
    if (sc.empty())
        return;
    else
    {
        path += c->name() + "=>";
        for (vector<Class*>::const_iterator p = sc.begin(); p != sc.end(); p++)
            if (p != sc.end())
                listAll((*p), path);
    }
}

