#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include "Node.h"
#include "Sort.h"
#include "AuditList.h"

const int MAX_LEVEL = 10; //Max 10 row

struct SkipNode {
    std::string key;                
    CafeNode targetNode;            
    SkipNode** forward;            

    SkipNode(std::string key, CafeNode node, int level) {
        this->key = key;
        this->targetNode = node;
        this->forward = new SkipNode*[level + 1];
        for (int i = 0; i <= level; i++) {
            this->forward[i] = nullptr;
        }
    }

    ~SkipNode() {
        delete[] forward;
    }
};

class MenuSkip {
private:
    int maxLevel;
    float p;
    int currentLevel;
    SkipNode* header;

    int randomLevel();
    std::string toLower(const std::string& str) const;

public:
    MenuSkip(int maxLvl = MAX_LEVEL, float prob = 0.5f);
    ~MenuSkip();

    void insert(const std::string& key, CafeNode node);
    void buildFromList(CafeNode head);

    CafeNode searchExact(const std::string& query);
    void searchSubString(CafeNode head, const std::string& query, CafeNode& searchHead, int& matchCount);
    void freeSearchResults(CafeNode searchHead);
};

void printSearchPurchase(CafeNode mainHead, MenuSkip& skipList);