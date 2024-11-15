// City.cpp
#include "City.h"
#include <iomanip>
#include <algorithm>

City::City() {}

City::~City() {
    for (auto& entry : hash) {
        delete entry.second;
    }
}

void City::addWeatherDataNode(unsigned int monthDay, int temp) {
    // Convert the monthDay to a string in the format MMDD
    string date = to_string(monthDay);
    if (date.length() == 3) {
        date = "0" + date;
    }

    // Create a new WeatherDataNode
    WeatherDataNode* node = new WeatherDataNode(date, temp);

    // Add the node to the hash map and the priority queue
    hash[date] = node;
    heap.push(node);
}

int City::getDailyWeather(unsigned int monthDay, unsigned int accessMode) const {
    // Convert the monthDay to a string in the format MMDD
    string date = to_string(monthDay);
    if (date.length() == 3) {
        date = "0" + date;
    }

    // Check if the date exists in the hash map
    auto it = hash.find(date);
    if (it != hash.end()) {
        return it->second->getTemperature(); // Return the temperature
    } else {
        // Handle the case where the date does not exist
        return -1; // return -1 if date is not found
    }
}

int City::getWeeklyWeather(unsigned int monthDay, unsigned int accessMode) const {
    // Convert the monthDay to a string in the format MMDD
    string startDate = to_string(monthDay);
    if (startDate.length() == 3) {
        startDate = "0" + startDate;
    }

    int totalTemp = 0;
    int count = 0;

    // Iterate through the next 7 days
    for (int i = 0; i < 7; ++i) {
        // Calculate the date for the current day in the format MMDD
        string date = to_string(monthDay + i);
        if (date.length() == 3) {
            date = "0" + date;
        }

        // Check if the date exists in the hash map
        auto it = hash.find(date);
        if (it != hash.end()) {
            totalTemp += it->second->getTemperature();
            ++count;
        }
    }

    // Return the average temperature
    return (count > 0) ? (totalTemp / count) : -1; // return -1 if no data is found for the week
}

vector<int> &City::getWeeklyWeatherOneCity(unsigned int monthDay, unsigned int accessMode) const {
    // Convert the monthDay to a string in the format MMDD
    string startDate = to_string(monthDay);
    if (startDate.length() == 3) {
        startDate = "0" + startDate;
    }

    vector<int> weeklyTemps;

    // Iterate through the next 7 days
    for (int i = 0; i < 7; ++i) {
        // Calculate the date for the current day in the format MMDD
        string date = to_string(monthDay + i);
        if (date.length() == 3) {
            date = "0" + date;
        }

        // Check if the date exists in the hash map
        auto it = hash.find(date);
        if (it != hash.end()) {
            weeklyTemps.push_back(it->second->getTemperature());
        } else {
            // If no data for the day, you can choose to push a default value or skip
            weeklyTemps.push_back(-1); // -1 as a placeholder for missing data
        }
    }

    return weeklyTemps;
}
