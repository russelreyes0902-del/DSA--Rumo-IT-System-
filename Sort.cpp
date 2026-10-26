#include <iostream>
#include "Search.h"
#include "Node.h"
#include "Sort.h"
#include "AuditList.h"
using namespace std;


void swapNode(CafeNode &head, CafeNode node1, CafeNode node2){ // swapNode function
    if (!node1 || !node2 || node1 == node2) return; // Checks if node1 or node2 is a nullptr or if node1 is equal to node2

    SalesData temp = node1->salesData;
    node1->salesData = node2->salesData;
    node2->salesData = temp;
}

int parseDate(const string& dateStr) {
    if (dateStr.length() != 10 || dateStr[2] != '-' || dateStr[5] != '-') return 0;
    
    try { // Error handling so that the program doesn't crash.
        string day = dateStr.substr(0, 2);
        string month = dateStr.substr(3, 2);
        string year = dateStr.substr(6, 4);

        return stoi(year + month + day);
    }
    catch (...) {
        return 0;
    }
}

CafeNode partition(CafeNode &head, CafeNode low, CafeNode high, bool ascending) {
    int pivot = high->count;
    CafeNode i = nullptr;

        for (CafeNode j = low; j != high; j = j->next) {
            if ((j->count <= pivot && ascending) || (j->count >= pivot && !ascending)) {
                if (i == nullptr) i = low;
                else i = i->next;
                swapNode(head, i, j);
            }
        }

    if (i == nullptr) i = low;
    else i = i->next;
    swapNode(head, i, high);
    return i;
}

void quickSort(CafeNode &head, CafeNode low, CafeNode high, bool ascending) {
    if (high != nullptr && low != high && low != high->next) {
        CafeNode pivotNode = partition(head, low, high, ascending);
        quickSort(head, low, pivotNode->prev, ascending);
        quickSort(head, pivotNode->next, high, ascending);
    }
}