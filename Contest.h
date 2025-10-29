#pragma once
#include "common_includes.h"

// Forward declarations
class Submission;
class Problem;

class Contest {
public:
    // Keep Standing struct public or make accessors if needed by compare func
    struct Standing {
        string username;
        int score;
        Standing() : username(""), score(0) {}
        Standing(string u, int s) : username(u), score(s) {}
    };
private:
    string contestID;
    string contestName;
    vector<string> problemIDs;
    map<string, int> standings; // username -> score map

public:
    Contest();
    Contest(string cID, string name);
    Contest(string fileLine);
    void addProblem(const string& pID);
    void registerSubmission(const Submission& sub);
    void showStandings() const;
    void displayContestProblems(const vector<Problem>& allProblems) const;
    string getContestID() const;
    string getContestName() const;
    const vector<string>& getProblemIDs() const;
    string forFile() const;

    friend bool compareStandingsPair(const pair<string, int>& a, const pair<string, int>& b);
    friend ostream& operator<<(ostream& os, const Contest& contest);
};

// Declare comparison function for sorting pairs (needs to be visible)
bool compareStandingsPair(const pair<string, int>& a, const pair<string, int>& b);