#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <chrono>
#include <ctime>
#include "Account.h"

using namespace std;

class hashTable
{
    int m;
    chrono::duration<long long, ratio<1, 1000000000>> time;
    Account error;
    vector<vector<Account>> table;
public:
    hashTable(int n);
    void insert(Account account);
    void remove(Account account);
    const Account& search(string username);
    Account& getRef(string username);
    int hasher(string username);
    chrono::duration<long long, ratio<1, 1000000000>> getTime();
};

#endif