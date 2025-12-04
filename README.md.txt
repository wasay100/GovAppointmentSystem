# Government Appointment System

A distributed appointment booking system for Pakistani government offices (NADRA, Passport) using custom B-tree and hash table data structures implemented from scratch in C++.

## Overview

This system eliminates long queues at government offices by allowing citizens to book specific appointment time slots online. The backend uses custom data structures for efficient appointment management, while the frontend provides an intuitive web interface.

## Features

- Custom B-tree implementation for time-ordered appointment storage
- Hash table with O(1) lookup for CNIC and confirmation codes
- JSON API for structured data output
- Multi-city support (Karachi, Lahore, Islamabad)
- Web interface with booking and search functionality
- Cloud deployment on AWS EC2

## Data Structures

### B-Tree
- Stores appointments sorted by date and time
- Enables efficient range queries for time slot searches
- Self-balancing structure maintains O(log n) operations

### Hash Table
- Provides constant-time CNIC lookups
- Fast confirmation code searches
- Collision handling via chaining

## Project Structure

GovAppointmentSystem/
├── src/
│ ├── BTree.cpp
│ ├── HashTable.cpp
│ ├── API.cpp
│ └── GovAppointmentSystem.cpp
├── include/
│ ├── Appointment.h
│ ├── BTree.h
│ ├── HashTable.h
│ ├── API.h
│ └── json.hpp
├── web/
│ ├── index.html
│ ├── login.html
│ ├── book.html
│ ├── search.html
│ ├── style.css
│ └── app.js
└── README.md


## Technologies

- **Language:** C++17
- **Build Tools:** Visual Studio 2022, g++
- **JSON Library:** nlohmann/json
- **Cloud Platform:** AWS EC2 (Ubuntu 24.04)
- **Frontend:** HTML5, CSS3, JavaScript

## Compilation and Execution

### Using g++ (Linux/AWS)
g++ -std=c++17 src/BTree.cpp src/HashTable.cpp src/API.cpp src/GovAppointmentSystem.cpp -I include -o appointment_system
./appointment_system


### Using Visual Studio 2022
1. Create new Console App project
2. Add all source files from `src/` and headers from `include/`
3. Build and run (Ctrl + F5)

## System Features

### Console Interface
1. Book New Appointment
2. Search by Date Range
3. Search by CNIC
4. Search by Confirmation Code
5. View All Appointments
6. Save Data to File
7. Exit

### Web Interface
- Pakistan-themed design (green and white colors)
- User authentication with role-based access
- Interactive booking forms
- Real-time appointment search
- Confirmation code generation

## AWS Deployment

The system is deployed on AWS EC2 infrastructure:
- Instance Type: t3.micro
- Operating System: Ubuntu 24.04 LTS
- Region: Asia Pacific (Sydney)

## Development

This project was developed as part of a Data Structures and Algorithms course, demonstrating practical applications of:
- Tree data structures
- Hash tables and collision resolution
- API design patterns
- Full-stack development
- Cloud deployment

## Author

Syed Muhammad Wasay  
December 2025

## License

Educational project for academic coursework.
