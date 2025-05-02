#include "transaction_list.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

// Destructor for TransactionList
TransactionList::~TransactionList() {
    TransactionNode* current = head;
    while (current != nullptr) {
        TransactionNode* temp = current;
        current = current->next;
        delete temp;
    }
}

// Append method to add transactions to the list
void TransactionList::append(const std::string& cid, const std::string& prod, const std::string& cat,
                              double pr, int d, int m, int y, const std::string& pay) {

    Transaction transaction(cid, prod, cat, pr, d, m, y, pay);
    TransactionNode* newNode = new TransactionNode(transaction);

    if (head == nullptr) {
        head = tail = newNode;
    }
    else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    size++;
}

// Method to load transaction data from CSV
bool TransactionList::loadFromCSV(const std::string& filename) {
    std::ifstream file(filename);
    std::string line;

    if (!file.is_open()) return false;
    getline(file, line);

    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string customerID, product, category, paymentMethod;
        double price;
        int day, month, year;

        std::getline(ss, customerID, ',');
        std::getline(ss, product, ',');
        std::getline(ss, category, ',');
        ss >> price;
        ss.ignore();
        ss >> day;
        ss.ignore();
        ss >> month;
        ss.ignore();
        ss >> year;
        ss.ignore();
        std::getline(ss, paymentMethod);

        append(customerID, product, category, price, day, month, year, paymentMethod);
    }

    file.close();
    return true;
}

// Get size of the list
int TransactionList::getSize() const {
    return size;
}

// Swap helper function for sorting
void TransactionList::swap(TransactionNode* a, TransactionNode* b) {
    std::swap(a->data.customerID, b->data.customerID);
    std::swap(a->data.product, b->data.product);
    std::swap(a->data.category, b->data.category);
    std::swap(a->data.price, b->data.price);
    std::swap(a->data.day, b->data.day);
    std::swap(a->data.month, b->data.month);
    std::swap(a->data.year, b->data.year);
    std::swap(a->data.paymentMethod, b->data.paymentMethod);
}

// Bubble sort by date
void TransactionList::bubbleSortByDate(long& comparisons, long& swaps) {
    bool swapped;
    for (TransactionNode* i = head; i != nullptr; i = i->next) {
        swapped = false;
        for (TransactionNode* j = head; j != nullptr && j->next != nullptr; j = j->next) {
            comparisons++;
            if (j->data.year > j->next->data.year ||
                (j->data.year == j->next->data.year && j->data.month > j->next->data.month) ||
                (j->data.year == j->next->data.year && j->data.month == j->next->data.month && j->data.day > j->next->data.day)) {
                swap(j, j->next);
                swapped = true;
                swaps++;
            }
        }
        if (!swapped) break;
    }
}

// Insertion sort by date
void TransactionList::insertionSortByDate(long& comparisons, long& swaps) {
    if (head == nullptr) return;  // Return if the list is empty

    // Start from the second node (since the first node is trivially sorted)
    for (TransactionNode* i = head->next; i != nullptr; i = i->next) {
        TransactionNode* key = i;      // The node to be inserted
        TransactionNode* j = i->prev;  // The node before 'key'

        // Move elements that are greater than 'key' to the right
        while (j != nullptr && (j->data.year > key->data.year ||
            (j->data.year == key->data.year && j->data.month > key->data.month) ||
            (j->data.year == key->data.year && j->data.month == key->data.month && j->data.day > key->data.day))) {
            comparisons++;

            // Move the 'j' node one step to the right (adjust pointers)
            j = j->prev;
        }

        // If we found a node to insert before
        if (j != nullptr) {
            // If 'key' is not already in the correct position
            if (key != j->next) {
                // Remove 'key' from its current position
                if (key->next != nullptr) {
                    key->next->prev = key->prev;
                }
                if (key->prev != nullptr) {
                    key->prev->next = key->next;
                }

                // Insert 'key' after 'j'
                key->next = j->next;
                if (j->next != nullptr) {
                    j->next->prev = key;
                }
                j->next = key;
                key->prev = j;

                // If 'key' was at the end of the list, update the tail
                if (key->next == nullptr) {
                    tail = key;
                }

                swaps++;
            }
        }
        else {
            // If 'key' is the smallest element (first in the list)
            if (key != head) {
                // Remove 'key' from its current position
                if (key->next != nullptr) {
                    key->next->prev = key->prev;
                }
                if (key->prev != nullptr) {
                    key->prev->next = key->next;
                }

                // Insert 'key' at the beginning of the list
                key->next = head;
                if (head != nullptr) {  // Check if head isn't null
                    head->prev = key;
                }
                key->prev = nullptr;  // Set 'key's prev pointer to nullptr because it becomes the first node
                head = key;           // Update 'head' to point to the new first node
                swaps++;
            }
        }
    }
}


//------------------- Merge Sort to sort customer transactions by date -------------------


void TransactionList::mergeSortByDate(long& comparisons, long& swaps) {
    head = mergeSort(head, comparisons, swaps);

    // Recalculate tail and update links
    tail = head;
    while (tail && tail->next) {
        tail = tail->next;
    }
}

TransactionNode* TransactionList::mergeSort(TransactionNode* node, long& comparisons, long& swaps) {
    if (!node || !node->next) {
        return node;
    }

    TransactionNode* middle = getMiddle(node);
    TransactionNode* secondHalf = middle->next;
    middle->next = nullptr;
    if (secondHalf) secondHalf->prev = nullptr;

    TransactionNode* left = mergeSort(node, comparisons, swaps);
    TransactionNode* right = mergeSort(secondHalf, comparisons, swaps);

    return mergeSortedLists(left, right, comparisons, swaps);
}

TransactionNode* TransactionList::getMiddle(TransactionNode* head) {
    if (!head) return nullptr;
    TransactionNode* slow = head;
    TransactionNode* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

TransactionNode* TransactionList::mergeSortedLists(TransactionNode* left, TransactionNode* right, long& comparisons, long& swaps) {
    Transaction transaction("", "", "", 0.0, 0, 0, 0, "");
    TransactionNode* dummy = new TransactionNode(transaction);
    TransactionNode* tail = dummy;

    while (left && right) {
        comparisons++;

        bool isLeftEarlier = false;

        if (left->data.year < right->data.year) {
            isLeftEarlier = true;
        }
        else if (left->data.year == right->data.year) {
            if (left->data.month < right->data.month) {
                isLeftEarlier = true;
            }
            else if (left->data.month == right->data.month) {
                if (left->data.day <= right->data.day) {
                    isLeftEarlier = true;
                }
            }
        }

        if (isLeftEarlier) {
            tail->next = left;
            left->prev = tail;
            left = left->next;
        }
        else {
            tail->next = right;
            right->prev = tail;
            right = right->next;
        }

        swaps++;
        tail = tail->next;
    }

    if (left) {
        tail->next = left;
        left->prev = tail;
    }
    else if (right) {
        tail->next = right;
        right->prev = tail;
    }

    TransactionNode* sortedHead = dummy->next;
    if (sortedHead) sortedHead->prev = nullptr;

    delete dummy;
    return sortedHead;
}


//------------------- Merge Sort to sort customer transactions by date -------------------



// Linear search by category and payment
int TransactionList::linearSearchByCategoryAndPayment(const std::string& category,
                                                      const std::string& payment,
                                                      long& steps, int& total) {
    steps = 0;
    total = 0;
    TransactionNode* current = head;
    while (current != nullptr) {
        steps++;
        if (current->data.category == category && current->data.paymentMethod == payment) {
            total++;
        }
        current = current->next;
    }
    return total;
}

// Filter search for electronics and credit card
int TransactionList::countByCategory(const std::string& category, long& steps, int& total) {
    steps = 0;
    total = 0;
    TransactionNode* current = head;
    while (current != nullptr) {
        steps++;
        if (current->data.category == category) {
            total++;
        }
        current = current->next;
    }
    return total;
}

int TransactionList::filterSearchElectronicsCreditCard(long& steps, int& total) {
    return linearSearchByCategoryAndPayment("Electronics", "Credit Card", steps, total);
}

// Binary search by date
TransactionNode* TransactionList::binarySearchByDate(int day, int month, int year, long& steps) {
    TransactionNode* current = head;
    int low = 0, high = size - 1;
    steps = 0;

    while (low <= high) {
        int mid = (low + high) / 2;
        current = head;
        for (int i = 0; i < mid; ++i) {
            current = current->next;
        }

        if (current->data.day == day && current->data.month == month && current->data.year == year) {
            return current;
        }
        else if (current->data.year < year || (current->data.year == year && current->data.month < month) ||
                 (current->data.year == year && current->data.month == month && current->data.day < day)) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
        steps++;
    }

    return nullptr;
}

void TransactionList::printAll() const {
    if (!head) {
        std::cout << "No transactions to display.\n";
        return;
    }

    TransactionNode* current = head;
    std::cout << "\n Transactions Sorted by Date:\n";
    std::cout << "---------------------------------------------------------\n";

    while (current) {
        // Format the date as day/month/year
        std::cout << current->data.day << "/" << current->data.month << "/" << current->data.year << " | "
            << current->data.category << " | "
            << current->data.paymentMethod << " | RM"
            << current->data.price << std::endl;
        current = current->next;
    }

    std::cout << "---------------------------------------------------------\n";
}

