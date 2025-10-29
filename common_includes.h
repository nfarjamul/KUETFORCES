#pragma once // Prevents multiple inclusions

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <sstream>
#include <fstream>
#include <algorithm> // For std::sort, std::find
#include <iomanip>   // For setw
#include <limits>    // For numeric_limits
#include <ctime>     // For submission timestamp

// Using namespace std as requested
using namespace std;

// Forward declarations (useful if headers include each other)
class User;
class Problem;
class Submission;
class Leaderboard;
class Contest;
class KuETforces;

// --- DECLARATION for Global Helper Function ---
int getIntegerInput(const string& prompt, int minVal, int maxVal);