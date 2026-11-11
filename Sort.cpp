#include <iostream>
#include <string>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <cctype>
#include "Node.h"
#include "Sort.h"
#include "AuditList.h"

bool isDigitChar(char c) {
    if (c >= '0' && c <= '9') return true;
    else return false;
}

int parseDate(const std::string& dateStr) {
    if (dateStr.length() != 10) return 0;

    if (dateStr[4] == '-' && dateStr[7] == '-') {
            if (!isDigitChar(dateStr[0]) || !isDigitChar(dateStr[1]) ||
            !isDigitChar(dateStr[2]) || !isDigitChar(dateStr[3]) ||
            !isDigitChar(dateStr[5]) || !isDigitChar(dateStr[6]) ||
            !isDigitChar(dateStr[8]) || !isDigitChar(dateStr[9])) {
            return 0;
        }
        int year = (dateStr[0] - '0') * 1000 + (dateStr[1] - '0') * 100 +
                   (dateStr[2] - '0') * 10 + (dateStr[3] - '0');
        int month = (dateStr[5] - '0') * 10 + (dateStr[6] - '0');
        int day = (dateStr[8] - '0') * 10 + (dateStr[9] - '0');

        return year * 10000 + month * 100 + day;
    }

        else if (dateStr[2] == '-' && dateStr[5] == '-') {
            if (!isDigitChar(dateStr[0]) || !isDigitChar(dateStr[1]) ||
                !isDigitChar(dateStr[3]) || !isDigitChar(dateStr[4]) ||
                !isDigitChar(dateStr[6]) || !isDigitChar(dateStr[7]) ||
                !isDigitChar(dateStr[8]) || !isDigitChar(dateStr[9])) {
            return 0;
        }

        int day = (dateStr[0] - '0') * 10 + (dateStr[1] - '0');
        int month = (dateStr[3] - '0') * 10 + (dateStr[4] - '0');
        int year = (dateStr[6] - '0') * 1000 + (dateStr[7] - '0') * 100 +
                   (dateStr[8] - '0') * 10 + (dateStr[9] - '0');

        return year * 10000 + month * 100 + day;
        }
        else return 0;
}

void swapNode(
    CafeNode &head, 
    CafeNode node1, 
    CafeNode node2
    ) { // swapNode function
    if (!node1 || !node2 || node1 == node2) return; // Checks if node1 or node2 is a nullptr or if node1 is equal to node2

    SalesData temp = node1->salesData;
    node1->salesData = node2->salesData;
    node2->salesData = temp;

    int tempCount = node1->count;
    node1->count = node2->count;
    node2->count = tempCount;
}

bool shouldSwap(
    CafeNode current,
    CafeNode pivot,
    SortField sortBy,
    bool ascending) {

    if (sortBy == SortField::COUNT) {
        return ascending ? (current->count <= pivot->count)
                         : (current->count >= pivot->count);
    }
    else if (sortBy == SortField::TOTAL_PRICE) {
        if (current->salesData.totalPrice != pivot->salesData.totalPrice) {
            return ascending ? (current->salesData.totalPrice <= pivot->salesData.totalPrice)
                             : (current->salesData.totalPrice >= pivot->salesData.totalPrice);
        }
        // Tie-breaker: preserve count sequence
        return ascending ? (current->count <= pivot->count)
                         : (current->count >= pivot->count);
    }
    else if (sortBy == SortField::DATE) {
        int currDate = parseDate(current->salesData.date);
        int pivDate = parseDate(pivot->salesData.date);
        if (currDate != pivDate) {
            return ascending ? (currDate <= pivDate) : (currDate >= pivDate);
        }
        // Tie-breaker: preserve count sequence
        return ascending ? (current->count <= pivot->count)
                         : (current->count >= pivot->count);
    }
    else if (sortBy == SortField::TRANSACTION_ID) {
        if (current->salesData.transactionID != pivot->salesData.transactionID) {
            return ascending ? (current->salesData.transactionID <= pivot->salesData.transactionID)
                             : (current->salesData.transactionID >= pivot->salesData.transactionID);
        }
        return ascending ? (current->count <= pivot->count)
                         : (current->count >= pivot->count);
    }
    else if (sortBy == SortField::QUANTITY) {
        if (current->salesData.quantity != pivot->salesData.quantity) {
            return ascending ? (current->salesData.quantity <= pivot->salesData.quantity)
                             : (current->salesData.quantity >= pivot->salesData.quantity);
        }
        return ascending ? (current->count <= pivot->count)
                         : (current->count >= pivot->count);
    }

    return false;
}
CafeNode partition(
    CafeNode &head, 
    CafeNode low, 
    CafeNode high,
    SortField sortBy, 
    bool ascending) {
    
    CafeNode mid = getMiddleNode(low, high);
    swapNode(head, mid, high);
        
    CafeNode i = nullptr;

    for (CafeNode j = low; j != high; j = j->next) {
        if (shouldSwap(j, high, sortBy, ascending) == true) {
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

void quickSort(
    CafeNode &head, 
    CafeNode low, 
    CafeNode high,
    SortField sortBy, 
    bool ascending) {
    if (high != nullptr && low != high && low != high->next) {
        CafeNode pivotNode = partition(head, low, high, sortBy, ascending);
        quickSort(head, low, pivotNode->prev, sortBy, ascending);
        quickSort(head, pivotNode->next, high, sortBy, ascending);
    }
}

CafeNode filterAuditData(
    CafeNode head,
    AuditFilter filterType,
    const std::string& strParam1,
    const std::string& strParam2,
    double numParam
) {
    CafeNode filteredHead = nullptr;
    CafeNode filteredTail = nullptr;

    for (CafeNode curr = head; curr != nullptr; curr = curr->next) {
        bool matches = false;
        SalesData data = curr->salesData;
        if (filterType == AuditFilter::ALL) {
            matches = true;
        }
        else if (filterType == AuditFilter::BY_PAYMENT_MODE) {
            if (data.modeOfPayment == strParam1) {
                matches = true;
            }
        }
        else if (filterType == AuditFilter::DISCOUNTED_ONLY) {
            if (data.isDiscounted == true) {
                matches = true;
            }
        }
        else if (filterType == AuditFilter::MISSING_REF_ID) {
            std::string mode = data.modeOfPayment;
            std::transform(mode.begin(), mode.end(), mode.begin(), ::tolower);
            if (mode != "cash" && data.referenceID == 0) {
                matches = true;
            }
        }
        else if (filterType == AuditFilter::DATE_RANGE) {
            int nodeDate = parseDate(data.date);
            int startDate = parseDate(strParam1);
            int endDate = parseDate(strParam2);
            
            if (nodeDate >= startDate && nodeDate <= endDate && nodeDate !=0) {
                matches = true;
            }
        }
        else if (filterType == AuditFilter::MIN_TOTAL_PRICE) {
            if (data.totalPrice >= numParam) {
                matches = true;
            }
        }

        if (matches == true) {
            CafeNode newNode = new Node(
                data.menuItem,
                data.tempOfDrink,
                data.sizeOfItem,
                data.typeOfDiscount,
                data.modeOfPayment,
                data.date,
                data.totalPrice,
                data.unitPrice,
                data.quantity,
                data.referenceID,
                data.transactionID,
                data.discountedPrice,
                data.discountedPercentage,
                data.isDiscounted,
                curr->count
            );

            if (filteredHead == nullptr) {
                filteredHead = newNode;
                filteredTail = newNode;
            }
            else {
                filteredTail->next = newNode;
                newNode->prev = filteredTail;
                filteredTail = newNode;
            }
        }
    }
    return filteredHead;
}

void promptAndSort(CafeNode &listHead) {
    if (listHead == nullptr) return;

    std::cout << "\nSort results by:\n";
    std::cout << "[1] Date\n";
    std::cout << "[2] Total Price\n";
    std::cout << "[3] Quantity\n";
    std::cout << "[4] Transaction ID\n";
    std::cout << "[5] Keep Default Order (No Sort)\n";
    std::cout << "Enter choice: ";

    int sortChoice;
    if (!(std::cin >> sortChoice)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return;
    }

    if (sortChoice < 1 || sortChoice > 4) return;

    SortField selectedField = SortField::DATE;
    if (sortChoice == 1) selectedField = SortField::DATE;
    else if (sortChoice == 2) selectedField = SortField::TOTAL_PRICE;
    else if (sortChoice == 3) selectedField = SortField::QUANTITY;
    else if (sortChoice == 4) selectedField = SortField::TRANSACTION_ID;
    
    // Prompt for Ascending or Descending
    std::cout << "\nSelect Sort Order:\n";
    std::cout << "[1] Ascending (Lowest to Highest / Oldest to Newest)\n";
    std::cout << "[2] Descending (Highest to Lowest / Newest to Oldest)\n";
    std::cout << "Enter choice: ";

    int orderChoice;
        if (!(std::cin >> orderChoice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            orderChoice = 1; // Default to ascending on bad input
        }

    bool isAscending = true;
    if (orderChoice == 1) isAscending = true;
    else if (orderChoice == 2) isAscending = false;
    else {
        std::cout << "Invalid choice. Defaulting to Ascending.\n";
        isAscending = true;
    }
    CafeNode tailNode = tail(listHead);
    quickSort(listHead, listHead, tailNode, selectedField, isAscending);
}

void printFilteredPurchase(CafeNode mainHead) {
    if (mainHead == nullptr) {
        std::cout << "\nNo transactions available to filter.";
        return;
    }
    clearScreen();

    std::cout << "\n======================================================================\n";
    std::cout << "                   RUMO-IT AUDIT SYSTEM - FILTER                      \n";
    std::cout << "======================================================================\n";
    std::cout << "[1] Filter by Mode of Payment (e.g., Cash, GCash)\n";
    std::cout << "[2] Filter Discounted Transactions Only\n";
    std::cout << "[3] Filter Non-Cash Transactions Missing Reference ID\n";
    std::cout << "[4] Filter by Date Range\n";
    std::cout << "[5] Filter by Minimum Total Price\n";
    std::cout << "[6] View All Transactions (Sort Only)\n";
    std::cout << "[0] Back to Main Menu\n";
    std::cout << "Enter choice: ";

    int filterChoice;
    if (!(std::cin >> filterChoice)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "Invalid choice. Press Enter to return...";
        std::cin.get();
        return;
    }

    if (filterChoice == 0) return;

    CafeNode filteredList = nullptr;

    if (filterChoice == 1) {
        std::string paymentMode;
        std::cout << "Enter Mode of Payment: ";
        std::getline(std::cin >> std::ws, paymentMode);
        filteredList = filterAuditData(mainHead, AuditFilter::BY_PAYMENT_MODE, paymentMode);
    }
    else if (filterChoice == 2) filteredList = filterAuditData(mainHead, AuditFilter::DISCOUNTED_ONLY);
    else if (filterChoice == 3) filteredList = filterAuditData(mainHead, AuditFilter::MISSING_REF_ID);
    else if (filterChoice == 4) {
        std::string startDate;
        std::string endDate;
        std::cout << "Enter Start Date (DD-MM-YYYY): ";
        std::cin >> startDate;
        std::cout << "Enter End Date (DD-MM-YYYY): ";
        std::cin >> endDate;

        int startKey = parseDate(startDate);
        int endKey = parseDate(endDate);

        if (startKey == 0 || endKey == 0) {
            std::cout << "Invalid date format! Use DD-MM-YYYY or YYYY-MM-DD.\n";
            std::cout << "Press Enter to return...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
            return;
        }

        if (startKey > endKey) {
            std::cout << "Error: Start date cannot be after End date.\n";
            std::cout << "Press Enter to return...";
            std::cin.ignore(10000, '\n');
            std::cin.get();
            return;
        }

        filteredList = filterAuditData(mainHead, AuditFilter::DATE_RANGE, startDate, endDate);
    }
    else if (filterChoice == 5) {
        double minPrice;
        std::cout << "Enter minimum price: ";
        if (!(std::cin >> minPrice) || minPrice < 0) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Invalid price entry.\n";
            return;
        }
        filteredList = filterAuditData(mainHead, AuditFilter::MIN_TOTAL_PRICE, "", "", minPrice);
    }
    else if (filterChoice == 6) {
        filteredList = filterAuditData(mainHead, AuditFilter::ALL);
    }
    else {
        std::cout << "Invalid choice. \n";
        return;
    }

    if (filteredList != nullptr) {
        promptAndSort(filteredList);
        printAllPurchases(filteredList, "FILTERED PURCHASES");

        CafeNode current = filteredList;
        while (current != nullptr) {
            CafeNode nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }
    else {
        std::cout << "\nNo transactions matched your filter criteria.\n";
        std::cout << "Press Enter to return...";
        std::cin.ignore();
        std::cin.get();
    }
}