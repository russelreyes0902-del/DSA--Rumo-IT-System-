#include <fstream>
#include <iostream>
#include <string>
#include <cctype>
#include <limits>
#include "FileOutput.h"
#include "AuditList.h"

const int maxPendingChanges = 100;
PendingChanges pendingChanges[maxPendingChanges];
int pendingCount = 0;

int getListLength(CafeNode head) {
    int count = 0;
    while (head != nullptr) {
        count++;
        head = head->next;
    }
    return count;
}

int getPendingCount() {
    return pendingCount;
}

PendingChanges getPendingChangeAt(int index) {
    if (index >= 0 && index < pendingCount) {
        return pendingChanges[index];
    }
    return PendingChanges();
}

void removePendingChangeAt(int index) {
    if (index >= 0 && index < pendingCount) {
        for (int i = index; i < pendingCount - 1; ++i) {
            pendingChanges[i] = pendingChanges[i + 1];
        }
        pendingCount--;
    }
}

void clearPendingChanges() {
    pendingCount = 0; 
}

bool hasUnsavedChanges() {
    return pendingCount > 0;
}

void addPendingChange(const std::string& type, const std::string& detail) {
    if (pendingCount < maxPendingChanges) {
        pendingChanges[pendingCount] = {type, pendingCount, detail, SalesData(), SalesData()};
        pendingCount++;
        std::cout << "Pending change added to unsaved changes.\n";
    } else {
        std::cout << "Maximum pending changes reached. Cannot add more changes.\n";
    }
}

void saveChangesToFile(CafeNode head, const std::string& filename) {
    std::ofstream oFile(filename);
    if (!oFile.is_open()) {
        std::cerr << "Error opening file for writing: " << filename << "\n";
        return;
    }

    oFile << "MenuItem,TempOfDrink,SizeOfItem,TypeOfDiscount,ModeOfPayment,Date,TotalPrice,UnitPrice,Quantity,ReferenceID,TransactionID,DiscountedPrice,DiscountedPercentage,isDiscounted\n";

    CafeNode current = head;
    while (current != nullptr) {
        oFile << current->salesData.menuItem << ","
              << current->salesData.tempOfDrink << ","
              << current->salesData.sizeOfItem << ","
              << current->salesData.typeOfDiscount << ","
              << current->salesData.modeOfPayment << ","
              << current->salesData.date << ","
              << current->salesData.totalPrice << ","
              << current->salesData.unitPrice << ","
              << current->salesData.quantity << ","
              << current->salesData.referenceID << ","
              << current->salesData.transactionID << ","
              << current->salesData.discountedPrice << ","
              << current->salesData.discountedPercentage << ","
              << (current->salesData.isDiscounted ? "1" : "0") << ","
              << current->count << "\n";
        current = current->next;
    }
    oFile.close();
    std::cout << "Changes saved to file: " << filename << "\n";
} 

void insertNode(CafeNode& head, const SalesData& newData, int position) {
    int length = getListLength(head);
    if (position < 1 || position > length + 1) {
        std::cout << "Invalid. Must be between 1 and " << (length + 1) << ".\n";
        return;
    }

    CafeNode newNode = new Node(
        newData.menuItem, 
        newData.tempOfDrink, 
        newData.sizeOfItem,
        newData.typeOfDiscount, 
        newData.modeOfPayment, 
        newData.date,
        newData.totalPrice, 
        newData.unitPrice, 
        newData.quantity,
        newData.referenceID, 
        newData.transactionID, 
        newData.discountedPrice,
        newData.discountedPercentage, 
        newData.isDiscounted, position
    );

    if (position == 1) {
        newNode->next = head;
        if (head != nullptr) head->prev = newNode;
        head = newNode;
    } else {
        CafeNode current = head;
        for (int i = 1; i < position - 1; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        if (current->next != nullptr) {
            current->next->prev = newNode;
        }
        current->next = newNode;
    }

    std::cout << "\n Node (" << newData.menuItem << ") successfully inserted at position " << position << ".\n";

    char choice;
    while (true) {
        std::cout << "Save change directly to file now? (Y/N): ";
        std::cin >> choice;
        choice = std::toupper(choice);
        if (choice == 'Y' || choice == 'N') {
            break;
        }
        std::cout << "Invalid option. Please enter 'Y' or 'N'.\n";
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    if (choice == 'Y') {
        saveChangesToFile(head, "inventory.csv");
        clearPendingChanges();
    } else {
        PendingChanges change;
        change.type = "INSERT";
        change.index = position;
        change.data = newData;
        change.details = "INSERT [" + newData.menuItem + "] at Position " + std::to_string(position);
        addPendingChange(change.type, change.details);
    }
}

void updateNode(CafeNode &head, const SalesData& data, int position) {
    if (head == nullptr || position < 1) {
        std::cout << "Invalid position or empty list.\n";
        return;
    }
    CafeNode current = head;
    int currentPos = 1;

    while (current != nullptr && currentPos < position) {
        current = current->next;
        currentPos++;
    }
    if (current == nullptr) {
        std::cout << "Position out of bounds.\n";
        return;
    }
    
    current->salesData = data;

    std::string detail = "Updated record at position " + std::to_string(position) + " (" + data.menuItem + ")";
    addPendingChange("UPDATE", detail);

    std::cout << "Record at position " << position << " updated successfully (Pending Save).\n";
}

void deleteNode(CafeNode &head, int position) {
    int length = getListLength(head);
    if (head == nullptr || position < 1 || position > length) {
        std::cout << "Invalid deletion position.\n";
        return;
    }

    CafeNode target = head;
    if (position == 1) {
        head = head->next;
        if (head != nullptr) head->prev = nullptr;
    } else {
        for (int i = 1; i < position; ++i) {
            target = target->next;
        }
        if (target->prev != nullptr) target->prev->next = target->next;
        if (target->next != nullptr) target->next->prev = target->prev;
    }

    SalesData removedData = target->salesData;
    delete target;

    std::cout << "\n Node (" << removedData.menuItem << ") at position " << position << " deleted.\n";

    char choice;
    while (true) {
        std::cout << "Save change directly to file now? (Y/N): ";
        std::cin >> choice;
        choice = std::toupper(choice);
        if (choice == 'Y' || choice == 'N') {
            break;
        }
        std::cout << "Invalid option. Please enter 'Y' or 'N'.\n";
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

    if (choice == 'Y') {
        saveChangesToFile(head, "inventory.csv");
        clearPendingChanges();
    } else {
        PendingChanges change;
        change.type = "DELETE";
        change.index = position;
        change.oldData = removedData;
        change.details = "DELETE [" + removedData.menuItem + "] from Position " + std::to_string(position);
        addPendingChange(change.type, change.details);
    }
}