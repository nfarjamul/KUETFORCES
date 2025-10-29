#include "User.h" // Include the header file for User class

// Initialize static member variable
int User::totalUsers = 0;

User::User() : rating(0), solvedCount(0) {}

User::User(string uname, string pass, string urole, int urating) :
    username(uname), password(pass), role(urole), rating(urating), solvedCount(0)
{} // Static count handled by KuETforces

User::User(string fileLine) : rating(0), solvedCount(0) {
    stringstream ss(fileLine); string segment; string favIDsString;
    if (getline(ss, username, '|') && getline(ss, password, '|') && getline(ss, role, '|') && getline(ss, segment, '|')) {
        try { rating = stoi(segment); } catch (...) {}
        if (getline(ss, segment, '|')) {
             try { solvedCount = stoi(segment); } catch (...) {}
            getline(ss, favIDsString);
            stringstream favSS(favIDsString); string favID;
            while (getline(favSS, favID, ',')) { if (!favID.empty()) { favoriteProblemIDs.push_back(favID); } }
        }
    } else { username = "error_loading"; password = ""; role = "contestant"; cerr << "Error: Invalid user file line format: " 
    << fileLine << endl; }
    // Static count handled by KuETforces
}
void User::displayProfile() const {
    cout << "\n--- User Profile ---" << endl; cout << left << setw(18) << "Username:" << username << endl;
    cout << left << setw(18) << "Role:" << role << endl; cout << left << setw(18) << "Rating:" << rating << endl;
    cout << left << setw(18) << "Problems Solved:" << solvedCount << endl; cout << left << setw(18) << "Favorite Problems:";
    if (favoriteProblemIDs.empty()) { cout << " None"; } else { bool first = true; for (const string& favID : favoriteProblemIDs) 
    { if (!first) cout << ", "; cout << favID; first = false; } }
    cout << endl; cout << "--------------------" << endl;
}
bool User::checkPassword(const string& pass) const { return (this->password == pass); }
void User::addFavoriteProblem(const string& problemID) {
    bool found = false; for (size_t i = 0; i < favoriteProblemIDs.size(); ++i) { if (favoriteProblemIDs[i] == problemID) 
    { found = true; break; } }
    if (found) { cout << "Problem '" << problemID << "' is already in favorites." << endl; }
    else { this->favoriteProblemIDs.push_back(problemID); cout << "Problem '" << problemID << "' added to favorites." << endl; }
}
void User::incrementSolvedCount() { this->solvedCount++; }
string User::getUsername() const { return this->username; }
string User::getRole() const { return this->role; }
int User::getRating() const { return this->rating; }
int User::getSolvedCount() const { return this->solvedCount; }
const vector<string>& User::getFavoriteProblemIDs() const { return this->favoriteProblemIDs; }
string User::forFile() const {
    stringstream ss; ss << this->username << "|" << this->password << "|" << this->role << "|" << this->rating <<
     "|" << this->solvedCount << "|";
    bool first = true; for (const string& favID : this->favoriteProblemIDs) { if (!first) ss << ","; ss << favID; first = false; }
     return ss.str();
}
User User::operator+(const User &other) const {
    User temp; temp.username = this->username + "&" + other.username; temp.role = "combined"; 
    temp.rating = this->rating + other.rating; temp.solvedCount = this->solvedCount + other.solvedCount; return temp;
}
// Friend function implementation is typically placed in a related .cpp file (like main.cpp or User.cpp)
// Putting it here for simplicity in this example structure.
void showNotification(const User& user, const string& message) {
    cout << "\n🔔 Notification for " << user.username << ": " << message << endl;
}
int User::getTotalUsers() { return totalUsers; }
void User::setTotalUsers(int count) { if (count >= 0) { totalUsers = count; } }