#pragma once
#include <string>
#include "Node.h"
#include "Search.h"
#include "Sort.h"

void clearScreen();

CafeNode tail(CafeNode &head);
CafeNode getMiddleNode(CafeNode low, CafeNode high);

std::string convertMonthToNumber(std::string monthInput);

int getTotalTransactions(CafeNode &head);

int getDailyItemsSold(
    CafeNode &head, 
    std::string targetDay, 
    std::string targetItem = "", 
    std::string targetSize = ""
);

int getMonthlyItemsSold(
    CafeNode &head, 
    std::string monthInput, 
    std::string targetYear, 
    std::string targetItem = "",
    std::string targetSize = ""
);

int getYearlyItemsSold(
    CafeNode &head, 
    std::string targetYear, 
    std::string targetItem = "",
    std::string targetSize = ""
);

void printPaginatedPurchases(CafeNode &head, const std::string& title, int maxRecords);
void printRecentPurchase(CafeNode &head);
void printAllPurchases(CafeNode &head, const std::string& title = "ALL PURCHASES");
void printSummaryStatistics(CafeNode &head);

SalesData editSalesData(const SalesData& currentData);
SalesData getSalesDataFromUser();

void viewUnsavedChanges(CafeNode &head, const std::string& filename);
void auditMenuHandler(CafeNode& head, const std::string& filename);