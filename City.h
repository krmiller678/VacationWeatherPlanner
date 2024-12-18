#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include "WeatherDataNode.h"

using namespace std;

/*
The City class contains all the data from the CSV after it has been sorted by City.

The two main containers in this class are our hash table and our heap.

This class should contain our search algorithms (functions) as well to find certain dates and the associated temperatures.

*/

// City.h

using namespace std;

class City {
public:
    // Constructor
    City();

    // Destructor
    ~City();

    // Mutators (Setters)
    // City.addNewDataPoint()
    void addWeatherDataNode(unsigned int monthDay, int temp);

    // Accessors (Getters)
    int getDailyWeather(unsigned int monthDay, unsigned int accessMode) const;
    int getWeeklyWeather(unsigned int monthDay, unsigned int accessMode) const; // Average across the week
    vector<int>& getWeeklyWeatherOneCity(unsigned int monthDay, unsigned int accessMode) const; // Per day weather for week

private:
    unordered_map<string, WeatherDataNode*> hash;
    priority_queue<WeatherDataNode*> heap;
};



