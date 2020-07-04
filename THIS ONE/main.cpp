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
    os << t.get_map() << endl;
    return os;
}

int main() {
   
    time_t now;
    time (&now);
    cout << ctime (&now) << endl;
    Date daje;
    daje.get_day("03/07/2020");
    Time time;
    time.get_time("14:45:58");
    map <string,Table> database;
    Table t;
    int q = 0;
   do {
        string command;
        getline(cin, command);
        if (command.find("CREATE") != string::npos) {
            string name = t.create_Table(command);
            database[name].set_target_names();
            //cout << database[name] << endl;
            cout << endl;
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
           database[name].insert_into(command);
            cout << database[name] << endl;
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
        } else if (command.find("QUIT") != string::npos) {
            q = 1;
        } else {
            cerr << "Oooops, something went wrong. Try again" << endl << endl; // così se sbaglia comando ripete subito
        }
        //print_Table();
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


