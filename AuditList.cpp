#include "Node.h"
#include "Search.h"
#include "Sort.h"
#include "AuditList.h"
#include "FileOutput.h"
#include <iomanip>
#include <iostream>
#include <cstdlib> 
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

void clearScreen() {
#ifdef _WIN32
    system("cls");   
#else
    system("clear"); 
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

CafeNode getMiddleNode(CafeNode low, CafeNode high) {
    CafeNode slow = low;
    CafeNode fast = slow;

    while (fast != high && fast->next != high) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
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

void printPaginatedPurchases(
CafeNode &head, 
    const std::string& title, 
    int maxRecords) {

    if (head == nullptr) {
        std::cout << "\nNo transactions found.\n";
        std::cout << "Press Enter to return to main menu...";
        std::cin.get();
        return;
    }
    
    MenuSkip skipList;
    skipList.buildFromList(head);

    int pageSize = 10;
    int totalNodes = getTotalTransactions(head);

    if (maxRecords > 0 && totalNodes > maxRecords) {
        totalNodes = maxRecords;
        }

int currentPage = 1;
    int totalPages = (totalNodes + pageSize - 1) / pageSize;
    std::string choice;

    do {
        clearScreen();

        CafeNode current = head;
        int skipCount = (currentPage - 1) * pageSize;
        for (int i = 0; i < skipCount && current != nullptr; i++) {
            current = current->next;
        }

        std::cout << "\n================================================================================================================================\n";
        std::cout << "                                           " << title << " (PAGE " << currentPage << " / " << totalPages << ")\n";
        std::cout << "================================================================================================================================\n";
        std::cout << "Date       | Menu Item                    | Size   | Temp | Qty | Unit Price | Total Price | Payment Mode | Disc % | Disc Price \n";
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

        int printedCount = 0;
        int startRecord = skipCount + 1;

        while (current != nullptr && printedCount < pageSize && (skipCount + printedCount) < totalNodes) {
            std::string dateDisplay = current->salesData.date;
            if (dateDisplay == "") {
                dateDisplay = "-";
            }

            std::string itemDisplay = current->salesData.menuItem;

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

            std::cout << std::left << std::setw(10) << dateDisplay << " | "
                      << std::left << std::setw(28) << itemDisplay << " | "
                      << std::left << std::setw(6)  << sizeDisplay << " | "
                      << std::left << std::setw(4)  << tempDisplay << " | "
                      << std::right << std::setw(3) << current->salesData.quantity << " | ₱"
                      << std::fixed << std::setprecision(2)
                      << std::setw(8) << current->salesData.unitPrice << " | ₱"
                      << std::setw(9) << current->salesData.totalPrice << " | "
                      << std::left << std::setw(12) << current->salesData.modeOfPayment;

            if (current->salesData.isDiscounted) {
                std::cout << " | "
                          << std::right << std::setw(5) << current->salesData.discountedPercentage << "% | ₱"
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

        std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Displaying records " << startRecord << "-" << endRecord << " of " << totalNodes << "\n";
        std::cout << "================================================================================================================================\n";

        std::cout << "Controls: ";
        if (currentPage < totalPages) {
            std::cout << "[N]ext  ";
        }
        if (currentPage > 1) {
            std::cout << "[P]revious  ";
        }
        std::cout << "[G]o to Page  [S]earch [F]ilter [E]xit\n";
        std::cout << "Enter choice: ";
        std::getline(std::cin >> std::ws, choice);

        if (choice.length() != 1) {
            std::cout << "Invalid input! Enter only one character at a time. Press Enter to continue..." << std::endl;
            std::cin.get();
        } else {
            char answer = choice[0];

            if ((answer == 'N' || answer == 'n') && currentPage < totalPages) {
                currentPage++;
            } else if ((answer == 'P' || answer == 'p') && currentPage > 1) {
                currentPage--;
            } else if (answer == 'G' || answer == 'g') {
                int targetPage;
                std::cout << "Enter page number (1-" << totalPages << "): ";

                if (std::cin >> targetPage) {
                    if (targetPage >= 1 && targetPage <= totalPages) {
                        currentPage = targetPage;
                    } else {
                        std::cout << "Invalid page number! Out of range.\n";
                        std::cout << "Press Enter to continue...";
                        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                        std::cin.get();
                    }
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                } else {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Invalid entry! Must be a number. Press Enter to continue...";
                    std::cin.get();
                }
            } 
            else if (answer == 'S' || answer == 's') printSearchPurchase(head, skipList);
            else if (answer == 'F' || answer == 'f') printFilteredPurchase(head);
            else if (answer == 'E' || answer == 'e') {
            } else {
                std::cout << "Invalid entry! Press Enter to continue...";
                std::cin.get();
            }
        }
    } while (choice[0] != 'E' && choice[0] != 'e');
}    

void printRecentPurchase(CafeNode &head) {
    if (head == nullptr) {
        std::cout << "\nNo transactions found.\n";
        std::cout << "Press Enter to return to main menu...";
        std::cin.get();
        return;
    }

    CafeNode tailNode = tail(head);
    quickSort(head, head, tailNode, SortField::DATE, false);
    printPaginatedPurchases(head, "RECENT PURCHASES", 100);
}

void printAllPurchases(CafeNode &head, const std::string& title) {
    if (head == nullptr) {
        std::cout << "\nNo transactions found.\n";
        std::cout << "Press Enter to return to main menu...";
        std::cin.get();
        return;
    }

    printPaginatedPurchases(head, title, -1);
}

void printSummaryStatistics(CafeNode &head) {
    if (head == nullptr) {
        std::cout << "\nNo transactions available for summary statistics.\n";
        std::cout << "Press Enter to return...";
        std::cin.get();
        return;
    }
    MenuSkip skipList;
    skipList.buildFromList(head);

    std::string choice;
    do {
        clearScreen();

        double overallRevenue = 0.0;
        long long overallUnits = 0;
        
        CafeNode current = head;
        CafeNode topItemNode = head;
        long long maxItemUnits = -1;

        while (current != nullptr) {
            overallRevenue += current->salesData.totalPrice;
            overallUnits += current->salesData.quantity;

            if (current->salesData.quantity > maxItemUnits) {
                maxItemUnits = current->salesData.quantity;
                topItemNode = current;
            }
            current = current->next;
        }
        std::string highestSellingItem = (topItemNode != nullptr) ? topItemNode->salesData.menuItem : "N/A";
       
        std::cout << "\n======================================================================\n";
        std::cout << "                        SALES SUMMARY STATISTICS                      \n";
        std::cout << "======================================================================\n";
        std::cout << "Highest Selling Item : " << highestSellingItem << "\n";
        std::cout << "Total Revenue        : ₱" << std::fixed << std::setprecision(2) << overallRevenue << "\n";
        std::cout << "Total Units Sold     : " << overallUnits << "\n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Choose [Y]early, [M]onthly, [D]aily filter, or [E]xit: ";
        
        std::getline(std::cin >> std::ws, choice);

        if (choice == "E" || choice == "e") {
            break;
        }
        else if (choice == "Y" || choice == "y" || choice == "M" || choice == "m" || choice == "D" || choice == "d") {
            std::string timeInput;
            std::string filterTypeLabel = "";

            if (choice == "Y" || choice == "y") {
                filterTypeLabel = "Yearly";
                std::cout << "Enter Year (e.g., 2026): ";
            }
            else if (choice == "M" || choice == "m") {
                filterTypeLabel = "Monthly";
                std::cout << "Enter Month and Year (e.g., 10-2026): ";
            }
            else if (choice == "D" || choice == "d") {
                filterTypeLabel = "Daily";
                std::cout << "Enter date (YYY-MM-DD): ";
            }
            std::getline(std::cin >> std::ws, timeInput);

            double filteredRevenue = 0.0;
            double filteredUnits = 0;
            CafeNode filteredHead = nullptr;
            CafeNode filteredTail = nullptr;

            current = head;
            while (current != nullptr) {
                bool matches = false;
                std::string dateStr = current->salesData.date;

                if (filterTypeLabel == "Yearly") {
                    if (dateStr.length() >= 4 && dateStr.substr(0,4) == timeInput) matches = true;
                }
                else if (filterTypeLabel == "Monthly") {
                    std::string monthNum = convertMonthToNumber(timeInput);
                    if (dateStr.length() >= 7 
                        && 
                        (dateStr.find(timeInput) != std::string::npos || (monthNum != "00" && dateStr.substr(5, 2) == monthNum))) {
                        matches = true;
                    }
                }
                else {
                    int targetDateKey = parseDate(timeInput);
                    int nodeDateKey = parseDate(dateStr);

                    if (targetDateKey != 0 && nodeDateKey != 0 && nodeDateKey == targetDateKey) {
                        matches = true;
                    } else if (dateStr == timeInput) { // Fallback to exact string match
                        matches = true;
                    }
                }

                if (matches) {
                    filteredRevenue += current->salesData.totalPrice;
                    filteredUnits += current->salesData.quantity;

                    SalesData data = current->salesData;
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
                        current->count
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
                current = current->next;
            }
            std::string filteredHighest = "N/A";
            if (filteredHead != nullptr) {
                CafeNode fTail = tail(filteredHead);
                quickSort(filteredHead, filteredHead, fTail, SortField::QUANTITY, false);
                filteredHighest = filteredHead->salesData.menuItem;
            }

            clearScreen();

            std::cout << "======================================================================\n";
            std::cout << "Highest Selling Item : " << filteredHighest << "\n";
            std::cout << "Total Revenue        : ₱" << std::fixed << std::setprecision(2) << filteredRevenue << "\n";
            std::cout << "Total Units Sold     : " << filteredUnits << "\n";
            std::cout << "======================================================================\n";
            std::cout << "Options: [S]earch  [F]ilter  [B]ack to Summary  [E]xit\n";
            std::cout << "Enter choice: ";

            std::getline(std::cin >> std::ws, choice);
            if (choice[0] == 'S' || choice[0] == 's') {
                printSearchPurchase(head, skipList);
            } else if (choice[0] == 'F' || choice[0] == 'f') {
                printFilteredPurchase(head);
            } else if (choice[0] == 'E' || choice[0] == 'e') {
                // Free filtered list memory before exit
                while (filteredHead != nullptr) {
                    CafeNode temp = filteredHead;
                    filteredHead = filteredHead->next;
                    delete temp;
                }
                break;
                
            }
            while (filteredHead != nullptr) {
                CafeNode temp = filteredHead;
                filteredHead = filteredHead->next;
                delete temp;
            }
        }
    } while(choice[0] != 'E' && choice[0] != 'e');
} 

void clearInputBuffer() {
    std::cin.clear();
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
}

std::string validateAndFormatMenuItem(const std::string& input) {
    if (input.empty()) return "";

    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    std::ifstream menuFile("menu_data.csv");
    if (!menuFile.is_open()) return input;

    std::string line;
    std::getline(menuFile, line); // Skip header

    while (std::getline(menuFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::string canonicalItemName = "";
        int columnIndex = 0;

        // Parse each column from the beginning of the line
        while (std::getline(ss, token, ',')) {
            if (columnIndex == 2) { // Index 2 is 'menuItem' (0: ID, 1: Category, 2: Name)
                canonicalItemName = token;
                break;
            }
            columnIndex++;
        }

        // Clean up quotes, carriage returns, and whitespace
        if (!canonicalItemName.empty() && canonicalItemName.front() == '"') canonicalItemName.erase(0, 1);
        if (!canonicalItemName.empty() && canonicalItemName.back() == '"') canonicalItemName.pop_back();
        if (!canonicalItemName.empty() && canonicalItemName.back() == '\r') canonicalItemName.pop_back();

        std::string lowerMenu = canonicalItemName;
        std::transform(lowerMenu.begin(), lowerMenu.end(), lowerMenu.begin(), ::tolower);

        if (lowerMenu == lowerInput || lowerMenu.find(lowerInput) != std::string::npos) {
            menuFile.close();
            return canonicalItemName;
        }
    }

    menuFile.close();
    return "";
}

bool itemHasTemperatureOption(const std::string& menuItemName) {
    std::ifstream menuFile("menu_data.csv");
    if (!menuFile.is_open()) return false;

    std::string line;
    std::getline(menuFile, line); // Skip header

    std::string lowerInput = menuItemName;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    while (std::getline(menuFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::string canonicalItemName = "";
        std::string tempField = "";
        int columnIndex = 0;

        while (std::getline(ss, token, ',')) {
            if (columnIndex == 2) canonicalItemName = token;
            if (columnIndex == 4) tempField = token; // column 4 is drinkOfTemp
            columnIndex++;
        }

        if (!canonicalItemName.empty() && canonicalItemName.front() == '"') canonicalItemName.erase(0, 1);
        if (!canonicalItemName.empty() && canonicalItemName.back() == '"') canonicalItemName.pop_back();
        if (!canonicalItemName.empty() && canonicalItemName.back() == '\r') canonicalItemName.pop_back();

        std::string lowerMenu = canonicalItemName;
        std::transform(lowerMenu.begin(), lowerMenu.end(), lowerMenu.begin(), ::tolower);

        if (lowerMenu == lowerInput) {
            if (!tempField.empty() && tempField != "N/A" && tempField != "None" && tempField != "\r") {
                menuFile.close();
                return true;
            }
        }
    }
    menuFile.close();
    return false;
}

bool itemHasSizeOption(const std::string& menuItemName) {
    std::ifstream menuFile("menu_data.csv");
    if (!menuFile.is_open()) return false;

    std::string line;
    std::getline(menuFile, line); // Skip header

    std::string lowerInput = menuItemName;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    while (std::getline(menuFile, line)) {
        if (line.empty()) continue;

        std::stringstream ss(line);
        std::string token;
        std::string canonicalItemName = "";
        std::string sizeField = "";
        int columnIndex = 0;

        while (std::getline(ss, token, ',')) {
            if (columnIndex == 2) canonicalItemName = token;
            if (columnIndex == 5) sizeField = token; // column 5 is sizeOfItem
            columnIndex++;
        }

        if (!canonicalItemName.empty() && canonicalItemName.front() == '"') canonicalItemName.erase(0, 1);
        if (!canonicalItemName.empty() && canonicalItemName.back() == '"') canonicalItemName.pop_back();
        if (!canonicalItemName.empty() && canonicalItemName.back() == '\r') canonicalItemName.pop_back();

        std::string lowerMenu = canonicalItemName;
        std::transform(lowerMenu.begin(), lowerMenu.end(), lowerMenu.begin(), ::tolower);

        if (lowerMenu == lowerInput) {
            if (!sizeField.empty() && sizeField != "N/A" && sizeField != "None" && sizeField != "\r") {
                menuFile.close();
                return true;
            }
        }
    }
    menuFile.close();
    return false;
}

SalesData editSalesData(const SalesData& currentData) {
    SalesData data = currentData;
    std::cout << "\n======================================================================\n";
    std::cout << "                         EDIT RECORD DETAILS                          \n";
    std::cout << "======================================================================\n";

    while (true) {
        std::cout << "Menu Item Name [" << data.menuItem << "]: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) break; 

        std::string matchedName = validateAndFormatMenuItem(input);
        if (!matchedName.empty()) {
            data.menuItem = matchedName;
            break;
        }
        std::cout << input << "' is not a valid menu item in the menu. Try again.\n";
    }

    // Conditionally check and prompt for Temperature
    if (itemHasTemperatureOption(data.menuItem)) {
        while (true) {
            std::cout << "Temperature (Hot/Iced/NA) [" << data.tempOfDrink << "]: ";
            std::string input;
            std::getline(std::cin, input);
            if (input.empty()) break;

            std::string lower = input;
            for (char &c : lower) c = std::tolower(c);

            if (lower == "hot") { data.tempOfDrink = "Hot"; break; }
            if (lower == "iced") { data.tempOfDrink = "Iced"; break; }
            if (lower == "n/a" || lower == "na") { data.tempOfDrink = "N/A"; break; }

            std::cout << "Invalid temperature. Enter 'Hot', 'Iced', or 'N/A'.\n";
        }
    } else {
        data.tempOfDrink = "N/A";
    }

    // Conditionally check and prompt for Size
    if (itemHasSizeOption(data.menuItem)) {
        while (true) {
            std::cout << "Size (Regular/Large) [" << data.sizeOfItem << "]: ";
            std::string input;
            std::getline(std::cin, input);
            if (input.empty()) break;

            std::string lower = input;
            for (char &c : lower) c = std::tolower(c);

            if (lower == "regular" || lower == "reg") { data.sizeOfItem = "Regular"; break; }
            if (lower == "large") { data.sizeOfItem = "Large"; break; }

            std::cout << "Invalid size. Enter 'Regular' or 'Large'.\n";
        }
    } else {
        data.sizeOfItem = "N/A";
    }

    while (true) {
        std::cout << "Type of Discount (Senior/PWD/None) [" << data.typeOfDiscount << "]: ";
        std::string input;
        std::getline(std::cin, input);
        if (input.empty()) break;

        std::string lower = input;
        for (char &c : lower) c = std::tolower(c);

        if (lower == "senior") { data.typeOfDiscount = "Senior"; break; }
        if (lower == "pwd") { data.typeOfDiscount = "PWD"; break; }
        if (lower == "none") { data.typeOfDiscount = "None"; break; }

        std::cout << "Invalid discount type. Enter Senior, PWD, or None.\n";
    }

    std::cout << "Mode of Payment [" << data.modeOfPayment << "]: ";
    std::string payInput;
    std::getline(std::cin, payInput);
    if (!payInput.empty()) data.modeOfPayment = payInput;

    std::string lowerPayment = data.modeOfPayment;
    for (char &c : lowerPayment) c = std::tolower(c);

    if (lowerPayment == "cash") {
        data.referenceID = 0; 
    } else {
        while (true) {
            std::cout << "Reference ID [" << data.referenceID << "]: ";
            std::string inputStr;
            std::getline(std::cin, inputStr);
            if (inputStr.empty()) break; 

            try {
                size_t pos = 0;
                long long val = std::stoll(inputStr, &pos);
                if (pos == inputStr.length() && val >= 0) {
                    data.referenceID = val;
                    break;
                }
                throw std::invalid_argument("Invalid reference ID");
            } catch (...) {
                std::cout << "Invalid Reference ID. Enter a positive number.\n";
            }
        }
    }

    while (true) {
        std::cout << "Transaction ID [" << data.transactionID << "]: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        if (inputStr.empty()) break; 

        try {
            size_t pos = 0;
            int val = std::stoi(inputStr, &pos);
            if (pos == inputStr.length() && val >= 0) {
                data.transactionID = val;
                break;
            }
            throw std::invalid_argument("Invalid transaction ID");
        } catch (...) {
            std::cout << "Invalid Transaction ID. Enter a positive integer.\n";
        }
    }

    while (true) {
        std::cout << "Date (YYYY-MM-DD) [" << data.date << "]: ";
        std::string dateInput;
        std::getline(std::cin, dateInput);
        if (dateInput.empty()) break;

        if (dateInput.length() == 10 && dateInput[4] == '-' && dateInput[7] == '-') {
            data.date = dateInput;
            break;
        }
        std::cout << "Invalid date format. Must be YYYY-MM-DD.\n";
    }

    while (true) {
        std::cout << "Unit Price [" << data.unitPrice << "]: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        if (inputStr.empty()) break; 

        try {
            size_t pos = 0;
            double val = std::stod(inputStr, &pos);
            if (pos == inputStr.length() && val >= 0.0) {
                data.unitPrice = val;
                break;
            }
            throw std::invalid_argument("Invalid numeric trailing characters");
        } catch (...) {
            std::cout << "Invalid price. Please enter a valid non-negative number.\n";
        }
    }

    while (true) {
        std::cout << "Quantity [" << data.quantity << "]: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        if (inputStr.empty()) break; 

        try {
            size_t pos = 0;
            int val = std::stoi(inputStr, &pos);
            if (pos == inputStr.length() && val > 0) {
                data.quantity = val;
                break;
            }
            throw std::invalid_argument("Invalid integer format");
        } catch (...) {
            std::cout << "Invalid quantity. Please enter a positive integer.\n";
        }
    }

    data.totalPrice = data.unitPrice * data.quantity;

    if (data.typeOfDiscount == "Senior" || data.typeOfDiscount == "PWD") {
        data.isDiscounted = true;
        data.discountedPercentage = 20.0;
        data.discountedPrice = data.totalPrice * 0.80;
    } else {
        data.isDiscounted = false;
        data.discountedPercentage = 0.0;
        data.discountedPrice = 0.0;
    }

    return data;
}

SalesData getSalesDataFromUser() {
    SalesData data;
    std::cout << "\n======================================================================\n";
    std::cout << "                        ENTER SALES DATA DETAILS                      \n";
    std::cout << "======================================================================\n";
    
    while (true) {
        std::cout << "Menu Item Name: ";
        std::getline(std::cin >> std::ws, data.menuItem);
        if (!data.menuItem.empty()) {
            std::string matchedName = validateAndFormatMenuItem(data.menuItem);
            if (!matchedName.empty()) {
                data.menuItem = matchedName;
                break;
            } else {
                std::cout << data.menuItem << " is not in menu. Try again.\n";
                continue;
            }
        }
        std::cout << "Input cannot be blank.\n";
    }

    while (true) {
        std::cout << "Temperature (Hot/Iced/NA): ";
        std::getline(std::cin, data.tempOfDrink);
        std::string lower = data.tempOfDrink;
        for (char &c : lower) c = std::tolower(c);

        if (lower == "hot") { data.tempOfDrink = "Hot"; break; }
        if (lower == "iced") { data.tempOfDrink = "Iced"; break; }
        if (lower == "n/a" || lower == "na") { data.tempOfDrink = "N/A"; break; }

        std::cout << "Invalid option. Enter 'Hot', 'Iced', or 'N/A'.\n";
    }

    while (true) {
        std::cout << "Size (Regular/Large): ";
        std::getline(std::cin, data.sizeOfItem);
        std::string lower = data.sizeOfItem;
        for (char &c : lower) c = std::tolower(c);

        if (lower == "regular" || lower == "reg") { data.sizeOfItem = "Regular"; break; }
        if (lower == "large") { data.sizeOfItem = "Large"; break; }

        std::cout << "Invalid size. Enter 'Regular' or 'Large'.\n";
    }

    while (true) {
        std::cout << "Type of Discount (Senior/PWD/None): ";
        std::getline(std::cin, data.typeOfDiscount);
        std::string lower = data.typeOfDiscount;
        for (char &c : lower) c = std::tolower(c);

        if (lower == "senior") { data.typeOfDiscount = "Senior"; break; }
        if (lower == "pwd") { data.typeOfDiscount = "PWD"; break; }
        if (lower == "none" || lower.empty()) { data.typeOfDiscount = "None"; break; }

        std::cout << "Invalid discount. Enter 'Senior', 'PWD', or 'None'.\n";
    }

    while (true) {
        std::cout << "Mode of Payment: ";
        std::getline(std::cin, data.modeOfPayment);
        if (!data.modeOfPayment.empty()) break;
        std::cout << "Input cannot be blank.\n";
    }

    while (true) {
        std::cout << "Date (YYYY-MM-DD): ";
        std::getline(std::cin, data.date);
        if (data.date.length() == 10 && data.date[4] == '-' && data.date[7] == '-') {
            break;
        }
        std::cout << "Invalid format. Please enter as YYYY-MM-DD.\n";
    }

    while (true) {
        std::cout << "Unit Price: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        try {
            size_t pos = 0;
            double val = std::stod(inputStr, &pos);
            if (pos == inputStr.length() && val >= 0.0) {
                data.unitPrice = val;
                break;
            }
            throw std::invalid_argument("Invalid double format");
        } catch (...) {
            std::cout << "Invalid price. Enter a valid non-negative number.\n";
        }
    }

    while (true) {
        std::cout << "Quantity: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        try {
            size_t pos = 0;
            int val = std::stoi(inputStr, &pos);
            if (pos == inputStr.length() && val > 0) {
                data.quantity = val;
                break;
            }
            throw std::invalid_argument("Invalid quantity format");
        } catch (...) {
            std::cout << "Invalid quantity. Enter a positive integer.\n";
        }
    }

    data.totalPrice = data.unitPrice * data.quantity;

    std::string lowerPayment = data.modeOfPayment;
    for (char &c : lowerPayment) c = std::tolower(c);

    if (lowerPayment == "cash") {
        data.referenceID = 0;
    } else {
        while (true) {
            std::cout << "Enter Reference ID: ";
            std::string inputStr;
            std::getline(std::cin, inputStr);
            try {
                size_t pos = 0;
                long long val = std::stoll(inputStr, &pos);
                if (pos == inputStr.length() && val >= 0) {
                    data.referenceID = val;
                    break;
                }
                throw std::invalid_argument("Invalid reference ID");
            } catch (...) {
                std::cout << "Invalid Reference ID. Enter a positive number.\n";
            }
        }
    }

    while (true) {
        std::cout << "Transaction ID: ";
        std::string inputStr;
        std::getline(std::cin, inputStr);
        try {
            size_t pos = 0;
            int val = std::stoi(inputStr, &pos);
            if (pos == inputStr.length() && val >= 0) {
                data.transactionID = val;
                break;
            }
            throw std::invalid_argument("Invalid transaction ID");
        } catch (...) {
            std::cout << "Invalid Transaction ID. Enter a positive integer.\n";
        }
    }

    if (data.typeOfDiscount == "Senior" || data.typeOfDiscount == "PWD") {
        data.isDiscounted = true;
        data.discountedPercentage = 20.0;
        data.discountedPrice = data.totalPrice * 0.80;
    } else {
        data.isDiscounted = false;
        data.discountedPercentage = 0.0;
        data.discountedPrice = 0.0;
    }

    return data;
}

void viewUnsavedChanges(CafeNode &head, const std::string& filename) {
    clearScreen();
    std::cout << "\n======================================================================\n";
    std::cout << "                        UNSAVED PENDING CHANGES                       \n";
    std::cout << "======================================================================\n";

    int count = getPendingCount();
    if (count == 0) {
        std::cout << " No pending changes to save.\n";
        std::cout << "======================================================================\n";
        std::cout << "Press Enter to return...";
        std::cin.get();
        return;
    }

    for (int i = 0; i < count; ++i) {
        PendingChanges change = getPendingChangeAt(i);
        std::cout << " [" << (i + 1) << "] " << change.details << "\n";
    }

    std::cout << "======================================================================\n";
    std::cout << "Options: [S]ave changes to file | [C]lear pending | [B]ack\n";
    std::cout << "Enter choice: ";
    std::string choice;
    std::getline(std::cin >> std::ws, choice);

    if (!choice.empty() && (choice[0] == 'S' || choice[0] == 's')) {
        saveChangesToFile(head, filename);
        clearPendingChanges();
        std::cout << "Press Enter to return...";
        std::cin.get();
    } else if (!choice.empty() && (choice[0] == 'C' || choice[0] == 'c')) {
        clearPendingChanges();
        std::cout << "Pending changes cleared without saving.\n";
        std::cout << "Press Enter to return...";
        std::cin.get();
    }
}

void auditMenuHandler(CafeNode& head, const std::string& filename) {
    int choice = 0;
    while (choice != 4) {
        clearScreen();
        std::cout << "\n======================================================================\n";
        std::cout << "                         INVENTORY OPERATIONS                         \n";
        std::cout << "======================================================================\n";
        std::cout << "[1] Insert New Record\n";
        std::cout << "[2] Update Existing Record\n";
        std::cout << "[3] Delete Record\n";
        std::cout << "[4] Return to Main Menu\n";
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Enter choice (1-4): ";

        if (!(std::cin >> choice) || choice < 1 || choice > 4) {
            std::cout << "Invalid option. Enter a number between 1 and 4.\n";
            clearInputBuffer();
            std::cout << "Press Enter to continue...";
            std::cin.get();
            continue;
        }

        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

        if (choice == 1) {
            SalesData newData = getSalesDataFromUser();
            int total = getTotalTransactions(head);
            int pos = 1;
            while (true) {
                std::cout << "Enter position to insert (1 to " << (total + 1) << "): ";
                if (std::cin >> pos && pos >= 1 && pos <= total + 1) {
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                    break;
                }
                std::cout << "Invalid position!\n";
                clearInputBuffer();
            }
            insertNode(head, newData, pos);
            std::cout << "Press Enter to continue...";
            std::cin.get();
        } 
        else if (choice == 2) {
            int total = getTotalTransactions(head);
            if (total == 0) {
                std::cout << "Inventory is empty!\n";
            } else {
                int pos = 1;
                while (true) {
                    std::cout << "Enter position to edit (1 to " << total << "): ";
                    if (std::cin >> pos && pos >= 1 && pos <= total) {
                        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                        break;
                    }
                    std::cout << "Invalid position!\n";
                    clearInputBuffer();
                }
                CafeNode current = head;
                for (int i = 1; i < pos && current != nullptr; ++i) {
                    current = current->next;
                }
                if (current != nullptr) {
                    SalesData updatedData = editSalesData(current->salesData);
                    updateNode(head, updatedData, pos);
                }
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        } 
        else if (choice == 3) {
            int total = getTotalTransactions(head);
            if (total == 0) {
                std::cout << "Inventory is empty!\n";
            } else {
                int pos = 1;
                while (true) {
                    std::cout << "Enter position to delete (1 to " << total << "): ";
                    if (std::cin >> pos && pos >= 1 && pos <= total) {
                        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                        break;
                    }
                    std::cout << "Invalid position!\n";
                    clearInputBuffer();
                }
                CafeNode current = head;
                for (int i = 1; i < pos && current != nullptr; ++i) {
                    current = current->next;
                }
                if (current != nullptr) {
                    std::cout << "\n Are you sure you want to delete record " << pos 
                              << " (" << current->salesData.menuItem << " - " << current->salesData.date << ")? (Y/N): ";
                    
                    char confirmChar;
                    std::cin >> confirmChar;
                    confirmChar = std::toupper(confirmChar);
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');

                    if (confirmChar == 'Y' || confirmChar == 'y') {
                        deleteNode(head, pos);
                    } else {
                        std::cout << "\n Deletion cancelled. Record was retained.\n";
                    }
                }
            }
            std::cout << "Press Enter to continue...";
            std::cin.get();
        }
    }
}