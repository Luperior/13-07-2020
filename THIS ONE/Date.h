//
// Created by Evry on 01/07/2020.
//

#ifndef PROGETTO_POLITO_2020_CLION_DATE_H
#define PROGETTO_POLITO_2020_CLION_DATE_H

#include <ctime>
#include "Control.h"
#include "Table.h"

class Date: Control {

public:
    Date();
    Date(const int& _day, const int& _month, const int& _year);
    Date(const Date &to_copy);
    virtual ~Date();

    void get_day (const string& str);

private:
    int day, month, year;
    string str;
};


#endif //PROGETTO_POLITO_2020_CLION_DATE_H
