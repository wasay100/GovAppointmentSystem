#include <httplib.h>
#include <iostream>
#include <string>

using namespace httplib;

int main() {
    Server svr;
    
    svr.Post("/api/book", [&](const Request& req, Response& res) {
        std::string cnic = req.get_param_value("cnic");
        std::string name = req.get_param_value("name");
        std::string date = req.get_param_value("date");
        
        std::string bookingId = cnic + "_" + name + "_" + date;
        
        res.set_header("Content-Type", "application/json");
        res.set_content("{\"bookingId\":\"" + bookingId + "\"}", "text/plain");
    });
    
    std::cout << "🚀 Server http://0.0.0.0:8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
}
