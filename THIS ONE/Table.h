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
    Table(const Table &to_copy);
    string create_Table(string& str);
    void save_nnull(const string& table_name);
    vector<bool> upload_nnull(const string &table_name);
    void save_ainc (const string& table_name);
    vector<bool> upload_ainc(const string &table_name);
    void save_table (const string &table_name);
    map <int, vector <string>> uploader(const string& table_name);
    void save_keys(const string &table_name);
    void upload_keys(const string& table_name);
    vector<string> getlabel(const vector<string>& structure);
    void set_target_names();
    vector<string> get_types(const vector<string>& structure);
    map <int, vector <string>> get_map();
    int insert_into(const string& str, map <string,Table> database);
    int update_record();
    void order_asc(const string& str, const vector<int>& number);
    void order_desc(const string& str, const vector<int>& number);
    void select_order_asc(const string& str, const vector<int>& number, const vector<int>& positions);
    void select_order_desc(const string& str, const vector<int>& number, const vector<int>& positions);
    void delete_from_table(const string& s2);
    string get_primary_key();
    string get_foreign_key();
    string get_reference();
    int size();
    vector <string> line (const int& idx);
    void print_table(const string& _str, map <string,Table> database);
    //bool myfloat(const float& a, const float& b);

private:
string str, str2; // secondo me queste possiamo rimuoverle, del resto derivano dall'esterno e non sono proprie della singola Table
                  // Lupo, 05/07
string primary_key, foreign_key, reference;
map <int, vector <string>> m;
vector <bool> n_null, a_inc;
int a_inc_count = 1;

};


#endif //PROGETTO_POLITO_2020_CLION_TABLE_H

