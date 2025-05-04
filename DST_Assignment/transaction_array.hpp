#ifndef TRANSACTION_ARRAY_HPP
#define TRANSACTION_ARRAY_HPP

#include "transaction.hpp"
#include <string>


class TransactionArray {
private:
    Transaction* data;       // Pointer to dynamic array
    int capacity;            // Current capacity of the array
    int count;               // Number of stored transactions


    // Private helper functions
    void expandIfNeeded();
    void quickSort(int low, int high);
    int partition(int low, int high);
    void swap(Transaction& a, Transaction& b);
    void mergeSortHelper(int left, int right);
    void merge(int left, int mid, int right);

public:
    TransactionArray();
    ~TransactionArray();

    // Load and access, to  initialize and present data.
    bool loadFromCSV(const char* filename);
    int getCount() const;
    void display() const;
    void printAt(int index) const;

    // Offers multiple sorting options 
    void quickSort();
    void mergeSort();
    void sortByCategoryPayment();

    // Binary search and search display Supports efficient and flexible data lookup.
    int binarySearchCategoryPayment(const std::string& category, const std::string& payment) const;
    int searchCategoryPaymentBinary(const std::string& category, const std::string& method, int& categoryCount, int& methodCount);



    // Helpers for filtering and statistics
    void getUniqueCategories(std::string* categories, int& catCount) const;
    void getUniquePaymentMethods(const std::string& category, std::string* methods, int& methodCount) const;
    void countMatching(const std::string& category, const std::string& method, int& categoryCount, int& methodCount, int& stepsTaken) const;
};

// Global counters for sort statistics Enables tracking performance
extern int comparisonCount;
extern int swapCount;

#endif // TRANSACTION_ARRAY_HPP