#pragma once
#include "Node.h"
//#include "Search.h"
//#include "Sort.h"
#include <iomanip>
#include <iostream>

void clearScreen();

CafeNode tail(CafeNode &head);

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

void printRecentPurchase(CafeNode &head);