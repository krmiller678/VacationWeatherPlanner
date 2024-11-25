#pragma once
#include <string>
using namespace std;
/*
The WeatherDataNode class (could be a struct) is really here to define operator overloading so that we have a way to organize
our data in our ADT. We need to be able to compare the date.

Once we compare the dates to insert a WeatherDataNode into our data structure in the City class, we also need to include
some kind of temperature averaging function to the WeatherDataNode to average the temps.

Should be a super simple class
*/



class WeatherDataNode {
public:
    WeatherDataNode(const string& date, int temp);

    // Function to get the temperature
    int getTemperature() const;



    // Destructor

    // Mutators (Setters)

    // Accessors (Getters)

    // Additional Functions

    // Operator Overloads - YES

private:
    string date;
    int temperature;
};

// commented out in case we want to use int instead
// private:
//     unsigned int _date = 0;
//     int temperature = 0;



