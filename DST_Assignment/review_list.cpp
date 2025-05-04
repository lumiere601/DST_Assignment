#include "review_list.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>

//load_CSV
void ReviewList::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Could not open file: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineCount = 0;

    // Skip header
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string product, customerID, ratingStr, reviewText;

        std::getline(ss, product, ',');
        std::getline(ss, customerID, ',');
        std::getline(ss, ratingStr, ',');

        // Get remainder of the line as reviewText (can contain commas, quotes, etc.)
        std::getline(ss, reviewText);

        try {
            int rating = std::stoi(ratingStr);

            Review review(customerID, product, reviewText, rating);
            ReviewNode* newNode = new ReviewNode(review);

            // If the list is empty, make the new node the head
            if (head == nullptr) {
                head = newNode;
            }
            else {
                // Otherwise, find the last node and add the new node there
                ReviewNode* current = head;
                while (current->next != nullptr) {
                    current = current->next;
                }
                current->next = newNode;
            }

        }
        catch (const std::exception& e) {
            std::cerr << "Error parsing rating on line " << lineCount + 2 << ": "
                << ratingStr << " (" << e.what() << ")" << std::endl;
        }

        ++lineCount;
    }

    std::cout << "Total reviews: " << lineCount << std::endl;
}

void ReviewList::displayAll() const {
    ReviewNode* current = head;
    int index = 1;

    if (current == nullptr) {
        std::cout << "No reviews to display." << std::endl;
        return;
    }

    while (current != nullptr) {
        std::cout << "Review #" << index++ << ": Customer ID: " << current->data.customerID
            << ", Product: " << current->data.productID
            << ", Rating: " << current->data.rating
            << ", Review Text: " << current->data.reviewText << std::endl;
        current = current->next;
    }
}

// Function to collect 1-star reviews
void ReviewList::collectOneStarReviews(ReviewNode*& filteredHead) {
    ReviewNode* current = head;
    int reviewCount = 0;
    while (current != nullptr) {
        if (current->data.rating == 1) {
            // Copy the 1-star review to filteredHead
            ReviewNode* newNode = new ReviewNode(current->data);
            newNode->next = nullptr;  // Set the next of the new node to nullptr (end of list)

            // If the list is empty, make the new node the head
            if (filteredHead == nullptr) {
                filteredHead = newNode;
            }
            else {
                // Traverse to the end of the list and add the new node
                ReviewNode* temp = filteredHead;
                while (temp->next != nullptr) {
                    temp = temp->next;
                }
                temp->next = newNode;
            }
            reviewCount++;
        }
        steps++;
        current = current->next;
    }

    // After collecting, display the 1-star reviews in a nice list format
    std::cout << "\n--- 1-Star Reviews ---\n";
    ReviewNode* temp = filteredHead;
    if (temp == nullptr) {
        std::cout << "No 1-star reviews found.\n";
    }
    else {
        int reviewNumber = 1; // Start numbering from 1
        while (temp != nullptr) {
            std::cout << "Review #" << reviewNumber++ << ": Rating: " << temp->data.rating
                << ", Customer ID: " << temp->data.customerID
                << ", Product: " << temp->data.productID
                << ", Review Text: " << temp->data.reviewText << std::endl;
            temp = temp->next;
        }
    }

    std::cout << "\nTotal 1-star reviews: " << reviewCount << std::endl;
}


// Function to extract words from review text and count their frequency
void ReviewList::extractWords(const std::string& reviewText, WordFreqNode*& wordHead) {
    std::stringstream ss(reviewText);
    std::string word;

    while (ss >> word) {
        // Remove punctuation from word manually
        std::string cleanWord = "";
        for (size_t i = 0; i < word.size(); ++i) {
            if (isalpha(word[i])) {
                cleanWord += tolower(word[i]); // convert to lowercase
            }
        }

        insertOrUpdateWord(wordHead, cleanWord);
    }
}

// Function to insert or update the frequency of a word in the list
void ReviewList::insertOrUpdateWord(WordFreqNode*& wordHead, const std::string& word) {
    WordFreqNode* current = wordHead;
    while (current != nullptr) {
        if (current->word == word) {
            current->count++;
            return;
        }
        current = current->next;
    }

    // If word is not found, insert a new node
    WordFreqNode* newNode = new WordFreqNode(word);
    newNode->next = wordHead;
    wordHead = newNode;
}

// Function to display the most frequent words (top N words)
void ReviewList::displayTopNWords(WordFreqNode* wordHead, int N) {

    WordFreqNode* current = wordHead;
    while (current != nullptr && N > 0) {
        std::cout << current->word << ": " << current->count << std::endl;
        current = current->next;
        N--;
    }
}

void ReviewList::displayAllWords(WordFreqNode* wordHead) {
    WordFreqNode* current = wordHead;
    if (current == nullptr) {
        std::cout << "No words found." << std::endl;
        return;
    }

    while (current != nullptr) {
        std::cout << current->word << ": " << current->count << std::endl;
        current = current->next;
    }
}

// Function to track performance metrics (steps for search operations)
void ReviewList::trackPerformanceMetrics() const {
    std::cout << "\n[Performance Metrics for Linear Searching]\n";
    std::cout << "Total steps taken during searching: " << steps << std::endl;
    std::cout << std::endl;
}

// Function to sort word frequencies by count (using bubble sort as an example)
void ReviewList::sortWordFrequencies(WordFreqNode*& wordHead) {
    if (wordHead == nullptr || wordHead->next == nullptr) {
        return; // No need to sort if the list is empty or has one element
    }

    using namespace std::chrono;
    auto start = high_resolution_clock::now();

    long sortSteps = 0;  // To track the number of comparisons
    long swapCount = 0;  // To track the number of swaps
    bool swapped;
    do {
        swapped = false;
        WordFreqNode* current = wordHead;
        while (current->next != nullptr) {
            sortSteps++; // Count comparison

            if (current->count < current->next->count) {
                // Swap manually without using std::swap
                std::string tempWord = current->word;
                int tempCount = current->count;
                current->word = current->next->word;
                current->count = current->next->count;
                current->next->word = tempWord;
                current->next->count = tempCount;

                swapped = true;
                swapCount++;  // Increment swap count
            }
            current = current->next;
        }
    } while (swapped);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);

    // Output performance metrics
    std::cout << "\n[Performance Metrics for Bubble Sort]\n";
    std::cout << "Time taken to sort (Bubble Sort): " << duration.count() << " microseconds\n";
    std::cout << "Total comparisons made: " << sortSteps << std::endl;
    std::cout << "Total swaps performed: " << swapCount << std::endl;
}

// Collect and process 1-star reviews, then extract and display the top N frequent words
void ReviewList::processOneStarReviews() {
    // Create a list to store 1-star reviews
    ReviewNode* filteredHead = nullptr;

    // Collect 1-star reviews
    collectOneStarReviews(filteredHead);

    // For each 1-star review, extract words and count frequencies
    WordFreqNode* wordHead = nullptr;
    ReviewNode* current = filteredHead;
    while (current != nullptr) {
        extractWords(current->data.reviewText, wordHead);
        current = current->next;
    }
    std::cout << "All appearing words before sorting: " << std::endl;
    displayAllWords(wordHead);
    sortWordFrequencies(wordHead);
    trackPerformanceMetrics();
    std::cout << "All appearing words after sorting: " << std::endl;
    displayAllWords(wordHead);
    std::cout << "Top 10 most frequent words: " << std::endl;
    displayTopNWords(wordHead, 10);
}
