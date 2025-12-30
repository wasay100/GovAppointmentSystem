#ifndef API_H
#define API_H
#include "BTree.h"
#include "HashTable.h"
#include <string>

class API {
private:
    BTree btree;
    HashTable hashTable;
public:
    API() : btree(3), hashTable(100) {}
    std::string bookAppointment(const std::string& cnic, const std::string& name, const std::string& date);
    Appointment* searchByCNIC(const std::string& cnic);
    bool cancelAppointment(const std::string& bookingId);
};
#endif
