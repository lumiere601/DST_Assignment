#ifndef TRANSACTION_ARRAY_HPP
#define TRANSACTION_ARRAY_HPP

#include "transaction.hpp"
#include <string>

class TransactionArray {
private:
    Transaction* data;       // Pointer to dynamic array
    int capacity;            // Current capacity of the array
    int count;               // Current number of stored transactions

    void expandIfNeeded();
    void quickSort(int low, int high);
    int partition(int low, int high);
    void swap(Transaction& a, Transaction& b);
    void mergeSortHelper(int left, int right);
    void merge(int left, int mid, int right);

public:
    TransactionArray();
    ~TransactionArray();

    int getCount() const;
    bool loadFromCSV(const char* filename);
    void quickSort();
    void mergeSort();
    void display() const;

    int binarySearchByDate(const std::string& targetDate) const;
    void printAt(int index) const;

    void getUniqueCategories(std::string* categories, int& catCount) const;
    void getUniquePaymentMethods(const std::string& category, std::string* methods, int& methodCount) const;

    void countMatching(const std::string& category, const std::string& method, int& categoryCount, int& methodCount, int& stepsTaken) const;
};

// Global counters for sort statistics
extern int comparisonCount;
extern int swapCount;

#endif // TRANSACTION_ARRAY_HPP