//Functions devoted to input validation

#include "TemperatureClass.h"

//################################## INPUT VALIDATION FUNCTIONS #################################

//Called when the user is asked to input a city name. The inputted city has to match one that's available from the
//dataset
bool Temperature::cityCheck(string input)
{
    for(outer = city1.begin(); outer!= city1.end(); outer++)
        if(input == outer->first)
            return true;

    return false;
}

//Called when the user is asked to input start and stop dates for their visit. Makes sure the date
//is in the proper format. Must be 2 digits, a forward slash and another 2 digits. It then checks to make
//sure the start dates and stop dates are in the calendar
bool Temperature::dateCheck(string input)
{
    if(input.length()!=5)
        return false;

    if(!isdigit(input[0]) || !isdigit(input[1]) || input[2]!='/' || !isdigit(input[3])
       || !isdigit(input[4]))
        return false;

    string startdate = input.substr(0,2);
    string enddate = input.substr(3,2);

    for(cal = calendar.begin(); cal!= calendar.end(); cal++)
        if(cal->first == startdate && cal->second == enddate)
            return true;

    return false;
}

//Called to check user input when user is prompted to choose celsius or farenheit as the temperature unit
bool Temperature::unitcheck(string input)
{
    if(input != "C" && input != "F")
        return false;

    return true;
}

//Called to check user input when user is prompted to enter a temperature. Temperature must
//be between 1 to 2 digits and every character must be a digit. Accounts for negative temps
bool Temperature::tempCheck(string input)
{
    int start = 0;
    int length = input.length();

    if(input.at(0)=='-')
    {
        length = input.length()-1;
        start = 1;
    }

    if(length <= 0 || length > 2)
        return false;

    for(int i=start; i<input.length();i++)
        if(!isdigit(input.at(i)))
            return false;

    return true;
}

//Called when user has to input a max temp for the temp range in options 1 and 2. If the max is less than the min,
//they need to try again
bool Temperature::upperCheck(string min, string max)
{
    if(stoi(min) > stoi(max))
        return false;

    return true;
}

