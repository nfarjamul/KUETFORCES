#include "Problem.h" // Include the header file for Problem class

// Initialize static member variable
int Problem::problemCount = 0;

Problem::Problem() : problemID("N/A"), title("N/A"), difficulty("0"), timeLimit("N/A") {}

Problem::Problem(string id, string title, string stmt, string diff, string limit,
                 string sampleOut, string solution, string edit, const vector<string>& tagsVec) :
    problemID(id), title(title), statement(stmt), difficulty(diff), timeLimit(limit),
    sampleOutput(sampleOut), solutionCode(solution), editorial(edit), tags(tagsVec)
{}
Problem::Problem(string fileLine) : problemID("ERR"), title("Error Loading"), difficulty("0"), timeLimit("N/A") {
  stringstream ss(fileLine); string tagsString; string temp_id, temp_title, temp_stmt, temp_diff, temp_limit, temp_sample, 
 temp_sol, temp_edit;
    if (getline(ss, temp_id, '|') && getline(ss, temp_title, '|') && getline(ss, temp_stmt, '|') && getline(ss, temp_diff, '|') &&
        getline(ss, temp_limit, '|') && getline(ss, temp_sample, '|') && getline(ss, temp_sol, '|') && getline(ss, temp_edit, '|')
         && getline(ss, tagsString)) {
        this->problemID = temp_id; this->title = temp_title; this->statement = temp_stmt; this->difficulty = temp_diff; 
        this->timeLimit = temp_limit;
        this->sampleOutput = temp_sample; this->solutionCode = temp_sol; this->editorial = temp_edit;
        stringstream tagSS(tagsString); string tag;
        while (getline(tagSS, tag, ',')) {
             size_t first = tag.find_first_not_of(' '); if (string::npos != first) { size_t last = tag.find_last_not_of(' ');
              tag = tag.substr(first, (last - first + 1)); if (!tag.empty()) { this->tags.push_back(tag); } }
        }
    } else { cerr << "Error: Invalid problem file line format: " << fileLine << endl; }
}

string Problem::forFile() const {
    stringstream ss; ss << this->problemID << "|" << this->title << "|" << this->statement << "|" << this->difficulty << "|"
     << this->timeLimit << "|" << this->sampleOutput << "|" << this->solutionCode << "|" << this->editorial << "|";
    bool first = true; for (const string& tag : this->tags) { if (!first) ss << ","; ss << tag; first = false; } return ss.str();
}

void Problem::showProblemDetails() const {
    cout << "\n-----------------------------------------" << endl; cout << " " << this->problemID << ": " << this->title 
    << endl; cout << "-----------------------------------------" << endl;
    cout << left << setw(12) << " Difficulty:" << this->difficulty << endl; cout << left << setw(12) << " Time Limit:" <<
     this->timeLimit << endl;
    cout << left << setw(12) << " Tags:" ; if (this->tags.empty()) { cout << " None"; } else { bool first = true;
     for (const string& tag : this->tags) { if (!first) cout << ", "; cout << tag; first = false; } }
    cout << "\n\n--- Statement ---" << endl; cout << this->statement << endl; cout << "\n--- Sample Output ---" << endl; 
    cout << this->sampleOutput << endl; cout << "-----------------------------------------" << endl;
}

void Problem::showEditorial() const {
    cout << "\n--- Editorial for " << this->problemID << " ---" << endl; cout << this->editorial << endl; 
    cout << "-----------------------------------------" << endl;
}
bool Problem::checkSolution(const string& submittedCode) const {
    return (submittedCode == this->solutionCode);
}
string Problem::getProblemID() const { return this->problemID; }
string Problem::getTitle() const { return this->title; }
const vector<string>& Problem::getTags() const { return this->tags; }

bool Problem::operator==(const Problem& other) const {
    return this->problemID == other.problemID;
}

int Problem::getProblemCount() { return problemCount; }
void Problem::setProblemCount(int count) { if (count >= 0) { problemCount = count; } }
void Problem::incrementProblemCount() { problemCount++; }