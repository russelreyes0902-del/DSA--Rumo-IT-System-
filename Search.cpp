#include "Search.h"
#include "Sort.h"
#include <iomanip>

//Random level generator for Skip List
int MenuSkip::randomLevel() {
    int lvl = 0;
    while ((float)rand() / RAND_MAX < p && lvl < maxLevel) {
        lvl++;
    }
    return lvl;
}

std::string MenuSkip::toLower(const std::string& str) const {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(),
                   [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

MenuSkip::MenuSkip(int maxLvl, float prob) 
    : maxLevel(maxLvl), p(prob), currentLevel(0) {
    header = new SkipNode("", nullptr, maxLevel);
}

MenuSkip::~MenuSkip() {
    SkipNode* currentNode = header;
    while (currentNode != nullptr) {
        SkipNode* nextNode = currentNode->forward[0];
        delete currentNode;
        currentNode = nextNode;
    }
}

void MenuSkip::insert(const std::string& key, CafeNode node) {
    //Store pointers to nodes that need updates per level
    SkipNode** update = new SkipNode*[maxLevel + 1];
    SkipNode* currentNode = header;

    std::string lowerKey = toLower(key);

    //Traverse the Skip List to find the position for insertion
    for (int i = currentLevel; i >= 0; i--) {
        while (currentNode->forward[i] != nullptr && toLower(currentNode->forward[i]->key) < lowerKey) {
            currentNode = currentNode->forward[i];
        }
        update[i] = currentNode;
    }

    currentNode = currentNode->forward[0];

    //Random level for the new node
    int rLevel = randomLevel();
    if (rLevel > currentLevel) {
        for (int i = currentLevel + 1; i <= rLevel; i++) {
            update[i] = header;
        }
        currentLevel = rLevel;
    }

    SkipNode* newNode = new SkipNode(key, node, rLevel);
    for (int i = 0; i <= rLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }

    delete[] update;
}

void MenuSkip::buildFromList(CafeNode head) {
    CafeNode currentNode = head;
    while (currentNode != nullptr) {
        insert(currentNode->salesData.menuItem, currentNode);
        currentNode = currentNode->next;
    }
}

//Exact search for a menuItem
CafeNode MenuSkip::searchExact(const std::string& query) {
    SkipNode* currentNode = header;
    std::string lowerQuery = toLower(query);

    for (int i = currentLevel; i >= 0; i--) {
        while (currentNode->forward[i] != nullptr && toLower(currentNode->forward[i]->key) < lowerQuery) {
            currentNode = currentNode->forward[i];
        }
    }

    currentNode = currentNode->forward[0];
    if (currentNode != nullptr && toLower(currentNode->key) == lowerQuery) {
        return currentNode->targetNode;
    }
    return nullptr;
}

//Substring search for menuItem
void MenuSkip::searchSubString(CafeNode head, const std::string& query, CafeNode& searchHead, int& matchCount) {
    searchHead = nullptr;
    matchCount = 0;
    if (query.empty()) return;

    std::string lowerQuery = toLower(query);
    CafeNode currentNode = head;
    CafeNode lastSearchResult = nullptr;

    while (currentNode != nullptr) {
        std::string lowerItem = toLower(currentNode->salesData.menuItem);
        if (lowerItem.find(lowerQuery) != std::string::npos) {
            CafeNode newSearchNode = new Node(
                currentNode->salesData.menuItem, 
                currentNode->salesData.tempOfDrink, 
                currentNode->salesData.sizeOfItem,
                currentNode->salesData.typeOfDiscount, 
                currentNode->salesData.modeOfPayment, 
                currentNode->salesData.date,
                currentNode->salesData.totalPrice, 
                currentNode->salesData.unitPrice, 
                currentNode->salesData.quantity,
                currentNode->salesData.referenceID, 
                currentNode->salesData.transactionID,
                currentNode->salesData.discountedPrice, 
                currentNode->salesData.discountedPercentage,
                currentNode->salesData.isDiscounted, 
                matchCount + 1
            );

            if (searchHead == nullptr) {
                searchHead = newSearchNode;
            } else {
                lastSearchResult->next = newSearchNode;
                newSearchNode->prev = lastSearchResult;
            }
            lastSearchResult = newSearchNode;
            matchCount++;
        }
        currentNode = currentNode->next;
    }
}

CafeNode MenuSkip::searchAllExact(
    const std::string& query,
    int& matchCount) {

    if (query.empty()) return nullptr;
    
    SkipNode* currentNode = header;
    std::string lowerQuery = toLower(query);

    for (int i = currentLevel; i >= 0; i--) {
        while (currentNode->forward[i] != nullptr && toLower(currentNode->forward[i]->key) < lowerQuery) {
                currentNode = currentNode->forward[i];
            }
    }

    currentNode = currentNode->forward[0];

    CafeNode resultHead = nullptr;
    CafeNode resultTail = nullptr;

    while (currentNode != nullptr && toLower(currentNode->key) == lowerQuery) {
        SalesData data = currentNode->targetNode->salesData;
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
            matchCount + 1            
        );

        if (resultHead == nullptr) {
            resultHead = newNode;
            resultTail = newNode;
        }
        else {
            resultTail->next = newNode;
            newNode->prev = resultTail;
            resultTail = newNode;
        }

        matchCount++;
        currentNode = currentNode->forward[0];
    }

    return resultHead;
}

void MenuSkip::freeSearchResults(CafeNode searchHead) {
    CafeNode currentNode = searchHead;
    while (currentNode != nullptr) {
        CafeNode nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
}

void printSearchPurchase(CafeNode mainHead, MenuSkip& skipList) {
    std::string searchQuery;
    std::cout << "\n======================================================================\n";
    std::cout << "                      RUMO-IT AUDIT SYSTEM - SEARCH                   \n";
    std::cout << "======================================================================\n";
    std::cout << "Enter Search Query (Menu Item): ";
    std::getline(std::cin >> std::ws, searchQuery);

    CafeNode searchHead = nullptr;
    int matchCount = 0;

    searchHead = skipList.searchAllExact(searchQuery, matchCount);

    if (matchCount == 0) {
        skipList.searchSubString(mainHead, searchQuery, searchHead, matchCount);
    }

    if (matchCount == 0) {
        std::cout << "\nNo transactions matching \"" << searchQuery << "\".\n";
        std::cout << "Press Enter to return...";
        std::cin.get();
        return;
    }

    promptAndSort(searchHead);

    int pageSize = 10;
    int currentPage = 1;
    int totalPages = (matchCount + pageSize - 1) / pageSize;
    char choice;

    do {
        clearScreen();
        CafeNode current = searchHead;
        int skipCount = (currentPage - 1) * pageSize;
        for (int i = 0; i < skipCount && current != nullptr; i++) {
            current = current->next;
        }

        std::cout << "\n================================================================================================================================\n";
        std::cout << "                                                    RUMO-IT AUDIT SYSTEM\n";
        std::cout << "================================================================================================================================\n";
        std::cout << "  Search: \"" << searchQuery << "\"                                                              [" << matchCount << " Matches Found]\n";
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";
        std::cout << "Date       | Menu Item                    | Size   | Temp | Qty | Unit Price | Total Price | Payment Mode | Disc % | Disc Price \n";
        std::cout << "--------------------------------------------------------------------------------------------------------------------------------\n";

        int printedCount = 0;
        int startRecord = skipCount + 1;

        while (current != nullptr && printedCount < pageSize) {
            std::string dateDisplay = current->salesData.date;
            if (dateDisplay == "") {
                dateDisplay = "-";
            }

            // Full menu item name (no truncation)
            std::string itemDisplay = current->salesData.menuItem;

            std::string sizeDisplay = current->salesData.sizeOfItem;
            if (sizeDisplay == "" || sizeDisplay == "None" || sizeDisplay == "N/A") {
                sizeDisplay = "-";
            }
            if (sizeDisplay.length() > 6) {
                sizeDisplay = sizeDisplay.substr(0, 5) + ".";
            }

            std::string tempDisplay = current->salesData.tempOfDrink;
            if (tempDisplay == "" || tempDisplay == "None" || tempDisplay == "N/A") {
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
        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Displaying records " << startRecord << "-" << endRecord << " of " << matchCount << "\n";
        std::cout << "======================================================================\n";
        std::cout << "Controls: ";
        if (currentPage < totalPages) std::cout << "[N]ext  ";
        if (currentPage > 1)          std::cout << "[P]revious  ";
        std::cout << "[G]o to Page  [C]lear Search / Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;

        if ((choice == 'N' || choice == 'n') && currentPage < totalPages) currentPage++;
        else if ((choice == 'P' || choice == 'p') && currentPage > 1) currentPage--;
        else if (choice == 'G' || choice == 'g') {
            int targetPage;
            std::cout << "Enter page number (1-" << totalPages << "): ";
            if (!(std::cin >> targetPage)) {
                std::cin.clear();
                std::cin.ignore(10000, '\n');
                std::cout << "Invalid input! Must be a number. Press Enter...";
                std::cin.get();
            } 
            else if (targetPage >= 1 && targetPage <= totalPages) currentPage = targetPage;
        }
    } while (choice != 'C' && choice != 'c' && choice != 'E' && choice != 'e');

    skipList.freeSearchResults(searchHead);
}