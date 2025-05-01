#include "transaction_list.hpp"
#include "transaction.hpp"
#include "review_list.hpp"
#include "review.hpp"
#include <iostream>
#include <string>
#include <chrono>  // For performance timing

// Available categories and payment methods
const std::string categories[] = { "Electronics", "Sports", "Groceries", "Furniture", "Fashion", "Books", "Toys", "Home Appliances", "Automotive", "Beauty" };
const std::string paymentMethods[] = { "Bank Transfer", "PayPal", "Credit Card", "Cash on Delivery", "Debit Card" };

// Function to display categories and payment methods for user input
static void displayCategories() {
    std::cout << "Available Categories: \n";
    for (size_t i = 0; i < sizeof(categories) / sizeof(categories[0]); ++i) {
        std::cout << (i + 1) << ". " << categories[i] << std::endl;
    }
}

static void displayPaymentMethods() {
    std::cout << "Available Payment Methods: \n";
    for (size_t i = 0; i < sizeof(paymentMethods) / sizeof(paymentMethods[0]); ++i) {
        std::cout << (i + 1) << ". " << paymentMethods[i] << std::endl;
    }
    std::cout << std::endl;
}

using namespace std;

int main() {

    //Transaction List Question
    TransactionList transactionList;
    if (!transactionList.loadFromCSV("transactions_cleaned_version.csv")) {
        std::cerr << "Failed to load CSV file." << std::endl;
        return 1;
    }
    std::cout << "Total transactions: " << transactionList.getSize() << std::endl;
    long comparisons = 0, swaps = 0, steps = 0;
    
    // --------- BUBBLE SORT ---------
    //transactionList = TransactionList();
    //transactionList.loadFromCSV("transactions_cleaned_version.csv");
    //transactionList.printAll(); 
    //auto start = std::chrono::high_resolution_clock::now();
    //transactionList.bubbleSortByDate(comparisons, swaps);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::cout << "Bubble Sort by Date:\n";
    //std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n";
    //std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    //std::cout << endl << endl << endl << endl << endl << endl;
    //transactionList.printAll();

    // --------- INSERTION SORT ---------
    //comparisons = swaps = 0;
    //transactionList = TransactionList();
    //transactionList.loadFromCSV("transactions_cleaned_version.csv");
    //transactionList.printAll();
    //auto start = std::chrono::high_resolution_clock::now();
    //transactionList.insertionSortByDate(comparisons, swaps);
    //auto end = std::chrono::high_resolution_clock::now();
    //std::cout << "Insertion Sort by Date:\n";
    //std::cout << "Comparisons: " << comparisons << ", Swaps: " << swaps << "\n";
    //std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    //std::cout << endl << endl << endl << endl << endl << endl;
    //transactionList.printAll();

    // --------- MERGE SORT ---------
    //comparisons = swaps = 0;
    //transactionList = TransactionList();
    //transactionList.loadFromCSV("transactions_cleaned_version.csv");
    //transactionList.printAll();
    //auto start = std::chrono::high_resolution_clock::now();
    //transactionList.mergeSortByDate(comparisons, swaps);  // Make sure this method accepts &updates metrics
    //auto end = std::chrono::high_resolution_clock::now();
    //std::cout << "Merge Sort by Date:\n";
    //std::cout << "Comparisons: " << comparisons << ", Swaps (recursive merges): " << swaps << "\n";
    //std::cout << "Time taken: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms\n";
    //std::cout << endl << endl << endl << endl << endl << endl;
    //transactionList.printAll();

    // ENDS HERE

    //Question 2 - What's the percentage of credit card use. // need fixes accept input //transaction_lists.
    //long stepsFilter = 0, stepsTotal = 0;
    //int totalFiltered = 0, totalElectronics = 0;
    //// Count "Electronics" + "Credit Card"
    //transactionList.filterSearchElectronicsCreditCard(stepsFilter, totalFiltered);
    //// Count all "Electronics"
    //transactionList.countByCategory("Electronics", stepsTotal, totalElectronics);
    //// Calculate percentage
    //double percentage = 0.0;
    //if (totalElectronics > 0) {
    //    percentage = (static_cast<double>(totalFiltered) / totalElectronics) * 100.0;
    //}
    //// Output results
    //std::cout << "Total Electronics transactions: " << totalElectronics << " (steps: " << stepsTotal << ")\n";
    //std::cout << "Electronics + Credit Card transactions: " << totalFiltered << " (steps: " << stepsFilter << ")\n";
    //std::cout << std::fixed << std::setprecision(2);
    //std::cout << "Percentage of Electronics purchases made with Credit Card: " << percentage << "%\n";

    // Question 2.1
    //std::string category;
    //std::string payment;
    //long stepsFilter = 0, stepsTotal = 0;
    //int totalFiltered = 0, totalCategory = 0;
    //// Display options and get user input for category
    //displayCategories();
    //std::cout << "Enter category number to filter by (1-" << sizeof(categories) / sizeof(categories[0]) << "): ";
    //int categoryChoice;
    //std::cin >> categoryChoice;
    //std::cin.ignore();  // Ignore the newline character left in the buffer
    //// Validate and set category based on user choice
    //if (categoryChoice >= 1 && categoryChoice <= sizeof(categories) / sizeof(categories[0])) {
    //    category = categories[categoryChoice - 1];  // Select category based on user input
    //}
    //else {
    //    std::cout << "Invalid category choice! Exiting...\n";
    //    return 1;
    //}
    //// Display options and get user input for payment method
    //displayPaymentMethods();
    //std::cout << "Enter payment method number to filter by (1-" << sizeof(paymentMethods) / sizeof(paymentMethods[0]) << "): ";
    //int paymentChoice;
    //std::cin >> paymentChoice;
    //std::cin.ignore();  // Ignore the newline character left in the buffer
    //// Validate and set payment method based on user choice
    //if (paymentChoice >= 1 && paymentChoice <= sizeof(paymentMethods) / sizeof(paymentMethods[0])) {
    //    payment = paymentMethods[paymentChoice - 1];  // Select payment method based on user input
    //}
    //else {
    //    std::cout << "Invalid payment method choice! Exiting...\n";
    //    return 1;
    //}
    //// Perform linear search by category and payment method
    //transactionList.linearSearchByCategoryAndPayment(category, payment, stepsFilter, totalFiltered);
    //std::cout << "Total transactions in category '" << category << "' with payment method '" << payment << "': " << totalFiltered << std::endl;
    //std::cout << "Steps taken during search: " << stepsFilter << std::endl;
    //// Perform count by selected category
    //transactionList.countByCategory(category, stepsTotal, totalCategory);
    //// Calculate the percentage
    //double percentage = 0.0;
    //if (totalCategory > 0) {
    //    percentage = (static_cast<double>(totalFiltered) / totalCategory) * 100.0;
    //}
    //std::cout << "\nResults for Category: '" << category << "' and Payment Method: '" << payment << "'\n";
    //std::cout << "--------------------------------------------------------------\n";
    //std::cout << "Total transactions in category '" << category << "': " << totalCategory << std::endl;
    //std::cout << category << " + " << payment << " transactions: " << totalFiltered << std::endl;
    //std::cout << "Percentage of " << category << " purchases made with " << payment << ": " << std::fixed << std::setprecision(2) << percentage << "%\n";
    //std::cout << "--------------------------------------------------------------\n";


    //Review List Question

    //Question 3
    ReviewList reviewList;
    reviewList.loadFromCSV("reviews_cleaned_version.csv");  // Load data from CSV
    reviewList.displayAll();
    reviewList.processOneStarReviews();

    return 0;
}
