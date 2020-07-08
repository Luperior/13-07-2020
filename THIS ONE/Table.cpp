//
// Created by Evry on 29/06/2020.
//

#include "Table.h"

Table::Table() {}

Table::Table(const string &_str, const string &_str2, const map<int, vector<string>>& _m, const vector<bool>& _n_null, const vector<bool>& _a_inc, const int& _a_inc_count, const string& _primary_key, const string& _foreign_key, const string& _reference) {
    str = _str;
    str2 = _str2;
    m = _m;
    n_null = _n_null;
    a_inc = _a_inc;
    a_inc_count = _a_inc_count;
    primary_key = _primary_key;
    foreign_key = _foreign_key;
    reference = _reference;
}

Table::~Table() {

}

string Table::get_primary_key() {
    return primary_key;
}

string Table::get_foreign_key() {
    return foreign_key;
}

string Table::get_reference() {
    return reference;
}

string Table::create_Table(string& str) {
    if ((str.find("CREATE") != string::npos) && (str.find("TABLE") != string::npos) && (str.find(" (") != string::npos)) {
        regex reg(R"(\b(?!\bCREATE|TABLE\b)\w+\b)");
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

void Table::order_asc(const string& str, const vector<int>& number) {
    regex reg(R"(\b(?!\bORDER|BY\b)\w+\b)");
    smatch match;
    regex_search(str, match, reg);
    vector<string> target;
    string order_label = match.str();
    for (int l = 0; l < m[1].size(); l++) {
        if (order_label == m[1][l]) {
            for (int p = 0; p < number.size(); p++) {
                target.emplace_back(m[number[p]][l]);
            }
        }
    }
    sort(target.begin(),target.end());
    vector<string> order = target;
    vector<int> order_index;
    for (int n = 0; n < m[1].size(); n++) {
        if (m[1][n] == order_label) { // supponendo che order_label sia l'etichetta guida
            for (int i = 0; i < order.size(); i++) { // vettore ordinato
                for (int j = 2; j < m.size(); j++) {
                    if (order[i] == m[j][n]) {
                        order_index.emplace_back(j);
                    }
                }
            }
        }
    }

    for (int k = 0; k < order_index.size(); k++) {
        cout << m[order_index[k]] << endl;
    }
}

void Table::select_order_asc(const string& str, const vector<int>& number, const vector<int>& positions) {
    regex reg(R"(\b(?!\bORDER|BY\b)\w+\b)");
    smatch match;
    regex_search(str, match, reg);
    vector<string> target;
    string order_label = match.str();
    for (int l = 0; l < m[1].size(); l++) {
        if (order_label == m[1][l]) {
            for (int p = 0; p < number.size(); p++) {
                target.emplace_back(m[number[p]][l]);
            }
        }
    }
    sort(target.begin(),target.end());
    vector<string> order = target;
    vector<int> order_index;
    for (int n = 0; n < m[1].size(); n++) {
        if (m[1][n] == order_label) { // supponendo che order_label sia l'etichetta guida
            for (int i = 0; i < order.size(); i++) { // vettore ordinato
                for (int j = 2; j < m.size(); j++) {
                    if (order[i] == m[j][n]) {
                        order_index.emplace_back(j);
                    }
                }
            }
        }
    }
    for (int d = 0; d < positions.size(); d++) {
        cout << m[1][positions[d]] << "\t";
    }
    cout << endl;
    for (int it = 0; it < order_index.size(); it++) {
        for (auto l = positions.begin(); l < positions.end(); l++) {
            cout << m[order_index[it]][*l] << "\t";
        }
        cout << endl;
    }
}

void Table::order_desc(const string& str, const vector<int>& number) {
    regex reg(R"(\b(?!\bORDER|BY\b)\w+\b)");
    smatch match;
    regex_search(str, match, reg);
    vector<string> target;
    string order_label = match.str();
    for (int l = 0; l < m[1].size(); l++) {
        if (order_label == m[1][l]) {
            for (int p = 0; p < number.size(); p++) {
                target.emplace_back(m[number[p]][l]);
            }
        }
    }
    sort(target.begin(),target.end());
    vector<string> order = target;
    vector<int> order_index;
    for (int n = 0; n < m[1].size(); n++) {
        if (m[1][n] == order_label) { // supponendo che order_label sia l'etichetta guida
            for (int i = 0; i < order.size(); i++) { // vettore ordinato
                for (int j = 2; j < m.size(); j++) {
                    if (order[i] == m[j][n]) {
                        order_index.emplace_back(j);
                    }
                }
            }
        }
    }

    for (int k = order_index.size() -1 ; k > -1 ; k--) {
        cout << m[order_index[k]] << endl; // stampo al contrario
    }
}

void Table::select_order_desc(const string& str, const vector<int>& number, const vector<int>& positions) {
    regex reg(R"(\b(?!\bORDER|BY\b)\w+\b)");
    smatch match;
    regex_search(str, match, reg);
    vector<string> target;
    string order_label = match.str();
    for (int l = 0; l < m[1].size(); l++) {
        if (order_label == m[1][l]) {
            for (int p = 0; p < number.size(); p++) {
                target.emplace_back(m[number[p]][l]);
            }
        }
    }
    sort(target.begin(),target.end());
    vector<string> order = target;
    vector<int> order_index;
    for (int n = 0; n < m[1].size(); n++) {
        if (m[1][n] == order_label) { // supponendo che order_label sia l'etichetta guida
            for (int i = 0; i < order.size(); i++) { // vettore ordinato
                for (int j = 2; j < m.size(); j++) {
                    if (order[i] == m[j][n]) {
                        order_index.emplace_back(j);
                    }
                }
            }
        }
    }
    for (int d = 0; d < positions.size(); d++) {
        cout << m[1][positions[d]] << "\t";
    }
    cout << endl;
    for (int it = order_index.size() -1; it > -1; it--) {
        for (auto l = positions.begin(); l < positions.end(); l++) {
            cout << m[order_index[it]][*l] << "\t";
        }
        cout << endl;
    }
}

void Table::delete_from_table(const string& s2) {
    string s3, buf4 , buf5;
    if (s2.find(';')!=string::npos) {
        regex regAlpha(R"(^[^;]+)");
        smatch matchAlpha;
        regex_search(s2, matchAlpha, regAlpha);
        s3 = matchAlpha.str();
        if (s3.find("WHERE") != string::npos) {
            regex reg4(R"(\w{0,22}[^ =])");
            regex reg5(R"(\=(.*))");
            smatch match4, match5;
            string s2A = s3.substr(6, string::npos);
            regex_search(s2A, match4, reg4);
            buf4 = match4.str(); // contiene il nome dell'etichetta da controllare
            regex_search(s3, match5, reg5);
            buf5 = match5.str(); // contiene il valore di tale etichetta da controllare
            buf5 = buf5.substr(2, string::npos);
            for (int j = 0; j <m[1].size(); j++) { // scorro la prima fila della mappa per trovare etichetta da controllare
                if (buf4 == m[1][j]) { // verifico che corrisponda
                    for (int it = 2; it < m.size(); it++) { // ora scorro tutte le righe della map per trovare dove assume il valore che cerco
                        if (m[it][j] == buf5) { // controllo che lo assuma
                            m.erase(it);
                        }
                    }
                }
            }
        }
    }
}

vector<string> Table::getlabel(const vector<string>& structure) {
    string s;
    vector <string> vect;
    for (int i = 0; i < structure.size(); i++) {
        if ((structure[i].find("NOT NULL") != string::npos) || (structure[i].find("AUTO_INCREMENT") != string::npos)) {
            if ((structure[i].find("NOT NULL") != string::npos) &&
                (structure[i].find("AUTO_INCREMENT") != string::npos)) {
                s = structure[i].substr(0, structure[i].find(' '));
                n_null.emplace_back(true);
                a_inc.emplace_back(true);
                vect.push_back(s);
            } else if (structure[i].find("NOT NULL") != string::npos) {
                s = structure[i].substr(0, structure[i].find(' '));
                n_null.emplace_back(true);
                a_inc.emplace_back(false);
                vect.push_back(s);
            } else if (structure[i].find("AUTO_INCREMENT") != string::npos) {
                s = structure[i].substr(0, structure[i].find(' '));
                a_inc.emplace_back(true);
                n_null.emplace_back(false);
                vect.push_back(s);
            }
        }
        else {
            s = structure[i].substr(0, structure[i].find(' '));
            vect.push_back(s);
            n_null.emplace_back(false);
            a_inc.emplace_back(false);
        }
    }
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
        } else if ((s.find("AUTO_INCREMENT")!= string::npos) && (s.find("INT")== string::npos)) { // ovvero se definisco un NON int come auto_inc
            cerr << "auto_increment can only be applied to INT data types: try again" << endl;
        } else if (s.find("PRIMARY KEY")!=string::npos) {
            regex reg(R"(\((.*?)\))"); // tutto ciò che è tra ( e )
            smatch match;
            regex_search(s, match, reg);
            primary_key = match[1].str();
        } else if ((s.find("FOREIGN KEY")!=string::npos) && (s.find("REFERENCES")!=string::npos)) {
            regex reg(R"(\((.*?)\))"); // tutto ciò che è tra ( e )
            smatch match, match_extra;
            regex_search(s, match, reg);
            foreign_key = match[1].str(); // il campo dipendente
            string extra = s.substr(s.find("REFERENCES ") +11, string::npos);
            /*regex_search(extra, match_extra, reg);
            string key_check = match_extra[1].str();*/ // il campo indipendente, ma lo commento perchè dovrebbe essere solo quello primary della tabella cui ci riferiamo
            regex reg0(R"(^([\w\-]+))");
            smatch match0;
            regex_search(extra, match0, reg0);
            string table_check = match0[1].str();
            reference = table_check; // ovvero la tabella dipendente si rifà a quella primaria check
        } else {
            names.push_back(s);
        }
    } while (v != 1);
    m[0] = get_types(names);
    m[1] = getlabel(names);
}

int Table::insert_into(const string& str, map <string,Table> database) {
    vector <string> primary_values;
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
                for (int k = 0; k < m[1].size(); k++) { // avvio controllo data types
                    for (int v = 0; v < targets.size(); v++) {
                        if (m[1][k] == targets [v]) {
                            if(!type_check (values [v], m[0][k])) // se ci sta qualche errore dovuto ai tipi
                            {
                                cerr << "wrong data type input: try again" << endl;
                                insert_into(reget_str(), database);
                                return 1;
                            }
                        }
                    }
                } // termine controllo data types
                for (int f = 0; f < targets.size(); f++) { // avvio controllo valori ripetuti prim_key
                    if (targets[f] == primary_key) {
                        for (int g = 0; g < m[1].size(); g++) {
                            if (m[1][g] == primary_key) {
                                for (int n = 2; n < m.size(); n++) {
                                    if (values[f] == m[n][g]) {
                                        cerr << "Primary key field already contains this value: try again"<< endl;
                                        insert_into(reget_str(), database);
                                        return 1;
                                    }
                                }
                            }
                        }
                    }
                } // termine controllo valori ripetuti prim_key
                for (int z = 0; z < targets.size(); z++) { // avvio controllo foreign key, ovvero se la tabella è connessa ad un'altra
                    if (foreign_key == targets[z]) {
                        for ( int y = 0; y < database[reference].get_map()[1].size(); y++) {
                            if (database[reference].get_map()[1][y] == database[reference].get_primary_key()) {
                                for (int w = 2; w < database[reference].get_map().size(); w++) { // HO IL DUBBIO SE W PARTE DA 0, 1 O 2
                                    primary_values.emplace_back(database[reference].get_map()[w][y]); // vettore per confrontare i valori
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
                        if (foreign_key==targets[z]) {
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
                    insert_into(error, database);
                    return 1; // ho piazzato il return altrimenti avrebbe continuato da qua e sovrascritto
                } // termine controllo foreign key
                for (int it = 0; it < m[1].size(); it++) { // inserimento provvisorio dei valori
                    int count = 0;
                    for (int it2 = 0; it2 < targets.size(); it2++) {
                        if (targets[it2] == m[1][it]) {
                            records.push_back(values[it2]);
                            count = 1;
                        }
                    }
                    if (count == 0) {
                        records.emplace_back("\t");
                    }
                }
                for (int p = 0; p < n_null.size(); p++) { // avvio controllo not null
                    bool c = true;
                    if (n_null[p] == true) {
                        c = false;
                        for (int d = 0; d < targets.size(); d++) {
                            if (m[1][p] == targets[d]) {
                                c = true;
                            }
                        }
                    }
                    if (!c) {
                        records[p] = "std_val";
                    }
                } // termine controllo not null
                m[i] = records; // inserimento effettivo dei valori
                for (int y = 0; y < a_inc.size(); y++) { // avvio eventuale correzione dovuta ad auto_inc
                    if (a_inc[y] == true) {
                        string str_value = to_string(a_inc_count);
                        m[i][y] = str_value;
                    }
                } // termine eventuale correzione dovuta ad auto_inc
            }
            a_inc_count++;
        } else { //richiama se stessa così da poter inserire tutto finchè non metto roba giusta
            cerr << "syntax error, try again" << endl;
            string string1;
            getline(cin, string1);
            insert_into(string1, database);
        }
    }
    return 1;
}

int Table::update_record() { // IMPORTANTE CONTROLLO RICORSIONE         LUPO 07/07/20
    string s1, s2 , buf, buf2, buf3, buf4, buf5;
    vector < string > set_names , set_values;
    getline ( cin, s1);
    if (s1.find("SET")!=string::npos) {
        string s1A = s1.substr(4, string::npos );
        stringstream ss(s1A);
        while (getline ( ss , buf , ',')) {
            regex reg2(R"(\w{0,22}[^ =])"); // ciò che è a sx dell'uguale, anche se in realtà il match prenderebbe la roba prima E quella dopo
            regex reg3(R"(\=(.*))"); // ciò che è a dx dell'uguale, uguale compreso
            smatch match2, match3;
            regex_search(buf, match2, reg2);
            buf2 = match2.str();
            set_names.push_back(buf2); // il names ora contiene i nomi dei campi da modificare
            regex_search(buf, match3, reg3);
            buf3 = match3.str();
            buf3 = buf3.substr(2, string::npos); // elimino l'uguale dal match
            set_values.push_back(buf3); // il values ora contiene i valori da inserire nei campi da modificare
        }
        getline ( cin, s2);
        if (s2.find(';')!=string::npos) {
            regex regAlpha(R"(^[^;]+)");
            smatch matchAlpha;
            regex_search(s2, matchAlpha, regAlpha);
            s2 = matchAlpha.str();
            if (s2.find("WHERE")!= string::npos) {
                regex reg4(R"(\w{0,22}[^ =])");
                regex reg5(R"(\=(.*))");
                smatch match4, match5;
                string s2A = s2.substr(6, string::npos);
                regex_search(s2A, match4, reg4);
                buf4 = match4.str(); // contiene il nome dell'etichetta da controllare
                regex_search(s2, match5, reg5);
                buf5 = match5.str(); // contiene il valore di tale etichetta da controllare
                buf5 = buf5.substr(2, string::npos);
                for (int k = 0; k < m[1].size(); k++) { // avvio controllo data types
                    for (int v = 0; v < set_names.size(); v++) {
                        if (m[1][k] == set_names [v]) {
                            if(!type_check (set_values [v], m[0][k])) // se ci sta qualche errore dovuto ai tipi
                            {
                                cerr << "wrong data type input: try again. First line MUST be skipped (= UPDATE + name)" << endl;
                                update_record();
                                return 0;
                            }
                        }
                    }
                } // termine controllo data types
                for (int k = 0; k < m[1].size(); k++) { // avvio controllo tentativo di sovrascrittura di dato auto_inc
                    for (int v = 0; v < set_names.size(); v++) {
                        if (m[1][k] == set_names[v]) {
                            if (a_inc[k] == true) {
                                cerr << "auto_increment data cannot be updated: try again. First line MUST be skipped (= UPDATE + name)" << endl;
                                update_record();
                                return 0;
                            }
                        }
                    }
                }  // termine controllo tentativo di sovrascrittura di dato auto_inc
                for (int j = 0; j <m[1].size(); j++) { // scorro la prima fila della mappa per trovare etichetta da controllare
                    if (buf4 == m[1][j]) { // verifico che corrisponda
                        for (int it = 2; it <m.size(); it++) { // ora scorro tutte le righe della map per trovare dove assume il valore che cerco
                            if (m[it][j] == buf5) { // controllo che lo assuma
                                for (int k = 0;k < set_names.size(); k++) { // vedo via via quali sono le etichette da modificare
                                    for (int l = 0; l < m[1].size(); l++) { // e vedo a che posizione corrispondono nella prima riga
                                        if (set_names[k] == m[1][l]) { // appena trovo un match
                                            m[it][l] = set_values[k]; // sostituisco il valore nuovo, corrispondente alla posizione di set_names
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}

int Table::size() {
    return m.size();
}

vector<string> Table::line(const int& idx) {
    return m[idx];
}

void Table::print_table(const string& str, map <string,Table> database) {
    if (str.find('*') != string::npos) {
        string from;
        getline(cin, from);
        if ((from.find("FROM") != string::npos) && (from.find(';') != string::npos)) {
            regex regAlpha(R"(^[^;]+)");
            smatch matchAlpha;
            regex_search(from, matchAlpha, regAlpha);
            from = matchAlpha.str();
            regex reg(R"(\b(?!\bFROM\b)\w+\b)");
            smatch match;
            regex_search(from, match, reg);
            string s = match.str();
            for (int i = 1; i < database[s].get_map().size(); i++) {
                cout << database[s].get_map()[i] << endl;
            }
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
                    string buf3 = match2.str().substr(2, string::npos); // contiene il valore dell'etichetta da controllare
                    vector<int> number;
                    for (int a = 0; a < database[s].get_map()[1].size(); a++) {
                        if (buf2 == database[s].get_map()[1][a]) {
                            for (int it = 2; it < database[s].get_map().size(); it++) {
                                if (buf3 == database[s].get_map()[it][a]) {
                                    number.emplace_back(it); // contiene tutti gli indici dei record dove la condizione WHERE è soddisfatta
                                }
                            }
                        }
                    }
                    cout << database[s].get_map()[1] << endl;
                    for (auto ti = number.begin(); ti < number.end(); ti++) {
                        cout << database[s].get_map()[*ti] << endl;
                    }
                } else {
                    string order_by;
                    getline(cin, order_by);
                    if ((order_by.find("ORDER BY") != string::npos) && (order_by.find(';') != string::npos)) {
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
                        string buf3 = match2.str().substr(2, string::npos); // contiene il valore dell'etichetta da controllare
                        vector<int> number;
                        for (int a = 0; a < database[s].get_map()[1].size(); a++) {
                            if (buf2 == database[s].get_map()[1][a]) {
                                for (int it = 2; it < database[s].get_map().size(); it++) {
                                    if (buf3 == database[s].get_map()[it][a]) {
                                        number.emplace_back(it); // contiene tutti gli indici dei record dove la condizione WHERE è soddisfatta
                                    }
                                }
                            }
                        }
                        if (order_by.find("ASC") != string::npos) {
                           database[s].order_asc(order_by, number);
                        } else if (order_by.find("DESC") != string::npos) {
                            database[s].order_desc(order_by, number);
                        }
                    }
                }
            } else if ((where.find("ORDER BY") != string::npos) && (where.find(';') != string::npos)) {
                regex reg9(R"(\b(?!\bFROM\b)\w+\b)");
                smatch match9;
                regex_search(from, match9, reg9);
                string s = match9.str();
                regex regAlpha(R"(^[^;]+)");
                smatch matchAlpha;
                regex_search(where, matchAlpha, regAlpha);
                where = matchAlpha.str();
                vector <int> number;
                for (int e = 2; e < database[s].get_map().size(); e++) {
                    number.emplace_back(e);
                }
                if (where.find("ASC") != string::npos) {
                    database[s].order_asc(where, number);
                } else if (where.find("DESC") != string::npos) {
                    database[s].order_desc(where, number);
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
                    vect.emplace_back(buf0); // vect contiene i campi che vogliamo stampare
                }
                vector<int> positions;
                for (int j = 0; j < vect.size(); j++) {
                    for (int k = 0; k < database[s].get_map()[1].size(); k++) {
                        if (vect[j] == database[s].get_map()[1][k]) {
                            cout << database[s].get_map()[1][k] << "\t";
                            positions.emplace_back(k); // positions contiene gli indici delle colonne delle etichette che ci interessa visualizzare
                        }
                    }
                }
                cout << endl;
                for (int it = 2; it < database[s].get_map().size(); it++) {
                    for (auto l = positions.begin(); l < positions.end(); l++) {
                        cout << database[s].get_map()[it][*l] << "\t";
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
                        string buf3 = match2.str().substr(2, string::npos); // contiene il valore dell'etichetta da controllare
                        vector<int> number;
                        for (int a = 0; a < database[s].get_map()[1].size(); a++) {
                            if (buf2 == database[s].get_map()[1][a]) {
                                for (int it = 2; it < database[s].get_map().size(); it++) {
                                    if (buf3 == database[s].get_map()[it][a]) {
                                        number.emplace_back(it); // contiene tutti gli indici delle righe (record) dove la condizione WHERE è soddisfatta
                                    }
                                }
                            }
                        }
                        vector<int> positions;
                        for (int j = 0; j < vect.size(); j++) {
                            for (int k = 0; k < database[s].get_map()[1].size(); k++) {
                                if (vect[j] == database[s].get_map()[1][k]) {
                                    cout << database[s].get_map()[1][k] << "\t";
                                    positions.emplace_back(k); // positions contiene gli indici delle colonne delle etichette che ci interessa visualizzare
                                }
                            }
                        }
                        cout << endl;
                        for (auto b = number.begin(); b < number.end(); b++) {
                            for (auto l = positions.begin(); l < positions.end(); l++) {
                                cout << database[s].get_map()[*b][*l] << "\t";
                            }
                            cout << endl;
                        }
                    } else {
                        string order_by;
                        getline(cin, order_by);
                        if ((order_by.find("ORDER BY") != string::npos) && (order_by.find(';') != string::npos)) {
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
                            string buf3 = match2.str().substr(2, string::npos); // contiene il valore dell'etichetta da controllare
                            vector<int> number;
                            for (int a = 0; a < database[s].get_map()[1].size(); a++) {
                                if (buf2 == database[s].get_map()[1][a]) {
                                    for (int it = 2; it < database[s].get_map().size(); it++) {
                                        if (buf3 == database[s].get_map()[it][a]) {
                                            number.emplace_back(it); // contiene tutti gli indici delle righe (record) dove la condizione WHERE è soddisfatta
                                        }
                                    }
                                }
                            }
                            vector<int> positions;
                            for (int j = 0; j < vect.size(); j++) {
                                for (int k = 0; k < database[s].get_map()[1].size(); k++) {
                                    if (vect[j] == database[s].get_map()[1][k]) {
                                        positions.emplace_back(k); // positions contiene gli indici delle colonne delle etichette che ci interessa visualizzare
                                    }
                                }
                            }
                            if (order_by.find("ASC") != string::npos) {
                                database[s].select_order_asc(where, number, positions);
                            } else if (order_by.find("DESC") != string::npos) {
                                database[s].select_order_desc(where, number, positions);
                            }
                        }
                    }
                } else if ((where.find("ORDER BY") != string::npos) && (where.find(';') != string::npos)) {
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
                        vect.emplace_back(buf0); // vect contiene i campi che vogliamo stampare
                    }
                    vector<int> positions;
                    for (int j = 0; j < vect.size(); j++) {
                        for (int k = 0; k < database[s].get_map()[1].size(); k++) {
                            if (vect[j] == database[s].get_map()[1][k]) {
                                positions.emplace_back(k); // positions contiene gli indici delle colonne delle etichette che ci interessa visualizzare
                            }
                        }
                    }
                    vector <int> number;
                    for (int e = 2; e < database[s].get_map().size(); e++) {
                        number.emplace_back(e);
                    }
                    if (where.find("ASC") != string::npos) {
                        database[s].select_order_asc(where, number, positions);
                    } else if (where.find("DESC") != string::npos) {
                        database[s].select_order_desc(where, number, positions);
                    }
                }
            }
        }
    }
}

void Table::save_table( map <string,Table>& database, const vector <string> &table_names) {
    int i = 0;
    for (const auto&it : database)
    {
        //ofstream outf(table_names[i] + ".txt");
        ofstream outf (table_names[i] + ".bin", ios::binary);
        outf << it.second.m << endl;
        outf.close();
        i++;
    }
} // salva le varie tabelle su file singoli
