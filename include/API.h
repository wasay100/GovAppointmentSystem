#pragma once
#include "BTree.h"
#include "HashTable.h"
#include "Appointment.h"
#include "json.hpp"
#include <string>
#include <fstream>
#include <vector>

using namespace std;
using json = nlohmann::json;

class AppointmentAPI {
private:
    BTree* btree;
    HashTable* htable;
    int appointmentCounter;

    string generateConfirmationCode(const string& city);

public:
    AppointmentAPI(BTree* bt, HashTable* ht);

    string bookAppointment(const string& city, const string& office,
        const string& service, const string& date,
        const string& time, const string& cnic,
        const string& name, const string& phone);

    string searchByDateRange(const string& fromDate, const string& toDate);
    string searchByCNIC(const string& cnic);
    string searchByConfirmation(const string& code);
    string getAllAppointments();

    void saveToFile(const string& filename);
    void loadFromFile(const string& filename);
    void loadInitialData();
};
