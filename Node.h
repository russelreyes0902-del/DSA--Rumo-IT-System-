#pragma once
#include <string>

struct Data {
    std::string menuItem;
    std::string modeOfPayment;
    std::string date;
    double totalPrice;
    double amount;
    double unitPrice;
};

struct Node {
    Data data;
    Node* next;
    Node* prev;

    Node(string mI, string mO, string d, double tP, double a, double uP) {
        data = {mI, mO, d, tP, a, uP};
        next = nullptr;
        prev = nullptr;
    }
};

typedef Node* NodePtr;