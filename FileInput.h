#pragma once
#include <string>
#include "Node.h"

void loadMenuData(const std:: string &filename);
void loadAuditData(const std:: string &filename, CafeNode &head, int maxBatch = 100);

//loads the menu data and audit data
//max records set to 100 so that the program doesn't crash when reading the audit data file. It will read it by batch of 100. 
