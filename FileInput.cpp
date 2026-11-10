#include <fstream> //handles both input and output file streams
#include <sstream> 
#include "FileInput.h"

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

//feel q ang haba masyado sa itaas 

void loadAuditData(const std:: string &filename, CafeNode &head, int maxRecords) {
    std:: ifstream iFile(filename);
    // iFile.open(filename);

    if (!iFile.is_open()) 
    return;

    std:: string line;
    std:: getline(iFile, line); //skips header

    int recordCount = 0; //initialize record count

    while (std:: getline(iFile, line) && (maxRecords == 0 || recordCount < maxRecords)){
        if (line.empty()) continue; 
        //skip the lines that are empty

        std:: istringstream ss(line); //string to break down the line 
        std:: string date, menuItemID, menuCategory, menuItem, tempOfDrink, sizeOfItem, quantityStr, modeOfPayment;
        std:: string unitPriceStr, totalPriceStr, typeOfDiscount, discountedPriceStr, discountedPercentageStr, referenceIDStr, transactionIDStr;
        
        //must match audit data csv
        std:: getline(ss, date, ',');
        std:: getline(ss, menuItemID, ',');
        std:: getline(ss, menuCategory, ',');
        std:: getline(ss, menuItem, ',');
        std:: getline(ss, tempOfDrink, ',');
        std:: getline(ss, sizeOfItem, ',');
        std:: getline(ss, quantityStr, ',');
        std:: getline(ss, modeOfPayment, ',');
        std:: getline(ss, unitPriceStr, ',');
        std:: getline(ss, totalPriceStr, ',');
        std:: getline(ss, typeOfDiscount, ',');
        std:: getline(ss, discountedPriceStr, ',');
        std:: getline(ss, discountedPercentageStr, ',');
        std:: getline(ss, referenceIDStr, ',');
        std:: getline(ss, transactionIDStr, ',');

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
    
    CafeNode newNode = new Node(menuItem, tempOfDrink, sizeOfItem, typeOfDiscount, modeOfPayment, date, totalPrice, unitPrice, quantity, referenceID, transactionID, discountedPrice, discountedPercentage, isDiscounted, recordCount + 1);

    if (head == nullptr) {
        head = newNode;
    } 

    else {
        CafeNode current = head;
        while (current->next != nullptr){
            current = current->next;
        }
        current->next = newNode;
        newNode->prev = current;
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


