#ifndef REVIEW_LIST_HPP
#define REVIEW_LIST_HPP

#include "review.hpp"  // Include the Review class from review.hpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

//Singled linked list
struct ReviewNode {
    Review data;          // Each node contains a Review
    ReviewNode* next;     // Pointer to the next node
    ReviewNode(const Review& review) : data(review), next(nullptr) {}
};

struct WordFreqNode {
    std::string word;
    int count;
    WordFreqNode* next;
    WordFreqNode(const std::string& w) : word(w), count(1), next(nullptr) {}
};

class ReviewList {
public:
    ReviewNode* head;  
    int steps;    

    // Constructor to initialize the list
    ReviewList() : head(nullptr), steps(0) {}
    // Function to load reviews from CSV into the linked list
    void loadFromCSV(const std::string& filename);

    void displayAll() const;

    // Function to filter out 1-star reviews
    void collectOneStarReviews(ReviewNode*& filteredHead);

    // Function to extract words from review text and count their frequency
    void extractWords(const std::string& reviewText, WordFreqNode*& wordHead);

    // Function to insert or update the frequency of a word in the list
    void insertOrUpdateWord(WordFreqNode*& wordHead, const std::string& word);

    // Function to display the most frequent words (top N words)
    void displayTopNWords(WordFreqNode* wordHead, int N);

    // Function to track performance metrics
    void trackPerformanceMetrics() const;

    // Function to sort word frequencies by count (added declaration here)
    void sortWordFrequencies(WordFreqNode*& wordHead);

    void processOneStarReviews();

    void displayAllWords(WordFreqNode* wordHead);
};

#endif // REVIEW_LIST_HPP
