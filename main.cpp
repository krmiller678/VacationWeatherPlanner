#include <iostream>
#include "TemperatureClass.h"
#include "Setup.cpp"
#include "Calculation.cpp"
#include "Display.cpp"
#include "InputValidation.cpp"
#include "Options.cpp"
#include "HelperFunctions.cpp"
using namespace std;

//Main
int main() {

    Temperature t;

    //Following 4 needed to set up the appropriate data structures from the CSV file
    vector <string> preInput = t.fileExtraction();
    t.mapMaker(preInput);
    t.calendarMaker();
    t.nodeMaker();
    t.timerInit();

    string input;

    cout << "Welcome to Temperature Planner!" << endl;
    cout << "Press enter to continue" << endl;

    while(1==1)
    {
        cin.ignore();

        input = t.mainMenu();

        if (input == "1")
            t.option1();

        if (input == "2")
            t.option2();

        if (input == "3")
            t.option3();

        if (input == "4")
            t.option4();

        if (input == "5" || t.mainMenuReturn() == "n")
            break;
    }

    cout << endl << "Thank you for using our app! Have a great day!";

    return 0;
}
