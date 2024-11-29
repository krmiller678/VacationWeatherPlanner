//Functions needed for displaying certain results and menu related optiions

#include "TemperatureClass.h"

//Needed to display the results of the time differences between using the ordered vs. unordered temperature maps
//in the city structt
void Temperature::winner(chrono::duration<double> elapsed, chrono::duration<double> elapsed2)
{

    cout << endl << "Runtime with ordered map: " << elapsed.count() << " seconds" << endl;
    cout << "Runtime with unordered map: " << elapsed2.count() << " seconds" << endl;
    if(elapsed.count() < elapsed2.count())
        cout << "Ordered map wins!" << endl;
    else
        cout << "Unordered map wins!"  << endl;
}

//Converts temperature to farenheit if needed and then puts the temperature in the final format for display
string Temperature::finalTemp(float weather, string input)
{
    if(input == "C")
        weather = (weather - 32) / 1.8;
    //weather = (weather * 1.8) + 32.0;

    weather = (weather * 100 + 0.5)/100;
    string val = to_string(weather);

    if(val.find(".")==3)
        val = val.substr(0,5);
    else
        val = val.substr(0,4);

    return val;
}

//Function to display the main menu. Different number choices will call different function acccordingly except for
//the number 5 which will lead to the program ending
string Temperature::mainMenu()
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

//Function called after the user has completed one of the options chosen from the main menu. Choosing y returns input
//that will lead back to the main menu. Choosing n will return input that will lead to the program ending
string Temperature::mainMenuReturn()
{
    string input;

    cout << endl << "Return to main menu? (please type y or n and press enter)" << endl;

    cin >> input;

    while (input != "y" && input != "n")
    {
        cout << "Please type y or n and press enter" << endl;
        cin >> input;
    }

    return input;
}
