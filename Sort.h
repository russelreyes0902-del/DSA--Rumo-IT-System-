#pragma once
#include <string>
#include "Node.h"
#include "AuditList.h"
#include "Search.h"

void swapNode(CafeNode &head, CafeNode node1, CafeNode node2); // swapNode function

int parseDate(const std:: string& dateStr);

CafeNode partition(CafeNode &head, CafeNode low, CafeNode high, bool ascending);

void quickSort(CafeNode &head, CafeNode low, CafeNode high, bool ascending) ;
