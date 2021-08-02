#pragma once
#include <vector>
#include <ctime>
#include <utility>
#include <iostream>
#include <string>

using namespace std;

class Account
{
public:
	struct personalAccount
	{
		string name;
		double balance;
		vector<pair<unsigned int, pair<double, string>>> paTransactionList;
		void renameAccount(string newname);
		void changeBalance(double amount, string username);
		personalAccount();
		personalAccount(double amount, string name);
		
	};
	Account();
	Account(string username, string password, string fullName, unsigned int logins, double balance);
	unsigned int getLogins();
	void updateBalance(double amount, string username);
	string getUsername();
	string getName();
	double getBalance();
	string getPassword();
	vector<pair<unsigned int, pair<double, string>>> getTransactionList();
	void addTransaction(double amount, string username);
	void createPersonalAccount(string name, double balance);
	void deleteAccount(string name);
	vector<personalAccount> personalAcc;
	int searchByName(string name);
	void paTransfer(double amount, string from, string to);
	void incrementLogins();
	void updateTotalBalance(double amount);

private:
	string username;
	string password;
	string fullName;
	unsigned int logins;
	vector<pair<unsigned int, pair<double, string>>> transactionList;
	double balance;
};