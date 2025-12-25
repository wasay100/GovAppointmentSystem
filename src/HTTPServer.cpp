#include "../include/httplib.h"
#include "../include/API.h"
#include "../include/json.hpp"
#include <iostream>

using namespace std;
using json = nlohmann::json;

int main() {
    BTree btree(3);
    HashTable htable(100);
    AppointmentAPI api(&btree, &htable);
    
    httplib::Server server;
    
    cout << "🚀 Server starting on http://localhost:8080" << endl;
    
    // CORS headers
    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
        {"Access-Control-Allow-Headers", "Content-Type"}
    });
    
    // OPTIONS preflight
    server.Options("/(.*)", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("", "text/plain");
    });
    
    // Test endpoint
    server.Get("/", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("✅ GovAppointmentSystem API LIVE on AWS VM!", "text/plain");
    });
    
    // Book appointment endpoint
    server.Post("/api/book", [&api](const httplib::Request& req, httplib::Response& res) {
        try {
            json data = json::parse(req.body);
            string code = api.bookAppointment(
                data["city"], data["office"], data["service"],
                data["date"], data["time"], data["cnic"],
                data["name"], data["phone"]
            );
            json response = {{"success", true}, {"confirmationCode", code}};
            res.set_content(response.dump(), "application/json");
            cout << "✅ Booked: " << data["name"] << " | Code: " << code << endl;
        } catch (const exception& e) {
            json error = {{"success", false}, {"message", "Booking failed"}};
            res.set_content(error.dump(), "application/json");
            cout << "❌ Error: " << e.what() << endl;
        }
    });
    
    cout << "✅ Server ready! Test: curl localhost:8080" << endl;
    server.listen("0.0.0.0", 8080);
    return 0;
}

