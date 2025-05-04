#include <iostream>
#include <fstream>
#include <sstream>
#include "transaction.hpp"
#include "review.hpp"

using namespace std;

// Helper function to check if a string is a valid positive integer
static bool isValidInteger(string s)
{
    if (s.empty()) return false;
    for (char c : s) {
        if (!isdigit(c)) return false;
    }
    return true;
}

// Helper to check if price is a valid float
static bool isValidFloat(const string& s)
{
    if (s.empty()) return false;
    bool decimalFound = false;
    for (char c : s) {
        if (c == '.') {
            if (decimalFound) return false;
            decimalFound = true;
        }
        else if (!isdigit(c)) {
            return false;
        }
    }
    return true;
}

// Helper to validate date format: dd/mm/yyyy
static bool isValidDateFormat(const string& date)
{
    if (date.length() != 10) return false;
    return isdigit(date[0]) && isdigit(date[1]) &&
        date[2] == '/' &&
        isdigit(date[3]) && isdigit(date[4]) &&
        date[5] == '/' &&
        isdigit(date[6]) && isdigit(date[7]) &&
        isdigit(date[8]) && isdigit(date[9]);
}

static void cleaning_transaction(const string& file_path) {
    ifstream input(file_path);
    if (!input.is_open()) {
        cout << "File not found. Please make sure transactions.csv is in the same directory." << endl;
        return;
    }

    string line;
    getline(input, line); // Skip header

    int capacity = 10;
    int size = 0;
    Transaction* transactions = new Transaction[capacity];

    while (getline(input, line)) {
        stringstream ss(line);
        string customer_id, product, category, price_str, date_str, payment_method;

        getline(ss, customer_id, ',');
        getline(ss, product, ',');
        getline(ss, category, ',');
        getline(ss, price_str, ',');
        getline(ss, date_str, ',');
        getline(ss, payment_method);

        if (customer_id.empty() || product.empty() || category.empty() ||
            price_str.empty() || date_str.empty() || payment_method.empty())
            continue;

        if (!isValidFloat(price_str) || !isValidDateFormat(date_str))
            continue;

        double price = stod(price_str);
        Transaction temp(customer_id, product, category, price, 0, 0, 0, payment_method);
        temp.parseDate(date_str);

        if (size == capacity) {
            capacity *= 2;
            Transaction* newArray = new Transaction[capacity];
            for (int i = 0; i < size; ++i)
                newArray[i] = transactions[i];
            delete[] transactions;
            transactions = newArray;
        }

        transactions[size++] = temp;
    }

    input.close();
    cout << "Stored " << size << " valid transactions." << endl;

    ofstream output("transactions_cleaned_version.csv");
    if (!output.is_open()) {
        cout << "Error creating cleaned file." << endl;
        delete[] transactions;
        return;
    }

    output << "Customer ID,Product,Category,Price,Date,Payment Method\n";
    for (int i = 0; i < size; ++i) {
        output << transactions[i].customerID << ","
            << transactions[i].product << ","
            << transactions[i].category << ","
            << transactions[i].price << ","
            << transactions[i].getDateString() << ","
            << transactions[i].paymentMethod << "\n";
    }

    output.close();
    delete[] transactions;
    cout << "Saved cleaned data to 'transactions_cleaned_version.csv'" << endl;
}

static void cleaning_review(const string& file_path) {
    ifstream input(file_path);
    if (!input.is_open()) {
        cout << "Error: Unable to open file '" << file_path << "'. Please check the path." << endl;
        return;
    }

    string line;
    getline(input, line); // Skip header

    int capacity = 10;
    int size = 0;
    Review* reviews = new Review[capacity];

    while (getline(input, line)) {
        stringstream ss(line);
        string product_id, customer_id, rating_str, review_text;

        getline(ss, product_id, ',');
        getline(ss, customer_id, ',');
        getline(ss, rating_str, ',');
        getline(ss, review_text);

        if (product_id.empty() || customer_id.empty() || rating_str.empty() || review_text.empty())
            continue;

        if (!isValidInteger(rating_str))
            continue;

        int rating = stoi(rating_str);
        Review temp(customer_id, product_id, review_text, rating);

        if (size == capacity) {
            capacity *= 2;
            Review* newArray = new Review[capacity];
            for (int i = 0; i < size; ++i)
                newArray[i] = reviews[i];
            delete[] reviews;
            reviews = newArray;
        }

        reviews[size++] = temp;
    }

    input.close();
    cout << "Stored " << size << " valid reviews." << endl;

    ofstream output("reviews_cleaned_version.csv");
    if (!output.is_open()) {
        cout << "Error: Failed to create output file." << endl;
        delete[] reviews;
        return;
    }

    output << "Product ID,Customer ID,Rating,Review Text\n";
    for (int i = 0; i < size; ++i) {
        output << reviews[i].productID << ","
            << reviews[i].customerID << ","
            << reviews[i].rating << ","
            << reviews[i].reviewText << "\n";
    }

    output.close();
    delete[] reviews;
    cout << "Saved cleaned data to 'reviews_cleaned_version.csv'" << endl;
}

//int main()
//{
//    cleaning_transaction("C:\\Users\\User\\Desktop\\DST_Cleaning\\uncleaned_file\\transactions.csv");
//    cleaning_review("C:\\Users\\User\\Desktop\\DST_Cleaning\\uncleaned_file\\reviews.csv");
//}