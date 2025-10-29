#pragma once
#include "common_includes.h" // Include common headers

class User {
private:
    string username;
    string password;
    string role;
    int rating;
    vector<string> favoriteProblemIDs;
    int solvedCount;
    static int totalUsers;

public:
    User();
    User(string uname, string pass, string urole, int urating);
    User(string fileLine);
    void displayProfile() const;
    bool checkPassword(const string& pass) const;
    void addFavoriteProblem(const string& problemID);
    void incrementSolvedCount();
    string getUsername() const;
    string getRole() const;
    int getRating() const;
    int getSolvedCount() const;
    const vector<string>& getFavoriteProblemIDs() const;
    string forFile() const;

    User operator+(const User &other) const;
    // Friend function DECLARATION
    friend void showNotification(const User& user, const string& message);
    static int getTotalUsers();
    static void setTotalUsers(int count);
};