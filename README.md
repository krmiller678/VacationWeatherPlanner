# VacationWeatherPlanner
Looking to plan your next trip? The Vacation Weather Planner has you covered! By using historical data, this app allows you to view weather trends in whichever area you are traveling to.

Specifically, this application will allow for you to input a large data set in the form of a csv. That csv is then transformed into a std::map (sorted) of Cities belonging to the class Cities of Interest. Each City in this std::map will link to a City object, which itself contains a struct called WeatherDataNode corresponding to a particular date. 

The WeatherDataNodes will be stored in a hash map std::unordered_map as well as a heap implemented as an std::priority_queue.
