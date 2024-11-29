//All functions needed to calculate the results of using the options of the program are herre

#include "TemperatureClass.h"

//Function needed when user decides to use celsius. The dataset is in farenheit so the user's input has to be covnerted
vector<float> Temperature::lowerUpper(string lower, string upper, string unit)
{
    vector<float> lowHigh;
    float low = stof(lower);
    float high = stof(upper);

    if(unit=="C")
    {
        low = 1.8 * low + 32;
        high = 1.8 * high + 32;
    }

    lowHigh.push_back(low);
    lowHigh.push_back(high);
    return lowHigh;
}

//Function used by option 1 that will take in the destination, start and end date of someone's trip. It will then
//find the city and look up the temperatures between those dates and return the average. This function accesses
//the ordered map in the city struct
float Temperature::weatherCalculate(string city, vector<string> start, vector<string> end)
{
    string startdate = start.at(0) + "/" + start.at(1);
    string enddate = end.at(0) + "/" + end.at(1);
    float total= 0.0;
    float count = 0.0;

    //find city
    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        if(cityMapIt->first->cityName == city)
            break;

    //find startdate
    for(inner = cityMapIt->first->DateTemps.begin();inner!= cityMapIt->first->DateTemps.end(); inner++)
        if(startdate==inner->first)
            break;

    if(startdate == enddate)
        return inner->second;

    while(1==1)
    {
        if(inner->second != 10000 && inner->first!=enddate)
        {
            total += inner->second;
            count += 1.0;
        }

        if(inner->first == "12/31")
            inner = cityMapIt->first->DateTemps.begin();
        else
            inner++;

        if(inner->first==enddate)
        {
            if(inner->second != 10000)
            {
                total += inner->second;
                count += 1.0;
            }
            break;
        }
    }
    if(count!=0)
        return total/count;
    else
        return 10000;
}

//This function does the same thing as weatherCalculate except it accesses the unordered map of daily temperatures in the
//city struct
float Temperature::weatherCalculate2(string city, vector<string> start, vector<string> end)
{
    string startdate = start.at(0) + "/" + start.at(1);
    string enddate = end.at(0) + "/" + end.at(1);

    float total= 0.0;
    float count = 0.0;

    //find city
    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        if(cityMapIt->first->cityName == city)
            break;

    it2 = cityMapIt->first->DateTemps2.find(startdate);

    if(startdate == enddate)
        return it2->second.second;

    while(1==1) {
        if (it2->second.second != 10000)
        {
            total += it2->second.second;
            count += 1.0;
        }

        if (it2->first == enddate)
            break;

        it2 = cityMapIt->first->DateTemps2.find(it2->second.first);
    }

    if(count!=0)
        return total/count;
    else
        return 10000;

}

//Funciton used by option2. It iterates through ever city in the cityMap then every calendear date in the ordered
//DateTemps map. If the temperature of a date is between what the user specified, that becomes the start date.
//Once a temperature is outside of the range, the previous date is the end date. It goes through the year making these
//date ranges for each city.
map <string, map<string, string> > Temperature::dateRanges(string lower, string upper, string unit)
{
    map <string, map<string, string> > rangesMap;

    string startDate = "0";
    string stopDate = "0";

    vector<float> lowHigh = lowerUpper(lower, upper, unit);
    float low = lowHigh.at(0);
    float high = lowHigh.at(1);

    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
    {
        for (inner = cityMapIt->first->DateTemps.begin(); inner != cityMapIt->first->DateTemps.end(); inner++)
        {
            if (inner->second >= low && inner->second <= high && startDate == "0" && inner->second!= 10000)
                startDate = inner->first;

            if ((inner->second < low || inner->second > high || inner->first == "12/31") && startDate != "0"
                && stopDate == "0"  && inner->second !=10000)
            {
                stopDate = inner->first;
                rangesMap[cityMapIt->first->cityName][startDate]=stopDate;
                startDate = "0"; stopDate = "0";
            }

        }
    }
    return rangesMap;
}

//Similar to dateRanges function except it uses the unordered DateTemps2 map
map <string, map<string, string> > Temperature::dateRanges2(string lower, string upper, string unit)
{
    map <string, map<string, string> > rangesMap;
    unordered_map <string, pair<string,float> >::iterator tempIt;

    string startDate = "0";
    string stopDate = "0";

    vector<float> lowHigh = lowerUpper(lower, upper, unit);
    float low = lowHigh.at(0);
    float high = lowHigh.at(1);

    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
    {
        it2 = cityMapIt->first->DateTemps2.find("01/01");

        while(1==1)
        {
            if (it2->second.second >= low && it2->second.second <= high && startDate == "0" && it2->second.second != 10000)
                startDate = it2->first;

            tempIt = cityMapIt->first->DateTemps2.find(it2->second.first);

            if ((tempIt->second.second < low || tempIt->second.second > high ||
                 tempIt->first == "12/31") && startDate != "0" && stopDate == "0"
                && tempIt->second.second !=10000)
            {
                stopDate = it2->first;
                rangesMap[cityMapIt->first->cityName][startDate]=stopDate;
                startDate = "0"; stopDate = "0";
            }

            if(it2->first == "12/31")
                break;

            it2 = cityMapIt->first->DateTemps2.find(tempIt->second.first);

        }
    }

    return rangesMap;
}

//Function used by option3 goes through ever city in CityMap and every calendar date in the ordered DateTemps map to
//calcualte an average temp for the year.
map <string, float> Temperature::yearlyAvg(string lower, string upper, string unit)
{
    vector<float> lowHigh = lowerUpper(lower, upper, unit);
    float low = lowHigh.at(0);
    float high = lowHigh.at(1);

    map <string, float> avgMap;

    float total, count = 0.0;
    float avg = 0.0;

    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
    {
        for (inner = cityMapIt->first->DateTemps.begin(); inner != cityMapIt->first->DateTemps.end(); inner++)
            if (inner->second != 10000)      //Value of 10000 meant nothing was calculated
            {
                total += inner->second;
                count += 1.0;
            }

        if(count != 0.0)
            avg = total/count;

        if(avg>= low && avg<= high)
            avgMap[cityMapIt->first->cityName]=avg;

        total = 0.0; count = 0.0; avg = 0.0;
    }
    return avgMap;
}

//Similar to yearlyAvg except this function uses the onordered DateTemps2 map
map <string, float> Temperature::yearlyAvg2(string lower, string upper, string unit)
{

    vector<float> lowHigh = lowerUpper(lower, upper, unit);
    float low = lowHigh.at(0);
    float high = lowHigh.at(1);

    map <string, float> avgMap;

    float total, count = 0.0;
    float avg = 0.0;

    for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
    {
        for (it2 = cityMapIt->first->DateTemps2.begin(); it2 != cityMapIt->first->DateTemps2.end(); it2++)
            if (it2->second.second != 10000)
            {
                total += it2->second.second;
                count += 1.0;
            }

        if (count != 0.0)
            avg = total / count;

        if (avg >= low && avg <= high)
            avgMap[cityMapIt->first->cityName] = avg;

        total = 0.0;
        count = 0.0;
        avg = 0.0;
    }
    return avgMap;
}
