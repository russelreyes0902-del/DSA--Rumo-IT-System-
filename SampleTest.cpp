#include <iostream>
#include "Node.h"
#include "AuditList.h"
#include "FileInput.h"
#include "Sort.h"
#include "Search.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main () {
#ifdef _WIN32
    SetConsoleOutputCP(65001); // Enables UTF-8 symbol display (₱)
#endif

    CafeNode head = nullptr;
    loadMenuData("menu_data.csv");
    loadAuditData("audit_data.csv", head);
    
    printRecentPurchase(head);

    return 0;
}