#include "hashTable.h"

using namespace std;

hashTable::hashTable(int n)
{
    this->m = n;
    this->error = Account("NOT FOUND", "NOT FOUND", "NOT FOUND", 0, 0);
    this->table = vector<vector<Account>>(n);
}

void hashTable::insert(Account account)
{
    table[hasher(account.getUsername())].push_back(account);
}

void hashTable::remove(Account account)
{
    int j = hasher(account.getUsername());
    for (unsigned int i = 0; i < table[j].size(); i++)
        if (table.at(j)[i].getUsername() == account.getUsername())
            table.at(j).erase(table.at(j).begin() + i);
}

const Account& hashTable::search(string username)
{
    auto begin = std::chrono::high_resolution_clock::now();
    int j = hasher(username);
    for (unsigned int i = 0; i < table[j].size(); i++)
        if (table.at(j)[i].getUsername() == username)
        {
            auto end = std::chrono::high_resolution_clock::now();
            this->time = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            return table.at(j)[i];
        }
    return this->error;
}

Account& hashTable::getRef(string username)
{
    int j = hasher(username);
    for (unsigned int i = 0; i < table[j].size(); i++)
        if (table.at(j)[i].getUsername() == username)
            return table.at(j)[i];
}

int hashTable::hasher(string username)
{
    int i = 0;
    for (char ch : username)
        i += ch;
    return i % m;
}

chrono::duration<long long, ratio<1, 1000000000>> hashTable::getTime()
{
    return this->time;
}