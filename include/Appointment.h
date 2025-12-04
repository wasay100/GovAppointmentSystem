#pragma once
#include <string>

using namespace std;

struct Appointment {
    string city;
    string office;
    string service;
    string date;
    string time;
    string cnic;
    string name;
    string phone;
    string confirmationCode;

    // Default constructor (ADDED THIS)
    Appointment()
        : city(""), office(""), service(""), date(""), time(""),
        cnic(""), name(""), phone(""), confirmationCode("") {
    }

    // Parameterized constructor
    Appointment(string c, string o, string s, string d, string t,
        string cn, string n, string p, string cc)
        : city(c), office(o), service(s), date(d), time(t),
        cnic(cn), name(n), phone(p), confirmationCode(cc) {
    }

    // Get combined datetime key for B-tree sorting
    string getDateTime() const {
        return date + " " + time;
    }
};
