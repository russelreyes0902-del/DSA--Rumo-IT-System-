#include "Node.h"
#include "Search.h"
#include "Sort.h"
#include "AuditList.h"
#include <iomanip>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <limits>

void clearScreen() {
#ifdef _WIN32
    system("cls");   // Windows
#else
    system("clear"); // Linux / macOS
#endif
}

// Use this file for Node purposes, i.e accessing node at position x, 
// updating node at position x, deleting and insertion of nodes.
CafeNode tail(CafeNode &head) {
    if (head == nullptr) return nullptr;
    CafeNode current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    return current;
}

std::string convertMonthToNumber(std::string monthInput) {  

    if (monthInput == "January" || 
        monthInput == "january" || 
        monthInput == "Jan" || 
        monthInput == "jan" ||
        monthInput == "01" || 
        monthInput == "1") {
        return "01";
    } 
    else if (monthInput == "February" || 
            monthInput == "february" || 
            monthInput == "Feb" || 
            monthInput == "feb" ||
            monthInput == "02" || 
            monthInput == "2") {
        return "02";
    } 
    else if (monthInput == "March" || 
            monthInput == "march" || 
            monthInput == "Mar" || 
            monthInput == "mar" ||
            monthInput == "03" || 
            monthInput == "3") {
        return "03";
    } 
    else if (monthInput == "April" || 
            monthInput == "april" || 
            monthInput == "Apr" || 
            monthInput == "apr" ||
            monthInput == "04" || 
            monthInput == "4") {
        return "04";
    } 
    else if (monthInput == "May" || 
            monthInput == "may" || 
            monthInput == "05" || 
            monthInput == "5") {
        return "05";
    } 
    else if (monthInput == "June" || 
            monthInput == "june" || 
            monthInput == "Jun" || 
            monthInput == "jun" ||
            monthInput == "06" || 
            monthInput == "6") {
        return "06";
    } 
    else if (monthInput == "July" || 
            monthInput == "july" || 
            monthInput == "Jul" || 
            monthInput == "jul" ||
            monthInput == "07" || 
            monthInput == "7") {
        return "07";
    } 
    else if (monthInput == "August" || 
            monthInput == "august" || 
            monthInput == "Aug" || 
            monthInput == "aug" ||
            monthInput == "08" || 
            monthInput == "8") {
        return "08";
    } 
    else if (monthInput == "September" || 
            monthInput == "september" || 
            monthInput == "Sep" || 
            monthInput == "sep" ||
            monthInput == "09" || 
            monthInput == "9") {
        return "09";
    } 
    else if (monthInput == "October" || 
            monthInput == "october" || 
            monthInput == "Oct" || 
            monthInput == "oct" ||
            monthInput == "10") {
        return "10";
    } 
    else if (monthInput == "November" || 
            monthInput == "november" || 
            monthInput == "Nov" || 
            monthInput == "nov" ||
            monthInput == "11") {
        return "11";
    } 
    else if (monthInput == "December" || 
            monthInput == "december" || 
            monthInput == "Dec" || 
            monthInput == "dec" ||
            monthInput == "12") {
        return "12";
    } 
    else {
        return "00"; // Return invalid code if input doesn't match
    }
}

int getTotalTransactions(CafeNode &head) { 
    // NOTE: This uses O(n) linear search to count the total nodes. Update this when we have File I/O functions
    // to dynamically calculat the amount of nodes without having to call the function again and again.
    CafeNode current = head;
    int count = 0;
    
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    return count;
}
//Statistics function to get the amount of items sold in a single day.
int getDailyItemsSold(
    CafeNode &head, 
    std::string targetDay, 
    std::string targetItem,
    std::string targetSize
    ) {

    if (head == nullptr) return 0;
    CafeNode current = head;
    int totalItemsSold = 0;

    while (current != nullptr) {
        if (current->salesData.date == targetDay) { 
            // This function requires a date, but the item menu is optional.
            // i.e searching for the amount of quantity sold in a target day, the function returns the value
            // If you want to get the total quantity of items sold in a targe day, input the name of the item since
            // items that are bought with different modeOfPayments are separated.
            // I.e node1 has spanish latte with quantity of 20 with mOP of Cash
            // and node2 has spanish latte with quantity of 15, with mOP of GCash
            bool matchesItem = (targetItem == "" || current->salesData.menuItem == targetItem);
            bool matchesSize = (targetSize == "" || current->salesData.sizeOfItem == targetSize);
            if (matchesItem && matchesSize) {
                totalItemsSold += current->salesData.quantity;
            }
        }
        current = current->next;
    }

    return totalItemsSold;
}

int getMonthlyItemsSold(
    CafeNode &head, 
    std::string monthInput, 
    std::string targetYear, 
    std::string targetItem,
    std::string targetSize
    ) {

    if (head == nullptr) return 0;
    
    std::string formattedMonth = convertMonthToNumber(monthInput);
    if (formattedMonth == "00") {
        return 0;
    }

    std::string targetMonth = formattedMonth + "-" + targetYear;

    CafeNode current = head;
    int totalItemsSold = 0;

    while (current != nullptr) {
    std::string nodeMonthYear = current->salesData.date.substr(3, 7);
        if (nodeMonthYear == targetMonth) {
            bool matchesItem = (targetItem == "" || current->salesData.menuItem == targetItem);
            bool matchesSize = (targetSize == "" || current->salesData.sizeOfItem == targetSize);
            if (matchesItem && matchesSize) {
                totalItemsSold += current->salesData.quantity;
            }
        }
        current = current->next;
    }
    return totalItemsSold;
}

int getYearlyItemsSold(
    CafeNode &head, 
    std::string targetYear, 
    std::string targetItem,
    std::string targetSize
    ) {

    if (head == nullptr) return 0;
    CafeNode current = head;
    int totalItemsSold = 0;

    while (current != nullptr) {
        std::string nodeYear = current->salesData.date.substr(6,4);
        if (nodeYear == targetYear) {
            bool matchesItem = (targetItem == "" || current->salesData.menuItem == targetItem);
            bool matchesSize = (targetSize == "" || current->salesData.sizeOfItem == targetSize);
            if (matchesItem && matchesSize) {
                totalItemsSold += current->salesData.quantity;
            }
        }
        current = current->next;
    }
    return totalItemsSold;
}

void printRecentPurchase(CafeNode &head) {
        if (head == nullptr) {
            std::cout << "\nNo recent transactions." << std::endl;
            return;
        }

        MenuSkip skipList;
        skipList.buildFromList(head);

        int pageSize = 10;
        int totalNodes = getTotalTransactions(head);
        int currentPage = 1;
        std::string choice;
        
        int totalPages = (totalNodes + pageSize - 1)/10;
        do {
            clearScreen();

            CafeNode current = head;            
            int skipCount = (currentPage - 1) * pageSize;
            for (int i = 0; i < skipCount && current != nullptr; i++) {
                current = current->next;
            }
            
        std::cout << "\n====================================================================================================================================================\n";
        std::cout << "                                                    RECENT PURCHASES (PAGE " << currentPage << " / " << totalPages << ")\n";
        std::cout << "====================================================================================================================================================\n";
        std::cout << "Menu Item       | Size   | Temp | Qty | Unit Price | Total Price | Payment Mode | Disc % | Disc Price \n";
       std::cout << "----------------------------------------------------------------------------------------------------------------------------------------------------\n";

        int printedCount = 0;
        int startRecord = skipCount + 1;   

        while (current != nullptr && printedCount < pageSize) {
            // 1. Format menuItem display (15 chars)
            std::string itemDisplay = current->salesData.menuItem;
            if (itemDisplay.length() > 15) {
                itemDisplay = itemDisplay.substr(0, 12) + "...";
            }

            std::string sizeDisplay = current->salesData.sizeOfItem;
            if (sizeDisplay == "" || sizeDisplay == "None") {
                sizeDisplay = "-";
            }
            if (sizeDisplay.length() > 6) {
                sizeDisplay = sizeDisplay.substr(0, 5) + ".";
            }

            std::string tempDisplay = current->salesData.tempOfDrink;
            if (tempDisplay == "" || tempDisplay == "None") {
                tempDisplay = "-";
            }
            if (tempDisplay.length() > 4) {
                tempDisplay = tempDisplay.substr(0, 4);
            }

            // 5. Print formatted row with separate Extras column
            std::cout << std::left << std::setw(15) << itemDisplay << " | "
                      << std::left << std::setw(6)  << sizeDisplay << " | "
                      << std::left << std::setw(4)  << tempDisplay << " | "
                      << std::right << std::setw(3) << current->salesData.quantity << " | $"
                      << std::fixed << std::setprecision(2)
                      << std::setw(8) << current->salesData.unitPrice << " | $"
                      << std::setw(9) << current->salesData.totalPrice << " | "
                      << std::left << std::setw(12) << current->salesData.modeOfPayment;
                      
            if (current->salesData.isDiscounted) {
                std::cout << " | "
                          << std::right << std::setw(5) << current->salesData.discountedPercentage << "% | $"
                          << std::setw(9) << current->salesData.discountedPrice;
            } else {
                std::cout << " | "
                          << std::right << std::setw(6) << "-" << " | "
                          << std::setw(10) << "-";
            }

            std::cout << "\n";

            current = current->next;
            printedCount++;
        }
            int endRecord = skipCount + printedCount;

            std::cout << "----------------------------------------------------------------------\n";
            std::cout << "Displaying records " << startRecord << "-" << endRecord << " of " << totalNodes << "\n";
            std::cout << "======================================================================\n";

            std::cout << "Controls: ";
            if (currentPage < totalPages) std::cout << "[N]ext  ";
            if (currentPage > 1)          std::cout << "[P]revious  ";
            std::cout << "[G]o to Page  [S]earch  [E]xit\n";
            std::cout << "Enter choice: ";
            std::getline(std::cin >> std::ws, choice);
            char answer = choice[0];
            if (choice.length() != 1) {
                std::cout << "Invalid input! Enter only one character at a time" << std::endl;
                std::cin.get();
            }
            else {
                if ((answer == 'N' || answer == 'n') && currentPage < totalPages) {
                    currentPage++;
                } 
                else if ((answer == 'P' || answer == 'p') && currentPage > 1) {
                    currentPage--;
                } 
                else if (answer == 'G' || answer == 'g') {
                    int targetPage;
                    std::cout << "Enter page number (1-" << totalPages << "): ";
                    
                    // Check if the input is a valid integer
                    if (std::cin >> targetPage) {
                        if (targetPage >= 1 && targetPage <= totalPages) {
                            currentPage = targetPage;
                        } else {
                            std::cout << "Invalid page number! Out of range.\n";
                            std::cout << "Press Enter to continue...";
                            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                            std::cin.get();
                        }
                        // Clear the leftover newline from std::cin >> targetPage
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    } else {
                        // Clear error flags caused by letters/symbols
                        std::cin.clear();
                        // Discard all invalid characters remaining in the buffer
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        
                        std::cout << "Invalid entry! Must be a number. Press Enter to continue...";
                        std::cin.get();
                    }
                }
                else if (answer == 'S' || answer == 's'){
                    printSearchPurchase(head, skipList);
                }
                else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid entry! Must be a number. Press Enter to continue...";
                    std::cin.get();
                }   
            }
        } while(choice[0] != 'E' && choice[0] != 'e');
   }