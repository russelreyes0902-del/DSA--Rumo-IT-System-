#include "Node.h"
#include "Search.h"
#include "Sort.h"
#pragma once

CafeNode tail(CafeNode &head) {
    if (head == nullptr) return nullptr;
    CafeNode temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp;
}