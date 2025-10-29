#pragma once
#include "common_includes.h"

class Problem {
private:
    string problemID;
    string title;
    string statement;
    string difficulty;
    string timeLimit;
    vector<string> tags;
    string sampleOutput;
    string solutionCode;
    string editorial;
    static int problemCount;

public:
    Problem();
    Problem(string id, string title, string stmt, string diff, string limit,
            string sampleOut, string solution, string edit, const vector<string>& tagsVec);
    Problem(string fileLine);
    void showProblemDetails() const;
    void showEditorial() const;
    bool checkSolution(const string& submittedCode) const;
    string getProblemID() const;
    string getTitle() const;
    const vector<string>& getTags() const;
    string forFile() const;

    bool operator==(const Problem& other) const;

    static int getProblemCount();
    static void setProblemCount(int count);
    static void incrementProblemCount();
};