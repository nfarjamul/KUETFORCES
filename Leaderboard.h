#pragma once
#include "common_includes.h"

// Forward declare User to avoid full include if possible
class User;

class Leaderboard {
public:
    Leaderboard();
    void displayByRating(const vector<User>& allUsers) const;
    void displayBySolvedCount(const vector<User>& allUsers) const;
    void operator()(const string& title) const;
};

// Define comparison functions here or in .cpp (must be visible to sort)
bool compareByRating(const User& u1, const User& u2);
bool compareBySolvedCount(const User& u1, const User& u2);