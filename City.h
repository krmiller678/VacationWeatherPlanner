#pragma once
#include <unordered_map>
#include <queue>
#include <string>
#include "WeatherDataNode.h"

/*
The City class contains all the data from the CSV after it has been sorted by City.

The two main containers in this class are our hash table and our heap.

This class should contain our search algorithms (functions) as well to find certain dates and the associated temperatures.

*/
class City
{
private:
    std::unordered_map<std::string, WeatherDataNode*> hash;
    std::priority_queue<WeatherDataNode*> heap;


public:
    // Constructor

    // Destructor

    // Mutators (Setters)
        // City.addNewDataPoint()
    void addWeatherDataNode(unsigned int monthDay, int temp);

    // Accessors (Getters)
    int getDailyWeather(unsigned int monthDay, unsigned int accessMode) const;
    int getWeeklyWeather(unsigned int monthDay, unsigned int accessMode) const; // Average across the week
    vector<int>& getWeeklyWeatherOneCity(unsigned int monthDay, unsigned int accessMode) const; // Per day weather for week

    // Additional Functions

    // Operator Overloads - NOT USED

};