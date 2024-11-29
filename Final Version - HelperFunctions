#include "TemperatureClass.h"

//Helper function that prints every city along with every unique date and temperature for that date that was found in the
//csv file
void Temperature::printCityData()
{
    for(outer = city1.begin(); outer!= city1.end(); outer++)
        for(inner = outer->second.begin(); inner!= outer->second.end(); inner++)
            cout  << outer->first << " " <<  inner->first << " " << inner->second << endl;
}

//Helper function to display the calendar
void Temperature::printCalendar()
{
    for(cal = calendar.begin(); cal!= calendar.end(); cal++)
        cout  << cal->first << "/" <<  cal->second << endl;
}

//Helper function to see every city and it's daily average weather for the year. This function access the ordered map
//in the city struct
void Temperature::printCityMap()
{
    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        for(inner = cityMapIt->first->DateTemps.begin();
            inner!= cityMapIt->first->DateTemps.end(); inner++)
            cout << cityMapIt->first->cityName << " " << inner->first << " " << inner->second << endl;
}

//Helper function to see every city and it's daily average weather for the year. This function access the unordered map
//in the city struct
void Temperature::printCityMap2()
{
    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
    {
        it2 = cityMapIt->first->DateTemps2.find("01/01");
        while(1==1)
        {
            cout << cityMapIt->first->cityName << " " << it2->first << " " << it2->second.second << endl;
            if(it2->first == "12/31")
                break;
            it2 = cityMapIt->first->DateTemps2.find(it2->second.first);
        }
    }
}

