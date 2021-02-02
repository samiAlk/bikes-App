/*main.cpp*/

//
// Sami al kabbani
// U. of Illinois, Chicago
// CS 251: Spring 2020
// 
// Lab Week 11: hashing of dates and lottery numbers (SOLUTION)
// 

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <utility>
#include "hash.h"
#include "vector"
#include "hashmap.h"
#include "util.h"
#include <algorithm>

using namespace std;


//
// 
// 
// info about any bikes station and its capacity
struct StationData
{	
	string abbrev, fullname, online_date, capacity, ID;
	double latitude, longitude;
	
	StationData()
	{
		
		abbrev = fullname = online_date = ID = capacity = "";
		latitude = longitude = 0.00;
		
	}
};

//
//
// info for the trips that were done using bikes
struct TripsData
{	
	string tripid, starttime, stoptime, bikeid, duration, fromAddress, toAddress, identifies, birthyear; 	
	int usage;
	
	TripsData()
	{
		
		tripid = starttime = stoptime = bikeid = duration = fromAddress = toAddress = identifies = birthyear = "";
		usage = 0; 
		
	}
};

//
// string2int
// 
// Converts a string to an integer, unless string is empty, in
// which case 0 is returned.
// 
int string2int(string s)
{
	if (s == "")
		return 0;
	else
		return stoi(s);
}

//
// inputData
// 
// Given a filename denoting lottery winning numbers,
// inputs that data into the given hash table.
// 
bool inputDataStations(string filename          // file name we are reading
, hashmap<string, StationData>& stationByID     // hash table for lookup by ID
, hashmap<string, StationData>& stationByAbbrev) // hash table for lookup by abbrev
{
	ifstream  infile(filename);        // opening the file
	
	if (!infile.good())            // checking if the file is correct
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
	

	while (getline(infile, line)){        // while there are files to read

			stringstream s(line);

			string abbrev, fullname, online_date, ID, capacity, latitude, longitude; 
			//inializing the values for the struct
			//all the values seprated by comas
			getline(s, ID, ',');      // getting the values one by one
			getline(s, abbrev, ',');   
			getline(s, fullname, ',');
			getline(s, latitude, ',');
			getline(s, longitude, ',');
			getline(s, capacity, ',');
			getline(s, online_date, ',');
			StationData ld; 

			//adding the values into the struct
			ld.ID = ID;       
			ld.abbrev = abbrev;
			ld.fullname = fullname;
			ld.latitude = stod(latitude);
			ld.longitude = stod(longitude);
			ld.capacity = capacity;
			ld.online_date = online_date;
		
			stationByID.insert(ID, ld, Hash);  // for stations by numbers

			stationByAbbrev.insert(abbrev, ld, HashAbbrev);  // for stations by abbreviation
			//ID = stoi(ID);
			//stationByID.VectorInsert(ID);		

			count++;

	}//end while
	
	cout << "# of stations: " << count << endl;

	return true;  // we have data to be processed:
}



bool inputDataTrips(string filename     // name of the file we are reading
, hashmap<string, TripsData>& tripsByID // hash table for trips by ID
, hashmap<string, TripsData>& bikesByID) // hash table for trips by bikes

{
	ifstream  infile(filename);        // opening the file
	
	if (!infile.good())            // checking if the file is correct
	{
		cout << "**Error: unable to open '" << filename << "'..." << endl;
		return false;
	}
	
	// file is open, start processing:
	string line;
	
	getline(infile, line);  // input and discard first row --- header row
	
	int count = 0;
	int bikeCount = 0;
	

	while (getline(infile, line)){        // while there are files to read

			stringstream s(line);
		
			string tripid, starttime, stoptime, bikeid, duration, fromAddress, toAddress, identifies, birthyear; 
			
			getline(s, tripid, ',');  
			getline(s, starttime, ',');   
			getline(s, stoptime, ',');           // getting each value sepreatly 
			getline(s, bikeid, ',');
			getline(s, duration, ',');
			getline(s, fromAddress, ',');
			getline(s, toAddress, ',');
			getline(s, identifies, ',');
			getline(s, birthyear, ',');

			TripsData ld; // struct call
			//adding the values into the struct
			ld.tripid = tripid;       
			ld.starttime = starttime;
			ld.stoptime = stoptime;
			ld.bikeid = bikeid;

			bool searchID = bikesByID.search(bikeid, ld, HashBikes);
			if(searchID == false){      // checking if the bike ID exist 
				bikeCount++;		   // to coun bikes only once
				
			}
			ld.usage++;
			ld.duration = duration;
			ld.fromAddress = fromAddress;
			ld.toAddress = toAddress;
			ld.identifies = identifies;
			ld.birthyear = birthyear;


			tripsByID.insert(tripid, ld, HashTrips);  // for stations by numbers
			bikesByID.insert(bikeid, ld, HashBikes);  // for stations by abbreviation

			count++;  // counting the enteries
		

	}//end while
	
	cout << "# of trips: " << count << endl;
	cout << "# of bikes: " << bikeCount << endl;

	return true;  // we have data to be processed:
}

// takes the time in seconds and gives time in hour, minutes and seconds
void duration(string time){
	int hour, minute, second;
	hour = minute = second = 0;  //inializing all the values to 0
	int intTime = stoi(time);

	if((intTime /3600) > 0){    // checking if the time has any hours in it
		hour = intTime % 3600;
		cout << hour << " hours, ";
	}
	else{
		hour = intTime;        // if not pass the time over to minutes
	}
    if((hour / 60) > 0){
	    minute = hour / 60;    // how many minutes in the time
		cout << minute << " minutes, ";
	}
	else{
		minute = hour;
	}
	if((minute % 60) > 0){
	    second = hour % 60;    // give us the seconds in the time
		cout << second << " seconds";
	}
}

//takes in ID from the vector and compare all latitude and longitude with the ones inputted
//and return the station ID if it is less than the distance
void nearByStation (vector <string> Keys        // vector of station IDs
, vector <pair<int, double>>& nearbyVector      // vector to store the pairs of distance and ID
, hashmap<string, StationData>& stationByID     // hash map for the IDs
, double X, double Y, double D){                // the input from the user

	StationData ld;
	pair <int, double> pairStation;
	nearbyVector.clear();
	int size = Keys.size();      //size of the vector
	int ID;
	for(int i=0; i <size; i++){
		stationByID.search(Keys[i], ld, Hash);
		double Distance = distBetween2Points(X, Y,ld.latitude, ld.longitude); // calcuating the distance
		if(Distance <= D){
			ID = stoi(Keys[i]);
			pairStation.first = ID;             // puting the values into a pair then that pair into the function
			pairStation.second = Distance;
			nearbyVector.push_back(pairStation);
		}// end if
	}// forloop
}// end nearByStation
	


// refered from website geeksforgeeks
bool ordering(const pair<int,double> &a, const pair<int,double> &b) 
{ 
    return(a.second < b.second); // sorting the pairs using the second 

}

/* the one and the only....... main*/
int main()
{
	vector <string> Keys;
	vector <pair<int, double>> nearbyVector;
	
	cout << "** DIVVY analysis program **" << endl;
	cout << endl;

	//
	// Allocate our hash table: 12 * 31 * 100 = 37,200
	// possible permutations:
	// 
	const int N = 10000;
	const int N50k = 50000;
	const int N2M = 2500000;

	
    hashmap<string, StationData> stationByID(N);
	hashmap<string, StationData> stationByAbbrev(N);
	hashmap<string, TripsData> tripsByID(N2M);
	hashmap<string, TripsData> bikesByID(N50k);
	//
	// input the winning numbers:
	// 
	string stationsFilename = "stations.csv";
	string tripsFilename ="trips.csv";
	string filename;
	
	cout << "Enter stations file> ";
	getline(cin, filename);           // user can type a filename, or just press ENTER
	if (filename != "")               // user entered a filename,use it
		stationsFilename = filename;
	
	
	cout << "Enter trips file> ";	
	getline(cin, filename);           // user can type a filename, or just press ENTER
	if (filename != "")               // user entered a filename,use it
		tripsFilename = filename;

	
	cout << endl << "Reading " << stationsFilename << endl;
	cout << "Reading " << tripsFilename << endl << endl;
	
	// reading the files and getting the values
	bool successID = inputDataStations(stationsFilename, stationByID, stationByAbbrev);

	bool successTrip = inputDataTrips(tripsFilename, tripsByID, bikesByID);
	
	Keys = stationByID.vector12();

	
	//
	// did we input anything?
	// 
	if ((!successID) || !successTrip)
	{
		cout << "No data, file not found?" << endl;
		return 0;
	}
	

	
	//
	// allow the user to lookup winning numbers by date:
	// 
	string command;
	
	cout << endl;
	cout << "Please enter a command, help, or #> ";
	getline(cin, command);
	//
	// user testing:
	//
	while (command != "#")
	{
	//
	// we have a date, let's look in hash table and
	// see if we have any data:
	// 
     StationData ld;
	 TripsData td;
	 if(isNumeric(command) == true){            // if the user input number for a station id
		 bool found = stationByID.search(command, ld, Hash);
		 if (!found){
		   cout << "Station not found" << endl;
		 }
		 else{
		   cout << "Station:" << endl;
		   cout << " ID: " << ld.ID << endl;
		   cout << " Abbrev: " << ld.abbrev << endl;
		   cout << " Fullname: " << ld.fullname << endl;
		   cout << " Location: (" << ld.latitude << ", " << ld.longitude << ")" << endl;
		   cout << " Capacity: " << ld.capacity << endl;
		   cout << " Online date: " << ld.online_date << endl;
		 }
	 }
		
	 else if(command == "help"){        // if the user input the string help for assistance
		 cout << "available commands:" << endl
		      << " Enter a station id (e.g. 341)" << endl
			  << " Enter a station abbreviation (e.g Adler)" << endl
			  << " Enter a trip id (Tr10426561)" << endl
			  << " Enter a bike id (e.g. B5218)" << endl
			  << " Nearby stations (e.g. nearby 41.86 -87.62 0.5)" << endl
			  << " Similar trips (e.g. similar Tr10424639 0.3)" << endl;
	 }
	 // looking up info by bike trip (e.g Tr10424639)	
	 else if(command[0] == 'T' && command[1] == 'r'){
		 bool found = tripsByID.search(command, td, HashTrips);
		 
		 if (!found){
		   cout << "Trip not found" << endl;
		 }
		 else{
			 cout << "Trip: " << endl;
			 cout << " ID: " << td.tripid << endl;
			 cout << " Starttime: " << td.starttime << endl;
			 cout << " bikeid: " << td.bikeid << endl;
			 cout << " Duration: "; duration(td.duration); cout << endl;
			 stationByID.search(td.fromAddress, ld, Hash); // searching for the abbrev by station id
			 cout << " From station: " << ld.abbrev << " (" << td.fromAddress << ")" << endl;
			 stationByID.search(td.toAddress, ld, Hash);   // searching for the abbrev by station id
			 cout << " To station: " << ld.abbrev << " (" << td.toAddress << ")" << endl;
			 cout << " Rider identifies as: " << td.identifies << endl;
			 cout << " BirthYear: " << td.birthyear << endl;
		 }
	 }
	 // looking up trips by bike ID
	 else if(command[0] == 'B'){
		 bool found = bikesByID.search(command, td, HashBikes);
		 if(!found){
			 cout << "Bike not found" << endl;
		 }
		 else{
			 cout << "Bike:" << endl;
			 cout << " ID: " << td.bikeid << endl;
			 cout << " Usage: " << td.usage << endl;			 
		 }	 
	 }
		
	 //if the user input nearby. which give him the nearby stations
	 else if(command.substr(0,6) == "nearby"){
		 stringstream s(command);
		 string inputX;                   // inializing the strings for the command
		 string inputY;
		 string inputD;
		 
		 getline(s, command, ' ');        // dividing the input into 3 strings
		 getline(s, inputX, ' ');
		 getline(s, inputY, ' ');
		 getline(s, inputD, ' ');
		 
		 cout << "Stations within " << inputD << " miles of (" << inputX << ", " << inputY << ")" << endl;  

		 double X = stod(inputX);         // changing them to double to do the math for the distance
		 double Y = stod(inputY);
		 double D = stod(inputD);
		 nearByStation (Keys, nearbyVector, stationByID, X, Y , D);
		 sort(nearbyVector.begin(), nearbyVector.end(), ordering);
		 int size = nearbyVector.size();
		 if(size == 0){                    // if no values int the vector, then there are none
			 cout << " none found" << endl;
		 }
		 for(int i=0; i<size; i++){          //printing the values form the vector
			 cout << " station " << nearbyVector[i].first << ": " << nearbyVector[i].second << " miles" << endl;
		 }
	 }// end nearby command
	 // similar command, get the ID and find trips within the start and end of the trip
	 else if(command.substr(0,7) == "similar"){
		 stringstream s(command);
		 string trip;
		 string D;
		 getline(s, command, ' '); 
		 getline(s, trip, ' ');                 //spliting the commands
		 getline(s, D, ' '); 
		 
		 cout << "Trips that follow a similar path (+/-" << D << " miles) as " << trip << endl;
		 tripsByID.search(trip, td, HashTrips);
		 stationByID.search(td.fromAddress, ld, Hash);         // search for the start station
		 
		 double X = ld.latitude;
		 double Y = ld.longitude;
		 
		 double Distance = stod(D);
		 
		 nearByStation (Keys, nearbyVector, stationByID, X, Y, Distance);
		 int size = nearbyVector.size();
		 cout << " nearby starting points: ";
		 for(int i=0; i<size; i++){
			 cout << nearbyVector[i].first << " ";                    //getting the station numbers
		 }
		 cout << endl;	 
			 // gettig the ending station now
		 stationByID.search(td.toAddress, ld, Hash);
		 X = ld.latitude;
		 Y = ld.longitude;
		 nearByStation (Keys, nearbyVector, stationByID, X, Y, Distance);  // search for the end station
		 size = nearbyVector.size();
		 cout << " nearby ending points: ";		 
		 for(int i=0; i<size; i++){
			 cout << nearbyVector[i].first << " ";                    //getting the station numbers
		 }		 
		 bikesByID.search(td.bikeid, td, HashBikes);
		 cout << endl << " Trip count: " << td.usage << endl;	 

	}//end similar
		
		
	 // checking stations by their names (abbreviation)
	 else{
		 bool found = stationByAbbrev.search(command, ld, HashAbbrev);
		 if (!found){
		   cout << "Station not found" << endl;
		 }
		 else{
		   cout << "Station:" << endl;
		   cout << " ID: " << ld.ID << endl;
		   cout << " Abbrev: " << ld.abbrev << endl;
		   cout << " Fullname: " << ld.fullname << endl;
		   cout << " Location: (" << ld.latitude << ", " << ld.longitude << ")" << endl;
		   cout << " Capacity: " << ld.capacity << endl;
		   cout << " Online date: " << ld.online_date << endl;
		 }
	 }
	  // repeating the process	 
	  cout << endl;
	  cout << "Please enter a command, help, or #> ";
	  getline(cin, command);
	}
	
	//
	// done!
	// 
	
	return 0;
}
