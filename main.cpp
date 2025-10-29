#include "KuETforces.h" // Include the main application class header
#include "common_includes.h" // Include common headers (for cout, cerr, bad_alloc, etc.)

// --- DEFINITION for Global Helper Function ---
// Gets a valid integer input from the user within a specified range [minVal, maxVal]
int getIntegerInput(const string& prompt, int minVal, int maxVal) {
    int choice;
    cout << prompt; // Display the prompt message to the user
    // Loop until valid input is received
    while (!(cin >> choice) || choice < minVal || choice > maxVal) {
        // Input was not an integer or was outside the allowed range
        cout << "Invalid input. Please enter a number between " << minVal << " and " << maxVal << ": ";
        cin.clear(); // Clear the error state flags on cin
        // Discard the rest of the invalid input line from the buffer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    // Discard any leftover characters (like the newline) from the valid input line
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return choice; // Return the validated integer
}

// --- MAIN FUNCTION ---
// The entry point of the KUETforces application
int main() {
    cout << "Starting KUETforces Application..." << endl;

    KuETforces* app = nullptr; // Initialize pointer to null

    // --- Syllabus Requirement: Use new ---
    // Dynamically allocate the main application object
    try {
        app = new KuETforces(); // Calls the KuETforces constructor, which loads data
    } catch (const std::bad_alloc& e) {
        // Handle memory allocation failure
        cerr << "FATAL ERROR: Failed to allocate memory for the application. " << e.what() << endl;
        return 1; // Exit with an error code
    } catch (const std::exception& e) {
        // Catch any other standard exceptions during construction
         cerr << "FATAL ERROR: An exception occurred during application initialization: " << e.what() << endl;
         if(app) delete app; // Attempt cleanup if partially constructed
        return 1;
    }
     catch (...) {
        // Catch any other unknown errors during construction
        cerr << "FATAL ERROR: An unknown error occurred during application initialization." << endl;
         if(app) delete app; // Attempt cleanup
        return 1;
    }

    // Run the application's main loop within a try-catch block
    try {
         app->run(); // Start the application execution
    } catch (const std::exception& e) {
         // Catch standard exceptions during runtime
         cerr << "\nRUNTIME ERROR: An exception occurred: " << e.what() << endl;
         // In a real application, might attempt to save critical data here
    } catch (...) {
         // Catch any other unknown exceptions during runtime
         cerr << "\nRUNTIME ERROR: An unknown exception occurred during execution." << endl;
    }

    // --- Syllabus Requirement: Use delete ---
    // Clean up the dynamically allocated memory
    delete app;
    app = nullptr; // Set pointer to null after deletion (good practice)

    cout << "KUETforces Application finished." << endl;
    return 0; // Indicate successful execution
}