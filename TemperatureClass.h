//Definition of the Temperature class

#ifndef WEATHER_TEMPERATURECLASS_H
#define WEATHER_TEMPERATURECLASS_H

#include <map>
#include <unordered_map>
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

class Temperature
        {
private:

    struct city {
        string cityName;
        map<string, float> DateTemps;
        unordered_map<string, pair<string, float> > DateTemps2;

        city(string name) { this->cityName = name; }
    };

//Private variables
    int timer;

    map<city *, string> cityMap;
    map<city *, string>::iterator cityMapIt;

    map<string, map<string, float> > city1;
    map<string, map<string, float> >::iterator outer;
    map<string, float>::iterator inner;

    unordered_map<string, pair<string, float> >::iterator it2;

    multimap<string, string> calendar;
    multimap<string, string>::iterator cal;

public:

    //Setup functions
    void timerInit();
    void calendarMaker();
    vector <string> fileExtraction();
    void mapMaker(vector <string> input);
    void nodeMaker();

    //Calculation functions
    vector<float> lowerUpper(string lower, string upper, string unit);
    float weatherCalculate(string city, vector<string> start, vector<string> end);
    float weatherCalculate2(string city, vector<string> start, vector<string> end);
    map <string, map<string, string> > dateRanges(string lower, string upper, string unit);
    map <string, map<string, string> > dateRanges2(string lower, string upper, string unit);
    map <string, float> yearlyAvg(string lower, string upper, string unit);
    map <string, float> yearlyAvg2(string lower, string upper, string unit);

    //Input validation functions
    bool cityCheck(string input);
    bool dateCheck(string input);
    bool unitcheck(string input);
    bool tempCheck(string input);
    bool upperCheck(string min, string max);

    //Display functions
    void winner(chrono::duration<double> elapsed, chrono::duration<double> elapsed2);
    string finalTemp(float weather, string input);
    string mainMenu();
    string mainMenuReturn();

    //Option functions
    vector<string> dateExtract(string date);
    void option1();
    void option2();
    void option3();
    void option4();

    //Helper functions
    void printCityData();
    void printCalendar();
    void printCityMap();
    void printCityMap2();

};

#endif //WEATHER_TEMPERATURECLASS_H
