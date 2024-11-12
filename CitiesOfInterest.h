#pragma once
#include <map>
#include <string>
#include "City.h"
using namespace std;

/*
The Cities of Interest class will contain a std::map of sorted "City" strings and their associated City objects.
This class will recognize the csv being input, and parse the data to pass to the corresponding City.
If the City does not exist in the map, create new city.
If the City does exist, call City.addNewDataPoint()

In addition to the above setters, this class will receive the requests from the main file to display the outputs.
*/
class CitiesOfInterest
{

private:
    std::map<std::string, City> cities;

public:
    // Constructor
    CitiesOfInterest();
    // Destructor - not needed

    // Mutators (Setters)
        // READ CSV and pass data to City
    void setCityWeather(string cityName, unsigned int monthDay, int temp);

    // Accessors (Getters) - access mode specifies if it is using 
    const vector<pair<string, int>>& getEveryCityDate(string cityName, unsigned int monthDay, unsigned int accessMode) const; // returns a vector of every cityName, temp
    const vector<pair<string, int>>& getEveryCityWeek(string cityName, unsigned int monthDay, unsigned int accessMode) const; // returns a vector of every cityName, avg temp for week
    const int getOneCityDate(string cityName, unsigned int monthDay, unsigned int accessMode) const; // returns temperature for the city on that day
    const vector<int> getOneCityWeek(string cityName, unsigned int monthDay, unsigned int accessMode) const; // returns a vector of temps for week starting with monthDay

    // Additional Functions

    // Operator Overloads - NOT USED

};

 //city  <  fulldate, temp>
 //         1995-01-01  67.3
 //         1995-03-12  80.1
 //         ...
 //         1994-04-12  90.1
 //miami
//
 //03/12  -   04/12
//
 //03/12   80.1
 //03/13  80.4
