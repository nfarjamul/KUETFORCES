#include "KuETforces.h" // Includes common_includes.h indirectly

// NOTE: The DEFINITION of getIntegerInput is REMOVED from this file.
//       It is now DECLARED in common_includes.h and DEFINED in main.cpp

// --- Constructor ---
KuETforces::KuETforces() : currentUser(nullptr) {
    this->loadAllData();
    if (this->allUsers.empty()) {
        cout << "No user file found. Creating default admin account (admin/admin123)." << endl;
        this->allUsers.push_back(User("admin", "admin123", "admin", 1500));
    }
    Problem::setProblemCount(this->allProblems.size());
    User::setTotalUsers(this->allUsers.size());
}

// --- Main application loop ---
void KuETforces::run() {
    cout << "\n=========================================" << endl;
    cout << "        Welcome to KUETforces!" << endl;
    cout << "=========================================" << endl;
    bool running = true;
    while (running) {
        int choice = 0;
        if (this->currentUser == nullptr) {
            choice = this->showMainMenu(); // Uses getIntegerInput internally
            switch (choice) {
                case 1: if (!this->login()) { cout << "\nLogin failed. Invalid username or password." << endl; cout << "Press Enter to continue..."; cin.ignore(numeric_limits<streamsize>::max(), '\n');} break;
                case 2: this->signUp(); break;
                case 3: running = false; break;
            }
        } else if (this->currentUser->getRole() == "admin") {
            choice = this->showAdminMenu(); // Uses getIntegerInput internally
            switch (choice) {
                case 1: this->admin_addProblem(); break;
                case 2: this->admin_createContest(); break;
                case 3: this->admin_banUser(); break;
                case 4: cout << "\nLogging out..." << endl; this->currentUser = nullptr; break;
            }
        } else { // Contestant
            choice = this->showContestantMenu(); // Uses getIntegerInput internally
            switch (choice) {
                case 1: this->contestant_viewProfile(); break;
                case 2: this->contestant_viewProblemset(); break;
                case 3: this->contestant_viewContests(); break;
                case 4: this->contestant_viewLeaderboard(); break;
                case 5: cout << "\nLogging out..." << endl; this->currentUser = nullptr; break;
            }
        }
    }
    this->saveData();
    cout << "\nExiting KUETforces. Goodbye!" << endl;
}

// --- Menu Display Functions ---
// These now correctly call the globally declared getIntegerInput
int KuETforces::showMainMenu() {
    cout << "\n--- Main Menu ---" << endl;
    cout << "1. Login" << endl;
    cout << "2. Sign Up" << endl;
    cout << "3. Exit" << endl;
    return getIntegerInput("Enter your choice: ", 1, 3); // Call global function
}

int KuETforces::showAdminMenu() {
    cout << "\n--- Admin Dashboard (" << this->currentUser->getUsername() << ") ---" << endl;
    cout << "1. Add Problem" << endl;
    cout << "2. Create Contest" << endl;
    cout << "3. Ban User" << endl;
    cout << "4. Logout" << endl;
    return getIntegerInput("Enter your choice: ", 1, 4); // Call global function
}

int KuETforces::showContestantMenu() {
    cout << "\n--- Contestant Menu (" << this->currentUser->getUsername() << ") ---" << endl;
    cout << "1. View Profile" << endl;
    cout << "2. View Problemset" << endl;
    cout << "3. View Contests" << endl;
    cout << "4. View Leaderboard" << endl;
    cout << "5. Logout" << endl;
    return getIntegerInput("Enter your choice: ", 1, 5); // Call global function
}

// --- Authentication ---
bool KuETforces::login() { /* ... unchanged ... */
    string username, password; cout << "Enter Username: "; getline(cin, username); cout << "Enter Password: "; getline(cin, password);
    for (size_t i = 0; i < allUsers.size(); ++i) { if (allUsers[i].getUsername() == username && allUsers[i].checkPassword(password)) { this->currentUser = &allUsers[i]; cout << "\nWelcome back, " << this->currentUser->getUsername() << "!" << endl; return true; } }
    return false;
}
void KuETforces::signUp() { /* ... unchanged ... */
    string username, password; cout << "Enter new Username: "; getline(cin, username); if (username.empty()) { cout << "Username cannot be empty." << endl; return; }
    for (const User& user : this->allUsers) { if (user.getUsername() == username) { cout << "Username '" << username << "' already taken." << endl; return; } }
    cout << "Enter new Password: "; getline(cin, password); if (password.empty()) { cout << "Password cannot be empty." << endl; return; }
    User newUser(username, password, "contestant", 0); *this += newUser; this->saveData(); cout << "Signup successful! You can now log in." << endl;
}

// --- Admin Actions ---
void KuETforces::admin_addProblem() { /* ... unchanged ... */
    string id, title, stmt, diff, limit, sampleOutput, solutionCode, editorial, tagLine;
    cout << "Enter Problem ID: "; getline(cin, id); if (id.empty()) { cout << "Problem ID cannot be empty." << endl; return; } if(this->searchProblem(id) != nullptr) { cout << "Error: Problem ID '" << id << "' already exists." << endl; return; }
    cout << "Enter Title: "; getline(cin, title); if (title.empty()) { cout << "Title cannot be empty." << endl; return; } cout << "Enter Statement: "; getline(cin, stmt);
    cout << "Enter Difficulty: "; getline(cin, diff); cout << "Enter Time Limit: "; getline(cin, limit); cout << "Enter Sample Output: "; getline(cin, sampleOutput);
    cout << "Enter Solution Code: "; getline(cin, solutionCode); if (solutionCode.empty()) { cout << "Solution code cannot be empty." << endl; return; }
    cout << "Enter Editorial: "; getline(cin, editorial); cout << "Enter tags (comma-separated): "; getline(cin, tagLine);
    vector<string> tagsVec; stringstream ss(tagLine); string tag; while (getline(ss, tag, ',')) { size_t first = tag.find_first_not_of(' '); if (string::npos != first) { size_t last = tag.find_last_not_of(' '); tag = tag.substr(first, (last - first + 1)); if (!tag.empty()) { tagsVec.push_back(tag); } } }
    Problem newProblem(id, title, stmt, diff, limit, sampleOutput, solutionCode, editorial, tagsVec); this->allProblems.push_back(newProblem); Problem::incrementProblemCount(); cout << "Problem '" << title << "' added." << endl;
}
void KuETforces::admin_banUser() { /* ... unchanged ... */
    string username; cout << "Enter username to ban: "; getline(cin, username); if (username == "admin") { cout << "Cannot ban admin." << endl; return; }
    auto it = allUsers.begin(); bool found = false; while (it != allUsers.end()) { if (it->getUsername() == username) { if (&(*it) == currentUser) { cout << "Cannot ban self." << endl; return; } it = allUsers.erase(it); found = true; break; } else { ++it; } }
    if (found) { User::setTotalUsers(allUsers.size()); cout << "User '" << username << "' banned." << endl; } else { cout << "User '" << username << "' not found." << endl; }
}
void KuETforces::admin_createContest() { /* ... unchanged ... */
    string id, name; cout << "Enter Contest ID: "; getline(cin, id); if (id.empty()) { cout << "Contest ID cannot be empty." << endl; return; }
    for(const Contest& c : allContests) { if(c.getContestID() == id) { cout << "Error: Contest ID exists." << endl; return; } }
    cout << "Enter Contest Name: "; getline(cin, name); if (name.empty()) { cout << "Name cannot be empty." << endl; return; }
    Contest newContest(id, name); cout << "Contest '" << name << "' created. Add problems." << endl; string pID;
    while (true) { cout << "Enter Problem ID ('done'/'0' to finish): "; getline(cin, pID); if (pID == "done" || pID == "0") break; if (pID.empty()) continue; Problem* fp = this->searchProblem(pID);
        if (fp != nullptr) { newContest.addProblem(pID); cout << " -> Problem '" << fp->getTitle() << "' added." << endl; } else { cout << " -> Problem ID not found." << endl; } }
    this->allContests.push_back(newContest); cout << "Contest '" << name << "' saved." << endl;
}

// --- Contestant Actions ---
void KuETforces::contestant_viewProfile() { if(currentUser) currentUser->displayProfile(); }
void KuETforces::contestant_viewProblemset() { /* ... Uses getIntegerInput internally ... */
    cout << "\n--- Problemset ---" << endl; if (this->allProblems.empty()) { cout << "No problems yet." << endl; return; }
    cout << left << setw(10) << "ID" << setw(40) << "Title" << endl; cout << setfill('-') << setw(50) << "" << setfill(' ') << endl;
    for(const Problem& prob : this->allProblems) { cout << left << setw(10) << prob.getProblemID() << setw(40) << prob.getTitle() << endl; }
    cout << setfill('-') << setw(50) << "" << setfill(' ') << endl; cout << "\nEnter Problem ID (0 to back): "; string id; getline(cin, id); if (id == "0" || id.empty()) return;
    Problem* prob = this->searchProblem(id);
    if (prob != nullptr) { prob->showProblemDetails(); cout << "\n--- Actions ---\n1. Submit\n2. Editorial\n3. Add Fav\n4. Back\n"; int choice = getIntegerInput("Action (1-4): ", 1, 4); // Call global function
        if (choice == 1) this->contestant_submitSolution(prob); else if (choice == 2) prob->showEditorial(); else if (choice == 3) this->currentUser->addFavoriteProblem(prob->getProblemID());
    } else { cout << "Problem ID '" << id << "' not found." << endl; }
}
void KuETforces::contestant_submitSolution(Problem* prob) { /* ... unchanged ... */
     if (!prob) { cout << "Error: Cannot submit to null problem." << endl; return; } string submittedCode; cout << "\n--- Submit Solution for: " << prob->getProblemID() << " ---\nPaste code (single line):" << endl; getline(cin, submittedCode);
    if (submittedCode.empty()) { cout << "Submission empty." << endl; return; } time_t now = time(0); string timeStr = ctime(&now); timeStr.pop_back(); string subID = "S" + to_string(this->allSubmissions.size() + 1001);
    Submission newSub(subID, prob->getProblemID(), this->currentUser->getUsername(), submittedCode, timeStr);
    if (prob->checkSolution(submittedCode)) { newSub.setVerdict("Accepted"); cout << "\nVerdict: Accepted!" << endl; this->currentUser->incrementSolvedCount(); } else { newSub.setVerdict("Wrong Answer"); cout << "\nVerdict: Wrong Answer!" << endl; }
    this->allSubmissions.push_back(newSub); for (Contest& contest : this->allContests) { contest.registerSubmission(newSub); } cout << "Submission " << subID << " recorded." << endl;
}
void KuETforces::contestant_viewLeaderboard() { /* ... Uses getIntegerInput internally ... */
    this->leaderboard("Global Rankings"); cout << "1. View by Rating\n2. View by Solved Count\n"; int choice = getIntegerInput("Choice (1-2): ", 1, 2); // Call global function
    if (choice == 1) this->leaderboard.displayByRating(this->allUsers); else if (choice == 2) this->leaderboard.displayBySolvedCount(this->allUsers);
}
void KuETforces::contestant_viewContests() { /* ... Uses getIntegerInput internally ... */
    cout << "\n--- Available Contests ---" << endl; if (this->allContests.empty()) { cout << "No contests available." << endl; return; }
    cout << left << setw(6) << "No." << setw(15) << "ID" << "Name" << endl; cout << "------------------------------------------" << endl; for (size_t i = 0; i < this->allContests.size(); ++i) { cout << left << setw(6) << (i + 1) << setw(15) << this->allContests[i].getContestID() << this->allContests[i].getContestName() << endl; }
    cout << "------------------------------------------" << endl; int choice = getIntegerInput("Contest Number (0 to back): ", 0, this->allContests.size()); // Call global function
    if (choice > 0) { Contest& selectedContest = this->allContests[choice - 1]; cout << "\n--- Contest Menu: " << selectedContest.getContestName() << " ---\n" << selectedContest << endl;
        cout << "\n1. View Problems\n2. View Standings\n3. Back\n"; int contestChoice = getIntegerInput("Choice (1-3): ", 1, 3); // Call global function
        if (contestChoice == 1) selectedContest.displayContestProblems(this->allProblems); else if (contestChoice == 2) selectedContest.showStandings(); }
}

// --- Search Functions ---
Problem* KuETforces::searchProblem(const string& problemID) { /* ... unchanged ... */
    for (size_t i = 0; i < this->allProblems.size(); ++i) { if (this->allProblems[i].getProblemID() == problemID) { return &this->allProblems[i]; } } return nullptr;
}
vector<Problem> KuETforces::searchProblemByTag(const string& tag) { /* ... unchanged ... */
    vector<Problem> foundProblems; cout << "\n--- Searching Tag: '" << tag << "' ---" << endl; bool found = false;
    for (const Problem& prob : this->allProblems) { const vector<string>& tags = prob.getTags(); bool tagFound = false; for (const string& currentTag : tags) { string singleTag=currentTag; size_t first=singleTag.find_first_not_of(' '); if(string::npos==first) continue; size_t last=singleTag.find_last_not_of(' '); singleTag=singleTag.substr(first, (last-first+1)); if (singleTag == tag) { tagFound = true; break; } }
        if (tagFound) { cout << "  - Found: " << prob.getProblemID() << ": " << prob.getTitle() << endl; foundProblems.push_back(prob); found = true; } }
    if (!found) { cout << "No problems found." << endl; } cout << "-----------------------------------------" << endl; return foundProblems;
}

// --- Operator Overload ---
KuETforces& KuETforces::operator+=(const User& newUser) { /* ... unchanged ... */
    for(const User& user : this->allUsers) { if (user.getUsername() == newUser.getUsername()) { cout << "Warning: User exists. Cannot add via +=." << endl; return *this; } }
    this->allUsers.push_back(newUser); User::setTotalUsers(allUsers.size()); cout << "User '" << newUser.getUsername() << "' added via operator+=" << endl; return *this;
}

// --- File I/O ---
void KuETforces::loadAllData() { /* ... unchanged ... */
    cout << "Loading data..." << endl; ifstream userFile("users.txt"); string line; allUsers.clear();
    while (getline(userFile, line)) { if (!line.empty()) { allUsers.push_back(User(line)); } } userFile.close();
    ifstream probFile("problems.txt"); allProblems.clear();
    while (getline(probFile, line)) { if (!line.empty()) { allProblems.push_back(Problem(line)); } } probFile.close();
    ifstream subFile("submissions.txt"); allSubmissions.clear();
    while (getline(subFile, line)) { if (!line.empty()) { allSubmissions.push_back(Submission(line)); } } subFile.close();
    ifstream contestFile("contests.txt"); allContests.clear();
    while (getline(contestFile, line)) { if (!line.empty()) { allContests.push_back(Contest(line)); } } contestFile.close();
    cout << "Rebuilding contest standings..." << endl; for (Contest& contest : allContests) { for (const Submission& sub : allSubmissions) { contest.registerSubmission(sub); } }
    cout << "Load complete: " << allUsers.size() << " users, " << allProblems.size() << " problems, " << allSubmissions.size() << " submissions, " << allContests.size() << " contests." << endl;
    User::setTotalUsers(allUsers.size()); Problem::setProblemCount(allProblems.size());
}
void KuETforces::saveData() { /* ... unchanged ... */
    cout << "Saving data..."; ofstream userFile("users.txt");
    if (userFile.is_open()) { for (const User& user : allUsers) { userFile << user.forFile() << endl; } userFile.close(); } else { cerr << "\nError: Could not open users.txt." << endl;}
    ofstream probFile("problems.txt");
    if (probFile.is_open()) { for (const Problem& prob : allProblems) { probFile << prob.forFile() << endl; } probFile.close(); } else { cerr << "\nError: Could not open problems.txt." << endl;}
    ofstream subFile("submissions.txt");
    if (subFile.is_open()) { for (const Submission& sub : allSubmissions) { subFile << sub.forFile() << endl; } subFile.close(); } else { cerr << "\nError: Could not open submissions.txt." << endl;}
    ofstream contestFile("contests.txt");
    if (contestFile.is_open()) { for (const Contest& contest : allContests) { contestFile << contest.forFile() << endl; } contestFile.close(); } else { cerr << "\nError: Could not open contests.txt." << endl;}
    cout << " Done." << endl;
}