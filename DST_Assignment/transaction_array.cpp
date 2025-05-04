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
        Transaction* newData = new Transaction[newCapacity];  // Safe

        for (int i = 0; i < count; ++i) {
            newData[i] = data[i];  // Shallow copy is fine since Transaction has no raw pointers
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }
}

int TransactionArray::getCount() const {
    return count;
}

// Helper to trim whitespace
std::string static trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\r\n");
    size_t last = str.find_last_not_of(" \t\r\n");
    return (first == std::string::npos || last == std::string::npos) ? "" : str.substr(first, last - first + 1);
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

        if (cid.empty() || priceStr.empty() || dateStr.empty()) continue;

        double price = std::stod(priceStr);
        int d, m, y;
        char delim;
        std::stringstream ssDate(dateStr);
        ssDate >> d >> delim >> m >> delim >> y;

        expandIfNeeded();
        data[count++] = Transaction(
            trim(cid), trim(prod), trim(cat), price, d, m, y, trim(pay)
        );
    }

    file.close();
    return true;
}

void TransactionArray::sortByCategoryPayment() {
    comparisonCount = 0;
    swapCount = 0;

    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            comparisonCount++;
            if (data[j].category > data[j + 1].category ||
                (data[j].category == data[j + 1].category &&
                    data[j].paymentMethod > data[j + 1].paymentMethod)) {
                swap(data[j], data[j + 1]);
            }
        }
    }
}

int TransactionArray::binarySearchCategoryPayment(const std::string& category, const std::string& payment) const {
    int left = 0, right = count - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        comparisonCount++;

        if (data[mid].category == category && data[mid].paymentMethod == payment) {
            return mid;
        }
        else if (data[mid].category < category ||
            (data[mid].category == category && data[mid].paymentMethod < payment)) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int TransactionArray::searchCategoryPaymentBinary(const std::string& category, const std::string& method, int& categoryCount, int& methodCount) {
    int steps = 0;
    categoryCount = 0;
    methodCount = 0;
    int left = 0, right = count - 1, foundIndex = -1;

    while (left <= right) {
        steps++;
        int mid = (left + right) / 2;
        int cmp = data[mid].category.compare(category);
        if (cmp == 0) {
            foundIndex = mid;
            break;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (foundIndex == -1) return steps;

    for (int i = foundIndex; i >= 0 && data[i].category == category; --i) {
        steps++;
        categoryCount++;
        if (data[i].paymentMethod == method) methodCount++;
    }
    for (int i = foundIndex + 1; i < count && data[i].category == category; ++i) {
        steps++;
        categoryCount++;
        if (data[i].paymentMethod == method) methodCount++;
    }

    return steps;
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
            swap(data[++i], data[j]);
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
        comparisonCount = 0;
        swapCount = 0;
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
        comparisonCount = 0;
        swapCount = 0;
        mergeSortHelper(0, count - 1);
    }
}

void TransactionArray::mergeSortHelper(int left, int right) {
    if (left >= right) return;

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