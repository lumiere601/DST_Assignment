#include "transaction_list.hpp"
#include "transaction.hpp"
#include <iostream>
#include <string>
#include <chrono>  // For performance timing


using namespace std;
int main() {
    cout << "Nyani?";

    TransactionList transactionList;

    if (!transactionList.loadFromCSV("transactions_cleaned_version.csv")) {
        std::cerr << "Failed to load CSV file." << std::endl;
        return 1;
    }

    std::cout << "Total transactions: " << transactionList.getSize() << std::endl;

    long comparisons = 0, swaps = 0, steps = 0;

    //// --------- BUBBLE SORT ---------
    transactionList = TransactionList();
    transactionList.loadFromCSV("transactions_cleaned_version.csv");
    transactionList.displaySortedByDate();
    auto start = std::chrono::high_resolution_clock::now();
    transactionList.bubbleSortByDate(comparisons, swaps);
    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Bubble Sort by Date:\n";
    std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n";
    std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    std::cout << endl << endl << endl << endl << endl << endl;
    transactionList.displaySortedByDate();

    //// --------- INSERTION SORT ---------
    //comparisons = swaps = 0;
    //transactionList = TransactionList();
    //transactionList.loadFromCSV("transactions_cleaned_version.csv");
    //transactionList.displaySortedByDate();
    //auto start = std::chrono::high_resolution_clock::now();
    //transactionList.insertionSortByDate(comparisons, swaps);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::cout << "Insertion Sort by Date:\n";
    //std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n";
    //std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    //std::cout << endl << endl << endl << endl << endl << endl;
    //transactionList.displaySortedByDate();

    //// --------- MERGE SORT ---------
    //comparisons = swaps = 0;
    //transactionList = TransactionList();
    //transactionList.loadFromCSV("transactions_cleaned_version.csv");
    //transactionList.displaySortedByDate();
    //auto start = std::chrono::high_resolution_clock::now();
    //transactionList.mergeSortByDate(comparisons, swaps);  // Make sure this method accepts &updates metrics
    //auto end = std::chrono::high_resolution_clock::now();
    //std::cout << "Merge Sort by Date:\n";
    //std::cout << "Comparisons: " << comparisons << ", Swaps (recursive merges): " << swaps << "\n";
    //std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    //std::cout << endl << endl << endl << endl << endl << endl;
    //transactionList.displaySortedByDate();

    // ENDS HERE
    return 0;
}
