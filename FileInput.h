#pragma once
#include <string>
#include "Node.h"

void loadMenuData(const std:: string &filename);
void loadAuditData(const std:: string &filename, CafeNode &head, int maxRecords = 0);

//loads the menu data and audit data
