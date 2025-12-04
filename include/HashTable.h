#pragma once
#include "Appointment.h"
#include <vector>

using namespace std;

class HashTable {
private:
    vector<vector<Appointment>> table;
    int capacity;

    int hashFunction(const string& key);

public:
    HashTable(int size = 1009);
    void insert(const Appointment& appt);
    vector<Appointment> searchByCNIC(const string& cnic);
    vector<Appointment> searchByConfirmation(const string& code);
};
