//
// Created by Evry on 29/06/2020.
//

#include "Table.h"

Table::Table() {}

Table::Table(const string &_str, const string &_str2, const map<int, vector<string>>& _m) {
    str = _str;
    str2 = _str2;
    m = _m;
}

Table::~Table() {

}

string Table::create_Table(string& str) {
    if ((str.find("CREATE") != string::npos) && (str.find("TABLE") != string::npos) && (str.find(" (") != string::npos)) {
        regex reg(R"(\b(?!\bCREATE|TABLE\b)\w+\b)"); //QUI HO SEGUITO UN CONSIGLIO DEL COMPILATORE CON QUELLA R INIZIALE
        smatch match;
        regex_search(str, match, reg);
        string test;
        test = match.str();
        return test;
    } else {
        cerr << "syntax error" << endl;
        string string1;
        getline (cin, string1);
        string test1 = create_Table(string1); //richiama se stessa così da poter inserire tutto finchè non metto roba giusta
        return test1;
    }
}

vector<string> Table::getlabel(const vector<string>& structure) {
    string s;
    vector <string> vect;
    for (int i = 0; i < structure.size(); i++)
    {
        s = structure[i].substr(0, structure[i].find(" "));
        vect.push_back(s);
    }
    //cout << vect.size() << endl;
    return vect;
}

vector<string> Table::get_types(const vector<string>& structure) {
    vector<string> vect;
    string s;
    for (int i = 0; i < structure.size(); i++)
    {
        s = structure[i].substr(structure[i].find(' '), string::npos);
        regex reg (R"([^\s]+)");
        smatch match;
        regex_search(s, match, reg);
        s = match.str();
        cout << "s corrisponde a" << s << endl;
        vect.push_back(s);
    }
    return vect;
}


map<int, vector<string>> Table::get_map() {
    return m;
}

void Table::set_target_names() {
    vector<string> names;
    int v = 0;
    do {
        string s;
        getline(cin, s);
        if (s.find(");")!= string::npos) {
            v = 1;
        } else {
            names.push_back(s);
        }
    } while (v != 1); //vedi poi di usare un match così anche se mette spazi blocca ugualmente
    m[0] = get_types(names);
    m[1] = getlabel(names);
}

int Table::insert_into(const string str) {
    if ((str.find("INSERT INTO ") != string::npos) && (str.find('(') != string::npos)) {
        string value_group, buf, buf2, insert, target_list, a2, a3;
        //regex reg(R"(\b(?!\bINSERT|INTO\b)\w+\b)");
        smatch match2, match3, match2A, match3A;
        //regex_search(str, match, reg);
        //test = match.str(); // nome della tabella da modificare
        int i = m.size(); // ogni volta che entro in insert into mette la riga dopo, dato che la 0 è occupata dai tipi e la 1 dalle etichette
        regex reg2("[\\(](.*)[\\)]");
        regex reg2A(R"([^ ,()]\w{0,22}|"^[0-9]+$")");
        regex_search(str, match2, reg2);
        target_list = match2.str();
        vector<string> targets = printMatchesIT(target_list, reg2A);
        getline(cin, insert);
        if (insert.find(';')!= string::npos) {
            regex regAlpha(R"(^[^;]+)");
            smatch matchAlpha;
            regex_search(insert, matchAlpha, regAlpha);
            insert = matchAlpha.str();
            if ((insert.find("VALUES") != string::npos) && (insert.find(" (") != string::npos)) { // valori separati da uno spazio
                regex reg3("[\\(](.*)[\\)]");
                regex reg3A(R"([^ ,()]\w{0,22}|"^[0-9]+$")"); // aggiungo +$ sennò matchava anche caratteri speciali, e la barra verticale è OR e la R iniziale suggerita
                regex_search(insert, match3, reg3);
                value_group = match3.str();
                vector<string> values = printMatchesIT(value_group, reg3A);
                vector<string> records;
                int quit = 0;
                for (int k = 0; k < m[1].size(); k++) {
                    for (int v = 0; v < targets.size(); v++) {
                        if (m[1][k] == targets [v]) {
                            if(!type_check (values [v], m[0][k]))
                            {
                                insert_into(reget_str());
                                return 1;
                            }
                        }
                    }
                }
               /* for (int z = 0; z < targets.size(); z++) {
                    if (foreign_keys[test]==targets[z]) {
                        for ( int y = 0; y < database[references[test]][0].size(); y++) {
                            if (database[references[test]][0][y] == primary_keys[references[test]]) {
                                for (int w = 0; w < database[references[test]].size(); w++) {
                                    primary_values.emplace_back(database[references[test]][w][y]); // vettore per confrontare i valori
                                }
                            }
                        }
                    }
                    else {
                        quit = 1;
                    }
                }
                for (int n = 0; n < primary_values.size(); n++) {
                    for (int z = 0; z < targets.size(); z++) {
                        if (foreign_keys[test]==targets[z]) {
                            if (primary_values[n]==values[z]) {
                                quit = 1;
                            }
                        }
                    }
                }
                if (quit != 1) {
                    cerr << "Primary keys error: try again" << endl;
                    string error;
                    getline (cin , error);
                    insert_into(error);
                    return 1; // ho piazzato il return altrimenti avrebbe continuato da qua e sovrascritto
                }*/
                for (int it = 0; it < m[1].size(); it++) {
                    int count = 0;
                    for (int it2 = 0; it2 < targets.size(); it2++) {
                        if (targets[it2] == m[1][it]) {
                            records.push_back(values[it2]);
                            count = 1;
                        }
                    }
                    if (count == 0) {
                        records.emplace_back("\t"); // al posto di push_back ha suggerito questo
                    }
                }
                m[i] = records;
            }
        } else {
            cerr << "syntax error, try again" << endl;
            string string1;
            getline(cin, string1);
            insert_into(string1); //richiama se stessa così da poter inserire tutto finchè non metto roba giusta
        }
    }
    return 1;
}

int Table::size() {
    return m.size();
}

vector<string> Table::line(const int& idx) {
    return m[idx];
}

void Table::print_table(const string& _str) {
    if (str.find('*') != string::npos) {
        string from;
        getline(cin, from);
        if ((from.find("FROM") != string::npos) && (from.find(';') != string::npos)) { // qui come mai è commentato tutto? in questo modo non compie alcuna azione quando
                                                                                                // voglio stampare semplicemente tutta la tabella
                                                                                                // 03/07 Lupo
           /* regex regAlpha(R"(^[^;]+)");
            smatch matchAlpha;
            regex_search(from, matchAlpha, regAlpha);
            from = matchAlpha.str();
            regex reg(R"(\b(?!\bFROM\b)\w+\b)");
            smatch match;
            regex_search(from, match, reg);
            string s = match.str();*/
            //cout << database[s];
        } else if (from.find("FROM") != string::npos) {
            string where;
            getline(cin, where);
            if (where.find("WHERE") != string::npos) {
                if (where.find(';') != string::npos) {
                    regex reg9(R"(\b(?!\bFROM\b)\w+\b)");
                    smatch match9;
                    regex_search(from, match9, reg9);
                    string s = match9.str();
                    regex regAlpha(R"(^[^;]+)");
                    smatch matchAlpha;
                    regex_search(where, matchAlpha, regAlpha);
                    where = matchAlpha.str();
                    string buf = where.substr(where.find("WHERE") + 6, string::npos);
                    regex reg(R"(\w{0,22}[^ =])");
                    smatch match, match2;
                    regex_search(buf, match, reg);
                    string buf2 = match.str(); // contiene il nome dell'etichetta da controllare
                    regex reg2(R"(\=(.*))");
                    regex_search(buf, match2, reg2);
                    string buf3 = match2.str().substr(2,string::npos); // contiene il valore dell'etichetta da controllare
                    vector<int> number;
                    for (int a = 0; a < m[1].size(); a++) {    //nell'originale al posto di m[0] c'era database[s]. Serve indicizzarlo nel main?
                                                               //spostiamo le regex nel main?       30/06/2020 Evry
                        if (buf2 == m[1][a]) {
                            for (int it = 2; it < m.size(); it++) {
                                if (buf3 == m[it][a]) {
                                    number.emplace_back(it); // contiene tutti gli indici dei record dove la condizione WHERE è soddisfatta
                                }
                            }
                        }
                    }
                    cout << m[1]<< endl;
                    for (auto ti= number.begin(); ti < number.end(); ti++) {
                        cout << m[*ti] << endl;
                    }
                } else {
                    string order_by;
                    getline(cin, order_by);
                    if ((order_by.find("ORDER BY") != string::npos) && (order_by.find(';') != string::npos)) {
                        if (order_by.find("ASC") != string::npos) {

                        } else if (order_by.find("DESC") != string::npos) {

                        }
                    }
                }
            }
            else if (where.find("ORDER BY")!= string::npos) {
                if (where.find("ASC")!= string::npos) {

                }
                else if (where.find("DESC")!= string::npos) {

                }
            }
        }
    } else {
        string from;
        getline(cin, from);
        if (from.find("FROM") != string::npos) {
            if (from.find(';') != string::npos) {
                regex regAlpha(R"(^[^;]+)");
                smatch matchAlpha;
                regex_search(from, matchAlpha, regAlpha);
                from = matchAlpha.str();
                regex reg(R"(\b(?!\bFROM\b)\w+\b)");
                smatch match;
                regex_search(from, match, reg);
                string s = match.str();
                string y = str.substr(str.find("SELECT") + 7, string::npos);
                stringstream ss(y);
                string buf;
                vector<string> vect;
                while (getline(ss, buf, ',')) {
                    regex reg0(R"([^\s]+)");
                    smatch match0;
                    regex_search(buf, match0, reg0);
                    string buf0 = match0.str();
                    vect.emplace_back(buf0);
                }
                vector<int> positions;
                for (int j = 0; j < vect.size(); j++) {
                    for (int k = 0; k < m[1].size(); k++) {
                        if (vect[j] == m[1][k]) {
                            cout << m[1][k] << "\t";
                            positions.emplace_back(k);
                        }
                    }
                }
                cout << endl;
                for (int it = 2; it < m.size(); it++) {
                    for (auto l = positions.begin(); l < positions.end(); l++) {
                        cout << m[it][*l] << "\t";
                    }
                    cout << endl;
                }
            } else {
                string where;
                getline(cin, where);
                if (where.find("WHERE") != string::npos) {
                    if (where.find(';') != string::npos) {
                        regex reg9(R"(\b(?!\bFROM\b)\w+\b)");
                        smatch match9;
                        regex_search(from, match9, reg9);
                        string s = match9.str();
                        string y = str.substr(str.find("SELECT") + 7, string::npos);
                        stringstream ss(y);
                        string buf9;
                        vector<string> vect;
                        while (getline(ss, buf9, ',')) {
                            regex reg0(R"([^\s]+)");
                            smatch match0;
                            regex_search(buf9, match0, reg0);
                            string buf0 = match0.str();
                            vect.emplace_back(buf0); // vect contiene i campi che vogliamo stampare
                        }
                        regex regAlpha(R"(^[^;]+)");
                        smatch matchAlpha;
                        regex_search(where, matchAlpha, regAlpha);
                        where = matchAlpha.str();
                        string buf = where.substr(where.find("WHERE") + 6, string::npos);
                        regex reg(R"(\w{0,22}[^ =])");
                        smatch match, match2;
                        regex_search(buf, match, reg);
                        string buf2 = match.str(); // contiene il nome dell'etichetta da controllare
                        regex reg2(R"(\=(.*))");
                        regex_search(buf, match2, reg2);
                        string buf3 = match2.str().substr(2,string::npos); // contiene il valore dell'etichetta da controllare
                        vector<int> number;
                        for (int a = 0; a < m[1].size(); a++) {
                            if (buf2 == m[1][a]) {
                                for (int it = 2; it < m.size(); it++) {
                                    if (buf3 == m[it][a]) {
                                        number.emplace_back(it); // contiene tutti gli indici delle righe (record) dove la condizione WHERE è soddisfatta
                                    }
                                }
                            }
                        }
                        vector<int> positions;
                        for (int j = 0; j < vect.size(); j++) {
                            for (int k = 0; k < m[1].size(); k++) {
                                if (vect[j] == m[1][k]) {
                                    cout << m[1][k] << "\t";
                                    positions.emplace_back(k);
                                }
                            }
                        }
                        cout << endl;
                        for (auto b = number.begin(); b < number.end(); b++) {
                            for (auto l = positions.begin(); l < positions.end(); l++) {
                                cout << m[*b][*l] << "\t";
                            }
                            cout << endl;
                        }
                    } else {
                        string order_by;
                        getline(cin, order_by);
                        if ((order_by.find("ORDER BY") != string::npos) && (order_by.find(';') != string::npos)) {
                            if (order_by.find("ASC") != string::npos) {

                            } else if (order_by.find("DESC") != string::npos) {

                            }
                        }
                    }
                }
                else if (where.find("ORDER BY")!= string::npos) {
                    if (where.find("ASC") != string::npos) {

                    } else if (where.find("DESC") != string::npos) {

                    }
                }
            }
        }
    }
}


/*
string &Table::operator[](std::size_t idx) {
    return [idx];
}

vector <string>& Table::operator new[](int &i, map <int, vector <string>> m) {
    vector <string> vect_str;
    m[i] = vect_str;
    return vect_str;
}*/

