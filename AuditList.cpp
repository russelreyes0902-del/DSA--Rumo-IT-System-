#include "Node.h"
#include "Search.h"
#include "Sort.h"
#pragma once

// Use this file for Node purposes, i.e accessing node at position x, 
// updating node at position x, deleting and insertion of nodes.
CafeNode tail(CafeNode &head) {
    if (head == nullptr) return nullptr;
    CafeNode temp = head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }
    return temp;
}

std::string convertMonthToNumber(std::string monthInput) {  

    if (monthInput == "January" || 
        monthInput == "january" || 
        monthInput == "Jan" || 
        monthInput == "01" || 
        monthInput == "1") {
        return "01";
    } 
    else if (monthInput == "February" || 
            monthInput == "february" || 
            monthInput == "Feb" || 
            monthInput == "02" || 
            monthInput == "2") {
        return "02";
    } 
    else if (monthInput == "March" || 
            monthInput == "march" || 
            monthInput == "Mar" || 
            monthInput == "03" || 
            monthInput == "3") {
        return "03";
    } 
    else if (monthInput == "April" || 
            monthInput == "april" || 
            monthInput == "Apr" || 
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
            monthInput == "06" || 
            monthInput == "6") {
        return "06";
    } 
    else if (monthInput == "July" || 
            monthInput == "july" || 
            monthInput == "Jul" || 
            monthInput == "07" || 
            monthInput == "7") {
        return "07";
    } 
    else if (monthInput == "August" || 
            monthInput == "august" || 
            monthInput == "Aug" || 
            monthInput == "08" || 
            monthInput == "8") {
        return "08";
    } 
    else if (monthInput == "September" || 
            monthInput == "september" || 
            monthInput == "Sep" || 
            monthInput == "09" || 
            monthInput == "9") {
        return "09";
    } 
    else if (monthInput == "October" || 
            monthInput == "october" || 
            monthInput == "Oct" || 
            monthInput == "10") {
        return "10";
    } 
    else if (monthInput == "November" || 
            monthInput == "november" || 
            monthInput == "Nov" || 
            monthInput == "11") {
        return "11";
    } 
    else if (monthInput == "December" || 
            monthInput == "december" || 
            monthInput == "Dec" || 
            monthInput == "12") {
        return "12";
    } 
    else {
        return "00"; // Return invalid code if input doesn't match
    }
}
//Statistics function to get the amount of items sold in a single day.
int getDailyItemsSold(
    CafeNode &head, 
    std::string targetDay, 
    std::string targetItem = ""
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
            if (targetItem == "" || current->salesData.menuItem == targetItem) {
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
    std::string targetItem = ""
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
            if (targetItem == "" || current->salesData.menuItem == targetItem) {
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
    std::string targetItem = ""
    ) {
        
    if (head == nullptr) return 0;
    CafeNode current = head;
    int totalItemsSold = 0;

    while (current != nullptr) {
        std::string nodeYear = current->salesData.date.substr(6,4);
        if (nodeYear == targetYear) {
            if (targetItem == "" || current->salesData.menuItem == targetItem) {
                totalItemsSold+= current->salesData.quantity;
            }
        }
    }
    return totalItemsSold;
}