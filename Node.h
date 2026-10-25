#pragma once
#include <string>

struct SalesData { // Groups the data into a single data struct to efficiently sort them all together for a better optimized swap function.
    std::string menuItem;
    std::string modeOfPayment;
    std::string date;
    double totalPrice;
    double amount;
    double unitPrice;
    int count;
};

struct Node {
    SalesData salesData;
    Node* next;
    Node* prev;

    Node(string mI, string mO, string d, double tP, double a, double uP, int c) {
        salesData = {mI, mO, d, tP, a, uP, c};
        next = nullptr;
        prev = nullptr;
    }
};

typedef Node* CafeNode; // Renamed the datatype Node* to CafeNode