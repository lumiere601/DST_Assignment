#ifndef REVIEW_ARRAY_HPP
#define REVIEW_ARRAY_HPP

#include <string>
#include <iostream>
#include "review.hpp"

class ReviewArray {
private:
    Review** reviews;
    int size;
    int capacity;

    void resize();

public:
    ReviewArray();
    ~ReviewArray();

    bool loadFromCSV(const std::string& filename);

    void append(const std::string& pid, const std::string& cid, int rating, const std::string& rt);
    int getSize() const;
    void printAll() const;

    int linearSearchByRating(const int& rating, long& steps, int& total);
    int filterSearchOneStarRating(long& steps, int& total);
    void displayFilteredOneStarReviews() const;
    void extractWordsFromReviews();
    void bubbleSortWordsByFrequency(long& comparison, long& swap);
    void printWordFrequencies() const;
    void printTop10WordFrequencies() const;
};

#endif // REVIEW_ARRAY_HPP
