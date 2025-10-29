#pragma once
#include "common_includes.h"

class Submission{
private:
    string submissionID;
    string problemID;
    string username;
    string submittedCode;
    string verdict;
    string submissionTime;

public:
    Submission();
    Submission(string sID, string pID, string uName, string code, string time);
    Submission(string fileLine);
    void setVerdict(const string& v);
    void displaySubmission() const;
    string getProblemID() const;
    string getUsername() const;
    string getVerdict() const;
    string getSubmissionID() const;
    string forFile() const;

    bool operator<(const Submission& other) const;
};