# Obtaining the project

# Option 1: Clone Repository
1. Go into terminal and type cd desireddirectory
2. Then type git clone https://github.com/krmiller678/VacationWeatherPlanner

# Option 2: Download Zip File
1. Use the green "< > Code button" at the top right of the repo and download the repo as a zip
2. Extract the ZIP file to a desired location

Once the project is saved, there are different methods to actually opening it:

# Running the project

# Clion
OPTION 1
1. Go into the project folder and open main.cpp.
2. Press OK for any pop ups (project wizard, configuration)
3. Allow everything to run first like symbools, indexing, etc...
4. Note - if you experience any issues with the cmake version, your IDE may prompt you to click fix which is ok to update

OPTION 2
1. Open the project folder
2. CLion will auto-detect the CMakeLists.txtand configure the project.

# Visual Studio
1. Go to File > Open > Folder and select the project folder.
2. Configure and Build the Project: Visual Studio will prompt you to configure the project. Follow the prompts.
3. Run main.cpp.

# Terminal (mac)
1. cd into the project folder created earlier
2. type     cmake .    and press enter
3. type     make       and press enter
4. type     ./VacationWeatherPlanner       and press enter
5. Wait for program to load then it can be used

# Additional
_**The program will take a few minutes to load the data after which it will run seamlessley. Running it entirely 
in the terminal however can result in better performance. 
The program is designed to be intuitive and self-explanatory with directions provided within the program interface.
Note that city_temperature was origininally 1 csv file but was split into 2 due to GitHub size upload limitations._** 



