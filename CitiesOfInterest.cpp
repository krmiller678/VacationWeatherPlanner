#include "CitiesOfInterest.h"

CitiesOfInterest::CitiesOfInterest(){
    // don't think we need anything in constructor as of yet...
}

void CitiesOfInterest::setCityWeather(string cityName, unsigned int monthDay, int temp){
    cities[cityName].addWeatherDataNode(monthDay, temp);
}

const vector<pair<string, int>>& CitiesOfInterest::getEveryCityDate(unsigned int monthDay, unsigned int accessMode) const{
    auto iter = cities.begin();
    vector<pair<string, int>> toReturn;
    for (; iter != cities.end(); iter++){
        toReturn.push_back(make_pair(iter->first, iter->second.getDailyWeather(monthDay, accessMode)));
    }
    return toReturn;
}

const vector<pair<string, int>>& CitiesOfInterest::getEveryCityWeek(unsigned int monthDay, unsigned int accessMode) const{
    auto iter = cities.begin();
    vector<pair<string, int>> toReturn;
    for (; iter != cities.end(); iter++){
        toReturn.push_back(make_pair(iter->first, iter->second.getWeeklyWeather(monthDay, accessMode)));
    }
    return toReturn;
}

const int CitiesOfInterest::getOneCityDate(string cityName, unsigned int monthDay, unsigned int accessMode) {
    return cities[cityName].getDailyWeather(monthDay, accessMode);
}

const vector<int>& CitiesOfInterest::getOneCityWeek(string cityName, unsigned int monthDay, unsigned int accessMode) {
    return cities[cityName].getWeeklyWeatherOneCity(monthDay, accessMode);
}