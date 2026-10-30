#include <iostream>
#include "Node.h"
#include "AuditList.h"
#include "FileInput.h"

void printRecentPurchase(CafeNode &head);

int main (){
    CafeNode head = nullptr;
    loadMenuData("menu_data.csv");
    loadAuditData("audit_data.csv", head, 100);
    printRecentPurchase(head);

    return 0;
}