/*hash.h*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <string>

using namespace std;

bool isNumeric(string s);
int Hash(string theDate, int N);
int HashTrips(string tripNum, int N);
int HashAbbrev(string abbrev, int N);
int HashTrips(string tripid, int N);
int HashBikes(string bikeid, int N);