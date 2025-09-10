#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// --- Struct for anomaly records ---

struct Anomaly {
    std::string type;
    std::string date;
    std::string description;
    double amount;
};

// Function to split a CSV line by a delimeter
std::vector<std::string> splitString(const std::string &line, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter )) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    std::ifstream file("transactions.csv"); //open CSV file
    if (!file.is_open()) {
         std::cout << "Error: Could not open file!" << std::endl;
         return 1;
    }

    std::string line;
    std::getline(file, line); // skip header row
    
    int transactionCount = 0;
    double totalDebit = 0.0;
    double totalCredit = 0.0;
    std::vector<Anomaly> anomalies;

    // --- Main loop ---
    while (std::getline(file, line)) {
	std::vector<std::string> values = splitString(line, ',');

	if (values.size() >= 5) {
	    std::string date = values[0];
	    std::string description = values[1];
	    std::string debitStr = values[2];
	    std::string creditStr = values[3];
	    std::string balanceStr = values[4];

	    double debit = debitStr.empty() ? 0.0 : std::stod(debitStr);
	    double credit = creditStr.empty() ? 0.0 : std::stod(creditStr);
	    double amount = debit > 0 ? debit : credit;

	    totalDebit += debit;
	    totalCredit += credit;
	    transactionCount++;

	    // --- Anomaly Detection ---
	    if (amount > 5000) {
		anomalies.push_back({"LARGE", date, description, amount});
	    }
	    if (static_cast<long>(amount) % 1000 == 0 && amount != 0.0) {
		anomalies.push_back({"ROUND", date, description, amount});
	    }


	}

    } // <-- closes loop

    file.close();

    //--- Summary Report ---
    std::cout << "\n--- Financial Scrubber Report ---" << std::endl;
    std::cout << "File: transactions.csv" << std::endl;
    std::cout << "Total Transactions: " << transactionCount << std::endl;
    std::cout << "Total Debit: " << totalDebit << std::endl;
    std::cout << "Total Credit: " << totalCredit << std::endl;
    std::cout << "Net Balance: " << (totalCredit - totalDebit) << std::endl;
    // --- Anomaly Report ---
    std::cout << "--- Anomalies Detected ---" << std::endl;
    for (const auto &a : anomalies) {
	    std::cout << "[" << a.type << "] "
		    << a.date << " - " << a.description
		    << ": " << a.amount <<std::endl;
    }

    return 0;

} // <-- closes main



