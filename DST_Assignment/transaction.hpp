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

    //Constructor to actual value
    Transaction(const std::string& cid, const std::string& prod, const std::string& cat,
        double pr, int d, int m, int y, const std::string& pay)
        : customerID(cid), product(prod), category(cat), price(pr),
        day(d), month(m), year(y), paymentMethod(pay) {
    }

    // Function to parse date in the format DD/MM/YYYY
    void parseDate(const std::string& dateStr) {
        std::stringstream ss(dateStr);
        char delimiter;
        ss >> day >> delimiter >> month >> delimiter >> year;
    }

    bool isEarlierThan(const Transaction& other) const {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }

    std::string getDateString() const {
        std::ostringstream oss;
        oss << std::setw(2) << std::setfill('0') << day << "/"
            << std::setw(2) << std::setfill('0') << month << "/"
            << std::setw(4) << std::setfill('0') << year;
        return oss.str();
    }
};
#endif
