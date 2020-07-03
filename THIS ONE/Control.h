//
// Created by Evry on 29/06/2020.
//

#ifndef PROGETTO_POLITO_2020_CLION_CONTROL_H
#define PROGETTO_POLITO_2020_CLION_CONTROL_H

#include <vector>
#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

class Control {
public:
    Control();
    Control(const string &str, const regex& _reg);
    virtual ~Control();
    vector <string> printMatchesIT(string str, regex reg);
    bool type_check (const string& str);
    bool c_int (const string& str);
    bool c_float (const string& str);
    bool c_char (const string& str);
    bool c_text (const string& str);
    bool c_date (const string& str);
    bool c_time (const string& str);

private:  //protected o private?
string str;
regex reg;
};


template <typename T> //operatore stampa vettore
ostream &operator<<(ostream &os, const vector<T> &v) {
    for (int i = 0; i < v.size(); ++i) {
        os << v[i] << "\t";
    }
    return os;
}

template <typename T, typename Z> // operatore stampa mappa
ostream& operator<<(ostream& os, const map < T , Z >& v)
{
    for (const auto  &x: v) {
        os << x.second << endl;
    }
    return os;
}
#endif //PROGETTO_POLITO_2020_CLION_CONTROL_H