#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <chrono>
#include <vector>
using namespace std;

class Weather
{
private:

    struct city
    {
        string cityName;
        map <string, float> DateTemps;

        city(string name)
        {this->cityName = name;}
    };

    map <city*, string> cityMap;
    map <city*, string>::iterator cityMapIt;

    unordered_map <string, map <string, float> > newCity;
    unordered_map <string, map <string, float> > city1;
    unordered_map <string, map <string, float> >::iterator outer;
    map <string, float>::iterator inner;
    multimap <string, string> calendar;
    multimap <string, string>::iterator cal;

public:

//Function to create a calendar. Only needs the first country and first year in the dataset to work.
//Leap years are not being used in this project for simplicity reasons
    void calendarMaker()
    {
        outer = city1.find("Algiers");
        inner = outer->second.begin();

            for(inner = outer->second.begin(); inner->first.substr(0,4) == "1995"; inner++)
            calendar.insert(pair<string, string>(inner->first.substr(5, 2), inner->first.substr(8, 2)));
    }

//Helper function to display the calendar
    void printCalendar()
    {
        for(cal = calendar.begin(); cal!= calendar.end(); cal++)
             cout  << cal->first << "/" <<  cal->second << endl;
    }

//Function devoted to reading in the file. It first puts every line into a vector and then
//put every delimited element into the next vector
    vector <string> fileExtraction()
    {
        ifstream f("city_temperature.csv");

        string s;
        vector <string> inputVect;
        vector <string> inputVect2;

         while (getline(f, s))
            inputVect.push_back(s);

        for(int i=0; i<inputVect.size();i++)
            for(int j = 0; inputVect.at(i)[j]!= '\0'; j++)
                if(inputVect.at(i)[j]==',' && inputVect.at(i)[j+1]==',')
                    inputVect2.push_back(inputVect.at(i).substr(j+2));

        f.close();

        return inputVect2;
    }


    void mapMaker(vector <string> input)
    {
        string word;
        string city,month,date,year, fulldate, temp;
        vector <string> words;

        for(int i=0; i<input.size();i++)
            {
            for(int j = 0; j<input.at(i).length(); j++)
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

    void print()
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            {
            inner = outer->second.begin();
            for(inner = outer->second.begin(); inner!= outer->second.end(); inner++)
                cout  << outer->first << " " <<  inner->first << " " << inner->second << endl;
            }
    }

    void nodeMaker()
    {
        float total = 0;
        float find = 0;

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
                    if(find != 0)
                        citypoint->DateTemps[cal->first + "/" + cal->second] = total / find;
                    else
                        citypoint->DateTemps[cal->first + "/" + cal->second] = 200.0; //200 means nothing as calculated
                    total = 0;
                    find = 0;
                }
            cityMap[citypoint];
        }
    }

    void printCityName()
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            cout  << outer->first << " " <<  endl;
    }

    void printCityMap()
    {
        for(cityMapIt = cityMap.begin(); cityMapIt!= cityMap.end(); cityMapIt++)
            for(inner = cityMapIt->first->DateTemps.begin();
                    inner!= cityMapIt->first->DateTemps.end(); inner++)
                cout << cityMapIt->first->cityName << " " << inner->first << " " << inner->second << endl;
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
        map <string, float>::iterator it;

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

    //Called when the user is asked to input a city name. The inputed city has to match one that's available from the
    //dataset
    bool cityCheck(string input)
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            if(input == outer->first)
                return true;

        return false;
    }

//Called when the user is asked to input start and stop dates for their visit. Makes sure the date
//is in the proper format
    bool dateCheck(string input)
    {
        if(input.length()!=5)
            return false;

        char one = input[0];
        char two = input[1];
        char three = input[2];
        char four = input[3];
        char five = input[4];

        if(isdigit(one) && isdigit(two) && three=='/' && isdigit(four) && isdigit(five))
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
                    //cout << inner->first << endl;
                    //cout << inner->second << endl;
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
};

int main() {

    Weather w;

    vector <string> preInput = w.fileExtraction();
    w.mapMaker(preInput);
    w.calendarMaker();
    w.nodeMaker();
    //w.printCityMap();
   // w.printCalendar();
 // w.print();
  // for(int i=0; i<preInput.size();i++)
      //  cout << preInput.at(i) << endl;

    string input = "0";
    int timer = 0;

    cout << "Welcome to Temp Planner" << endl;
    cout << "Press Enter to Continue" << endl;

    while(1==1) {

        cin.ignore();

        //cout << "Flushing the output stream." << flush;
        //system("clear");

        string input;
        string input2;

        cout << "Please choose one of the following: " << endl;
        cout << "There is somewhere I want to go (type 1 and press enter): " << endl;
        cout << "I want to visit somewhere with a certain weather (type 2 and press enter): " << endl;
        cout << "I want to move somewhere with a certain weather (type 3 and press enter): " << endl;
        cout << "Technical specifications mode (type 4 and press enter): " << endl;
        cout << "Quit (type 5 and press enter): " << endl;

        cin >> input;

        while (input != "1" && input != "2" && input != "3" && input != "4" && input != "5") {
                cout << "Please type 1, 2, 3, 4 or 5 and press enter" << endl;
                cin >> input;
        }

        if (input == "5")
            break;

        if (input == "4")
        {
            cout << "Display Timer? (type 1 and press enter)" << endl;
            cout << "Specify algorithm? (type 2 and press enter)" << endl;
            cout << "Show dataset? (type 3 and press enter)" << endl;

            cin >> input2;

            while (input2 != "1" && input2 != "2" && input2 != "3") {
                cout << "Please type 1, 2 or 3 and press enter" << endl;
                cin >> input2;
            }
            if(input2 == "1")
                timer = 1;
        }

        if (input == "1")
        {
            cout << "Please choose one of the following cities: " << endl;
            w.printCityName();
            cin >> input;

            while (w.cityCheck(input) != 1) {
                cout << "Please try again:" << endl;
                cin >> input;
            }

            string city = input;

            cout << "Please enter the start date in the format MM/DD" << endl;
            cin >> input;
            while (w.dateCheck(input) != 1) {
                cout << "Please try again:" << endl;
                cin >> input;
            }

            vector<string> startDate = w.dateExtract(input);

            cout << "Please enter the end date in the format MM/DD" << endl;
            cin.clear();
            cin >> input;
            while (w.dateCheck(input) != 1) {
                cout << "Please try again:" << endl;
                cin.clear();
                cin >> input;
            }

            vector<string> endDate = w.dateExtract(input);

            cout << "Enter C for celsius or F for farenheiht" << endl;

            cin >> input;

            while (w.unitcheck(input) != 1) {
                cout << "Please try again:" << endl;
                cin.clear();
                cin >> input;
            }

            string unit = input;

            auto start = std::chrono::high_resolution_clock::now();

            float weather = w.weatherCalculate(city, startDate, endDate);

            auto end = std::chrono::high_resolution_clock::now();

            string val = w.finalTemp(weather, unit);

            cout << "The predicted, average temperature in " << city << " for "
                 << startDate.at(0) << "/" << startDate.at(1) << " to "
                 << endDate.at(0) << "/" << endDate.at(1) << " is " <<
                val << " degrees " << unit << endl << endl;

            if(timer==1) {
                std::chrono::duration<double> elapsed = end - start;
                cout << "Runtime: " << elapsed.count() << " seconds" << endl << endl;
            }
        }

        if (input == "3")
        {
            cout << endl << "Please specify the temperature unit (type C or F and press enter)" << endl;

            cin >> input;

            while (w.unitcheck(input) != 1)
            {
                cout << "Please try again:" << endl;
                cin.clear();
                cin >> input;
            }

            string unit = input;

            cout << "What is the lower end of your ideal, yearly average temperature (enter 1 to 3 digits"
                            " and press enter)" << endl;

            cin >> input;

            while (w.tempCheck(input) != 1)
            {
                cout << "Please try again:" << endl;
                cin.clear();
                cin >> input;
            }

            string lower = input;

            cout << "What is the upper end of your ideal, yearly average temperature (enter 1 to 3 digits"
                            " and press enter)" << endl;

            cin >> input;

            while (w.tempCheck(input) != 1)
            {
                cout << "Please try again:" << endl;
                cin.clear();
                cin >> input;
            }

            string upper = input;

            map <string, float> avgMap;
            map <string, float>::iterator it;

            avgMap = w.yearlyAvg(lower, upper, unit);

            if(avgMap.empty())
            {
                cout << "There are no cities with a yearly, average temperature" <<
                     " within the range you specified. Would " << endl << "you like to " <<
                     "readjust the range? (press y and enter or press n and enter to continue)" << endl;

                //need input here
            }

            else
                cout << "The following cities have a yearly, average temperature in your" <<
                " specified range:" << endl;

            for(it = avgMap.begin(); it!= avgMap.end(); it++)
                cout << it->first << " " << w.finalTemp(it->second, unit) << " " << unit << endl;

            cout << endl;
    }
        cout << "Return to main menu? (please type y or n and press enter)" << endl;

        cin >> input;

        while (input != "y" && input != "n")
        {
            cout << "Please type y or n and press enter" << endl;
            cin >> input;
        }

        if(input == "n")
            break;
    }

    cout << endl << "Thank you for using our app! Have a great day!";

    return 0;
}
