#include "Table.h"
#include <ctime>
#include "Date.h"
#include "Time.h"


/*ostream& operator<<(ostream& os, Table& t){ // operatore stampa tabella
    os << t.get_map();
    return os;
}*/ // ho commentato perchè forse potremmo toglierlo dato che non lo richiamiamo mai nel main

int main() {
    map <string,Table> database;
    vector<string> database_names;
    Table t;
    Control c;
    c.upload_tablenames(database_names);
    for (int in = 0; in < database_names.size(); in++)
    {
        Table obj_buff;
        obj_buff.uploader(database_names[in]);
        obj_buff.upload_ainc(database_names[in]);
        obj_buff.upload_nnull(database_names[in]);
        obj_buff.upload_keys(database_names[in]);
        database[database_names[in]] = obj_buff;
    }
    int q = 0;
   do {
        string command;
        getline(cin, command);
        if (command.find("CREATE") != string::npos) {
            string name = t.create_Table(command);
            bool b = database[name].set_target_names(database);
            if (!b) {
                database.erase(name);
            } else {
                database_names.emplace_back(name);
                cout << "Table " + name + " successfully created" << endl << endl;
            }
        } else if (command.find("INSERT") != string::npos) {
            regex reg(R"(\b(?!\bINSERT|INTO\b)\w+\b)");         //ci va un if/else nel caso in cui sia inserito male? 30/06 Evry
            smatch match;
            regex_search(command, match, reg);
            string name = match.str();
           database[name].insert_into(command, database);  // IMPORTANTE: ADESSO MANDO DATABASE A INSERT INTO PER POTER AVER TRACCIA DELLE ALTRE TABLE PER IL COLLEGAMENTO Lupo 05/07
            cout << "Record successfully inserted into Table " + name << endl << endl;
        }  else if (command.find("UPDATE") != string::npos) {
            regex reg(R"(\b(?!\bUPDATE\b)\w+\b)");
            smatch match;
            regex_search(command, match, reg);
            string name= match.str();
            database[name].update_record();
            cout << "Table " + name + " successfully updated" << endl << endl;
        } else if (command.find("SELECT") != string::npos) {
            t.print_table(command, database);
            cout << endl;
        } else if (command.find("DROP") != string::npos) {
            if (command.find(';') != string::npos) {
                regex regAlpha(R"(^[^;]+)");
                smatch matchAlpha;
                regex_search(command, matchAlpha, regAlpha);
                command = matchAlpha.str();
                if (command.find("DROP TABLE") != string::npos) {
                    regex reg(R"(\b(?!\bDROP|TABLE\b)\w+\b)");
                    smatch match;
                    regex_search(command, match, reg);
                    string drop = match.str();
                    if (database[drop].get_map().empty()) {
                        cerr << "No such map exists" << endl;
                    } else {
                        database.erase(drop);
                        vector<string>::iterator del;
                        del = find(database_names.begin(), database_names.end(), drop);
                        database_names.erase(del);
                        cout << "Table " + drop + " successfully removed" << endl << endl;
                    }
                }
            }
        } else if (command.find("TRUNCATE") != string::npos) {
            if (command.find(';')!=string::npos) {
                regex regAlpha(R"(^[^;]+)");
                smatch matchAlpha;
                regex_search(command, matchAlpha, regAlpha);
                command = matchAlpha.str();
                if (command.find("TRUNCATE TABLE") != string::npos) {
                    regex reg(R"(\b(?!\bTRUNCATE|TABLE\b)\w+\b)");
                    smatch match;
                    regex_search(command, match, reg);
                    string drop = match.str();
                    database[drop].get_map().erase(2); // svuoto la map corrispondente al nome indicato, utilizzato come indice drop dalla riga 2 così restano le etichette
                    cout << "Table " + drop + " successfully truncated" << endl << endl;
                }
            }
        } else if (command.find("DELETE") != string::npos) {
            regex reg(R"(\b(?!\bDELETE|FROM\b)\w+\b)");
            smatch match;
            regex_search(command, match, reg);
            string table_name= match.str();
            string s2;
            getline ( cin, s2);
            database[table_name].delete_from_table(s2);
            cout << "Table " + table_name + " successfully deleted" << endl << endl;
        } else if (command.find("QUIT()") != string::npos) {
            q = 1;
        } else {
            cerr << "Oooops, something went wrong. Try again" << endl << endl; // così se sbaglia comando ripete subito
        }
    } while (q != 1);
    for (int k= 0; k < database_names.size(); k++) {
        database[database_names[k]].save_table(database_names[k]);
        database[database_names[k]].save_ainc(database_names[k]);
        database[database_names[k]].save_nnull(database_names[k]);
        database[database_names[k]].save_keys(database_names[k]);
    }
    c.save_tablenames(database_names); // creo i file ognuno con un nome
    return 0;
}



