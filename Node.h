#include <string>
#pragma once
using namespace std;

struct Node {
    string menuItem;
    string modeOfPayment;
    string date;
    double totalPrice;
    double amount;
    double unitPrice;
    Node* next;
    Node* prev;
    
};