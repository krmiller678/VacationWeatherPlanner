//Functions needed to convert the CSV file into the needed data stuctures for program use

#include "TemperatureClass.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//Initialize timer
void Temperature::timerInit()
{
    timer = 0;
}
//Function to create a calendar. Only needs the first country and first year in the dataset to work.
//Leap years are not being used in this project for simplicity reasons
void Temperature::calendarMaker()
{
    outer = city1.find("Algiers");
    inner = outer->second.begin();

    for(inner = outer->second.begin(); inner->first.substr(0,4) == "1995"; inner++)
        calendar.insert(pair<string, string>(inner->first.substr(5, 2), inner->first.substr(8, 2)));
}

//Function devoted to reading in the file. It first puts every line into a vector and then puts every delimited element
//into another next vector
vector <string> Temperature::fileExtraction()
{
    string s;
    vector <string> inputVect;
    vector <string> inputVect2;

    ifstream f("city_temperature1.csv");

    while (getline(f, s))
        inputVect.push_back(s);

    f.close();

    ifstream x("city_temperature2.csv");

    while (getline(x, s))
        inputVect.push_back(s);

    for(int i=0; i<inputVect.size();i++)
        for(int j = 0; inputVect.at(i)[j]!= '\0'; j++)
            if(inputVect.at(i)[j]==',' && inputVect.at(i)[j+1]==',')
                inputVect2.push_back(inputVect.at(i).substr(j+2));

    return inputVect2;
}

//Initializes the city1 ordered map where the key is a distinct city found from the csv file and the value is
//another ordered map where the key is a distinct historical date and it's value is the temperature on that day.
//Most of the function is devoted to getting the full date in the proper format from the csv
void Temperature::mapMaker(vector<string> input) {
    string word;
    string city, month, date, year, fulldate, temp;
    vector<string> words;

    for (int i = 1; i < input.size(); i++) {
        istringstream iss(input[i]);
        getline(iss, city, ',');
        getline(iss, month, ',');
        getline(iss, date, ',');
        getline(iss, year, ',');
        getline(iss, temp, ',');

        if (month.size() == 1) month = "0" + month;
        if (date.size() == 1) date = "0" + date;

        if (year.length() == 4 && city != "Muscat") {
            // Some rows in CSV had 3 digits for year. Muscat had negligible temperature data
            fulldate = year + "-" + month + "-" + date;

            // Direct conversion
            float temperature = stof(temp);
            city1[city][fulldate] = temperature;

        }
    }
}

//For each city and every date, this function calculates the average temperature for a date for every year in the past.
//Initializes both the ordered temperature and unordered temperature maps in the city struct
void Temperature::nodeMaker()
{
    float total = 0;
    float find = 0;
    string date, nextdate;

    //go through each city in the raw data
    for(outer = city1.begin(); outer!= city1.end(); outer++)
    {
        city* citypoint = new city(outer->first);

        for(cal = calendar.begin(); cal!= calendar.end(); cal++)
        {
            for(inner = outer->second.begin(); inner != outer->second.end(); inner++)
            {
                if(cal->first == inner->first.substr(5, 2) && cal->second == inner->first.substr(8, 2))
                {
                    if(inner->second != -99)
                    {  // cout << citypoint->cityName << " " << date << " " << inner->first << " " << total << " " << find << " " << endl;
                        total += inner->second;
                        find += 1.0;
                    }
                }
            }

            //this part is needed to be able to initialize the unordered map in city struct

            date = cal->first + "/" + cal->second;

            if(date == "12/31")
                nextdate = "01/01";
            else
            {
                cal++;
                nextdate = cal->first + "/" + cal->second;
                cal--;
            }

            if(find != 0)
            {
                citypoint->DateTemps[cal->first +  "/" + cal->second] = total / find;
                citypoint->DateTemps2[date]= make_pair(nextdate, total / find);
            }
            else
            {
                citypoint->DateTemps[cal->first + "/" + cal->second] = 10000.0; //10000 means nothing was calculated
                citypoint->DateTemps2[date]= make_pair(nextdate, 10000.0);
            }

            total = 0;
            find = 0;
        }
        cityMap[citypoint];
    }
}
