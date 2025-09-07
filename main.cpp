#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Function to split a CSV line by a delimeter
std::vector<std::string> splitString(const std::string line, char delimiter
) {
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;

    while (std::getline(ss, token, delimiter )) {
        tokens.push_back(token);
    }
    return tokens;
}

int main()
{
    std::ifstream file("transactions.csv"); //open CSV file
    if (!file.is_open()) {
         std::cout << "Error: Could not open file!" << std::endl;
         return 1;
    }

    std::string line;
    while ( std::getline(file, line)) {
        std::vector<std::string> values = splitString(line, ',');

        // Print each value
        for (size_t i = 0; i < values.size(); i++) {
            std::cout << "" << values[i] << "";
            if (i < values.size() - 1) std::cout << ", ";
        }
        // Print the raw line 
        std::cout << "Line: " << line << std::endl;

        // Parse into fields
        std::stringstream ss(line);
        std::string field;
        int fieldNumber = 1;

        while (std::getline(ss, field, ',')) {
            std::cout << "Field " << fieldNumber << ": '" << field <<
        "'" << std::endl;
            fieldNumber++;
    }

    std::cout << std::endl; // separate rows

    }

    file.close();
    return 0;
}
