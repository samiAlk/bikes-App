/*hash.cpp*/

//
// Prof. Joe Hummel
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <string>
#include <cctype>  /*isdigit*/
#include <regex>   /*regular expressions*/

#include "hash.h"


using namespace std;

//
// isNumeric
//
// Returns true if the given string is numeric (all digits), false
// if not.  If the string is empty, false is returned since there 
// are no digits present.
//
bool isNumeric(string s)
{
	//
	// A string is numeric if it contains 1 or more digits, so let's
	// use a regular expression to check that.
	//
	// we are using POSIX basic notation for regular expressions, see
	//   https://en.cppreference.com/w/cpp/regex/ecmascript
	// where [:d:] means digit, [[:d:]] means match a single digit.
	// The + means match the preceding sub-expression 1 or more times.
	//
	regex pattern("[[:d:]]+", regex::ECMAScript);

	smatch matchResults;  // provides more details on the match

	if (regex_match(s, matchResults, pattern))
		return true;
	else
		return false;
}

//
// Hash
//
// This is necessary so we can pass the existing gradescope tests,
// instead of having to create a new set of tests.  There's no
// other reason for it.
//
int Hash(string theDate, int N)
{
  int index = stoi(theDate);
  return index % N;
}
// taking the name and switching to numbers
// and used to create an index
int HashAbbrev(string abbrev, int N){
	int num = 0;
	int size = abbrev.length();
	for(int i=0; i<size; i++){
		num = num + int(abbrev[i]);
	}
	return num % N;
}
// using trip id to create an index
// deleting first 2 letters and sub by 10M
int HashTrips(string tripid, int N){
	tripid = tripid.erase(0,2);
	int index = stoi(tripid);

	return index % N ;
}
// using bike ids for indexes
// deleting first letter and using the id as index
int HashBikes(string bikeid, int N){
	bikeid.erase(0,1);
	int index = stoi(bikeid);
	return index % N;
}
