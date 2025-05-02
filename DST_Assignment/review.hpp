#ifndef REVIEW_HPP
#define REVIEW_HPP

#include <string>

class Review {
public:
    std::string customerID;    // Customer ID
    std::string productID;       // Product ID
    std::string reviewText;    // Review text
    int rating;                // Review rating (e.g., 1-5 stars)

    // Default constructor
    Review() : rating(0) {}

    // Constructor to initialize with data
    Review(const std::string& cid, const std::string& prod, const std::string& revText, int rate)
        : customerID(cid), productID(prod), reviewText(revText), rating(rate) {
    }
};

#endif // REVIEW_HPP
