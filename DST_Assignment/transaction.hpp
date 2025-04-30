#ifndef TRANSACTION_HPP // Check if TRANSACTION_HPP is not already defined
#define TRANSACTION_HPP // Define it

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

class Transaction {
public:
    std::string customerID;    // Customer ID
    std::string product;       // Product name
    std::string category;      // Product category
    double price;              // Price of the product
    int day, month, year;      // Date (Day, Month, Year)
    std::string paymentMethod; // Payment method

    // Constructor to initialize with default values
    Transaction() : price(0.0), day(0), month(0), year(0) {}

    // Function to parse date in the format DD/MM/YYYY
    void parseDate(const std::string& dateStr) {
        std::stringstream ss(dateStr);
        char delimiter;
        ss >> day >> delimiter >> month >> delimiter >> year;
    }

    // Optional: Function to print transaction details (for debugging)
    void printTransaction() const {
        std::cout << "Customer ID: " << customerID << ", "
                  << "Product: " << product << ", "
                  << "Category: " << category << ", "
                  << "Price: " << price << ", "
                  << "Date: " << std::setw(2) << std::setfill('0') << day << "/"
                  << std::setw(2) << std::setfill('0') << month << "/"
                  << year << ", "
                  << "Payment Method: " << paymentMethod << std::endl;
    }
};

#endif // TRANSACTION_HPP // End the guard
