#pragma once
#include "Node.h"
#include <string>

struct PendingChanges {
    std::string type;
    int index;
    std::string details;
    SalesData data;
    SalesData oldData;
};

void insertNode(Node*& head, const SalesData& newItem, int position);
void updateNode(Node*& head, const SalesData& data, int position);
void deleteNode(Node*& head, int position);

void saveChangesToFile(Node* head, const std::string& filename);
bool hasUnsavedChanges();

int getPendingCount();
PendingChanges getPendingChangeAt(int index);
void addPendingChange(const std::string& type, const std::string& detail);
void removePendingChangeAt(int index);
void clearPendingChanges();

