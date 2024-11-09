
//  The months which have 31 days are January, March, May, July, August, October, and
// December. The months which have 30 days are April, June, September, and November.

/*
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
 */