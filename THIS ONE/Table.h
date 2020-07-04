//
// Created by Evry on 29/06/2020.
//

#ifndef PROGETTO_POLITO_2020_CLION_TABLE_H
#define PROGETTO_POLITO_2020_CLION_TABLE_H

#include "Control.h"

class Table:Control {
public:
    Table();
    Table(const string &_str, const string &_str2, const map<int, vector<string>>& _m, const vector<bool>& _n_null, const vector<bool>& _a_inc);
    virtual ~Table();
    string create_Table(string& str);
    vector<string> getlabel(const vector<string>& structure); //manca NOT NULL
    void set_target_names(); //da aggiornare
    vector<string> get_types(const vector<string>& structure);
    map <int, vector <string>> get_map();
    int insert_into(const string str);
    int size();
    //vector <string>& operator new[](int&i);
    //string& operator[](std::size_t idx);
    vector <string> line (const int& idx);
    void print_table(const string& _str);


protected:
string str, str2;
map <int, vector <string>> m;
vector <bool> n_null, a_inc;

};


#endif //PROGETTO_POLITO_2020_CLION_TABLE_H

