#pragma once
#include <string>

struct SalesData { // Groups the data into a single data struct to efficiently sort them all together for a better optimized swap function.
    std::string menuItem;
    std::string sizeOfItem; // set the string sizeOfItem = "" if the item doesn't have a size.
    std::string typeOfDiscount; // if typeOfDiscount is None, set isDiscounted to false.
    std::string modeOfPayment;
    std::string date;
    double totalPrice; // totalPrice per quantity per modeOfPayment
    int quantity;
    double unitPrice;
    int referenceID; // if modeOfPayment is Cash, set referenceID equal to 0.
    int transactionID;
    int discountedPrice; // set to 0 if isDiscounted is false
    int discountedPercentage; // set to 0 if isDiscounted is false
    bool isDiscounted; 
};

struct Node {
    SalesData salesData;
    int count;
    Node* next;
    Node* prev;

    Node(std::string mI, std::string mO, std::string sOI, 
        std::string tOD, std::string d, double tP, 
        int q, double uP, int rID, 
        int tID, int discountedPrice, int discountedPercentage, 
        bool iD, int c) {
        salesData = {
            mI, mO, sOI, 
            tOD, d, tP, 
            q, uP, rID, 
            tID, discountedPrice, discountedPercentage, 
            iD
        };
        count = c;
        next = nullptr;
        prev = nullptr;
    }
};

typedef Node* CafeNode; // Renamed the datatype Node* to CafeNode