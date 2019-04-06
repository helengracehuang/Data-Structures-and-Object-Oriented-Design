//
//  linear.cpp
//  Homework 3
//
//  Created by Xin Huang on 2/11/18.
//  Copyright © 2018 Xin Huang. All rights reserved.
//
/*
#include <cmath>
#include <cassert>
#include <iostream>

using namespace std;
*/
bool somePredicate(double x);
/*
bool somePredicate(double x)
{
    return x >= 0;
}
*/

// Return false if the somePredicate function returns false for at
// least one of the array elements; return true otherwise.
bool allTrue(const double a[], int n)
{
    if (n <= 0)
        return true;
    if (!somePredicate(a[n-1]))
        return false;
    return (allTrue(a, n-1));
}

// Return the number of elements in the array for which the
// somePredicate function returns false.
int countFalse(const double a[], int n)
{
    if (n <= 0)
        return 0;
    if (!somePredicate(a[n-1]))
        return countFalse(a, n-1) + 1;
    return countFalse(a, n-1);
}

// Return the subscript of the first element in the array for which
// the somePredicate function returns false.  If there is no such
// element, return -1.

int firstFalse(const double a[], int n)
{
    if (n <= 0)
        return -1;
    int i = firstFalse(a, n-1);
    if (i != -1)
        return i;
    if (!somePredicate(a[n-1]))
        return n-1;
    return -1;
}

// Return the subscript of the smallest double in the array (i.e.,
// the one whose value is <= the value of all elements).  If more
// than one element has the same smallest value, return the smallest
// subscript of such an element.  If the array has no elements to
// examine, return -1.
int indexOfMin(const double a[], int n)
{
    if (n <= 0)
        return -1;
    if (n == 1)
        return 0;
    if (a[indexOfMin(a, n-1)] > a[n-1])
        return n-1;
    return indexOfMin(a, n-1);
}

// If all n2 elements of a2 appear in the n1 element array a1, in
// the same order (though not necessarily consecutively), then
// return true; otherwise (i.e., if the array a1 does not include
// a2 as a not-necessarily-contiguous subsequence), return false.
// (Of course, if a2 is empty (i.e., n2 is 0), return true.)
// For example, if a1 is the 7 element array
//    10 50 40 20 50 40 30
// then the function should return true if a2 is
//    50 20 30
// or
//    50 40 40
// and it should return false if a2 is
//    50 30 20
// or
//    10 20 20
bool includes(const double a1[], int n1, const double a2[], int n2)
{
    if (n2 <= 0)
        return true;
    if (n1 < n2)
        return false;
    if (a1[0] == a2[0])
        return includes(a1+1, n1-1, a2+1, n2-1);
    return includes(a1+1, n1-1, a2, n2);
}

/*
int main()
{
    double testNegatives[5] = { 1, 3, -2, 5, 7 };
    double testNoNegatives[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(allTrue(testNegatives, 5) == false);
    assert(allTrue(testNegatives, 3) == false);
    assert(allTrue(testNegatives, 2) == true);
    assert(allTrue(testNoNegatives, 10) == true);
    assert(allTrue(testNoNegatives, 1) == true);
    assert(allTrue(testNoNegatives, 0) == true);
    cerr << "Passed allTrue tests." << endl;
    double testCountNegatives[5] = { 1, -2, -3, -4, 5 };
    double testCountSomeNegatives[10] = { -5, 0, 28, 5, 1, 23, -5, 1, 2, 14 };
    double testCountAllNegatives[5] = { -7, -3, -9, -1, -15 };
    assert(countFalse(testCountNegatives, 5) == 3);
    assert(countFalse(testCountNegatives, 4) == 3);
    assert(countFalse(testCountNegatives, 2) == 1);
    assert(countFalse(testCountNegatives, 1) == 0);
    assert(countFalse(testCountNegatives, 0) == 0);
    assert(countFalse(testCountSomeNegatives, 10) == 2);
    assert(countFalse(testCountSomeNegatives, 7) == 2);
    assert(countFalse(testCountSomeNegatives + 1, 9) == 1);
    assert(countFalse(testCountSomeNegatives, 0) == 0);
    assert(countFalse(testCountSomeNegatives, 1) == 1);
    assert(countFalse(testCountAllNegatives, 5) == 5);
    assert(countFalse(testCountAllNegatives, 3) == 3);
    assert(countFalse(testCountAllNegatives + 4, 1) == 1);
    assert(countFalse(testCountAllNegatives, 0) == 0);
    cerr << "Passed countFalse tests." << endl;
    
    double testFindNegative[5] = { 1, 3, -2, 5, 7 };
    double testFindNegativeLong[10] = { -5, 0, 28, 5, 1, 23, -5, 1, 2, 14 };
    double testFindNoNegatives[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    assert(firstFalse(testFindNegative, 5) == 2);
    assert(firstFalse(testFindNegative, 3) == 2);
    assert(firstFalse(testFindNegative, 2) == -1);
    assert(firstFalse(testFindNegative + 2, 3) == 0);
    assert(firstFalse(testFindNegative + 3, 2) == -1);
    assert(firstFalse(testFindNegativeLong, 10) == 0);
    assert(firstFalse(testFindNegativeLong, 2) == 0);
    assert(firstFalse(testFindNegativeLong + 1, 9) == 5);
    assert(firstFalse(testFindNegativeLong + 2, 8) == 4);
    assert(firstFalse(testFindNoNegatives, 10) == -1);
    cerr << "Passed firstFalse tests." << endl;
    double testMinIndex[5] = { 1, 3, -2, 5, 7 };
    double testMinNoNeg[5] = { 0, 1, 2, 3, 4 };
    double testGettingSmaller[4] = { 5, 3, 1, -9 };
    double testGettingBigger[4] = { -9, 1, 3, 5 };
    assert(indexOfMin(testMinIndex, 5) == 2);
    assert(indexOfMin(testMinIndex, 3) == 2);
    assert(indexOfMin(testMinIndex + 3, 2) == 0);
    assert(indexOfMin(testMinIndex, 2) == 0);
    assert(indexOfMin(testMinNoNeg, 5) == 0);
    assert(indexOfMin(testMinNoNeg + 2, 3) == 0);
    assert(indexOfMin(testMinNoNeg + 4, 1) == 0);
    assert(indexOfMin(testGettingSmaller, 4) == 3);
    assert(indexOfMin(testGettingBigger, 4) == 0);
    double testMoreMin[5] = { 19, 11, 13, 15, 17 };
    assert(indexOfMin(testMoreMin, 5) == 1);
    assert(indexOfMin(testMoreMin, 2) == 1);
    assert(indexOfMin(testMoreMin, 1) == 0);
    assert(indexOfMin(testMoreMin + 2, 3) == 0);
    cerr << "Passed indexOfMin tests." << endl;
    double a1[7] = { 10, 50, 40, 20, 50, 40, 30 };
    double a2[3] = { 50, 20, 30 };
    double a3[3] = { 50, 40, 40 };
    double a4[3] = { 10, 20, 20 };
    double a5[3] = { 50, 30, 20 };
    assert(includes(a1, 7, a2, 3) == true);
    assert(includes(a1, 7, a3, 3) == true);
    assert(includes(a1, 7, a4, 3) == false);
    assert(includes(a1, 7, a5, 3) == false);
    cerr << "Passed includes tests." << endl;
}
*/

