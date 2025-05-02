#include "review_array.hpp"
#include "review.hpp"
#include "transaction_array.hpp"
#include "transaction.hpp"
#include <iostream>
#include <string>
#include <chrono>  // For performance timing


using namespace std;
using namespace std::chrono;

//int main() {
//    //Question 1
//    TransactionArray transactionArray;
//
//    // Load CSV
//    if (!transactionArray.loadFromCSV("transactions_cleaned_version.csv")) {
//        cout << "Failed to load transactions.\n";
//        return 1;
//    }
//    //int comparisonCount = 0;
//    //int swapCount = 0;
//
//    cout << "Total transactions loaded: " << transactionArray.getCount() << "\n";
//    cout << "\nTransactions BEFORE Sorting:\n";
//    transactionArray.display();
//
//    // Prompt user to choose sorting method
//    int choice;
//    cout << "\nChoose sorting method:\n";
//    cout << "1. Quick Sort\n";
//    cout << "2. Merge Sort\n";
//    cout << "Enter choice (1 or 2): ";
//    cin >> choice;
//    if (choice != 1 && choice != 2) {
//        cout << "Invalid choice. Exiting.\n";
//        return 1;
//    }
//    comparisonCount = 0;
//    swapCount = 0;
//    auto start = high_resolution_clock::now();
//    if (choice == 1) {
//        transactionArray.quickSort();
//    }
//    else if (choice == 2) {
//        transactionArray.mergeSort();
//    }
//    auto end = high_resolution_clock::now();
//    cout << "\nTransactions AFTER Sorting by Date:\n";
//    transactionArray.display();
//    string sortName = (choice == 1) ? "Quick Sort" : "Merge Sort";
//    cout << "\n" << sortName << " Comparisons: " << comparisonCount;
//    cout << "\n" << sortName << " Swaps: " << swapCount;
//    cout << "\n" << sortName << " Time: "
//        << duration_cast<milliseconds>(end - start).count() << " ms\n";
//    //Question 2
//    string categories[100];
//    int catCount = 0;
//    transactionArray.getUniqueCategories(categories, catCount);
//    cout << "\nAvailable Categories:\n";
//    for (int i = 0; i < catCount; ++i)
//        cout << i + 1 << ". " << categories[i] << "\n";
//    int catChoice = -1;
//    while (true) {
//        cout << "\nSelect a category (1-" << catCount << "): ";
//        cin >> catChoice;
//        if (cin.fail() || catChoice < 1 || catChoice > catCount) {
//            cout << "Invalid selection. Try again.\n";
//            cin.clear();
//            cin.ignore(10000, '\n');
//        }
//        else {
//            cin.ignore();
//            break;
//        }
//    }
//    string selectedCategory = categories[catChoice - 1];
//    string methods[100];
//    int methodCount = 0;
//    transactionArray.getUniquePaymentMethods(selectedCategory, methods, methodCount);
//    if (methodCount == 0) {
//        cout << "No payment methods found for this category.\n";
//        return 1;
//    }
//    cout << "\nAvailable Payment Methods for '" << selectedCategory << "':\n";
//    for (int i = 0; i < methodCount; ++i)
//        cout << i + 1 << ". " << methods[i] << "\n";
//    int methodChoice = -1;
//    while (true) {
//        cout << "\nSelect a payment method (1-" << methodCount << "): ";
//        cin >> methodChoice;
//        if (cin.fail() || methodChoice < 1 || methodChoice > methodCount) {
//            cout << "Invalid selection. Try again.\n";
//            cin.clear();
//            cin.ignore(10000, '\n');
//        }
//        else {
//            cin.ignore();
//            break;
//        }
//    }
//    string selectedMethod = methods[methodChoice - 1];
//    int categoryCount = 0, methodCountInCategory = 0, stepsTaken = 0;
//    transactionArray.countMatching(selectedCategory, selectedMethod, categoryCount, methodCountInCategory, stepsTaken);
//    double percentage = categoryCount > 0
//        ? (static_cast<double>(methodCountInCategory) / categoryCount) * 100.0
//        : 0.0;
//    cout << "\nResults for Category: '" << selectedCategory << "' and Payment Method: '" << selectedMethod << "'\n";
//    cout << "------------------------------------------------------------\n";
//    cout << "Total transactions in category '" << selectedCategory << "': " << categoryCount << "\n";
//    cout << selectedCategory << " + " << selectedMethod << " transactions: " << methodCountInCategory << "\n";
//    cout << "Percentage of " << selectedCategory << " purchases made with " << selectedMethod
//        << ": " << fixed << setprecision(2) << percentage << "%\n";
//    cout << "Steps taken during search: " << stepsTaken << "\n";
//    cout << "------------------------------------------------------------\n";
//
//    //Question 3
//    //ReviewArray reviewArray;
//    //// Load data from CSV
//    //if (!reviewArray.loadFromCSV("reviews_cleaned_version.csv")) {
//    //    std::cerr << "Failed to load CSV file." << std::endl;
//    //    return 1;
//    //}
//    //std::cout << "Total reviews: " << reviewArray.getSize() << std::endl;
//    //long step = 0, comparison = 0, swap = 0;
//    //int total = 0;
//    //// --------- LINEAR SEARCH ---------
//    //reviewArray.filterSearchOneStarRating(step, total);
//    //reviewArray.displayFilteredOneStarReviews();
//    //std::cout << "Linear Search for 1-Star Ratings:\n";
//    //std::cout << "Steps: " << step << ", Total: " << total << "\n";
//    //std::cout << "---------------------------------------------------------\n";
//    //// --------- PERFORMANCE MEASUREMENTS ---------
//    //auto start1 = std::chrono::high_resolution_clock::now();
//    //reviewArray.extractWordsFromReviews();
//    //auto end1 = std::chrono::high_resolution_clock::now();
//    //auto start2 = std::chrono::high_resolution_clock::now();
//    //reviewArray.bubbleSortWordsByFrequency(comparison, swap);
//    //auto end2 = std::chrono::high_resolution_clock::now();
//    //std::cout << "[Sort Performance Metrics]\n";
//    //std::cout << "Total sort steps (comparisons): " << comparison << " | Total swaps: " << swap << "\n";
//    //std::cout << "Time to extract words: " << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count() << " ms\n";
//    //std::cout << "Time to sort (Bubble Sort): " << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count() << " ms\n";
//    //reviewArray.printTop10WordFrequencies();
//    ////reviewArray.printWordFrequencies();
//
//    return 0;
//}
