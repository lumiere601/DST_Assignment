#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

class TransactionNode {
public:
    std::string customerID;
    std::string product;
    std::string category;
    double price;
    int day, month, year;
    std::string paymentMethod;
    TransactionNode* next;
    TransactionNode* prev;

    TransactionNode(const std::string& cid, const std::string& prod, const std::string& cat,
        double pr, int d, int m, int y, const std::string& pay);
};

class TransactionList {
private:
    TransactionNode* head;
    TransactionNode* tail;
    int size;

    void swap(TransactionNode* a, TransactionNode* b);
    TransactionNode* mergeSort(TransactionNode* head, long& comparisons, long& swaps);
    TransactionNode* mergeSortedLists(TransactionNode* left, TransactionNode* right, long& comparisons, long& swaps);
    TransactionNode* getMiddle(TransactionNode* head);

public:
    TransactionList();
    ~TransactionList();
    bool loadFromCSV(const std::string& filename);
    void append(const std::string& cid, const std::string& prod, const std::string& cat,    
        double pr, int d, int m, int y, const std::string& pay);
    int getSize() const;
    void printAll() const;

    void bubbleSortByDate(long& comparisons, long& swaps);
    void insertionSortByDate(long& comparisons, long& swaps);
    void mergeSortByDate(long& comparisons, long& swaps);

    int linearSearchByCategoryAndPayment(const std::string& category,
        const std::string& payment,
        long& steps, int& total);
    int filterSearchElectronicsCreditCard(long& steps, int& total);
    TransactionNode* binarySearchByDate(int day, int month, int year, long& steps);
    int countByCategory(const std::string& category, long& steps, int& total);
};

#endif // TRANSACTION_HPP
