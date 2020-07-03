//
// Created by Lupo on 02/07/2020.
//

#ifndef PROGETTO_POLITO_2020_CLION_TIME_H
#define PROGETTO_POLITO_2020_CLION_TIME_H
#include <ctime>
#include "Control.h"
#include "Table.h"


class Time:Control {
public:
    Time();
    Time(const int& hr, const int& min, const int& sec);
    Time(const Time &to_copy);
    virtual ~Time();
    void get_time(const string& str);

private:
    int sec, min, hour;
    string str;

};


#endif //PROGETTO_POLITO_2020_CLION_TIME_H
