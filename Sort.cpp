#include <iostream>
#include "Search.h"
#include "Node.h"
#include "Sort.h"
using namespace std;


void swapNode(NodePtr node1, NodePtr node2){ // swapNode function
    if (!node1 || !node2 || node1 == node2) return; // Checks if node1 or node2 is a nullptr or if node1 is equal to node2

    Data temp = node1->data;
    node1->data = node2->data;
    node2->data = temp;
}