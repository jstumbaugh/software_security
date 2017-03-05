// buffer_overflow.cpp

#include <iostream>
#include <cstdlib>

using namespace std;

const char* game_name(int number) {
    if (number == 1)
        return "SMU vs. Tulsa 3/2/2017";
    else if (number == 2)
        return "SMU vs. Memphis 3/4/2017";
    else if (number == 3)
        return "SMU vs. Cincinnati 3/12/2017";
}

int random_number() {
    return rand() % 300 + 1;
}

int main(int argv, char *argc[]) {
    cout << "===================================\n";
    cout << "|         SMU Ticket Office       |\n";
    cout << "===================================\n";

    // Game selection
    char game[20] = "0";
    cout << "Games available for purchase\n";
    while (atoi(game) != 1 && atoi(game) != 2 && atoi(game) != 3) {
        cout << "  1: " << game_name(1) << "\n  2: " << game_name(2) << "\n  3: " << game_name(3) << "\n\nWhich game would you like to buy tickets for?\n > ";
        cin >> game;
        cout << game << endl;
    }

    // Number of tickets selection
    char tickets[20] = "0";
    cout << "\nHow many tickets would you like to buy for " << game_name(atoi(game))<< "?\n > ";
    cin >> tickets;
    int num_tickets = atoi(tickets);

    // Section number
    char section[20] = "0";
    int section1 = random_number();
    int section2 = random_number();
    int section3 = random_number();
    double section1_cost = random_number();
    double section2_cost = random_number();
    double section3_cost = random_number();

    cout << "\nWe have " << num_tickets << " tickets seated together in the following sections:\n";
    cout << "  Section " << section1 << " - $" << section1_cost << " each\n";
    cout << "  Section " << section2 << " - $" << section2_cost << " each\n";
    cout << "  Section " << section3 << " - $" << section3_cost << " each\n";
    cout << "\nWhich section would you like to sit in?\n > ";
    cin >> section;

    cout << section << endl;

    return 0;
}
