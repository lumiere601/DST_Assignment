#include "review_array.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cctype>
#include <cstring>

// Constructor
ReviewArray::ReviewArray() : reviews(nullptr), size(0), capacity(10) {
    reviews = new Review * [capacity];
}

struct WordFreq {
    std::string word;
    int freq;
};

WordFreq wordFreqArray[1000];
int wordCount = 0;

// Destructor
ReviewArray::~ReviewArray() {
    for (int i = 0; i < size; ++i) {
        delete reviews[i];
    }
    delete[] reviews;
}

bool ReviewArray::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // Skip header

    int lineCount = 0;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string productID, customerID, ratingStr, reviewText;

        std::getline(ss, productID, ',');
        std::getline(ss, customerID, ',');
        std::getline(ss, ratingStr, ',');
        std::getline(ss, reviewText);

        try {
            int rating = std::stoi(ratingStr);
            append(productID, customerID, rating, reviewText);
            ++lineCount;
        }
        catch (...) {
            std::cerr << "Skipping invalid line with rating: " << ratingStr << std::endl;
        }
    }

    std::cout << "Loaded " << lineCount << " reviews from CSV.\n";
    return true;
}

void ReviewArray::resize() {
    capacity *= 2;
    Review** newReviews = new Review * [capacity];
    for (int i = 0; i < size; ++i) {
        newReviews[i] = reviews[i];
    }
    delete[] reviews;
    reviews = newReviews;
}

void ReviewArray::append(const std::string& pid, const std::string& cid, int rating, const std::string& rt) {
    if (size >= capacity) {
        resize();
    }
    reviews[size++] = new Review(cid, pid, rt, rating);
}

int ReviewArray::getSize() const {
    return size;
}

void ReviewArray::printAll() const {
    std::cout << "Rating | ProductID   | CustomerID    | Review\n";
    std::cout << "---------------------------------------------------------\n";
    for (int i = 0; i < size; ++i) {
        std::cout << reviews[i]->rating << "      | "
            << reviews[i]->productID << "     | "
            << reviews[i]->customerID << "      | "
            << reviews[i]->reviewText << std::endl;
    }
}

int ReviewArray::linearSearchByRating(const int& rating, long& steps, int& total) {
    steps = 0;
    total = 0;
    for (int i = 0; i < size; ++i) {
        steps++;
        if (reviews[i]->rating == rating) {
            total++;
        }
    }
    return total;
}

int ReviewArray::filterSearchOneStarRating(long& steps, int& total) {
    return linearSearchByRating(1, steps, total);
}

void ReviewArray::displayFilteredOneStarReviews() const {
    std::cout << "\nFiltered 1-Star Reviews:\n";
    std::cout << "---------------------------------------------------------\n";
    for (int i = 0; i < size; ++i) {
        if (reviews[i]->rating == 1) {
            std::cout << reviews[i]->rating << "      | "
                << reviews[i]->productID << "     | "
                << reviews[i]->customerID << "      | "
                << reviews[i]->reviewText << std::endl;
        }
    }
}

void ReviewArray::extractWordsFromReviews() {
    wordCount = 0; // Reset the word count

    for (int i = 0; i < size; ++i) {
        if (reviews[i]->rating == 1) {
            std::stringstream ss(reviews[i]->reviewText);
            std::string word;

            while (ss >> word) {
                // Clean the word: remove punctuation and convert to lowercase
                std::string cleanWord = "";
                for (char c : word) {
                    if (!std::ispunct(static_cast<unsigned char>(c))) {
                        cleanWord += std::tolower(static_cast<unsigned char>(c));
                    }
                }

                if (!cleanWord.empty()) {
                    bool found = false;

                    // Check if the word is already in the frequency array
                    for (int j = 0; j < wordCount; ++j) {
                        if (wordFreqArray[j].word == cleanWord) {
                            wordFreqArray[j].freq++;
                            found = true;
                            break;
                        }
                    }

                    // If not found, add it
                    if (!found && wordCount < 1000) {
                        wordFreqArray[wordCount].word = cleanWord;
                        wordFreqArray[wordCount].freq = 1;
                        wordCount++;
                    }
                }
            }
        }
    }
}


void ReviewArray::bubbleSortWordsByFrequency(long& comparison, long& swap) {
    comparison = 0;
    swap = 0;
    bool swapped;
    for (int i = 0; i < wordCount - 1; ++i) {
        swapped = false;
        for (int j = 0; j < wordCount - i - 1; ++j) {
            comparison++;
            if (wordFreqArray[j].freq < wordFreqArray[j + 1].freq) {
                std::swap(wordFreqArray[j], wordFreqArray[j + 1]);
                swap++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

void ReviewArray::printWordFrequencies() const {
    std::cout << "Word Frequencies:\n";
    for (int i = 0; i < wordCount; ++i) {
        std::cout << wordFreqArray[i].word << ": " << wordFreqArray[i].freq << "\n";
    }
}

void ReviewArray::printTop10WordFrequencies() const {
    std::cout << "Top 10 Words (Frequency Sorted):\n";
    for (int i = 0; i < 10 && i < wordCount; ++i) {
        std::cout << wordFreqArray[i].word << ": " << wordFreqArray[i].freq << "\n";
    }
}
