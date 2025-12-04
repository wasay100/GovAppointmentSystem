#include "API.h"
#include <iostream>

using namespace std;

AppointmentAPI::AppointmentAPI(BTree* bt, HashTable* ht) {
    btree = bt;
    htable = ht;
    appointmentCounter = 100;
}

string AppointmentAPI::bookAppointment(const string& city, const string& office,
    const string& service, const string& date, const string& time,
    const string& cnic, const string& name, const string& phone) {

    string prefix = "APT-";
    if (city == "Karachi") prefix += "KHI-";
    else if (city == "Lahore") prefix += "LHR-";
    else if (city == "Islamabad") prefix += "ISB-";
    else prefix += "PAK-";

    string confirmationCode = prefix + to_string(appointmentCounter++);

    Appointment newAppt(city, office, service, date, time, cnic, name, phone, confirmationCode);
    btree->insert(newAppt);
    htable->insert(newAppt);

    json response = {
        {"success", true},
        {"message", "Appointment booked successfully"},
        {"confirmationCode", confirmationCode},
        {"city", city},
        {"office", office},
        {"date", date},
        {"time", time},
        {"name", name}
    };

    return response.dump(4);
}

string AppointmentAPI::searchByDateRange(const string& fromDate, const string& toDate) {
    vector<Appointment> results = btree->rangeSearch(fromDate, toDate);

    json appointmentsArray = json::array();
    for (const auto& appt : results) {
        appointmentsArray.push_back({
            {"city", appt.city},
            {"office", appt.office},
            {"service", appt.service},
            {"date", appt.date},
            {"time", appt.time},
            {"name", appt.name},
            {"cnic", appt.cnic},
            {"confirmationCode", appt.confirmationCode}
            });
    }

    json response = {
        {"success", true},
        {"count", results.size()},
        {"from", fromDate},
        {"to", toDate},
        {"appointments", appointmentsArray}
    };

    return response.dump(4);
}

string AppointmentAPI::searchByCNIC(const string& cnic) {
    vector<Appointment> results = htable->searchByCNIC(cnic);

    json appointmentsArray = json::array();
    for (const auto& appt : results) {
        appointmentsArray.push_back({
            {"city", appt.city},
            {"office", appt.office},
            {"service", appt.service},
            {"date", appt.date},
            {"time", appt.time},
            {"name", appt.name},
            {"confirmationCode", appt.confirmationCode}
            });
    }

    json response = {
        {"success", true},
        {"cnic", cnic},
        {"count", results.size()},
        {"appointments", appointmentsArray}
    };

    return response.dump(4);
}

string AppointmentAPI::searchByConfirmation(const string& code) {
    vector<Appointment> results = htable->searchByConfirmation(code);

    if (results.empty()) {
        json response = {
            {"success", false},
            {"message", "Appointment not found"}
        };
        return response.dump(4);
    }

    const auto& appt = results[0];
    json response = {
        {"success", true},
        {"appointment", {
            {"city", appt.city},
            {"office", appt.office},
            {"service", appt.service},
            {"date", appt.date},
            {"time", appt.time},
            {"cnic", appt.cnic},
            {"name", appt.name},
            {"phone", appt.phone},
            {"confirmationCode", appt.confirmationCode}
        }}
    };

    return response.dump(4);
}

string AppointmentAPI::getAllAppointments() {
    return searchByDateRange("2000-01-01 00:00", "2099-12-31 23:59");
}

void AppointmentAPI::saveToFile(const string& filename) {
    ofstream file(filename);
    if (file.is_open()) {
        file << getAllAppointments();
        file.close();
        cout << "Data saved to " << filename << endl;
    }
}

void AppointmentAPI::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (file.is_open()) {
        json data = json::parse(file);
        file.close();
        cout << "Data loaded from " << filename << endl;
    }
}
