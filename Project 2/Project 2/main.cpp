//
//  main.cpp
//  Project 2
//
//  Created by Xin Huang on 1/28/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "Map.h"
#include <cassert>
#include <iostream>

//These tests were performed on maps from strings to doubles
//These tested the main functions from Homework 1
//Default constructor, empty(), size(), insert(), update(), insertOrUpdate(), erase(), contains(), get(), and swap()

using namespace std;

int main()
{
    Map m;                //Default constructor
    assert(m.empty());        //test empty
    assert(!m.erase("lol"));    //test nothing to erase
    m.insert("A", 1.23);        //test inserting
    m.insert("B", 2.34);
    m.insert("C", 3.45);
    assert(m.size() == 3);    //test size
    KeyType k = "B";            //Setting values and keys
    ValueType v = 9.87;
    KeyType k1 = "D";
    ValueType v1 = 2.36;
    KeyType k2 = "A";
    ValueType v2 = 5.67;
    KeyType k3 = "B";
    ValueType v4 = 5.89;
    ValueType v3;
    KeyType key;
    ValueType val;
    assert(m.get(0, key, val) && key == "A" && val == 1.23);        //testing get
    assert(!m.get(-1, key, val) && key == "A" && val == 1.23);            //testing invalid i in get
    assert(m.contains("A") && m.contains("B") && !m.contains("D"));
    assert(m.update(k, v) && m.get(k, v3) && v3 == 9.87);                //testing update
    assert(!m.insert(k3, v4) && m.get(k3, v3) && v3 == 9.87);            //testing invalid insert
    assert(m.insertOrUpdate(k2, v2) && m.get(k2, v3) && v3 == 5.67);    //testing insertOrUpdate
    assert(m.size() == 3);
    assert(m.insertOrUpdate(k1, v1) && m.get(k1, v3) && v3 == 2.36);
    assert(m.size() == 4);
    assert(m.erase("C") && m.size() == 3);                                //testing erase
    assert(!m.get("C", v3));                                        //testing erase/invalid get
    assert(v3 == 2.36 && !m.contains("C"));
    
    std::cout << "Passed test group 1" << std::endl;

    //Testing swap
    Map m1;
    m1.insert("Z", 3.21);
    m1.insert("Y", 5.43);
    m.swap(m1);                //testing swap
    assert(m.contains("Z") && m.contains("Y"));
    assert(m1.contains("A") && m1.size() == 3);
    
    std::cout << "Passed test group swap" << std::endl;

    //Testing assignment operator and copy constructor
    ValueType vv;
    Map m2(m1);        //testing copy constructor
    assert(m2.contains("A") && m2.contains("B") && m2.get("B", vv) && vv == 9.87 && m2.size() == 3);
    Map m3;
    m3.insert("K", 1.23);
    m3 = m1;            //testing assignment operator
    assert(m3.contains("D") && m3.contains("B") && m3.get("D", vv) && vv == 2.36 && m3.size() == 3);
    assert(m3.erase("A") && m3.size() == 2);    //testing erasing head
    m3 = m2;                                    //testing assignment operator
    assert(m3.size() == 3);                                                               // FAIL!!!
    assert(m3.erase("B"));                      //testing erasing middle
    assert(!m3.contains("B"));
    m3 = m1;                                    //testing assignment operator
    assert(m3.erase("D") && m3.size() == 2);    //testing erasing tail
    
    std::cout << "Passed test group assignment operator and copy constructor" << std::endl;

    //testing combine and subtract and aliasing
    Map map;               // a 0, b 1, c 2, d 3, e 4
    map.insert("a", 0);
    map.insert("b", 1);
    map.insert("c", 2);
    map.insert("d", 3);
    map.insert("e", 4);
    Map map4(map);
    Map q(map);
    Map r(map);
    Map map1;             // d 3, e 6, f 7
    map1.insert("d", 3);
    map1.insert("e", 6);
    map1.insert("f", 7);
    Map w(map1);
    Map result;
    assert(!combine(map, map1, result) && result.size() == 5 && !result.contains("e") && result.contains("d"));    //testing combine
    assert(!combine(map, map1, map) && map.size() == 5 && !map.contains("e") && map.contains("d"));        //testing aliasing
    Map map2;
    map2.insert("h", 7);
    map2.insert("g", 8);
    assert(combine(map4, map2, result) && result.size() == 7 && !result.contains("f"));        //testing combine with true
    Map y;
    y.insert("a", 1);
    y.insert("b", 2);
    y.insert("c", 3);
    y.insert("d", 4);
    y.insert("e", 5);
    Map u;
    u.insert("a", 5);
    u.insert("b", 4);
    u.insert("c", 8);
    u.insert("d", 2);
    u.insert("e", 1);
    Map i;
    assert(!combine(y, u, i));    //checks if none are combined
    assert(i.empty());

    Map results;
    subtract(q, w, results);        //testing subtract
    assert(results.size() == 3 && results.contains("a") && !results.contains("d") && !results.contains("f"));
    subtract(q, w, q);            //testing aliasing
    assert(q.size() == 3 && q.contains("a") && !q.contains("d") && !q.contains("f"));
    Map g;
    g.insert("a", 1);
    g.insert("b", 2);
    g.insert("c", 3);
    g.insert("d", 4);
    g.insert("e", 5);
    Map newh;
    newh.insert("a", 5);   // Of all h.insert, only this is running correct. Why?!!!!!!!!!!!
    newh.insert("b", 4);
    newh.insert("c", 8);
    newh.insert("d", 2);
    newh.insert("e", 1);
    Map j;
    subtract(g, newh, j);    //checks if all are subtracted
    assert(j.empty());
    
    cout << "Passed test group combine & subtract" << endl;
    
    cout << "Passed all tests" << endl;
}
