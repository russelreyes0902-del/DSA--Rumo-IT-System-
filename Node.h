#pragma once
#include <string>

struct SalesData { // Groups the data into a single data struct to efficiently sort them all together for a better optimized swap function.
    std::string menuItem;
    std::string typeOfDiscount;
    std::string modeOfPayment;
    std::string date;
    double totalPrice;
    double amount;
    double unitPrice;
    int referenceID;
    int transactionID;
    bool isDiscounted;
};

struct Node {
    SalesData salesData;
    int count;
    Node* next;
    Node* prev;

    Node(std::string mI, std::string mO, std::string tOD, std::string d, double tP, double a, double uP, int rID, int tID, bool iD, int c) {
        salesData = {mI, mO, tOD, d, tP, a, uP, rID, tID, iD};
        count = c;
        next = nullptr;
        prev = nullptr;
    }
};

typedef Node* CafeNode; // Renamed the datatype Node* to CafeNode