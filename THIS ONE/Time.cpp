//
// Created by Lupo on 02/07/2020.
//

#include "Time.h"

Time::Time() {

}

Time::~Time() {

}

Time::Time(const int& hr, const int& m, const int& s) {
    sec = s; min = m; hour = hr;
}

Time::Time(const Time &to_copy) {
    *this = to_copy;
}

void Time::get_time(const string &str) {
    vector <string> vect;
    regex reg("\\d{2}");
    vect = printMatchesIT(str, reg);
    // cout << vect;
}

