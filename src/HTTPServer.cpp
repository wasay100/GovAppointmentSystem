#include "httplib.h"
#include "API.h"
#include "json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
    // Create data structures
    BTree btree(3);
    HashTable htable(100);
    
    // Create AppointmentAPI
    AppointmentAPI api(&btree, &htable);
    
    httplib::Server server;
    
    cout << "🚀 Server starting on http://localhost:8080" << endl;
    
    // CORS headers
    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });
    
    // Handle OPTIONS requests
    server.Options("/(.*)", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("", "text/plain");
    });
    
    // Test endpoint
    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("✅ Government Appointment System API is running!", "text/plain");
    });
    
    // Book appointment
    server.Post("/api/book", [&api](const httplib::Request& req, httplib::Response& res) {
        try {
            json data = json::parse(req.body);
            
            string confirmationCode = api.bookAppointment(
                data["city"], data["office"], data["service"],
                data["date"], data["time"], data["cnic"],
                data["name"], data["phone"]
            );
            
            json response;
            response["success"] = true;
            response["confirmationCode"] = confirmationCode;
            response["message"] = "Appointment booked successfully!";
            
            res.set_content(response.dump(), "application/json");
            cout << "✅ Booked: " << data["name"] << " (" << confirmationCode << ")" << endl;
            
        } catch (exception& e) {
            json error;
            error["success"] = false;
            error["message"] = "Error: " + string(e.what());
            res.set_content(error.dump(), "application/json");
        }
    });
    
    // Search by CNIC
    server.Get(R"(/api/search/cnic/(.+))", [&api](const httplib::Request& req, httplib::Response& res) {
        string cnic = req.matches[1];
        string jsonResult = api.searchByCNIC(cnic);
        res.set_content(jsonResult, "application/json");
        cout << "🔍 CNIC search: " << cnic << endl;
    });
    
    // Search by confirmation code
    server.Get(R"(/api/search/code/(.+))", [&api](const httplib::Request& req, httplib::Response& res) {
        string code = req.matches[1];
        string jsonResult = api.searchByConfirmation(code);
        res.set_content(jsonResult, "application/json");
        cout << "🔍 Code search: " << code << endl;
    });
    
    // Get all appointments
    server.Get("/api/appointments", [&api](const httplib::Request&, httplib::Response& res) {
        string jsonResult = api.getAllAppointments();
        res.set_content(jsonResult, "application/json");
    });
    
    // Search by date range
    server.Get("/api/search/daterange", [&api](const httplib::Request& req, httplib::Response& res) {
        string startDate = req.get_param_value("start");
        string endDate = req.get_param_value("end");
        string jsonResult = api.searchByDateRange(startDate, endDate);
        res.set_content(jsonResult, "application/json");
        cout << "📅 Date range: " << startDate << " to " << endDate << endl;
    });
    
    cout << "✅ Server running! Open http://localhost:8080" << endl;
    server.listen("0.0.0.0", 8080);
    
    return 0;
}
