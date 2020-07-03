//
// Created by Evry on 01/07/2020.
//

#include "Date.h"
Date::Date() {

}

Date::~Date() {

}

Date::Date(const int& _day, const int& _month, const int& _year) {
    day = _day; month = _month; year = _year;
}

Date::Date(const Date &to_copy) {
    *this = to_copy;
}

void Date::get_day(const string &str) { // 12/12/2012

    vector <string> vect_str;
    regex reg("\\d{4}|\\d{2}");
    vect_str = printMatchesIT(str, reg);
    if (vect_str.size()!=3) {
        cerr << "wrong date input" << endl;
    } else {
        for (int i = 0; i < 3; i++) {
            if (i == 2 && vect_str[i].size() == 4) {
                year = stoi(vect_str[i]);
                cout << setw(4) << year << endl;
            } else if (i != 2 && vect_str[i].size() == 2) {
                if (i == 0) {
                    day = stoi(vect_str[i]);
                    cout << setw(2) << day << "/";
                } else if (i == 1) {
                    month = stoi(vect_str[i]);
                    cout << setw(2) << month << "/";
                }

            }
        }
    }

}


