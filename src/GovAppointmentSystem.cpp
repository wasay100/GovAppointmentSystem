#include <iostream>
#include "BTree.h"
#include "HashTable.h"
#include "API.h"

using namespace std;

void displayMenu() {
    cout << endl;
    cout << "============================================" << endl;
    cout << "   GOVERNMENT APPOINTMENT SYSTEM - API" << endl;
    cout << "============================================" << endl;
    cout << "1. Book New Appointment" << endl;
    cout << "2. Search by Date Range" << endl;
    cout << "3. Search by CNIC" << endl;
    cout << "4. Search by Confirmation Code" << endl;
    cout << "5. View All Appointments" << endl;
    cout << "6. Save Data to File" << endl;
    cout << "7. Exit" << endl;
    cout << "============================================" << endl;
    cout << "Enter choice: ";
}

int main() {
    cout << "=== Government Appointment System - Phase 2 ===" << endl << endl;

    BTree btree(3);
    HashTable htable(1009);
    AppointmentAPI api(&btree, &htable);

    // Add initial sample data
    cout << "Loading sample data..." << endl;
    api.bookAppointment("Karachi", "NADRA Saddar", "New CNIC",
        "2025-12-05", "09:30", "42101-1234567-1",
        "Ali Ahmed", "0300-1234567");

    api.bookAppointment("Lahore", "NADRA Gulberg", "CNIC Renewal",
        "2025-12-05", "10:00", "35201-1111111-3",
        "Hassan Ali", "0300-5555555");

    cout << "Sample data loaded!" << endl;

    int choice;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            string city, office, service, date, time, cnic, name, phone;
            cout << "City: "; getline(cin, city);
            cout << "Office: "; getline(cin, office);
            cout << "Service: "; getline(cin, service);
            cout << "Date (YYYY-MM-DD): "; getline(cin, date);
            cout << "Time (HH:MM): "; getline(cin, time);
            cout << "CNIC: "; getline(cin, cnic);
            cout << "Name: "; getline(cin, name);
            cout << "Phone: "; getline(cin, phone);

            cout << endl << api.bookAppointment(city, office, service, date, time, cnic, name, phone) << endl;
        }
        else if (choice == 2) {
            string from, to;
            cout << "From (YYYY-MM-DD HH:MM): "; getline(cin, from);
            cout << "To (YYYY-MM-DD HH:MM): "; getline(cin, to);
            cout << endl << api.searchByDateRange(from, to) << endl;
        }
        else if (choice == 3) {
            string cnic;
            cout << "Enter CNIC: "; getline(cin, cnic);
            cout << endl << api.searchByCNIC(cnic) << endl;
        }
        else if (choice == 4) {
            string code;
            cout << "Enter Confirmation Code: "; getline(cin, code);
            cout << endl << api.searchByConfirmation(code) << endl;
        }
        else if (choice == 5) {
            cout << endl << api.getAllAppointments() << endl;
        }
        else if (choice == 6) {
            api.saveToFile("appointments.json");
        }
        else if (choice == 7) {
            cout << "Thank you for using the system!" << endl;
            break;
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    return 0;
}
