// buffer_overflow.cpp

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <regex>
#include <ctime>
#include <cstring>

using namespace std;

const char* game_name(int number) {
    if (number == 1)
        return "SMU vs. Tulsa 3/2/2017";
    else if (number == 2)
        return "SMU vs. Memphis 3/4/2017";
    else if (number == 3)
        return "SMU vs. Cincinnati 3/12/2017";
    else
       return "";
}

int random_number(int seed) {
    srand(time(0) + seed);
    return rand() % 300 + 1;
}

int main(int argv, char *argc[]) {
    cout << "===================================\n";
    cout << "|         SMU Ticket Office       |\n";
    cout << "===================================\n";

    int b = (((4000 / 32) + 25) - 35 * -30 + 2432) % 42; // 20

    string l;
    fstream f("tmp.txt");
    int x;
    if (f.is_open()) {
        getline(f, l);
        x = stoi(l);
        f.seekg(0, f.beg);
        f << x + 1 << endl;
        f.close();
    } else {
        x = 1;
    }

    b = b + x;
    cout << "BUFFER LENGTH: " << b << endl;

    // Game selection
    char game[20] = "0";
    cout << "Games available for purchase\n";
    game[19] = '\0';
    while (!regex_match(game, regex("(1|2|3)"))) {
        cout << "  1: " << game_name(1) << "\n  2: " << game_name(2) << "\n  3: " << game_name(3) << "\n\nWhich game would you like to buy tickets for?\n > ";
        cin >> game;
    }

    // Number of tickets selection
    /* char* tickets = new char[5]; */
    char tickets[5] = "0";
    cout << "\nHow many tickets would you like to buy for " << game_name(atoi(game))<< "?\n > ";
    cin >> tickets;

    /* int num_tickets = atoi(tickets); */

    // Section number
    char section[20] = "";
    int section1 = 112;
    int section2 = 201;
    int section3 = 313;
    double section1_cost = random_number(section1);
    double section2_cost = random_number(section2);
    double section3_cost = random_number(section3);

    cout << "\nWe have " << atoi(tickets) << " tickets seated together in the following sections:\n";
    section[19] = '\0';
    while (!regex_match(section, regex("(112|201|313)"))) {
        cout << "  Section " << section1 << " - $" << section1_cost << " each\n";
        cout << "  Section " << section2 << " - $" << section2_cost << " each\n";
        cout << "  Section " << section3 << " - $" << section3_cost << " each\n";
        cout << "\nWhich section would you like to sit in?\n > ";
        cin >> section;
    }

    double cost;
    if (atoi(section) == section1)
        cost = section1_cost * atoi(tickets);
    else if (atoi(section) == section2)
        cost = section2_cost * atoi(tickets);
    else
        cost = section3_cost * atoi(tickets);

    cout << "\nOk, we have reserved " << atoi(tickets)<< " tickets in section " <<
      section << " for " << game_name(atoi(game)) << ". The total cost is $" <<
      cost <<". Please pick them up in the box office. Have a nice day!\n\n";

    return 0;
}
