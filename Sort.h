#pragma once
#include <string>
#include "Node.h"

enum class AuditFilter {
    ALL,
    BY_PAYMENT_MODE,       // Matches modeOfPayment
    DISCOUNTED_ONLY,       // isDiscounted == true
    MISSING_REF_ID,        // modeOfPayment != "Cash" && referenceID == 0
    DATE_RANGE,            // date within range
    MIN_TOTAL_PRICE        // totalPrice >= threshold
};

enum class SortField {
    COUNT,
    TOTAL_PRICE,
    DATE,
    TRANSACTION_ID,
    QUANTITY
};

bool isDigitChar(char c);

int parseDate(const std::string& dateStr);

void swapNode(
    CafeNode &head, 
    CafeNode node1, 
    CafeNode node2);

bool shouldSwap(
    CafeNode current, 
    CafeNode pivot, 
    SortField sortBy, 
    bool ascending);

// Quicksort functions
CafeNode partition(
    CafeNode &head, 
    CafeNode low, 
    CafeNode high, 
    SortField sortBy, 
    bool ascending);

void quickSort(
    CafeNode &head, 
    CafeNode low, 
    CafeNode high, 
    SortField sortBy,
    bool ascending);

// Filter function (default arguments go here in the header)
CafeNode filterAuditData(
    CafeNode head,
    AuditFilter filterType,
    const std::string& strParam1 = "",
    const std::string& strParam2 = "",
    double numParam = 0.0
);

void promptAndSort(CafeNode &listHead);

void printFilteredPurchase(CafeNode mainHead);