#include "Account.h"

using namespace std;

Account::Account()
{
	this->username = "";
	this->password = "";
	this->fullName = "";
	this->logins = 0;
	this->balance = 0.00;
}

Account::Account(string username, string password, string fullName, unsigned int logins, double balance) {
	this->username = username;
	this->password = password;
	this->fullName = fullName;
	this->logins = logins;
	this->balance = balance;
	this->personalAcc.push_back(personalAccount(this->balance, "Checkings"));
}

string Account::getUsername()
{
	return this->username;
}

unsigned int Account::getLogins() {
	return this->logins;
}

string Account::getName()
{
	return this->fullName;
}

double Account::getBalance()
{
	return this->balance;
}

string Account::getPassword()
{
	return this->password;
}

vector<pair<unsigned int, pair<double, string>>> Account::getTransactionList()
{
	return this->transactionList;
}

void Account::updateBalance(double amount, string username)
{
	this->balance += amount;
	this->transactionList.push_back(make_pair(time(0), make_pair(amount, username)));
}

void Account::addTransaction(double amount, string username) {
	this->transactionList.push_back(make_pair(time(0), make_pair(amount, username)));
}

void Account::createPersonalAccount(string name, double balance) {
	personalAccount p;
	p.balance = balance;
	p.name = name;
	personalAcc.push_back(p);
}

void Account::deleteAccount(string name) {
	int n = personalAcc.size();
	if (personalAcc[n-1].name == name) {
		personalAcc.pop_back();
	}
	for (unsigned int i = 0; i < personalAcc.size() - 1; i++) {
		if (personalAcc[i].name == name) {
			swap(personalAcc[i], personalAcc[n - 1]);
			personalAcc.pop_back();
			break;
		}
	}
}

void Account::personalAccount::changeBalance(double amount, string username) 
{
	this->balance += amount;
	this->paTransactionList.push_back(make_pair(time(0), make_pair(amount, username)));
}

void Account::personalAccount::renameAccount(string newname) {
	this->name = newname;
}
Account::personalAccount::personalAccount()
{
	this->name = "";
	this->balance = 0.0;
}

Account::personalAccount::personalAccount(double amount, string name)
{
	this->name = name;
	this->balance = amount;
}

int Account::searchByName(string name) 
{
	for (unsigned int i = 0; i < personalAcc.size(); i++)
		if (personalAcc[i].name == name) 
			return i;
}

void Account::paTransfer(double amount, string from, string to) 
{
	personalAcc[searchByName(from)].changeBalance(amount, to);
	personalAcc[searchByName(to)].changeBalance(amount * -1, from);
}

void Account::incrementLogins()
{
	this->logins++;
}

void Account::updateTotalBalance(double amount)
{
	this->balance += amount;
}