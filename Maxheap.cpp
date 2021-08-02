#include "Maxheap.h"

void Maxheap::heapify(int i)
{
	int parent = ((i - 2) / 2);
	if (parent >= 0)
	{
		if (heap[i].getLogins() > heap[parent].getLogins())
		{
			swap(heap[i], heap[parent]);
			heapify(parent);
		}
	}
}

void Maxheap::insertNode(Account& account)
{
	heap.push_back(account);
	heapify((heap.size() - 1));
}

void Maxheap::printHeap()
{
	for (unsigned int i = 0; i < heap.size(); i++)
		cout << heap[i].getUsername() << " " << heap[i].getLogins() << endl;
	cout << "--------------------------------------" << endl;
}

int Maxheap::returnIndex(Account& account)
{
	for (unsigned int i = 0; i < heap.size(); i++)
		if (heap[i].getUsername() == account.getUsername())
			return i;
	return 0;
}

Account Maxheap::searchName(string userName)
{
	auto begin = std::chrono::high_resolution_clock::now();
	for (unsigned int i = 0; i < heap.size(); i++)
	{
		if (heap[i].getUsername() == userName)
		{
			auto end = std::chrono::high_resolution_clock::now();
			this->time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
			return heap[i];
		}
	}
	return heap[0];
}

chrono::duration<long long, ratio<1, 1000000000>> Maxheap::getTime()
{
	return this->time;
}