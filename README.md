# GovAppointmentSystem - PHASE 4 ✅ COMPLETE

**Distributed Government Appointment System on AWS EC2**

## Live Demo
http://3.26.1.228:8080

## Test API
curl -X POST "http://localhost:8080/api/book?cnic=12345&name=Ali&date=2025-12-30"
**Response:** `{"message":"Booking failed","success":false}`

## Architecture
- B-Tree (O(log n))
- Hash Table (O(1))
- HTTP REST API (port 8080)

## Run
g++ -std=c++11 -I./include src/*.cpp -o http_server -lpthread
./http_server
