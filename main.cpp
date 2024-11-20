#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <string>
using namespace std;

class Weather
{
private:

//City struct represent a city and has 2 maps to store the average, daily temperature for every day of the year. Accessing
//these different maps is what will be compared for the 2 different data structures
    struct city
    {
        string cityName;
        map <string, float> DateTemps;
        unordered_map <string, pair<string,float> > DateTemps2;

        city(string name)
        {this->cityName = name;}
    };

    int timer = 0;
    int fileRows = 0;

    map <city*, string> cityMap;
    map <city*, string>::iterator cityMapIt;

    map <string, map <string, float> > city1;
    map <string, map <string, float> >::iterator outer;
    map <string, float>::iterator inner;

    unordered_map <string, pair<string,float> >::iterator it2;

    multimap <string, string> calendar;
    multimap <string, string>::iterator cal;

public:

//###########################    SETUP FUNCTIONS ################################################

//Function to create a calendar. Only needs the first country and first year in the dataset to work.
//Leap years are not being used in this project for simplicity reasons
    void calendarMaker()
    {
        outer = city1.find("Algiers");
        inner = outer->second.begin();

        for(inner = outer->second.begin(); inner->first.substr(0,4) == "1995"; inner++)
            calendar.insert(pair<string, string>(inner->first.substr(5, 2), inner->first.substr(8, 2)));
    }

//Function devoted to reading in the file. It first puts every line into a vector and then puts every delimited element
//into another next vector
    vector <string> fileExtraction()
    {
        ifstream f("city_temperature.csv");

        string s;
        vector <string> inputVect;
        vector <string> inputVect2;

        while (getline(f, s))
            inputVect.push_back(s);

        fileRows = inputVect.size();

        for(int i=0; i<inputVect.size();i++)
            for(int j = 0; inputVect.at(i)[j]!= '\0'; j++)
                if(inputVect.at(i)[j]==',' && inputVect.at(i)[j+1]==',')
                    inputVect2.push_back(inputVect.at(i).substr(j+2));

        f.close();

        return inputVect2;
    }

//Initializes the city1 ordered map where the key is a distinct city found from the csv file and the value is
//another ordered map where the key is a distinct historical date and it's value is the temperature on that day.
//Most of the function is devoted to getting the full date in the proper format from the csv
    void mapMaker(vector <string> input)
    {
        string word;
        string city,month,date,year, fulldate, temp;
        vector <string> words;

        for(int i=0; i < input.size(); i++)
        {
            for(int j = 0; j < input.at(i).length(); j++)
            {
                if(input.at(i)[j]==',')
                {
                    words.push_back(word);
                    word.clear();
                    continue;
                }
                word+=input.at(i)[j];
            }
            word.erase(word.size() - 1);
            words.push_back(word);
            word.clear();
            city = words.at(0);

            if(words.at(1).size()==1)
                month = "0" + words.at(1);
            else month = words.at(1);

            if(words.at(2).size()==1)
                date= "0" + words.at(2);
            else date = words.at(2);

            year= words.at(3);
            temp= words.at(4);
            words.clear();

            fulldate += year + "-" + month + "-" + date;

            city1[city][fulldate]=stof(temp);

            fulldate.clear();
        }
    }

//For each city and every date, this function calculates the average temperature for a date for every year in the past.
//
    void nodeMaker()
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
                    if (cal->first == inner->first.substr(5, 2)
                        && cal->second == inner->first.substr(8, 2))
                    {
                        if(inner->second != -99)
                        {
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
                    //initialize the ordered map in city struct
                    citypoint->DateTemps[cal->first + "/" + cal->second] = total / find;
                    citypoint->DateTemps2[date]= make_pair(nextdate, total / find);
                }
                else
                {
                    citypoint->DateTemps[cal->first + "/" + cal->second] = 200.0; //200 means nothing as calculated
                    citypoint->DateTemps2[date]= make_pair(nextdate, 200.0);
                }


                total = 0;
                find = 0;
            }
            cityMap[citypoint];
        }
    }

//###########################    CALCULATION FUNCTIONS ################################################

//Function used by option 1 that will take in the destination, start and end date of someone's trip. It will then
//find the city and look up the temperatures between those dates and return the average. This function accesses
//the ordered map in the city struct
    float weatherCalculate(string city, vector<string> start, vector<string> end)
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
        for(inner = cityMapIt->first->DateTemps.begin();
            inner!= cityMapIt->first->DateTemps.end(); inner++)
            if(startdate==inner->first)
                break;

        while(1==1)
        {
            if(inner->second != 200 && inner->first!=enddate)
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
                if(inner->second != 200)
                {
                    total += inner->second;
                    count += 1.0;
                }
                break;
            }
        }
        return total/count;
    }

//This function does the same thing as weatherCalculate except it accesses the unordered map of daily temperatures in the
//city struct
    float weatherCalculate2(string city, vector<string> start, vector<string> end)
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
        it2 = cityMapIt->first->DateTemps2.find(startdate);

        while(1==1) {
            if (it2->second.second != 200)
            {
                total += it2->second.second;
                count += 1.0;
            }

            if (it2->first == enddate)
                break;

            it2 = cityMapIt->first->DateTemps2.find(it2->second.first);
        }

        return total/count;
    }

    map <string, float> yearlyAvg(string lower, string upper, string unit)
    {
        float low = stof(lower);
        float high = stof(upper);

        if(unit=="F")
        {
            low = (low - 32) / 1.8;
            high = (high - 32) / 1.8;
        }

        map <string, float> avgMap;

        float total, count = 0.0;
        float avg = 0.0;

        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        {
            for (inner = cityMapIt->first->DateTemps.begin(); inner != cityMapIt->first->DateTemps.end(); inner++)
                if (inner->second != 200)
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

    map <string, float> yearlyAvg2(string lower, string upper, string unit)
    {
        float low = stof(lower);
        float high = stof(upper);

        if(unit=="F")
        {
            low = (low - 32) / 1.8;
            high = (high - 32) / 1.8;
        }

        map <string, float> avgMap;

        float total, count = 0.0;
        float avg = 0.0;

        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        {
            for (it2 = cityMapIt->first->DateTemps2.begin(); it2 != cityMapIt->first->DateTemps2.end(); it2++)
                if (it2->second.second != 200)
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

    map <string, map<string, string> > dateRanges(string lower, string upper, string unit)
    {

        map <string, map<string, string> > rangesMap;

        float low = stof(lower);
        float high = stof(upper);

        string startDate = "0";
        string stopDate = "0";

        if(unit=="F")
        {
            low = (low - 32) / 1.8;
            high = (high - 32) / 1.8;
        }

        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        {
            for (inner = cityMapIt->first->DateTemps.begin(); inner != cityMapIt->first->DateTemps.end(); inner++)
            {
                if (inner->second >= low && inner->second <= high && startDate == "0" && inner->second!= 200)
                    startDate = inner->first;

                if ((inner->second < low || inner->second > high || inner->first == "12/31") && startDate != "0" && stopDate == "0"
                    && inner->second !=200)
                {
                    inner--;
                    stopDate = inner->first;
                    inner++;
                    rangesMap[cityMapIt->first->cityName][startDate]=stopDate;
                    startDate = "0"; stopDate = "0";
                }
            }
        }
        return rangesMap;

    }

    map <string, map<string, string> > dateRanges2(string lower, string upper, string unit)
    {
        map <string, map<string, string> > rangesMap;
        unordered_map <string, pair<string,float> >::iterator tempIt;

        float low = stof(lower);
        float high = stof(upper);

        string startDate = "0";
        string stopDate = "0";

        if(unit=="F")
        {
            low = (low - 32) / 1.8;
            high = (high - 32) / 1.8;
        }

        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
        {
            it2 = cityMapIt->first->DateTemps2.find("01/01");

            while(1==1)
            {
                if (it2->second.second >= low && it2->second.second <= high && startDate == "0" && it2->second.second != 200)
                    startDate = it2->first;

                tempIt = cityMapIt->first->DateTemps2.find(it2->second.first);

                if ((tempIt->second.second < low || tempIt->second.second > high ||
                     tempIt->first == "12/31") && startDate != "0" && stopDate == "0"
                    && tempIt->second.second !=200)
                {
                    stopDate = it2->first;
                    rangesMap[cityMapIt->first->cityName][startDate]=stopDate;
                    startDate = "0"; stopDate = "0";
                }

                if(it2->first == "12/31")
                    break;

                //  it2 = cityMapIt->first->DateTemps2.find(it2->second.first);
                it2 = cityMapIt->first->DateTemps2.find(tempIt->second.first);
                // it2 = cityMapIt->first->DateTemps2.find(tempIt->second.first);
            }
        }

        return rangesMap;
    }

//################################## INPUT VALIDATION FUNCTIONS #################################

//Called when the user is asked to input a city name. The inputted city has to match one that's available from the
//dataset
    bool cityCheck(string input)
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            if(input == outer->first)
                return true;

        return false;
    }

//Called when the user is asked to input start and stop dates for their visit. Makes sure the date
//is in the proper format. Must be 2 digits, a forward slash and another 2 digits. It then checks to make
//sure the start dates and stop dates are in the calendar
    bool dateCheck(string input)
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
    bool unitcheck(string input)
    {
        if(input != "C" && input != "F")
            return false;

        return true;
    }

//Called to check user input when user is prompted to enter a temperature. Temperature must
//be between 1 to 3 digits and every character must be a digit
    bool tempCheck(string input)
    {
        if(input.length()<=0 || input.length() > 3)
            return false;

        for(int i=0; i<input.length();i++)
            if(!isdigit(input.at(i)))
                return false;

        return true;
    }

//Converts temperature to farenheit if needed and then puts the temperature in the final format for display
    string finalTemp(float weather, string input)
    {
        if(input == "F")
            weather = (weather * 1.8) + 32.0;

        weather = (weather * 100 + 0.5)/100;
        string val = to_string(weather);

        if(val.find(".")==3)
            val = val.substr(0,5);
        else
            val = val.substr(0,4);

        return val;
    }

//Function needed only by option 1 to get the user input of MM/DD into the proper format for use. Has it's own
//function since it's called for both the start date and the end date
    vector<string> dateExtract(string date)
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

//Needed to display the results of the time differences between using the ordered vs. unordered temperature maps
//in the city structt
    void winner(chrono::duration<double> elapsed, chrono::duration<double> elapsed2)
    {

        cout << "Runtime with ordered map: " << elapsed.count() << " seconds" << endl;
        cout << "Runtime with unordered map: " << elapsed2.count() << " seconds" << endl;
        if(elapsed.count() < elapsed2.count())
            cout << "Ordered map wins!" << endl;
        else
            cout << "Unordered map wins!" << endl << endl;
    }

//################################ OPTION FUNCTIONS ###############################################


//Function that is called when the user picks option 1 in the program. Displays the list of available cities,
//allows the user to specify the date range and temperature unit, then it displays the predicted, average
//temp for that timeframe
    void option1(string input)
    {
        cout << endl << "Please choose one of the following cities: " << endl;

        //print out every city for the user to choose from
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            cout  << outer->first << " " <<  endl;

        cin >> input;

        while (cityCheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin >> input;
        }

        string city = input;

        cout << endl << "Please enter the start date in the format MM/DD" << endl;
        cin >> input;
        while (dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin >> input;
        }

        vector<string> startDate = dateExtract(input);

        cout << endl << "Please enter the end date in the format MM/DD" << endl;
        cin.clear();
        cin >> input;

        while (dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        vector<string> endDate = dateExtract(input);

        cout << endl << "Enter C for celsius or F for farenheit" << endl;

        cin >> input;

        while (unitcheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string unit = input;

        auto start = std::chrono::high_resolution_clock::now();
        float weather = weatherCalculate(city, startDate, endDate);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed = end - start;

        start = std::chrono::high_resolution_clock::now();
        weatherCalculate2(city, startDate, endDate);
        end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> elapsed2 = end - start;

        string val = finalTemp(weather, unit);

        cout << endl << "The predicted, average temperature in " << city << " for "
             << startDate.at(0) << "/" << startDate.at(1) << " to "
             << endDate.at(0) << "/" << endDate.at(1) << " is " <<
             val << " degrees " << unit << endl << endl;

        if(timer==1)
            winner(elapsed, elapsed2);

    }

    void option2(string input)
    {
        cout << endl << "Please specify the temperature unit (type C or F and press enter)" << endl;

        cin >> input;

        while (unitcheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string unit = input;

        cout << "What is the lower end of your ideal, average temperature (enter 1 to 3 digits"
                " and press enter)" << endl;

        cin >> input;

        while (tempCheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string lower = input;

        cout << "What is the upper end of your ideal, average temperature (enter 1 to 3 digits"
                " and press enter)" << endl;

        cin >> input;

        while (tempCheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string upper = input;

        map <string, map<string, string> > rangesMap;
        map <string, map<string, string> > ::iterator rangeOuter;
        map<string, string> ::iterator rangeInner;

        std::chrono::duration<double> elapsed, elapsed2;

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
            cout << "There are no cities with temperatures between your desired range at any point" <<
                 " during the year" << endl << endl;
            return;
        }

        for(rangeOuter = rangesMap.begin(); rangeOuter!= rangesMap.end(); rangeOuter++) {
            cout << rangeOuter->first << ": ";
            for (rangeInner = rangeOuter->second.begin(); rangeInner != rangeOuter->second.end(); rangeInner++)
                if(rangeInner->first == rangeInner->second)
                    cout << rangeInner->first << " ";
                else
                    cout << rangeInner->first << "-" << rangeInner->second << " ";

            cout << endl;
        }

        if(timer==1)
            winner(elapsed, elapsed2);

    }

    void option3(string input)
    {
        cout << endl << "Please specify the temperature unit (type C or F and press enter)" << endl;

        cin >> input;

        while (unitcheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string unit = input;

        cout << "What is the lower end of your ideal, yearly average temperature (enter 1 to 3 digits"
                " and press enter)" << endl;

        cin >> input;

        while (tempCheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string lower = input;

        cout << "What is the upper end of your ideal, yearly average temperature (enter 1 to 3 digits"
                " and press enter)" << endl;

        cin >> input;

        while (tempCheck(input) != 1)
        {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        string upper = input;

        map <string, float> avgMap;
        map <string, float>::iterator it;

        std::chrono::duration<double> elapsed, elapsed2;

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
            cout << "There are no cities with a yearly, average temperature" <<
                 " within the range you specified. Would " << endl << "you like to " <<
                 "readjust the range? (press y and enter or press n and enter to continue)" << endl;
        }

        else
            cout << "The following cities have a yearly, average temperature in your" <<
                 " specified range:" << endl;

        for(it = avgMap.begin(); it!= avgMap.end(); it++)
            cout << it->first << " " << finalTemp(it->second, unit) << " " << unit << endl;

        cout << endl;

        if(timer==1)
            winner(elapsed, elapsed2);

    }

    void option4()
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
            cout << endl << "Data structure comparison will now be displayed" << endl << endl;
        }
        else
        {
            timer = 0;
            cout << endl << "Data structure comparison will no longer be displayed" << endl << endl;
        }
    }

    string mainMenu()
    {
        string input;
        cout << endl << "Please choose one of the following: " << endl;
        cout << "There is somewhere I want to go (type 1 and press enter): " << endl;
        cout << "I want to visit somewhere with a certain weather (type 2 and press enter): " << endl;
        cout << "I want to move somewhere with a certain weather (type 3 and press enter): " << endl;
        cout << "Data structure comparison display mode (type 4 and press enter): " << endl;
        cout << "Quit (type 5 and press enter): " << endl;

        cin >> input;

        while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5")
        {
            cout << "Please type 1, 2, 3, 4 or 5 and press enter" << endl;
            cin >> input;
        }
        return input;
    }

    string mainMenuReturn()
    {
        string input;

        cout << "Return to main menu? (please type y or n and press enter)" << endl;

        cin >> input;

        while (input != "y" && input != "n")
        {
            cout << "Please type y or n and press enter" << endl;
            cin >> input;
        }

        return input;

    }
//##########################   HELPER FUNCTIONS  ####################################

//Helper function that prints every city along with every unique date and temperature for that date that was found in the
//csv file
    void printCityData()
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
        {
            inner = outer->second.begin();
            for(inner = outer->second.begin(); inner!= outer->second.end(); inner++)
                cout  << outer->first << " " <<  inner->first << " " << inner->second << endl;
        }
    }

    //Helper function to display the calendar
    void printCalendar()
    {
        for(cal = calendar.begin(); cal!= calendar.end(); cal++)
            cout  << cal->first << "/" <<  cal->second << endl;
    }

//Helper function to see every city and it's daily average weather for the year. This function access the ordered map
//in the city struct
    void printCityMap()
    {
        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
            for(inner = cityMapIt->first->DateTemps.begin();
                inner!= cityMapIt->first->DateTemps.end(); inner++)
                cout << cityMapIt->first->cityName << " " << inner->first << " " << inner->second << endl;

    }

//Helper function to see every city and it's daily average weather for the year. This function access the unordered map
//in the city struct
    void printCityMap2()
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


};

int main() {

    Weather w;

    vector <string> preInput = w.fileExtraction();
    w.mapMaker(preInput);
    w.calendarMaker();
    w.nodeMaker();

    string input;

    cout << "Welcome to Temperature Planner!" << endl;
    cout << "Press enter to continue" << endl;

    while(1==1)
    {
        cin.ignore();

        input = w.mainMenu();

        if (input == "1")
            w.option1(input);

        if (input == "2")
            w.option2(input);

        if (input == "3")
            w.option3(input);

        if (input == "4")
            w.option4();

        if (input == "5" || w.mainMenuReturn() == "n")
            break;
    }

    cout << endl << "Thank you for using our app! Have a great day!";

    return 0;
}
