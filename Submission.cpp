#include "Submission.h" // Include the header file for Submission class

Submission::Submission() : submissionID("N/A"), problemID("N/A"), username("N/A"), verdict("N/A") {}

Submission::Submission(string sID, string pID, string uName, string code, string time) :
    submissionID(sID), problemID(pID), username(uName), submittedCode(code), verdict("Pending"), submissionTime(time) {}

Submission::Submission(string fileLine) : submissionID("ERR"), problemID("ERR"), username("ERR"), verdict("Error") {
    stringstream ss(fileLine); string temp_sid, temp_pid, temp_uname, temp_code, temp_verdict, temp_time;
    if (getline(ss, temp_sid, '|') && getline(ss, temp_pid, '|') && getline(ss, temp_uname, '|') && getline(ss, temp_code, '|') &&
        getline(ss, temp_verdict, '|') && getline(ss, temp_time)) {
        this->submissionID = temp_sid; this->problemID = temp_pid; this->username = temp_uname;
        this->submittedCode = temp_code; this->verdict = temp_verdict; this->submissionTime = temp_time;
    } else { cerr << "Error: Invalid submission file line format: " << fileLine << endl; }
}

string Submission::forFile() const {
    stringstream ss; ss << this->submissionID << "|" << this->problemID << "|" << this->username << "|" << this->submittedCode << "|" << this->verdict << "|" << this->submissionTime; return ss.str();
}

void Submission::setVerdict(const string& v) { this->verdict = v; }

void Submission::displaySubmission() const {
     cout << "  - ID: " << setw(5) << left << this->submissionID << " Problem: " << setw(8) << left << this->problemID
          << " User: " << setw(15) << left << this->username << " Verdict: " << setw(15) << left << this->verdict << " Time: " << this->submissionTime << endl;
}

string Submission::getProblemID() const { return this->problemID; }
string Submission::getUsername() const { return this->username; }
string Submission::getVerdict() const { return this->verdict; }
string Submission::getSubmissionID() const { return this->submissionID; }

bool Submission::operator<(const Submission& other) const {
    return this->submissionID < other.submissionID;
}