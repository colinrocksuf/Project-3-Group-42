#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <time.h>
#include "Account.h"
#include "hashTable.h"
#include "Maxheap.h"

using namespace std;

int main()
{
    hashTable table(100000);
    Maxheap maxheap;

    //get from csv
    ifstream inFile("database.csv");
    string lineFromFile;
    getline(inFile, lineFromFile);
    int count = 0;
    if (inFile.is_open())
    {
        while (getline(inFile, lineFromFile) && count < 100000)
        {
            string readUsername = "";
            string tempPassword = "";
            string readName = "";
            string tempLogins = " ";
            unsigned int readLogins = 0;
            string tempBalance = "";
            double readBalance = 0;
            string tempTransactionAmount = "";
            int readTransactionAmount = 0;

            istringstream stream(lineFromFile);

            getline(stream, readUsername, ',');
            getline(stream, tempPassword, ',');
            getline(stream, readName, ',');
            getline(stream, tempLogins, ',');
            readLogins = stoi(tempLogins);
            getline(stream, tempBalance, ',');
            readBalance = stod(tempBalance);
            getline(stream, tempTransactionAmount, ',');
            readTransactionAmount = stoi(tempTransactionAmount);

            //create new account object
            Account account = Account(readUsername, tempPassword, readName, readLogins, readBalance);
            table.insert(account);
            maxheap.insertNode(account);
            count++;
        }
    }
    cout << "Welcome to COOL BANK\n\nWhat would you like to do?\n0. Quit\n1. Login\n2. Register\n\n";
    int i = 100;
    string j = "100";
    cin >> i;
    Account target;
    Account::personalAccount paTarget;
    while (i != 0)
    {
        system("CLS");

        switch (i)
        {
            case 0:
            {
                i = 0;
                break;
            }
            case 3:
            {
                cout << "Welcome to COOL BANK\n\nWhat would you like to do?\n0. Quit\n1. Login\n2. Register\n\n";
                cin >> i;
                break;
            }
            case 1:
            {
                //login stuff
                string name, password;
                cout << "Username: ";
                cin >> name;
                cout << "Password: ";
                cin >> password;
                cout << endl;
                target = table.search(name);

                if (target.getUsername() == "NOT FOUND" || target.getPassword() != password)
                {
                    cout << "Error: Invalid password or username not found.\nEnter any number to continue.\n";
                    cin >> j;
                    i = 1; // get it to go again
                    break;
                }
                target.incrementLogins();
                maxheap.heapify(maxheap.returnIndex(target));
                i = 11;
                break;
            }
            case 2:
            {
                //register
                string username, password, firstName, lastName, tempBalance;
                double balance;
                cout << "First Name: ";
                cin >> firstName;
                cout << "Last Name: ";
                cin >> lastName;
                string name = firstName + " " + lastName;
                cout << "Username: ";
                cin >> username;
                cout << "Password: ";
                cin >> password;
                cout << "Starting Balance: $";
                cin >> tempBalance;
                balance = stod(tempBalance);
                while (balance < 0)
                {
                    cout << "Re-enter positive amount: ";
                    cin >> balance;
                }
                cout << endl;
                target = Account(username, password, name, 0, balance);
                table.insert(target);
                maxheap.insertNode(target);
                maxheap.heapify(maxheap.returnIndex(target));
                i = 11;
                break;
            }
            case 11:
            {
                //account homepage
                table.search(target.getUsername());
                maxheap.searchName(target.getUsername());
                printf("Found using hash table lookup in %.6f seconds.\n", table.getTime().count() * 1e-9);
                printf("Found using max heap lookup in %.6f seconds.\n\n", maxheap.getTime().count() * 1e-9);
                cout << "COOL BANK" << endl << endl;
                cout << "Hello " << target.getName() << endl;
                cout << "Your total account balance is currently $" << target.getBalance() << "\n";
                cout << "What would you like to do?\n1. View Accounts\n2. Create an Account\n3. Log Out\n\n";
                cin >> i;
                //Changed numbering system for readability
                if (i == 1)
                    i = 7;
                else if (i == 2)
                    i = 6;


                break;
            }
            case 4:
            {
                //history page
                cout << "Current account: " << paTarget.name << endl << endl;
                cout << "Welcome to your transaction history!\n\n";
                int count = 0;
                for (pair<unsigned int, pair<double, string>> p : target.personalAcc[target.searchByName(paTarget.name)].paTransactionList)
                {
                    string tf = "";
                    if (p.second.first < 0)
                        tf = " - to ";
                    else
                        tf = " - from ";
                    struct tm date;
                    time_t t = p.first;
                    localtime_s(&date, &t);
                    cout << "On " << (date.tm_year + 1900) << '-' << (date.tm_mon + 1) << '-' << date.tm_mday << " at " << date.tm_hour << ":" << date.tm_min;
                    cout << tf << p.second.second << " : $" << fabs(p.second.first) << endl;
                    count++;
                }
                if (count == 0)
                {
                    cout << "No transactions have been made." << endl;
                }
                cout << endl;
                cout << "Enter any number to continue. " << endl;
                cin >> j;
                i = 7;
                break;
            }
            case 5:
            {
                //make transaction
                cout << "Current account: " << paTarget.name << endl << endl;
                cout << "Enter the username of the account you wish to make a transaction with: ";
                string transferTo;
                cin >> transferTo;
                Account transferToward = table.search(transferTo);
                while (transferToward.getUsername() == "NOT FOUND")
                {
                    cout << "Account not found. Re-enter username: ";
                    cin >> transferTo;
                    transferToward = table.search(transferTo);
                }
                cout << endl;
                string withdrawAcc;
                cout << "Enter the amount you wish to send: $";
                string tempBalanceChange;
                cin >> tempBalanceChange;
                double balanceChange;
                balanceChange = stod(tempBalanceChange);

                while (balanceChange <= 0)
                {
                    cout << "Re-enter positive amount: ";
                    cin >> balanceChange;
                }
                while (balanceChange > target.personalAcc[target.searchByName(paTarget.name)].balance)
                {
                    cout << "Insufficient funds" << endl;
                    cout << "Enter a correct amount: " << endl;
                    cin >> balanceChange;
                }
                transferToward.personalAcc[0].changeBalance(balanceChange, target.getName());
                table.getRef(transferToward.getUsername()) = transferToward;
                target.personalAcc[target.searchByName(paTarget.name)].changeBalance(balanceChange * -1, transferToward.getName());
                target.updateTotalBalance(balanceChange * -1);
                table.getRef(transferTo).updateTotalBalance(balanceChange);
                table.getRef(target.getUsername()) = target;

                cout << "Enter any number to continue" << endl;
                cin >> j;
                i = 11;
                break;
            }
            case 13:
            {
                //make transaction
                cout << "Current account: " << paTarget.name << endl << endl;
                cout << "Enter the name of the account you wish to transfer to: ";
                string transferTo;
                cin >> transferTo;
                cout << endl;
                cout << "Enter the amount you wish to transfer: ";
                string tempBalanceChange;
                cin >> tempBalanceChange;
                double balanceChange;
                balanceChange = stod(tempBalanceChange);
                while (balanceChange <= 0)
                {
                    cout << "Re-enter positive amount: ";
                    cin >> balanceChange;
                }
                while (balanceChange > target.personalAcc[target.searchByName(paTarget.name)].balance)
                {
                    cout << "Insufficient funds" << endl;
                    cout << "Enter a correct amount: " << endl;
                    cin >> balanceChange;
                    //break;
                }
                target.personalAcc[target.searchByName(transferTo)].changeBalance(balanceChange, paTarget.name);
                target.personalAcc[target.searchByName(paTarget.name)].changeBalance(balanceChange * -1, target.personalAcc[target.searchByName(transferTo)].name);
                table.getRef(target.getUsername()) = target;

                cout << "Enter any number to continue" << endl;
                cin >> j;
                i = 11;
                break;
            }
            case 6:
            {
                //create personal account
                cout << "Name of account: ";
                string accName;
                cin >> accName;
                cout << "Balance: ";
                string tempBalance;
                double balance;
                cin >> tempBalance;
                balance = stod(tempBalance);
                //create and push back personal acc
                while (balance > target.personalAcc[0].balance) 
                {
                    cout << "Insufficient funds\nEnter a correct amount: ";
                    cin >> tempBalance;
                    balance = stod(tempBalance);
                }
                target.createPersonalAccount(accName, 0);
                target.personalAcc[target.searchByName(accName)].changeBalance(balance, "Checkings");
                target.personalAcc[0].changeBalance(balance * -1, target.personalAcc[target.searchByName(accName)].name);
                table.getRef(target.getUsername()) = target;
                //send back to acc page
                i = 11;
                break;
            }
            case 7:
            {
                int count = 0;
                //edit personal account
                cout << "Which account would you like to view?\n";
                for (unsigned int k = 0; k < target.personalAcc.size(); k++) {
                    cout << k + 1 << ". " << target.personalAcc[k].name << " : $" << target.personalAcc[k].balance << endl;
                }
                cout << "Please enter the name or 'back': ";
                string name;
                bool found = false;
                cin >> name;
                cout << endl;
                if (name == "back")
                {
                    i = 11;
                    break;
                }
                else
                {
                    for (unsigned int k = 0; k < target.personalAcc.size(); k++)
                    {
                        if (target.personalAcc[k].name == name)
                        {
                            found = true;
                            paTarget = target.personalAcc[k];
                            break;
                        }
                    }
                    if (found == true) {
                        cout << endl;
                        system("CLS");
                        cout << "Current account: " << paTarget.name << endl << endl;
                        cout << "What would you like to do?\n\n1. Send money\n2. Transfer money to another account\n3. View Transaction History\n";
                        if (paTarget.name != "Checkings")
                        {
                            cout << "4. Rename Account\n5. Delete Account\n";
                        }
                        cout << "6. Go Back\n\n";
                        cin >> i;
                        //Renumbered for readability
                        if (i == 1)
                            i = 5;
                        else if (i == 2)
                            i = 13;
                        else if (i == 3)
                            i = 4;
                        else if (i == 4)
                            i = 8;
                        else if (i == 5)
                            i = 9;
                        else if (i == 6)
                            i = 11;

                        break;
                    }
                    else {
                        cout << "Account not found" << endl;
                        cout << "Enter any number to continue" << endl;
                        cin >> j;
                        break;
                    }
                }
            }
            case 8:
            {
                cout << "Current account: " << paTarget.name << endl << endl;
                string temp = paTarget.name;
                cout << "Enter new name: ";
                string name;
                cin >> name;
                for (int k = 0; k < target.personalAcc.size(); k++) 
                    if (temp == target.personalAcc[k].name) 
                        target.personalAcc[k].name = name;
                cout << "Balance for " << paTarget.name << " is: " << paTarget.balance << endl;
                i = 11;
                break;
            }
            case 9:
            {
                cout << "Current account: " << paTarget.name << endl << endl;
                for (int k = 0; k < target.personalAcc.size(); k++)
                    if (target.personalAcc[k].name == paTarget.name)
                    {
                        target.personalAcc[0].balance += target.personalAcc[k].balance;
                        target.deleteAccount(paTarget.name);
                    }
                i = 11;
                break;
            }
        }
    }
    return 0;
}
