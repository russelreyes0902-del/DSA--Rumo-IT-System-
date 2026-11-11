#include <iostream>
#include <limits>
#include "Node.h"
#include "AuditList.h"
#include "FileInput.h"
#include "FileOutput.h"
#include "Search.h"
#include "Sort.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main () {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Enables UTF-8 symbol display (₱)
#endif

    CafeNode auditHead = nullptr;
    loadMenuData("menu_data.csv");
    loadAuditData("inventory.csv", auditHead);
    
    MenuSkip skipList;
    skipList.buildFromList(auditHead);

    int choice = 0;

    do {
        clearScreen();
        
        std::cout << "\n======================================================================\n";
        std::cout << "                      RUMO-IT AUDIT SYSTEM                            \n";
        std::cout << "======================================================================\n";
        std::cout << "[1] View Sales Summary Statistics\n";
        std::cout << "[2] View All Purchases\n";
        std::cout << "[3] View Recent Purchases\n";
        std::cout << "[4] View Menu\n";
        std::cout << "[5] Inventory Operations\n"; 
        std::cout << "[6] View Unsaved Changes (" << getPendingCount() << " pending)\n";
        std::cout << "[7] Exit Program\n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Enter your choice (1-7): ";
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
            std::cout << "\nInvalid input! Please enter a number between 1 and 7.\n";
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
        switch (choice) {
            case 1:
                printSummaryStatistics(auditHead);
                break;
            case 2:
                printAllPurchases(auditHead, "ALL PURCHASES");
                break;
            case 3:
                printRecentPurchase(auditHead);
                break;
            case 4:
                printMenu("menu_data.csv");
                break;
            case 5:
                auditMenuHandler(auditHead, "inventory.csv");
                break;
            case 6:
                viewUnsavedChanges(auditHead, "inventory.csv");
                break;
            case 7:
                std::cout << "\nExiting RUMO-IT Audit System. Goodbye!\n";
                break;
            default:
                std::cout << "\nInvalid choice! Please choose between 1 and 5.\n";
                std::cout << "Press Enter to continue...";
                std::cin.get();
                break;
        }

    } while (choice != 7);

    while (auditHead != nullptr) {
        CafeNode temp = auditHead;
        auditHead = auditHead->next;
        delete temp;
    }

    return 0;
}