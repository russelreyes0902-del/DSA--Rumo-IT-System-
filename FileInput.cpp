#include <fstream> //handles both input and output file streams
#include <sstream> 
#include <iostream>
#include <iomanip>
#include "FileInput.h"
#include "AuditList.h"

//function for missing values 
std:: string cleanMissingValue(const std:: string &input, const std:: string &defaultValue = "-"){
    if (input.empty() || input == "N/A" || input == "None"){
        return defaultValue;
    }
    return input;
}

//function to convert text to double 
double convertToDouble(const std:: string &str) {
    if (str.empty())
        return 0.0;
   try {
        return std:: stod(str);
    } catch (...) {
        return 0.0;
    }
}

//function to convert text to int 
int convertToInt(const std:: string &str, int defaultValue = 0){
    if (str.empty())
        return defaultValue;
    try {
        return std:: stoi(str);
    } catch (...) {
        return defaultValue;
    }
}

//function to convert text to long long
long long convertToLongLong(const std:: string &str, long long defaultValue = 0){
    if (str.empty())
        return defaultValue;
    try {
        return std:: stoll(str);
    } catch (...) {
        return defaultValue;
    }
}

void loadAuditData(const std:: string &filename, CafeNode &head, int maxRecords) {
    std:: ifstream iFile(filename);
    // iFile.open(filename);

    if (!iFile.is_open()) 
    return;

    std:: string line;
    std:: getline(iFile, line); //skips header

    int recordCount = 0; //initialize record count
    CafeNode tail = nullptr;

    while (std:: getline(iFile, line) && (maxRecords == 0 || recordCount < maxRecords)){
        if (line.empty()) continue; 
        //skip the lines that are empty

        std:: istringstream ss(line); //string to break down the line 
        std:: string date, menuItemID, menuCategory, menuItem, tempOfDrink, sizeOfItem, quantityStr, modeOfPayment;
        std:: string unitPriceStr, totalPriceStr, typeOfDiscount, discountedPriceStr, discountedPercentageStr, referenceIDStr, transactionIDStr;
        
        //must match audit data csv
        std::getline(ss, date, ',');
        std::getline(ss, menuItemID, ',');
        std::getline(ss, menuCategory, ',');
        std::getline(ss, menuItem, ',');
        std::getline(ss, tempOfDrink, ',');
        std::getline(ss, sizeOfItem, ',');
        std::getline(ss, quantityStr, ',');
        std::getline(ss, modeOfPayment, ',');
        std::getline(ss, unitPriceStr, ',');
        std::getline(ss, totalPriceStr, ',');
        std::getline(ss, typeOfDiscount, ',');
        std::getline(ss, discountedPriceStr, ',');
        std::getline(ss, discountedPercentageStr, ',');
        std::getline(ss, referenceIDStr, ',');
        std::getline(ss, transactionIDStr, ',');

        tempOfDrink = cleanMissingValue(tempOfDrink, "N/A");
        sizeOfItem = cleanMissingValue(sizeOfItem, "N/A");
        typeOfDiscount = cleanMissingValue(typeOfDiscount, "N/A");
        bool isDiscounted = (typeOfDiscount != "N/A");

        double totalPrice = convertToDouble(totalPriceStr);
        double unitPrice = convertToDouble(unitPriceStr);
        int quantity = convertToInt(quantityStr, 1);
        long long referenceID = referenceIDStr.empty() ? 0 : convertToLongLong(referenceIDStr);
        int transactionID = transactionIDStr.empty() ? 0 :convertToInt(transactionIDStr);
        double discountedPrice = isDiscounted ? convertToDouble(discountedPriceStr) : 0.0;
        double discountedPercentage = isDiscounted ? convertToDouble(discountedPercentageStr) : 0.0;
    
        CafeNode newNode = new Node(
            menuItem, tempOfDrink, sizeOfItem, typeOfDiscount,
            modeOfPayment, date, totalPrice, unitPrice, quantity,
            referenceID, transactionID, discountedPrice,
            discountedPercentage, isDiscounted, recordCount + 1
        );

        if (head == nullptr) {
            head = newNode;
            tail = newNode;
        } 
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        recordCount++;
    }

    iFile.close();
}

void loadMenuData(const std:: string &filename) {
    std:: ifstream iFile(filename);
    //iFile.open(filename);

    if (!iFile.is_open()) return;

    std:: string line;
    std:: getline(iFile, line);

    //reads the menu data line by line until the end
    while (std:: getline(iFile, line)){ 
    }
    iFile.close();
}

void printMenu(const std::string &filename) {
    std::ifstream iFile(filename);

    if (!iFile.is_open()) {
        std::cout << "\nError: Could not open menu file \"" << filename << "\".\n";
        std::cout << "Press Enter to return...";
        std::cin.get();
        return;
    }

    std::string line;
    std::getline(iFile, line); // Skip header: menuItemID,menuCategory,menuItem,totalPrice,drinkOfTemp,sizeOfItem

    clearScreen();

    std::cout << "\n=========================================================================================\n";
    std::cout << "                                RUMO-IT SYSTEM - MENU                                    \n";
    std::cout << "=========================================================================================\n";
    std::cout << std::left << std::setw(8)  << "ID" 
              << std::setw(15) << "Category" 
              << std::setw(30) << "Menu Item" 
              << std::setw(12) << "Temp" 
              << std::setw(12) << "Size" 
              << std::right << std::setw(10) << "Price" << "\n";
    std::cout << "-----------------------------------------------------------------------------------------\n";

    int itemCount = 0;
    while (std::getline(iFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string id, category, name, priceStr, temp, size;

        // Parse CSV columns matching menu_data.csv format
        std::getline(ss, id, ',');        // menuItemID
        std::getline(ss, category, ',');  // menuCategory
        std::getline(ss, name, ',');      // menuItem
        std::getline(ss, priceStr, ',');  // totalPrice (Price per unit)
        std::getline(ss, temp, ',');      // drinkOfTemp
        std::getline(ss, size, ',');      // sizeOfItem

        // Clean up empty optional fields for better visual presentation
        if (temp.empty()) temp = "-";
        if (size.empty()) size = "-";

        double price = convertToDouble(priceStr);

        std::cout << std::left << std::setw(8)  << id 
                  << std::setw(15) << category 
                  << std::setw(30) << name 
                  << std::setw(12) << temp 
                  << std::setw(12) << size 
                  << " ₱" << std::right << std::setw(8) << std::fixed << std::setprecision(2) << price << "\n";
        itemCount++;
    }

    iFile.close();

    std::cout << "-----------------------------------------------------------------------------------------\n";
    std::cout << "Total Menu Items Listed: " << itemCount << "\n";
    std::cout << "========================================================================================-\n";
    std::cout << "Press Enter to return to main menu...";
    std::cin.get();
}

