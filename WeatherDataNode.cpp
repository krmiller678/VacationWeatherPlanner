#include "WeatherDataNode.h"

// Define the constructor to initialize the date and temperature
WeatherDataNode::WeatherDataNode(const string& date, int temp) {
    this->date = date;
    this->temperature = temp;
}

// Define the function to get the temperature
int WeatherDataNode::getTemperature() const {
    return temperature;
}

