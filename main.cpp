#include <iostream>
#include <string>
#include <map>
#include <fstream>
using namespace std;

map<string, string> contacts; // contact book

// Load contacts from file
void loadContacts() {
    ifstream file("contacts.txt");
    string name, number;
    while (file >> name >> number) {
        contacts[name] = number;
    }
    file.close();
}

// Save contacts to file
void saveContacts() {
    ofstream file("contacts.txt");
    for (auto &c : contacts) {
        file << c.first << " " << c.second << endl;
    }
    file.close();
}

// Save SMS message to file
void saveSMS(const string &message) {
    ofstream file("sms.txt", ios::app); // append mode
    file << message << endl;
    file.close();
}

// Load SMS messages from file
void loadSMS() {
    ifstream file("sms.txt");
    string line;
    cout << "\n--- SMS History ---\n";
    while (getline(file, line)) {
        cout << line << endl;
    }
    file.close();
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
        cin >> choice;

        if (choice == 1) {
            // Call cost calculator
            int minutes, type;
            double cost;
            cout << "Enter call duration in minutes: ";
            cin >> minutes;
            cout << "Choose call type:\n1. Local (RM0.10/min)\n2. International (RM0.50/min)\nChoice: ";
            cin >> type;

            if (type == 1) cost = minutes * 0.10;
            else if (type == 2) cost = minutes * 0.50;
            else { cout << "Invalid call type.\n"; continue; }

            cout << "Total call cost: RM" << cost << endl;
        }

        else if (choice == 2) {
            // Contact book
            int action;
            cout << "\n--- Contact Book ---\n";
            cout << "1. Add Contact\n";
            cout << "2. Search Contact\n";
            cout << "3. Delete Contact\n";
            cout << "Choose an option: ";
            cin >> action;

            if (action == 1) {
                string name, number;
                cout << "Enter name: ";
                cin >> name;
                cout << "Enter phone number: ";
                cin >> number;
                contacts[name] = number;
                saveContacts(); // save immediately
                cout << "Contact saved!\n";
            } 
            else if (action == 2) {
                string name;
                cout << "Enter name to search: ";
                cin >> name;
                if (contacts.find(name) != contacts.end())
                    cout << "Number: " << contacts[name] << endl;
                else
                    cout << "Contact not found.\n";
            }
            else if (action == 3) {
                string name;
                cout << "Enter name to delete: ";
                cin >> name;
                if (contacts.erase(name)) {
                    saveContacts(); // update file
                    cout << "Contact deleted.\n";
                } else {
                    cout << "Contact not found.\n";
                }
            }
        }

        else if (choice == 3) {
            // SMS simulator
            string message;
            cout << "Type your SMS message: ";
            cin.ignore(); // clear buffer
            getline(cin, message);
            cout << "Sending message...\n";
            cout << "Message sent: \"" << message << "\"\n";
            saveSMS(message); // save message
        }

        else if (choice == 4) {
            // View SMS history
            loadSMS();
        }

        else if (choice == 5) {
            cout << "Exiting program. Goodbye!\n";
        }

        else {
            cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 5);

    return 0;
}
