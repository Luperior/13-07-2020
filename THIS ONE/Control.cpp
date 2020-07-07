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
    try {
        stoi(str);
        return true;
    }
    catch (exception &e) {
        return false;
    }
}

bool Control::c_float(const string &str) {
    try {
        stof(str);
        return true;
    }
    catch (exception &e) {
        return false;
    }
}

bool Control::c_char(const string &str) {
    if (str.size()==1) {
        return true;
    } else
    return false;
}

bool Control::c_text(const string &str) {
    //if ((str.find('/')!=string::npos) || (str.find(':')!=string::npos) || (str.find('-')!=string::npos)) {
    if (str.size() > MAXSIZE) {
        return false;
    } else
    return true;
}

bool Control::c_date(const string &str) {
    // controllo che sia compatibile con una data
    return true;
}

bool Control::c_time(const string &str) {
    // controllo che sia compatibile con un orario
    return true;
}

bool Control::type_check(const string &str, const string& type) {
    if (type.find("INT")!=string::npos) {
        return c_int(str);
    }
    if (type.find("FLOAT")!=string::npos) {
        return c_float(str);
    }
    if (type.find("CHAR")!=string::npos) {
        return c_char(str);
    }
    if (type.find("TEXT")!=string::npos) {
        return c_text(str);
    }
    if (type.find("DATE")!=string::npos) {
        return c_date(str);
    }
    if (type.find("TIME")!=string::npos) {
        return c_time(str);
    }
    else return false;
}

string Control::reget_str() {
    string re_str;
    getline(cin, re_str);
    return re_str;
}

void Control::save_tablenames(const vector<string>& table_names) {
    ofstream outf ("table_names.bin", ios::binary);
    //ofstream outf ("table_names.txt");
    for (auto it = table_names.begin(); it < table_names.end(); it++)
    {
        outf << *it << endl;
    }
} // salva i nomi delle tabelle

vector <string> Control::upload_tablenames(vector <string>& table_names) {
    string s;
    //ifstream inf("table_names.txt");
    ifstream inf("table_names.bin", ios::binary);
    while (getline(inf, s))
    {
        table_names.push_back(s);
    }
    inf.close();
    return table_names;
} // ricarica i nomi delle tabelle
