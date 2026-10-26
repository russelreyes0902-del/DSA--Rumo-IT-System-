#include "Node.h"
#include "Search.h"
#include "Sort.h"
#pragma once

CafeNode tail(CafeNode &head);

std::string convertMonthToNumber(std::string monthInput);

int getDailyItemsSold(
    CafeNode &head, 
    std::string targetDay, 
    std::string targetItem = ""
    );

int getMonthyItemsSold(
    CafeNode &head, 
    std::string monthInput, 
    std::string targetYear, 
    std::string targetItem = ""
    );

int getYearlyItemsSold(CafeNode &head, 
    std::string targetYear, 
    std::string targetItem = ""
    );