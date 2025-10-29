#pragma once
#include "common_includes.h"
#include "User.h"         // Include necessary headers
#include "Problem.h"
#include "Submission.h"
#include "Contest.h"
#include "Leaderboard.h"

class KuETforces {
private:
    vector<User> allUsers;
    vector<Problem> allProblems;
    vector<Submission> allSubmissions;
    vector<Contest> allContests;
    Leaderboard leaderboard;
    User* currentUser; // Pointer TO a User in allUsers

    // Private helper functions
    int showMainMenu();
    bool login();
    void signUp();
    int showAdminMenu();
    int showContestantMenu();
    void loadAllData();
    void saveData();
    void admin_addProblem();
    void admin_createContest();
    void admin_banUser();
    void contestant_viewProfile();
    void contestant_viewProblemset();
    void contestant_submitSolution(Problem* prob);
    void contestant_viewContests();
    void contestant_viewLeaderboard();

public:
    KuETforces();
    // No destructor needed for vector members
    void run();

    // Function Overloads
    Problem* searchProblem(const string& problemID); // Returns pointer into vector
    vector<Problem> searchProblemByTag(const string& tag); // Returns vector copy

    // Operator Overload
    KuETforces& operator+=(const User& newUser);
};