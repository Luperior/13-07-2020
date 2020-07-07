//
// Created by Evry on 29/06/2020.
//

#ifndef PROGETTO_POLITO_2020_CLION_TABLE_H
#define PROGETTO_POLITO_2020_CLION_TABLE_H

#include "Control.h"

class Table:Control {
public:
    Table();
    Table(const string &_str, const string &_str2, const map<int, vector<string>>& _m, const vector<bool>& _n_null, const vector<bool>& _a_inc, const int& _a_inc_count, const string& _primary_key, const string& _foreign_key, const string& _reference);
    virtual ~Table();
    string create_Table(string& str);
    vector<string> getlabel(const vector<string>& structure); //manca NOT NULL
    void set_target_names(); //da aggiornare
    vector<string> get_types(const vector<string>& structure);
    map <int, vector <string>> get_map();
    int insert_into(const string& str, map <string,Table> database);
    int update_record(const string& str);
    void ordiniamoli();
    void delete_from_table(const string& s2);
    string get_primary_key();
    string get_foreign_key();
    string get_reference();
    int size();
    vector <string> line (const int& idx);
    void print_table(const string& _str, map <string,Table> database);


protected:
string str, str2; // secondo me queste possiamo rimuoverle, del resto derivano dall'esterno e non sono proprie della singola Table
                  // Lupo, 05/07
string primary_key, foreign_key, reference;
map <int, vector <string>> m;
vector <bool> n_null, a_inc;
int a_inc_count = 1;

};


#endif //PROGETTO_POLITO_2020_CLION_TABLE_H

