#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
#include <iomanip>
using namespace std;

class Weather
{
private:

    struct city{
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

    //  The months which have 31 days are January, March, May, July, August, October, and
    // December. The months which have 30 days are April, June, September, and November.

    void calendarMaker()
    {
        string month;
        string date;

        int j = 1;

        while (j< 13)
        {
            if (j == 1 || j == 3 || j == 5 || j == 7 || j == 8 || j == 10 || j == 12)
            {
                for (int i = 1; i <= 31; i++)
                {
                    if (j < 10)
                    {
                        month += "0";
                        month += to_string(j);
                    }
                    else month = to_string(j);

                    if (i < 10)
                    {
                        date += "0";
                        date += to_string(i);
                    }
                    else date = to_string(i);
                    calendar.insert(pair<string, string>(month, date));
                    month.clear();
                    date.clear();
                }
                j++;
            }

            if (j == 4 || j == 6 || j == 9 || j == 11)
            {
                for (int i = 1; i <= 30; i++)
                {
                    if (j < 10)
                    {
                        month += "0";
                        month += to_string(j);
                    } else month = to_string(j);

                    if (i < 10)
                    {
                        date += "0";
                        date += to_string(i);
                    }
                    else date = to_string(i);
                    calendar.insert(pair<string, string>(month, date));
                    month.clear();
                    date.clear();
                }
                j++;
            }

            if(j==2)
            {
                for (int i = 1; i <= 28; i++)
                {
                    if (i < 10)
                    {
                        date += "0";
                        date += to_string(i);
                    }
                    else date = to_string(i);

                    calendar.insert(pair<string, string>("02", date));
                    date.clear(); month.clear();
                }
                j++;
            }
        }
    }
    void printCalendar()
    {
        for(cal = calendar.begin(); cal!= calendar.end(); cal++)
             cout  << cal->first << "/" <<  cal->second << endl;
    }

    vector <string> inputExtraction()
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
        int count;

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

                        if(temp!="-99")
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
           { cout  << outer->first << " " <<  inner->first << " " << inner->second << endl;

               }

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
                            total += inner->second;
                            find += 1.0;
                        }
                    }
                    if(find != 0)
                    citypoint->DateTemps[cal->first + "/" + cal->second] = total / find;
                    else
                       citypoint->DateTemps[cal->first + "/" + cal->second] = 200.0;
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

    bool cityCheck(string input)
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            if(input == outer->first)
                return true;

        return false;
    }

    bool dateCheck(string input)
    {
        if(input.length()!=5)
            return false;

        char one = input[0];
        char two = input[1];
        char three = input[2];
        char four = input[3];
        char five = input[4];

        if(isdigit(one) && isdigit(two) && three=='/' && isdigit(four)
        && isdigit(five))
            return true;

        return false;
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

        //FIND startdate

        for(inner = cityMapIt->first->DateTemps.begin();
            inner!= cityMapIt->first->DateTemps.end(); inner++)
            if(startdate==inner->first)
                break;

            while(1==1)
            {
                if(inner->second != 200 && inner->first!=enddate)
                {
                  //  cout << inner->first << endl;
                  //  cout << inner->second << endl;
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

    vector<string> dateExtract(string date) {

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

    vector <string> preInput = w.inputExtraction();
    w.mapMaker(preInput);
    w.calendarMaker();
    w.nodeMaker();
    w.printCityMap();
    //w.printCalendar();
 //  w.print();
  // for(int i=0; i<preInput.size();i++)
      //  cout << preInput.at(i) << endl;


    cout << "Welcome to Temp Planner" << endl;
    cout << "Press Enter to Continue" << endl;
    cin.ignore();

    //cout << "Flushing the output stream." << flush;
    //system("clear");

    string input;

    cout << "Please choose one of the following: "<< endl;
    cout << "There is somewhere I want to go (type 1 and press enter): "<< endl;
    cout << "I want to go somehwere with a certain weather (type 2 and press enter): "<< endl;
    while(input!= "1" && input != "2")
    {
        cin >> input;
        if(input!= "1" && input != "2")
            cout << "Please type 1 or 2 and press enter" << endl;
    }

    if(input == "1")
    {
        cout << "Please choose one of the following cities: " << endl;
        w.printCityName();
        cin >> input;

        while (w.cityCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin >> input;
        }

        string city = input;

        cout << "Please enter the start date in the format M/D" << endl;
        cin >> input;
        while (w.dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin >> input;
        }

        vector<string>startDate = w.dateExtract(input);

        cout << "Please enter the end date in the format M/D" << endl;
        cin.clear();
        cin >> input;
        while (w.dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        vector<string> endDate = w.dateExtract(input);

        cout << "Enter c for celsius or f for farenheiht" << endl;

        cin>>input;

        while (input != "c" && input != "f") {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }

        float weather = w.weatherCalculate(city,startDate, endDate);
        char unit = 'c';
        if(input == "f")
        {weather = (weather * 1.8) + 32.0;
            unit = 'f';}

        float value = (weather * 100 + 0.5)/100;
        string val = to_string(value);

        if(val.find(".")==3)
            val = val.substr(0,5);
        else  val = val.substr(0,4);

        cout << "Average Weather for " << city << " from "
        << startDate.at(0) << "/" << startDate.at(1) << " to "
                << endDate.at(0) << "/" << endDate.at(1) << " is " <<
                                                                 val <<
      " degrees " << unit;
    }



    return 0;
}
