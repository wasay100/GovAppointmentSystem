#include "HashTable.h"
#include <iostream>

using namespace std;

// Constructor
HashTable::HashTable(int size) {
    capacity = size;
    table.resize(capacity);
}

// Hash function
int HashTable::hashFunction(const string& key) {
    int hash = 0;
    for (char c : key) {
        hash = (hash * 31 + c) % capacity;
    }
    return hash;
}

// Insert appointment
void HashTable::insert(const Appointment& appt) {
    int index = hashFunction(appt.cnic);
    table[index].push_back(appt);
}

// Search by CNIC
vector<Appointment> HashTable::searchByCNIC(const string& cnic) {
    int index = hashFunction(cnic);
    vector<Appointment> results;

    for (const auto& appt : table[index]) {
        if (appt.cnic == cnic) {
            results.push_back(appt);
        }
    }

    return results;
}

// Search by confirmation code
vector<Appointment> HashTable::searchByConfirmation(const string& code) {
    for (const auto& bucket : table) {
        for (const auto& appt : bucket) {
            if (appt.confirmationCode == code) {
                return vector<Appointment>{appt};
            }
        }
    }
    return vector<Appointment>();
}
