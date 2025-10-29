#include "Leaderboard.h"
#include "User.h" // Now include the full User definition

// Define comparison functions (can also be in main or utils)
bool compareByRating(const User& u1, const User& u2) {
    return u1.getRating() > u2.getRating();
}
bool compareBySolvedCount(const User& u1, const User& u2) {
    return u1.getSolvedCount() > u2.getSolvedCount();
}


Leaderboard::Leaderboard() {} // Constructor

void Leaderboard::displayByRating(const vector<User>& allUsers) const {
    if (allUsers.empty()) { cout << "\nNo users to display on leaderboard." << endl; return; }
    vector<User> sortedUsers = allUsers; // Make copy
    sort(sortedUsers.begin(), sortedUsers.end(), compareByRating); // Sort copy
    (*this)("By Rating"); // Use operator()
    cout << "------------------------------------------" << endl; cout << left << setw(6) << "Rank" << setw(20) << "Username" << setw(10) << "Rating" << endl; cout << "------------------------------------------" << endl;
    int rank = 1; for (const User& user : sortedUsers) { if (user.getRole() == "contestant") { cout << left << setw(6) << rank++ << setw(20) << user.getUsername() << setw(10) << user.getRating() << endl; } }
    cout << "------------------------------------------" << endl;
}

void Leaderboard::displayBySolvedCount(const vector<User>& allUsers) const {
    if (allUsers.empty()) { cout << "\nNo users to display on leaderboard." << endl; return; }
    vector<User> sortedUsers = allUsers; // Make copy
    sort(sortedUsers.begin(), sortedUsers.end(), compareBySolvedCount); // Sort copy
    (*this)("By Solved Count"); // Use operator()
    cout << "------------------------------------------" << endl; cout << left << setw(6) << "Rank" << setw(20) << "Username" << setw(10) << "Solved" << endl; cout << "------------------------------------------" << endl;
    int rank = 1; for (const User& user : sortedUsers) { if (user.getRole() == "contestant") { cout << left << setw(6) << rank++ << setw(20) << user.getUsername() << setw(10) << user.getSolvedCount() << endl; } }
    cout << "------------------------------------------" << endl;
}

void Leaderboard::operator()(const string& title) const {
    cout << "\n--- Leaderboard: " << title << " ---" << endl;
}