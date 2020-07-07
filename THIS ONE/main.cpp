#include "Table.h"
#include <ctime>
#include "Date.h"
#include "Time.h"

//ci siamo dimenticati la push_back nel vettore target_names? (contenitore di tutti i nomi delle tabelle)
//ricordiamoci quando faremo update                         30/06/2020 Evry

//Ho momenteamente spostato "operatore stampa vettore in "Table.h" perchè mi serviva nel metodo "print_table"
//Dovremmo mettere tutti gli operatori in una classe template? Probabilmente sì.
//Potevo fare di meglio e mettere l'operatore sotto "Control.h"? Ovvio!
//Re-edit: alla fine ho messo tutto in Control.h, la classe template dava troppe grane ed errori    30/06/2020 Evry


ostream& operator<<(ostream& os, Table& t){ // operatore stampa tabella
    os << t.get_map();
    return os;
}

int main() {
    /*time_t now;
    time (&now);
    cout << ctime (&now) << endl;
    Date daje;
    daje.get_day("03/07/2020");
    Time time;
    time.get_time("14:45:58");*/ // ho commentato per non "sporcare" ogni volta quando avvio il codice
    map <string,Table> database;
    vector<string> database_names;
    Table t;
    int q = 0;
   do {
        string command;
        getline(cin, command);
        if (command.find("CREATE") != string::npos) {
            string name = t.create_Table(command); // ottengo il nome della mia prossima tabella
                                                      // di fatto non serve t, potremmo portarlo fuori? Lupo 05/07
            database[name].set_target_names();
            //cout << database[name] << endl;
            database_names.emplace_back(name);
            cout << "Table " + name + " successfully created" << endl << endl;
        }/*
        else if (command.find("UPDATE") != string::npos) {
            update_record(command);
            cout << endl;
        }*/
        else if (command.find("INSERT") != string::npos) {
            regex reg(R"(\b(?!\bINSERT|INTO\b)\w+\b)");         //ci va un if/else nel caso in cui sia inserito male? 30/06 Evry
            smatch match;
            regex_search(command, match, reg);
            string name = match.str();
           database[name].insert_into(command, database);  // IMPORTANTE: ADESSO MANDO DATABASE A INSERT INTO PER POTER AVER TRACCIA DELLE ALTRE TABLE PER IL COLLEGAMENTO Lupo 05/07
            cout << database[name] << endl;
            cout << "Record successfully inserted into Table " + name << endl << endl;
        }  else if (command.find("UPDATE") != string::npos) {
            regex reg(R"(\b(?!\bUPDATE\b)\w+\b)");
            smatch match;
            regex_search(command, match, reg);
            string name= match.str();
            database[name].update_record(command);
            cout << "Table " + name + " successfully updated" << endl << endl;
        } else if (command.find("SELECT") != string::npos) { //aggiunto print_table con SELECT. Non collaudato
            regex regAlpha(R"(^[^;]+)");        //Ho un po' scopiazzato da "insert_into". Ho spostato le regex, ecc fuori dal metodo
            smatch matchAlpha;                       //in modo da poter poi avere database[name] al posto di t.     30/06/2020  Evry
            regex_search(command, matchAlpha, regAlpha);
            command = matchAlpha.str();
            regex reg(R"(\b(?!\bFROM\b)\w+\b)");
            smatch match;
            regex_search(command, match, reg);
            string name = match.str();
            database[name].print_table(command);
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
                    database.erase(drop);
                    vector<string>::iterator del;
                    del = find(database_names.begin(), database_names.end(), drop);
                    database_names.erase(del);
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
                }
            }
        } else if (command.find("ORDER") != string::npos) {
            regex reg(R"(\b(?!\bORDER|FROM\b)\w+\b)");         //ci va un if/else nel caso in cui sia inserito male? 30/06 Evry
            smatch match;
            regex_search(command, match, reg);
            string name = match.str();
            database[name].ordiniamoli();
        } else if (command.find("DELETE") != string::npos) {
            regex reg(R"(\b(?!\bDELETE|FROM\b)\w+\b)");
            smatch match;
            regex_search(command, match, reg);
            string table_name= match.str();
            string s2;
            getline ( cin, s2);
            database[table_name].delete_from_table(s2);
        } else if (command.find("QUIT()") != string::npos) {
            q = 1;
        } else {
            cerr << "Oooops, something went wrong. Try again" << endl << endl; // così se sbaglia comando ripete subito
        }
    } while (q != 1);
    /*if (q==1) {
        for (const auto &x : m) {
            cout << x.second << endl;
        }
        // salvo su file essendo comando QUIT
        exit(0);
    }*/
    return 0;
    }


