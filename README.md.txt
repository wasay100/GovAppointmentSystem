# Government Appointment System

A distributed appointment booking system for Pakistani government offices (NADRA, Passport) using custom data structures.

## Features

- Custom B-tree implementation for sorted time slot storage
- Hash table for O(1) CNIC and confirmation code lookups
- JSON API for appointment management
- Support for multiple cities (Karachi, Lahore, Islamabad)

## Data Structures Used

### B-Tree
- Stores appointments sorted by date and time
- Enables fast range queries (e.g., "all slots between 9 AM - 12 PM")
- Balanced tree structure for efficient insertion and search

### Hash Table
- Instant CNIC number lookups
- Fast confirmation code searches
- Chaining for collision handling

## Project Structure

GovAppointmentSystem/
├── src/ # Source files
│ ├── BTree.cpp # B-tree implementation
│ ├── HashTable.cpp # Hash table implementation
│ ├── API.cpp # API layer
│ └── GovAppointmentSystem.cpp # Main program
├── include/ # Header files
│ ├── Appointment.h # Appointment structure
│ ├── BTree.h # B-tree interface
│ ├── HashTable.h # Hash table interface
│ ├── API.h # API interface
│ └── json.hpp # JSON library
├── docs/ # Documentation
└── README.md # This file


## Technologies

- **Language:** C++17
- **Build System:** Visual Studio 2022 / g++
- **JSON Library:** nlohmann/json (formatting only)
- **Cloud Platform:** AWS EC2 (upcoming)
- **Version Control:** GitHub

## How to Compile and Run

### Using Visual Studio 2022
1. Open Visual Studio 2022
2. Create new Console App project
3. Add all files from `src/` and `include/`
4. Build: Ctrl + Shift + B
5. Run: Ctrl + F5

### Using g++
