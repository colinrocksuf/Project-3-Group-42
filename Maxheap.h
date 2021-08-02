#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <vector>
#include <utility>
#include <iostream>
#include <chrono>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "Account.h"

class Maxheap {
public:
	void heapify(int i);
	void insertNode(Account& account);
	void printHeap();
	int returnIndex(Account& account);
	Account searchName(string userName);
	chrono::duration<long long, ratio<1, 1000000000>> getTime();
private:
	chrono::duration<long long, ratio<1, 1000000000>> time;
	vector<Account> heap;
};

#endif