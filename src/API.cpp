#include "API.h"
#include <string>

std::string API::bookAppointment(const std::string& cnic, const std::string& name, const std::string& date) {
    return cnic + "_" + name + "_" + date;
}

Appointment* API::searchByCNIC(const std::string& cnic) {
    return nullptr;
}

bool API::cancelAppointment(const std::string& bookingId) {
    return true;
}
