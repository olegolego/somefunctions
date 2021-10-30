#include <bits/stdc++.h>
using namespace std;

const int Months[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
const char *MONTH_NAMES[] = {"", "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December"};
const char *DAY_OF_WEEK[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

string formatin(string s, int k)
{
    string t = s;
    reverse(t.begin(), t.end());
    while ((int)t.size() != k)
    {
        t.push_back('0');
    }
    reverse(t.begin(), t.end());
    return t;
}

bool leap_year(int year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

int count_days(int year)
{
    return (year - 1) * 365 + (year - 1) / 400 + (year - 1) / 4 - (year - 1) / 100;
}

class date
{
 public:
    int day, month, year;
    string to_text() const
    {
        string s = MONTH_NAMES[month];
        return s + " " + to_string(day) + ", " + to_string(year);
    }

    void from_text(const string &s)
    {
        istringstream help_str(s);
        string montH;
        char point;

        help_str >> montH >> day >> point >> year;

        int index = 1;
        while (MONTH_NAMES[index] != montH)
        {
            index++;
        }
        month = index;
    }

    date &operator++()
    {
        day++;
        if (MONTH_NAMES[month] == "February" && leap_year(year) && day == 29)
        {
            return *this;
        }

        if (Months[month] < day)
        {
            day = 1;
            month++;
        }

        if (month > 12)
        {
            month = 1;
            year++;
        }

        return *this;
    }

    date operator--(int)
    {
        date help = *this;
        day--;
        if (day == 0)
        {
            month--;
            if (MONTH_NAMES[month] == "February" && leap_year(year))
            {
                day = 29;
            }

            else
            {
                if (month == 0)
                {
                    month = 12;
                    year--;
                }

                day = Months[month];
            }
        }

        return help;
    }

    operator int() const
    {
        int ans_day = day;
        int index = 1;
        while (index != month)
        {
            ans_day += Months[index];
            index++;
        }

        if (month > 2 && leap_year(year))
        {
            ans_day++;
        }

        ans_day += count_days(year);
        return ans_day;
    };

    string day_of_the_week() const
    {
        int daysall = int();
        int week = daysall % 7;
        return DAY_OF_WEEK[week];
    }

    date(int n)
    {
        year = n / 390;
        while (count_days(year + 1) < n)
            year++;

        n -= count_days(year);
        int Monthss[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
        if (leap_year(year))
        {
            Monthss[2] = 29;
        }

        int index = 0;
        while (n > 0)
        {
            n -= Monthss[index + 1];
            ++index;
        }

        month = index;
        day = n + Monthss[month];
    }

    date(int a, int b, int c)
    {
        day = a;
        month = b;
        year = c;
    }

    date()
    {
        day = 1;
        year = 1;
        month = 1;
    }
};

int count_day(date a)
{
    return a.year * 1500 + a.month * 40 + a.day;
} 
bool operator>(date a, date b)
{
    return count_day(a) > count_day(b);
}
bool operator>=(date a, date b)
{
    return count_day(a) >= count_day(b);
}

bool operator<(date a, date b)
{
    return count_day(a) < count_day(b);
}

bool operator<=(date a, date b)
{
    return count_day(a) <= count_day(b);
}

bool operator==(date a, date b)
{
    return count_day(a) == count_day(b);
}

bool operator!=(date a, date b)
{
    return count_day(a) != count_day(b);
}

int operator-(const date &a, const date &b)
{
    return (int)a - (int)b;
}

date operator+(date a, int b)
{
    return date(int(a) + b);
}

date operator-(date a, int b)
{
    return date(int(a) - b);
}

date &operator+=(date &a, int b)
{
    a = a + b;
    return a;
}

date &operator-=(date &a, int b)
{
    a = a - b;
    return a;
}

istream &operator>>(istream &in, date &a)
{
    char point;
    in >> a.day >> point >> a.month >> point >> a.year;
    return in;
}

ostream &operator<<(ostream &out, const date &a)
{
    string day = to_string(a.day);
    day = formatin(day, 2);

    string month = to_string(a.month);
    month = formatin(month, 2);

    string year = to_string(a.year);
    year = formatin(year, 4);

    out << day << '.' << month << '.' << year;
    return out;
}

