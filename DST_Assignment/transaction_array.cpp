#include "transaction_array.hpp"
#include "transaction.hpp"
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <sstream>

// Global counters
int comparisonCount = 0;
int swapCount = 0;

TransactionArray::TransactionArray() : data(nullptr), capacity(0), count(0) {}

TransactionArray::~TransactionArray() {
    delete[] data;
}

void TransactionArray::expandIfNeeded() {
    if (count >= capacity) {
        int newCapacity = (capacity == 0) ? 10 : capacity * 2;
        Transaction* newData = new Transaction[newCapacity];
        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

int TransactionArray::getCount() const {
    return count;
}

bool TransactionArray::loadFromCSV(const char* filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return false;

    std::string line;
    getline(file, line); // Skip header

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string cid, prod, cat, priceStr, dateStr, pay;
        getline(ss, cid, ',');
        getline(ss, prod, ',');
        getline(ss, cat, ',');
        getline(ss, priceStr, ',');
        getline(ss, dateStr, ',');
        getline(ss, pay, ',');

        double price = std::stod(priceStr);
        int d, m, y;
        std::stringstream ssDate(dateStr);
        char delim;
        ssDate >> d >> delim >> m >> delim >> y;

        expandIfNeeded();
        data[count++] = Transaction(cid, prod, cat, price, d, m, y, pay);
    }

    file.close();
    return true;
}

void TransactionArray::swap(Transaction& a, Transaction& b) {
    Transaction temp = a;
    a = b;
    b = temp;
    swapCount++;
}

int TransactionArray::partition(int low, int high) {
    Transaction pivot = data[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        comparisonCount++;
        if (data[j].isEarlierThan(pivot)) {
            ++i;
            swap(data[i], data[j]);
        }
    }
    swap(data[i + 1], data[high]);
    return i + 1;
}

void TransactionArray::quickSort(int low, int high) {
    if (low < high) {
        int pi = partition(low, high);
        quickSort(low, pi - 1);
        quickSort(pi + 1, high);
    }
}

void TransactionArray::quickSort() {
    if (count > 0) {
        quickSort(0, count - 1);
    }
}

void TransactionArray::display() const {
    std::cout << "\n=====================================================================\n";
    for (int i = 0; i < count; ++i) {
        const Transaction& t = data[i];
        std::cout << t.customerID << "," << t.product << "," << t.category << ","
            << std::fixed << std::setprecision(2) << t.price << ","
            << (t.day < 10 ? "0" : "") << t.day << "/"
            << (t.month < 10 ? "0" : "") << t.month << "/"
            << t.year << "," << t.paymentMethod << "\n";
    }
}

void TransactionArray::printAt(int index) const {
    if (index >= 0 && index < count) {
        const Transaction& t = data[index];
        std::cout << t.customerID << "," << t.product << "," << t.category << ","
            << std::fixed << std::setprecision(2) << t.price << ","
            << (t.day < 10 ? "0" : "") << t.day << "/"
            << (t.month < 10 ? "0" : "") << t.month << "/"
            << t.year << "," << t.paymentMethod << "\n";
    }
}

void TransactionArray::getUniqueCategories(std::string* categories, int& catCount) const {
    catCount = 0;
    for (int i = 0; i < count; ++i) {
        bool exists = false;
        for (int j = 0; j < catCount; ++j) {
            if (data[i].category == categories[j]) {
                exists = true;
                break;
            }
        }
        if (!exists) {
            categories[catCount++] = data[i].category;
        }
    }
}

void TransactionArray::getUniquePaymentMethods(const std::string& category, std::string* methods, int& methodCount) const {
    methodCount = 0;
    for (int i = 0; i < count; ++i) {
        if (data[i].category == category) {
            bool exists = false;
            for (int j = 0; j < methodCount; ++j) {
                if (data[i].paymentMethod == methods[j]) {
                    exists = true;
                    break;
                }
            }
            if (!exists) {
                methods[methodCount++] = data[i].paymentMethod;
            }
        }
    }
}

void TransactionArray::countMatching(const std::string& category, const std::string& method, int& categoryCount, int& methodCount, int& stepsTaken) const {
    categoryCount = methodCount = stepsTaken = 0;
    for (int i = 0; i < count; ++i) {
        stepsTaken++;
        if (data[i].category == category) {
            categoryCount++;
            if (data[i].paymentMethod == method) {
                methodCount++;
            }
        }
    }
}

void TransactionArray::mergeSort() {
    if (count > 0) {
        mergeSortHelper(0, count - 1);
    }
}

void TransactionArray::mergeSortHelper(int left, int right) {
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;
    mergeSortHelper(left, mid);
    mergeSortHelper(mid + 1, right);
    merge(left, mid, right);
}

void TransactionArray::merge(int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Transaction* L = new Transaction[n1];
    Transaction* R = new Transaction[n2];

    for (int i = 0; i < n1; i++) L[i] = data[left + i];
    for (int j = 0; j < n2; j++) R[j] = data[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        comparisonCount++;
        if (L[i].isEarlierThan(R[j])) {
            data[k++] = L[i++];
        }
        else {
            data[k++] = R[j++];
        }
        swapCount++;
    }

    while (i < n1) {
        data[k++] = L[i++];
        swapCount++;
    }

    while (j < n2) {
        data[k++] = R[j++];
        swapCount++;
    }

    delete[] L;
    delete[] R;
}