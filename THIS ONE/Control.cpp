//
// Created by Evry on 29/06/2020.
//

#include "Control.h"

Control::Control() {}

Control::~Control() {

}

vector<string> Control::printMatchesIT(string str, regex reg) {
    //cout << "PrintMatchesIT:" << endl;
    vector <string> vect;
    sregex_iterator currentMatch(str.begin(), str.end(), reg);
    sregex_iterator lastMatch;
    do
    {
        smatch match = *currentMatch;
        //cout << match.str() << endl;
        vect.push_back(match.str());
        currentMatch++;
    } while (currentMatch != lastMatch);
    // cout << "vector:" << vect << endl;
    return vect;
}

Control::Control(const string &_str, const regex& _reg) {
    str = _str;
    reg = _reg;
}

bool Control::c_int(const string &str) {
    if (stoi(str) == true) { // non ne sono convintissimo
        return true;
    } else
    return false;
}

bool Control::c_float(const string &str) {
    if (stof(str) == true) {
        return true;
    } else
    return false;
}

bool Control::c_char(const string &str) {
    if (str.size()==1) {
        return true;
    } else
    return false;
}

bool Control::c_text(const string &str) {
    if ((str.find('/')!=string::npos) || (str.find(':')!=string::npos) || (str.find('-')!=string::npos)) {
        return false;
    } else
    return true;
}

bool Control::c_date(const string &str) {
    // controllo che sia compatibile con una data
    return false;
}

bool Control::c_time(const string &str) {
    // controllo che sia compatibile con un orario
    return false;
}

bool Control::type_check(const string &str, const string& type) {
    if (type.find("INT")!=string::npos) {
        c_int(str);
    }
    if (type.find("FLOAT")!=string::npos) {
        c_float(str);
    }
    if (type.find("CHAR")!=string::npos) {
        c_char(str);
    }
    if (type.find("TEXT")!=string::npos) {
        c_text(str);
    }
    if (type.find("DATE")!=string::npos) {
        c_date(str);
    }
    if (type.find("TIME")!=string::npos) {
        c_time(str);
    } else
    return false;
}

