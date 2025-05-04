#ifndef TRANSACTION_LIST_HPP
#define TRANSACTION_LIST_HPP

#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include "transaction.hpp"

struct TransactionNode {
public:
    Transaction data;
    TransactionNode* next;
    TransactionNode* prev;
    TransactionNode(const Transaction& t)
        : data(t), next(nullptr), prev(nullptr) {
    }
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
    TransactionList() : head(nullptr), tail(nullptr), size(0) {}
    ~TransactionList();
    bool loadFromCSV(const std::string& filename);
    void InsertNodeAtBack(const std::string& cid, const std::string& prod, const std::string& cat,
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
    int countByCategory(const std::string& category, long& steps, int& total);
};
#endif // TRANSACTION_LIST_HPP
