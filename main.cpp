#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <limits>
using namespace std;

map<string, string> contacts;      // contact book
vector<string> smsHistory;         // sms history

// --- Utility: clear input buffer safely ---
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// --- Load contacts from file ---
void loadContacts() {
    ifstream file("contacts.txt");
    if (!file) return; // file might not exist yet
    string name, number;
    while (file >> name >> number) {
        contacts[name] = number;
    }
    file.close();
}

// --- Save contacts to file ---
void saveContacts() {
    ofstream file("contacts.txt");
    for (auto &c : contacts) {
        file << c.first << " " << c.second << endl;
    }
    file.close();
}

// --- Save SMS message to file ---
void saveSMS(const string &message) {
    ofstream file("sms.txt", ios::app); // append mode
    if (!file) {
        cout << "Error: Could not open sms.txt for writing.\n";
        return;
    }
    file << message << endl;
    file.close();
}

// --- Load SMS messages from file ---
void loadSMS() {
    ifstream file("sms.txt");
    if (!file) {
        cout << "No SMS history found.\n";
        return;
    }
    string line;
    cout << "\n--- SMS History ---\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
}

// --- Call cost calculator ---
void callCostCalculator() {
    double minutes, cost;
    int type;

    cout << "Enter call duration in minutes: ";
    if (!(cin >> minutes)) {
        cout << "Invalid input! Please enter numbers only.\n";
        clearInput();
        return;
    }

    cout << "Choose call type:\n1. Local (RM0.10/min)\n2. International (RM0.50/min)\nChoice: ";
    if (!(cin >> type)) {
        cout << "Invalid input! Please enter numbers only.\n";
        clearInput();
        return;
    }

    if (type == 1) cost = minutes * 0.10;
    else if (type == 2) cost = minutes * 0.50;
    else { 
        cout << "Invalid call type.\n"; 
        return; 
    }

    cout << "Total call cost: RM" << cost << endl;
}

// --- Manage contacts ---
void manageContacts() {
    int action;
    cout << "\n--- Contact Book ---\n";
    cout << "1. Add Contact\n";
    cout << "2. Search Contact\n";
    cout << "3. Delete Contact\n";
    cout << "4. View All Contacts\n"; // 🔥 New option
    cout << "Choose an option: ";

    if (!(cin >> action)) {
        cout << "Invalid input! Numbers only.\n";
        clearInput();
        return;
    }

    if (action == 1) {
        string name, number;
        cout << "Enter name (one word only): ";
        getline(cin >> ws, name);   // ws eats whitespace
        cout << "Enter phone number: ";
        getline(cin, number);
        contacts[name] = number;
        saveContacts(); // save immediately
        cout << "Contact saved!\n";
    } 
    else if (action == 2) {
        string name;
        cout << "Enter name to search: ";
        getline(cin >> ws, name);
        if (contacts.find(name) != contacts.end())
            cout << "Number: " << contacts[name] << endl;
        else
            cout << "Contact not found.\n";
    }
    else if (action == 3) {
        string name;
        cout << "Enter name to delete: ";
        getline(cin >> ws, name);
        if (contacts.erase(name)) {
            saveContacts(); // update file
            cout << "Contact deleted.\n";
        } else {
            cout << "Contact not found.\n";
        }
    }
    else if (action == 4) { // ✅ Show all contacts
        if (contacts.empty()) {
            cout << "No contacts saved.\n";
        } else {
            cout << "\n--- All Contacts ---\n";
            for (auto &c : contacts) {
                cout << c.first << " : " << c.second << endl;
            }
        }
    }
    else {
        cout << "Invalid option in Contact Book.\n";
    }
}

// --- SMS simulator ---
void smsSimulator() {
    string message;
    cout << "Type your SMS message: ";
    getline(cin >> ws, message);   // ws fixes skipped input
    if (message.empty()) {
        cout << "Message cannot be empty!\n";
        return;
    }
    cout << "Sending message...\n";
    cout << "Message sent: \"" << message << "\"\n";
    saveSMS(message); // save message
}

int main() {
    int choice;
    loadContacts(); // load contacts when program starts

    do {
        cout << "\n===============================\n";
        cout << "   Simple Phone Assistant\n";
        cout << "===============================\n";
        cout << "1. Call Cost Calculator\n";
        cout << "2. Contact Book\n";
        cout << "3. SMS Message Simulator\n";
        cout << "4. View SMS History\n";
        cout << "5. Exit\n";
        cout << "Choose an option (1-5): ";

        if (!(cin >> choice)) {
            cout << "Invalid input! Please enter a number.\n";
            clearInput();
            continue;
        }

        if (choice == 1) callCostCalculator();
        else if (choice == 2) manageContacts();
        else if (choice == 3) smsSimulator();
        else if (choice == 4) loadSMS();
        else if (choice == 5) cout << "Exiting program. Goodbye!\n";
        else cout << "Invalid choice. Please try again.\n";

    } while (choice != 5);

    return 0;
}
