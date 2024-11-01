#include <iostream>
#include <map>
#include <unordered_map>
#include <fstream>
using namespace std;

class Weather
{
private:

   unordered_map <string, map <string, float> > city1;
   unordered_map <string, map <string, float> >::iterator outer;
   map <string, float>::iterator inner;

    // unordered_map <string, unordered_map <vector<string>, float> > citymap;
     //unordered_map <string, unordered_map <vector<string>, float> > ::iterator outer;
   // unordered_map <string, unordered_map <string, float> >::iterator outer;
     // unordered_map <vector<string>, float>::iterator inner;

    vector <string> results;

public:

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
             // cout << input.at(i).length() << endl;
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

                 // month= words.at(1);

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
                 //  cout << inner->first.size() << endl;
               }

      }
    }

    void printCityName()
    {
        for(outer = city1.begin(); outer!= city1.end(); outer++)
            cout  << outer->first << " " <<  endl;

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
};


int main() {

    Weather w;

    vector <string> preInput = w.inputExtraction();
    w.mapMaker(preInput);
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
        cout << "Please enter the start date in the format MM/DD" << endl;
        cin >> input;
        while (w.dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin >> input;
        }
        cout << "in1" << input.at(0) <<endl;
        cout << "in2" << input.at(1) <<endl;
        cout << "in" << input;
        string startMonth;
        startMonth.append(input[0], input[1]);
        string startDay;
        startDay.append(input[3], input[4]);

        cout << "Please enter the end date in the format MM/DD" << endl;
        cin.clear();
        cin >> input;
        while (w.dateCheck(input) != 1) {
            cout << "Please try again:" << endl;
            cin.clear();
            cin >> input;
        }
       // string endMonth = endMonth + input[0] + input[1];
       // string endDay = endDay + input[0] + input[1];

        cout << startMonth << "/" << startDay ;
        //<< "-" << endMonth << endDay;



    }

  //  cout << "There is somewhere I want to go (type 1 and press enter): "<< endl;
   // cout << "I want to go somewhere with a certain weather (type 2 and press enter): "<< endl;
    //while(input!= "1" && input != "2")
   // {
    //    cin >> input;
     //   if(input!= "1" && input != "2")
     //       cout << "Please type 1 or 2 and press enter" << endl;
    //}


    return 0;
}
