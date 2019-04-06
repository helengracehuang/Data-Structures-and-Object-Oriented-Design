//
//  testMap.cpp
//  Homework 1
//
//  Created by Xin Huang on 1/21/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//

#include "Map.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Map m;
    m.insert("A", 10);
    m.insert("B", 44);
    m.insert("C", 10);
    string all;
    double total = 0;
    for (int n = 0; n < m.size(); n++)
    {
        string k;
        double v;
        m.get(n, k, v);
        all += k;
        total += v;
    }
    cout << all << total;
    
    /////
    
    Map gpas;
    gpas.insert("Fred", 2.956);
    gpas.insert("Ethel", 3.538);
    double v1;
    string k1;
    assert(gpas.get(1, k1, v1) && (k1 == "Fred" || k1 == "Ethel"));
    string k2;
    assert(gpas.get(1, k2, v1) && k2 == k1);
    
    /////
    
    Map gpass;
    gpass.insert("Fred", 2.956);
    assert(!gpass.contains(""));
    gpass.insert("Ethel", 3.538);
    gpass.insert("", 4.000);
    gpass.insert("Lucy", 2.956);
    assert(gpass.contains(""));
    gpass.erase("Fred");
    assert(gpass.size() == 3 && gpass.contains("Lucy") && gpass.contains("Ethel") && gpass.contains("") && !gpass.contains("Fred"));
    
    /////
    
    Map m1;
    m1.insert("Fred", 2.956);
    Map m2;
    m2.insert("Ethel", 3.538);
    m2.insert("Lucy", 2.956);
    m1.swap(m2);
    assert(m1.size() == 2 && m1.contains("Ethel") && m1.contains("Lucy") &&
           m2.size() == 1 && m2.contains("Fred"));
    
    /////
    
    Map m3;  // maps strings to doubles
    assert(m3.empty());
    ValueType v3 = -1234.5;
    assert(!m3.get("abc", v3) && v3 == -1234.5); // v unchanged by get failure
    m3.insert("xyz", 9876.5);
    assert(m3.size() == 1);
    KeyType k3 = "hello";
    assert(m3.get(0, k3, v3) && k3 == "xyz"  &&  v3 == 9876.5);
    
    /////
    //End of Supplied Tests
    /////
    //tested empty(), size(), insert(), contains(), get()x2
    //Need to test update(), insertorupdate(), get()x2, swap()
    
    Map map;
    map.insert("A", 1.23);
    map.insert("B", 2.34);
    map.insert("C", 3.45);
    KeyType key = "B";
    ValueType value = 9.87;
    KeyType key1 = "D";
    ValueType val1 = 2.36;
    KeyType key2 = "A";
    ValueType val2 = 5.67;
    ValueType value2;
    assert(map.update(key, value) && map.get(key, value2) && value2 == 9.87);
    assert(map.insertOrUpdate(key2, val2) && map.get(key2, value2) && value2 == 5.67);
    assert(map.insertOrUpdate(key1, val1) && map.get(key1, value2) && value2 == 2.36);
    
    Map map2;
    map2.insert("Z", 3.21);
    map2.insert("Y", 5.43);
    map.swap(map2);
    assert(map.contains("Z") && map.contains("Y"));
    assert(map2.contains("A") && map2.size() == 4);
    
    cout << "Passed all tests" << endl;
}

/*
 int main()
 {
 Map m;  // maps ints to strings
 assert(m.empty());
 ValueType v = "Ouch";
 assert( !m.get(42, v)  &&  v == "Ouch"); // v unchanged by get failure
 m.insert(123456789, "Wow!");
 assert(m.size() == 1);
 KeyType k = 9876543;
 assert(m.get(0, k, v)  &&  k == 123456789  &&  v == "Wow!");
 cout << "Passed all tests" << endl;
 }
 */
