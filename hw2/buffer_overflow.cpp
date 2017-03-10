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
        x = random_number(4) % 5 + 1;
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
    char tickets[b];
    cout << "\nHow many tickets would you like to buy for " << game_name(atoi(game))<< "?\n > ";
    scanf("%s", tickets);

    int num_tickets = atoi(tickets);

    // Section number
    char section_num[3];
    int section1 = 112;
    int section2 = 201;
    int section3 = 313;
    double section1_cost = random_number(section1);
    double section2_cost = random_number(section2);
    double section3_cost = random_number(section3);

    cout << "\nWe have " << num_tickets << " tickets seated together in the following sections:\n";
    int section;
    while (!regex_match(section_num, regex("(112|201|313)"))) {
	cout << "  Section " << section1 << " - $" << section1_cost << " each\n";
        cout << "  Section " << section2 << " - $" << section2_cost << " each\n";
        cout << "  Section " << section3 << " - $" << section3_cost << " each\n";
        cout << "\nWhich section would you like to sit in?\n > ";

        scanf("%s", section_num);

        section = atoi(section_num);
    }

    double ticket_price;
    if (section == section1)
        ticket_price = section1_cost;
    else if (section == section2)
        ticket_price = section2_cost;
    else
        ticket_price = section3_cost;

    double cost = ticket_price * num_tickets;

    if (cost > 0 && num_tickets > 0) {
        cout << "\nOk, we have reserved " << num_tickets << " tickets in section " <<
          section << " for " << game_name(atoi(game)) << ". The total cost is $" <<
          cost <<". Please pick them up in the box office. Have a nice day!\n\n";
    } else {
        cout << "Uh oh, " << num_tickets << " tickets at $" << ticket_price << " means we own you $" << cost * -1 << "!\n";
    }

    return 0;
}
