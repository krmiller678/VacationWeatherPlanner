//All functions needed for the menu options contained here

#include "TemperatureClass.h"

//Function needed only by option 1 to get the user input of MM/DD into the proper format for use. Has it's own
//function since it's called for both the start date and the end date
vector<string> Temperature::dateExtract(string date)
{
    vector<string> datevect;
    string Month;
    Month += date[0];
    Month += date[1];
    datevect.push_back(Month);

    string Day;
    Day += date[3];
    Day += date[4];
    datevect.push_back(Day);

    return datevect;
}


//Function that is called when the user picks option 1 in the program. Displays the list of available cities,
//allows the user to specify the date range and temperature unit, then it displays the predicted, average
//temp for that timeframe. Most of the function is for user interface/input validation. The actual calculations
//occur when it calls the weatherCaculate function.
void Temperature::option1()
{
    string input;
    cout << endl << "Please choose one of the following cities: " << endl;

    //print out every city for the user to choose from
    for(outer = city1.begin(); outer!= city1.end(); outer++)
        cout  << outer->first << " " <<  endl;

    cin >> input;

    while (cityCheck(input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin >> input;
    }

    string city = input;

    cout << endl << "Please enter the start date in the format MM/DD" << endl;
    cin >> input;
    while (dateCheck(input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin >> input;
    }

    vector<string> startDate = dateExtract(input);

    cout << endl << "Please enter the end date in the format MM/DD" << endl;
    cin.clear();
    cin >> input;

    while (dateCheck(input) != 1) {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    vector<string> endDate = dateExtract(input);

    cout << endl << "Enter C for celsius or F for farenheit" << endl;

    cin >> input;

    while (unitcheck(input) != 1) {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string unit = input;
    float weather;
    chrono::duration<double> elapsed, elapsed2;


    if(timer==0)
        weather = weatherCalculate(city, startDate, endDate);

    if(timer==1)
    {
        auto start = std::chrono::high_resolution_clock::now();
        weather = weatherCalculate(city, startDate, endDate);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        start = std::chrono::high_resolution_clock::now();
        weatherCalculate2(city, startDate, endDate);
        end = std::chrono::high_resolution_clock::now();
        elapsed2 = end - start;
    }

    if(weather == 10000.0)
    {
        cout << endl << "Unforunately there isn't historical data available to be able to calculate the " <<
             "predicted average temperature for ";
        if(startDate == endDate)
            cout << "this date" << endl;
        else
            cout << "this date range" << endl;

        cout << "Would you like to try again? (press y and enter or n and enter)" << endl;

        cin >> input;

        while (input != "y" && input != "n")
        {
            cout << "Please type y or n and press enter" << endl;
            cin >> input;
        }

        if(input == "y")
            option1();

        return;

    }

    string val = finalTemp(weather, unit);

    cout << endl << "The predicted, average temperature in " << city;
    if (startDate != endDate)
        cout << " for " << startDate.at(0) << "/" << startDate.at(1) << " to "
             << endDate.at(0) << "/" << endDate.at(1);
    else
        cout << " on " << startDate.at(0) << "/" << startDate.at(1);

    cout << " is " << val << " degrees " << unit << endl;


    if(timer==1)
        winner(elapsed, elapsed2);

}

//Function that is called when the user picks option 2 in the program. The user specifies the temperature unit, and the
//min/max of the range of their desired temperature. Most of the function is for user interface/input validation.
//The actual calculations occur when it calls the dateRanges function.
void Temperature::option2()
{
    string input;

    cout << endl << "Please specify the temperature unit (type C or F and press enter)" << endl;

    cin >> input;

    while (unitcheck(input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string unit = input;

    cout << endl << "What is the lower end of your ideal, average temperature (enter 1 to 2 digits"
                    " and press enter)" << endl;

    cin >> input;

    while (tempCheck(input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string lower = input;

    cout << endl << "What is the upper end of your ideal, average temperature (enter 1 to 2 digits"
                    " and press enter)" << endl;

    cin >> input;

    while (tempCheck(input) != 1 || upperCheck(lower, input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string upper = input;

    map <string, map<string, string> > rangesMap;
    map <string, map<string, string> > ::iterator rangeOuter;
    map<string, string> ::iterator rangeInner;

    chrono::duration<double> elapsed, elapsed2;

    if(timer==0)
        rangesMap = dateRanges(lower, upper, unit);

    if(timer==1)
    {
        auto start = std::chrono::high_resolution_clock::now();
        rangesMap = dateRanges(lower, upper, unit);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        start = std::chrono::high_resolution_clock::now();
        dateRanges2(lower, upper, unit);
        end = std::chrono::high_resolution_clock::now();
        elapsed2 = end - start;
    }

    if(rangesMap.empty())
    {
        cout << endl << "There are no cities with temperatures between your desired range at any point" <<
             " during the year. Would you like to readjust the range? (press y and enter to try " <<
             "again or press n and enter to continue)" << endl << endl;

        cin >> input;

        while (input != "y" && input != "n")
        {
            cout << "Please type y or n and press enter" << endl;
            cin >> input;
        }

        if(input == "y")
            option2();
    }
    else
    {
          cout << endl << "The following cities with the following date ranges will be within" <<
        " your acceptable temperature range: " << endl << endl;
        
        for (rangeOuter = rangesMap.begin(); rangeOuter != rangesMap.end(); rangeOuter++) {
            cout << rangeOuter->first << ": ";
            for (rangeInner = rangeOuter->second.begin(); rangeInner != rangeOuter->second.end(); rangeInner++)
                if (rangeInner->first == rangeInner->second)
                    cout << rangeInner->first << " ";
                else
                    cout << rangeInner->first << "-" << rangeInner->second << " ";

            cout << endl;
        }

        if (timer == 1)
            winner(elapsed, elapsed2);
    }

}

//Function that is called when the user picks option 3 in the program. The user specifies the temperature unit, and the
//min/max of the range of their desired temperature. Most of the function is for user interface/input validation.
//The actual calculations occur when it calls the yearlyAvg function.
void Temperature::option3()
{
    string input;
    cout << endl << "Please specify the temperature unit (type C or F and press enter)" << endl;

    cin >> input;

    while (unitcheck(input) != 1) {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string unit = input;

    cout << endl << "What is the lower end of your ideal, yearly average temperature (enter 1 to 2 digits"
                    " and press enter)" << endl;

    cin >> input;

    while (tempCheck(input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string lower = input;

    cout << endl << "What is the upper end of your ideal, yearly average temperature (enter 1 to 2 digits"
                    " and press enter)" << endl;

    cin >> input;

    while (tempCheck(input) != 1 || upperCheck(lower, input) != 1)
    {
        cout << endl << "Please try again:" << endl;
        cin.clear();
        cin >> input;
    }

    string upper = input;

    map <string, float> avgMap;
    map <string, float>::iterator it;

    chrono::duration<double> elapsed, elapsed2;

    if(timer==0)
        avgMap = yearlyAvg(lower, upper, unit);

    if(timer==1)
    {
        auto start = std::chrono::high_resolution_clock::now();
        avgMap = yearlyAvg(lower, upper, unit);
        auto end = std::chrono::high_resolution_clock::now();
        elapsed = end - start;

        start = std::chrono::high_resolution_clock::now();
        yearlyAvg2(lower, upper, unit);
        end = std::chrono::high_resolution_clock::now();
        elapsed2 = end - start;
    }

    if(avgMap.empty())
    {
        cout << endl << "There are no cities with a yearly, average temperature" <<
             " within the range you specified. Would " << endl << "you like to " <<
             "readjust the range? (press y and enter to try again or press n and enter to continue)" << endl;

        cin >> input;

        while (input != "y" && input != "n")
        {
            cout << endl << "Please type y or n and press enter" << endl;
            cin >> input;
        }

        if(input == "y")
            option3();
    }
    else {
        cout << "The following cities have a yearly, average temperature in your" <<
             " specified range:" << endl;

        for (it = avgMap.begin(); it != avgMap.end(); it++)
            cout << it->first << " " << finalTemp(it->second, unit) << " " << unit << endl;

        if (timer == 1)
            winner(elapsed, elapsed2);
    }

}

//This function will allow the user to input y/n to turn on/off the private timer variable. The timer variable is
//located in the 3 option functions and when turned on, it runs a system timer on the already in use ordered temperature map
//and also now runs the unordered temperature map with a system timer. It then allows display of the time results using both types
void Temperature::option4()
{
    string input2;

    cout << endl << "Type y to display data structure comparison or n to turn it off" << endl;

    cin >> input2;

    while(input2 != "y" && input2 != "n")
    {
        cout << "Please type y or n and press enter" << endl;
        cin >> input2;
    }

    if(input2 == "y")
    {
        timer = 1;
        cout << endl << "Data structure comparison will now be displayed"  << endl;
    }
    else
    {
        timer = 0;
        cout << endl << "Data structure comparison will no longer be displayed" << endl << endl;
    }
}
