#include "Contest.h"
#include "Submission.h" // Need full definition for registerSubmission
#include "Problem.h"    // Need full definition for displayContestProblems

// Define comparison function (can also be in main or utils)
bool compareStandingsPair(const pair<string, int>& a, const pair<string, int>& b) {
    return a.second > b.second; // Sort descending by score
}


Contest::Contest() : contestID("N/A"), contestName("N/A") {}

Contest::Contest(string cID, string name) : contestID(cID), contestName(name) {}

Contest::Contest(string fileLine) : contestID("ERR"), contestName("Error Loading") {
    stringstream ss(fileLine); string pidsString; string temp_id, temp_name;
    if (getline(ss, temp_id, '|') && getline(ss, temp_name, '|') && getline(ss, pidsString)) {
        this->contestID = temp_id; this->contestName = temp_name;
        stringstream pidSS(pidsString); string pID; while (getline(pidSS, pID, ',')) { if (!pID.empty()) { this->problemIDs.push_back(pID); } }
    } else { cerr << "Error: Invalid contest file line format: " << fileLine << endl; }
}

string Contest::forFile() const {
    stringstream ss; ss << this->contestID << "|" << this->contestName << "|"; bool first = true; for (const string& pID : this->problemIDs) { if (!first) ss << ","; ss << pID; first = false; } return ss.str();
}

void Contest::addProblem(const string& pID) { this->problemIDs.push_back(pID); }

void Contest::registerSubmission(const Submission& sub) {
    bool problemInContest = false; for (size_t i = 0; i < problemIDs.size(); ++i) { if (problemIDs[i] == sub.getProblemID()) { problemInContest = true; break; } }
    if (!problemInContest) return;
    if (sub.getVerdict() == "Accepted") { string username = sub.getUsername(); this->standings[username] += 100; }
}

void Contest::showStandings() const {
    if (this->standings.empty()) { cout << "\nNo standings available yet for contest '" << this->contestName << "'." << endl; return; }
    vector<pair<string, int>> sortedStandings(this->standings.begin(), this->standings.end()); sort(sortedStandings.begin(), sortedStandings.end(), compareStandingsPair);
    cout << "\n--- Standings for " << this->contestName << " ---" << endl; cout << "------------------------------------------" << endl;
    cout << left << setw(6) << "Rank" << setw(20) << "Username" << setw(10) << "Score" << endl; cout << "------------------------------------------" << endl;
    for (size_t i = 0; i < sortedStandings.size(); ++i) { cout << left << setw(6) << (i + 1) << setw(20) << sortedStandings[i].first << setw(10) << sortedStandings[i].second << endl; }
    cout << "------------------------------------------" << endl;
}

void Contest::displayContestProblems(const vector<Problem>& allProblems) const {
    cout << "\n--- Problems for " << this->contestName << " ---" << endl; if (this->problemIDs.empty()) { cout << "  (No problems added to this contest yet)" << endl; cout << "-----------------------------------------" << endl; return; }
    for (const string& pID : this->problemIDs) { bool found = false; for (const Problem& prob : allProblems) { if (prob.getProblemID() == pID) { cout << "  - " << setw(8) << left << prob.getProblemID() << ": " << prob.getTitle() << endl; found = true; break; } } if (!found) { cout << "  - " << setw(8) << left << pID << ": (Problem details not found)" << endl; } }
    cout << "-----------------------------------------" << endl;
}

string Contest::getContestID() const { return this->contestID; }
string Contest::getContestName() const { return this->contestName; }
const vector<string>& Contest::getProblemIDs() const { return this->problemIDs; }

// Operator << implementation (friend function)
ostream& operator<<(ostream& os, const Contest& contest) {
    os << "--------------------" << endl; os << " Contest Summary" << endl; os << "--------------------" << endl;
    os << left << setw(15) << " ID:" << contest.contestID << endl; os << left << setw(15) << " Name:" << contest.contestName << endl;
    os << left << setw(15) << " # Problems:" << contest.problemIDs.size() << endl; os << "--------------------"; return os;
}