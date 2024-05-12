#include <iostream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <algorithm> // Needed for transform function

using namespace std;

// Define cryptocurrency data structure
struct Cryptocurrency {
    string name;
    string symbol;
    double price;
};

// Sample cryptocurrency data (for demonstration purposes)
unordered_map<string, Cryptocurrency> cryptocurrencyData = {
    {"Bitcoin", {"Bitcoin", "X", 50000.0}},
    {"Ethereum", {"Ethereum", "Y", 3000.0}},
    {"Litecoin", {"Litecoin", "Z", 150.0}}
};

// Define user data structure
struct User {
    string username;
    string password;
    double balance;
    unordered_map<string, double> portfolio; // Cryptocurrency symbol -> Quantity
};

// Define a simple database to store user data
unordered_map<string, User> userDatabase;

const double WALLET_LIMIT = 100000.0;

// Function to register a new user
void registerUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username already exists
    if (userDatabase.find(username) != userDatabase.end()) {
        cout << "Username already exists. Please choose a different username.\n";
        return;
    }

    cout << "Enter password: ";
    cin >> password;

    // Create a new user and add to the database
    User newUser;
    newUser.username = username;
    newUser.password = password;
    newUser.balance = WALLET_LIMIT; // Initial balance for new users
    userDatabase[username] = newUser;

    cout << "Registration successful. Welcome, " << username << "!\n";
}

// Function to authenticate a user
bool authenticateUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;

    // Check if the username exists in the database
    if (userDatabase.find(username) == userDatabase.end()) {
        cout << "User not found. Please register or verify your username.\n";
        return false;
    }

    cout << "Enter password: ";
    cin >> password;

    // Check if the password matches
    if (userDatabase[username].password != password) {
        cout << "Incorrect password. Please try again.\n";
        return false;
    }

    return true; // Authentication successful
}

// Function to display cryptocurrency prices
void displayCryptocurrencyPrices() {
    cout << "Current Cryptocurrency Prices:\n";
    cout << setw(15) << "Symbol" << setw(15) << "Name" << setw(15) << "Price (USD)" << endl;
    for (auto &[symbol, cryptocurrency] : cryptocurrencyData) {
        // Randomly fluctuate cryptocurrency prices
        double fluctuation = ((rand() % 2001) - 1000) / 100.0; // Random fluctuation between -10.00% and +10.00%
        cryptocurrency.price += cryptocurrency.price * (fluctuation / 100.0);

        cout << setw(15) << cryptocurrency.symbol << setw(15) << cryptocurrency.name << setw(15) << fixed << setprecision(2) << cryptocurrency.price << endl;
    }
}

// Function to buy cryptocurrency
// Function to buy cryptocurrency
// Function to buy cryptocurrency
void buyCryptocurrency(string username) {
    string symbol;
    double quantity;
    cout << "Enter the symbol of the cryptocurrency you want to buy (X, Y, or Z): ";
    cin >> symbol;

    // Convert symbol to uppercase
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    // Check if the cryptocurrency symbol is valid
    if (symbol != "X" && symbol != "Y" && symbol != "Z") {
        cout << "Invalid cryptocurrency symbol. Please choose a valid symbol.\n";
        return;
    }

    cout << "Enter the quantity to buy: ";
    cin >> quantity;

    // Check if the quantity is valid
    if (quantity <= 0) {
        cout << "Invalid quantity. Please enter a positive value.\n";
        return;
    }

    // Check if the user has sufficient balance
    double totalCost = quantity * cryptocurrencyData[symbol].price;
    if (userDatabase[username].balance - totalCost < 0) {
        cout << "Insufficient balance. Please add funds to your account.\n";
        return;
    }

    // Deduct the total cost from the user's balance
    userDatabase[username].balance -= totalCost;

    // Update the user's cryptocurrency portfolio
    userDatabase[username].portfolio[symbol] += quantity;

    cout << "Successfully bought " << quantity << " " << symbol << " for $" << totalCost << ".\n";
}


// Function to sell cryptocurrency
void sellCryptocurrency(string username) {
    string symbol;
    double quantity;
    cout << "Enter the symbol of the cryptocurrency you want to sell (X, Y, or Z): ";
    cin >> symbol;

    // Convert symbol to uppercase
    transform(symbol.begin(), symbol.end(), symbol.begin(), ::toupper);

    // Check if the cryptocurrency symbol is valid
    if (symbol != "X" && symbol != "Y" && symbol != "Z") {
        cout << "Invalid cryptocurrency symbol. Please choose a valid symbol.\n";
        return;
    }

    cout << "Enter the quantity to sell: ";
    cin >> quantity;

    // Check if the user has sufficient quantity to sell
    if (quantity <= 0 || userDatabase[username].portfolio[symbol] < quantity) {
        cout << "Invalid quantity or insufficient balance. Please try again.\n";
        return;
    }

    // Update the user's balance and portfolio
    double totalGain = quantity * cryptocurrencyData[symbol].price;
    userDatabase[username].balance += totalGain;
    userDatabase[username].portfolio[symbol] -= quantity;

    cout << "Successfully sold " << quantity << " " << symbol << " for $" << totalGain << ".\n";
}

// Function to display user's portfolio
void displayPortfolio(string username) {
    cout << "Portfolio for user: " << username << endl;
    cout << "Balance: $" << userDatabase[username].balance << endl;
    cout << "Cryptocurrency Holdings:\n";
    for (auto &[symbol, quantity] : userDatabase[username].portfolio) {
        cout << symbol << ": " << quantity << endl;
    }
}

// Function to check profit/loss
void checkProfitLoss(string username) {
    double totalInvestment = 0.0;
    double currentPortfolioValue = 0.0;

    // Calculate total investment
    for (auto &[symbol, quantity] : userDatabase[username].portfolio) {
        totalInvestment += quantity * cryptocurrencyData[symbol].price;
    }

    // Calculate current portfolio value
    for (auto &[symbol, quantity] : userDatabase[username].portfolio) {
        currentPortfolioValue += quantity * cryptocurrencyData[symbol].price;
    }

    double profitLoss = currentPortfolioValue - totalInvestment;

    cout << "Total Investment: $" << totalInvestment << endl;
    cout << "Portfolio Value: $" << currentPortfolioValue << endl;
    cout << "Profit/Loss: $" << profitLoss << endl;
}

int main() {
    srand(time(0)); // Seed random number generator

    while (true) {
        int choice;
        cout << "\nWelcome to Cryptocurrency Simulator\n";
        cout << "1. Sign Up\n";
        cout << "2. Sign In\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                if (authenticateUser()) {
                    cout << "Authentication successful.\n";
                    while (true) {
                        cout << "\nCryptocurrency Simulator Menu\n";
                        cout << "1. Display Cryptocurrency Prices\n";
                        cout << "2. Buy Cryptocurrency\n";
                        cout << "3. Sell Cryptocurrency\n";
                        cout << "4. Check Profit/Loss\n";
                        cout << "5. Display Portfolio\n";
                        cout << "6. Sign Out\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice) {
                            case 1:
                                displayCryptocurrencyPrices();
                                break;
                            case 2:
                                buyCryptocurrency(userDatabase["username"].username); // Replace "username" with authenticated user's username
                                break;
                            case 3:
                                sellCryptocurrency(userDatabase["username"].username); // Replace "username" with authenticated user's username
                                break;
                            case 4:
                                checkProfitLoss(userDatabase["username"].username); // Replace "username" with authenticated user's username
                                break;
                            case 5:
                                displayPortfolio(userDatabase["username"].username); // Replace "username" with authenticated user's username
                                break;
                            case 6:
                                cout << "Signing out.\n";
                                break;
                            default:
                                cout << "Invalid choice. Please try again.\n";
                        }

                        if (choice == 6) {
                            break; // Exit the inner loop (menu)
                        }
                    }
                }
                break;
            case 3:
                cout << "Exiting program. Goodbye!\n";
                return 0;
            default:
                cout << "Thanks for using Cryptocurrency.\n";
        }
    }

    return 0;
}
