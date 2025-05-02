#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

struct TransactionCleaning
{
    string customer_id;
    string product;
    string category;
    float price;
    string date;
    string payment_method;
};

struct ReviewCleaning
{
    string product_id;
    string customer_id;
    int rating;
    string review_text;
};

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

static void cleaning_transaction(string file_path)
{
    ifstream input(file_path);
    if (!input.is_open()) {
        cout << "File not found. Please make sure transactions.csv is in the same directory." << endl;
        return;
    }

    string line;
    getline(input, line); // Skip header

    int capacity = 10;
    int size = 0;
    TransactionCleaning* transactions = new TransactionCleaning[capacity];

    while (getline(input, line)) {
        stringstream ss(line);
        string customer_id, product, category, price_str, date, payment_method;

        getline(ss, customer_id, ',');
        getline(ss, product, ',');
        getline(ss, category, ',');
        getline(ss, price_str, ',');
        getline(ss, date, ',');
        getline(ss, payment_method);

        if (customer_id.empty() || product.empty() || category.empty() ||
            price_str.empty() || date.empty() || payment_method.empty())
            continue;

        if (!isValidFloat(price_str) || !isValidDateFormat(date))
            continue;

        float price = stof(price_str);

        if (size == capacity) {
            capacity *= 2;
            TransactionCleaning* newArray = new TransactionCleaning[capacity];
            for (int i = 0; i < size; i++)
                newArray[i] = transactions[i];
            delete[] transactions;
            transactions = newArray;
        }

        transactions[size++] = { customer_id, product, category, price, date, payment_method };
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
    for (int i = 0; i < size; i++) {
        output << transactions[i].customer_id << ","
            << transactions[i].product << ","
            << transactions[i].category << ","
            << transactions[i].price << ","
            << transactions[i].date << ","
            << transactions[i].payment_method << "\n";
    }

    output.close();
    delete[] transactions;
    cout << "Saved cleaned data to 'transactions_cleaned_version.csv'" << endl;
}

static void cleaning_review(string file_path)
{
    //open file using this one
    ifstream myReviewFile;
    myReviewFile.open(file_path);
    if (!myReviewFile.is_open())
    {
        cout << "There is error locating the file, please make it inside your directory ya";
        return; //this one to indicate there is error if no error return 0
    }

    //define the column here first
    string line = "", product_id = "", customer_id = "", review_text = "", rating_str = ""; //the rating str to obtain string , because the csv file got string
    int rating = 0;
    int location = 0;

    // Manual dynamic array setup ,
    int capacity = 10;
    int size = 0;
    ReviewCleaning* reviews = new ReviewCleaning[capacity]; //for dynamic array

    //this one to skip the column name
    getline(myReviewFile, line);

    while (getline(myReviewFile, line))
    {
        //Here is where u read the line by finding comma ya
        stringstream ss(line);
        getline(ss, product_id, ',');
        getline(ss, customer_id, ',');
        getline(ss, rating_str, ',');
        getline(ss, review_text); // last field


        //data cleaning happen here
        if (product_id.empty() || customer_id.empty() || rating_str.empty() || review_text.empty())
            continue;
        if (!isValidInteger(rating_str))
            continue;

        //if no issue need to convert the string rating to int for storing
        rating = stoi(rating_str);

        // Resize array if needed
        if (size == capacity)
        {
            capacity *= 2;
            ReviewCleaning* newArray = new ReviewCleaning[capacity];
            for (int i = 0; i < size; i++)
                newArray[i] = reviews[i];
            delete[] reviews;
            reviews = newArray;
        }

        // Store valid review
        reviews[size++] = { product_id, customer_id, rating, review_text };

    }

    myReviewFile.close();
    cout << "Done storing " << size << " valid reviews." << endl;

    // Save to new CSV
    ofstream outFile("reviews_cleaned_version.csv");
    if (!outFile.is_open()) {
        cout << "Error creating output file." << endl;
        delete[] reviews;
        return;
    }

    // Write the header , since i don't have it in my array
    outFile << "Product ID,Customer ID,Rating,Review Text\n";

    // Write the data
    for (int i = 0; i < size; i++) {
        outFile << reviews[i].product_id << ","
            << reviews[i].customer_id << ","
            << reviews[i].rating << ","
            << reviews[i].review_text << "\n";
    }

    outFile.close();
    delete[] reviews;
    cout << "Successfully saved cleaned reviews to 'reviews_cleaned_version.csv'" << endl;
}

//int main()
//{
//    cleaning_transaction("C:\\Users\\User\\Desktop\\DST_Cleaning\\uncleaned_file\\transactions.csv");
//    cleaning_review("C:\\Users\\User\\Desktop\\DST_Cleaning\\uncleaned_file\\reviews.csv");
//}