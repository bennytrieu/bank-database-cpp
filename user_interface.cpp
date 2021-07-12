/****************************************************************
//
//  NAME:        Benny Trieu
//
//  HOMEWORK:    Project2
//
//  CLASS:       ICS 212
//
//  INSTRUCTOR:  Ravi Narayan
//
//  DATE:        December 1st, 2020
//
//  FILE:        user_interface.cpp
//
//  DESCRIPTION:
//  A user interface that displays the menu options for the
//  bank at the user's convenience
//
****************************************************************/

#include<iostream>
#include<iomanip>
#include<string.h>
#include"record.h"
#include"llist.h"
using namespace std;
void menu();
void getaddress(char[], int);

/****************************************************************
//
//  Function name: main
//
//  DESCRIPTION:   The main hub of the code that helps run 
//                 the user interface for the bank.
//                 
//  Parameters:    argc (int) : contains the number of arguments
//                              inputted into the c file
//                 argv[] (char*): stores the arguments
//
//  Return values:  0 : tells the code its all good
//                 
//
****************************************************************/

int main(int argc, char *argv[])
{
    int lever, status, value, num, position, fin, state, acc, condition, button, transfer;
    char letters[100];
    char name[100];
    char address[100];
    lever = 0;
    position = 1;
    state = 1;
    condition = 1;
    button = 1;
    transfer = 0;
    llist mylist;
    #ifdef DEBUGMODE
        cout << "*****DEBUG MODE ON*****\n";
    #endif
    cout << "Hello welcome to the bank\n\n";
    menu();
    while (lever == 0)
    {
        status = 1;
        if (cin >> letters)
        {
            value = strlen(letters);
            if (strncmp (letters, "add", value) == 0 || strncmp (letters, "Add", value) == 0)
            {
                condition = 1;
                button = 1;
                cout << "Add has been chosen\n";
                cout << "account #:";
                do
                {
                    cin >> acc;
                    if (cin.fail())
                    {
                        cout << "This is not a number, please try again:";
                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                    else
                    {
                        if (acc <= 0)
                        {
                            cout << "not a valid number, try again:";
                        }
                        else
                        {
                            condition = 0;
                        }
                    }
                }
                while (condition == 1);
                cin.ignore(100, '\n');
                cout << "name:";
                do
                {
                    cin.getline(name, 100);
                    button++;
                }
                while (button == 1);
                cout << "Address(Press enter and then '!' when finished):";
                getaddress(address, transfer);
                mylist.addRecord(acc, name, address);
                cout << "\n\naccount#:" << acc << "\nname:" << name << "\naddress:"
                << address << endl;
                cout << "Welcome back to the menu\n\n";
                menu();
                status++;
            }
            if (strncmp (letters, "printall", value) == 0 ||
                strncmp(letters, "Printall", value) == 0)
            {
                cout << "Here are all the records:\n\n";
                mylist.printAllRecords();
                cout << "Welcome back\n\n";
                menu();
                status++;
            }
            if (strncmp (letters, "find", value) == 0 || strncmp (letters, "Find", value) == 0)
            {
                state = 1;
                cout << "Find has been chosen\n";
                cout << "what account # would you like to find:";
                do
                {
                    cin >> fin;
                    if (cin.fail())
                    {
                        cout << "This is not a number, please try again:";
                        cin.clear();
                        cin.ignore(100, '\n');
                    }
                    else
                    {
                        if (fin <=0)
                        {
                            cout << "not a valid number, try again:";
                        }
                        else
                        {
                            cout << endl;
                            state = 0;
                        }
                    }
                }
                while (state == 1);
                mylist.findRecord(fin);
                cout << "Welcome back to the menu\n\n";
                menu();
                status++;
            }
            if (strncmp (letters, "delete", value) == 0 || strncmp(letters, "Delete", value) == 0)
            {
                position = 1;
                cout << "Delete has been chosen\n";
                cout << "what account # would you like to delete:";
                do
                {
                    cin >> num;
                    {
                        if (cin.fail())
                        {
                            cout << "This is not a number, please try again:";
                            cin.clear();
                            cin.ignore(100, '\n');
                        }
                        else
                        {
                            if (num <= 0)
                            {
                                cout << "not a valid number, try again:";
                            }
                            else
                            {
                                position = 0;
                            }
                        }
                    }
                }
                while (position == 1);
                mylist.deleteRecord(num);
                cout << "Welcome back to the menu\n\n";
                menu();
                status++;
            }
            if (strncmp (letters, "quit", value) == 0 || strncmp (letters, "Quit", value) == 0)
            {
                cout << "Have a nice day :)\n";
                lever = 1;
                status = 2;
            }
            else if (status == 1)
            {
                cout << "INVALID, Please try again:";
            }
        }
    }
    return 0;
}

/****************************************************************
//  
//  Function name: menu
// 
//  DESCRIPTION:   Prints the options given and prompts the user
//                 to choose an option
//  
//  Parameters:    none
//                         
//  Return values: none
//    
****************************************************************/

void menu()
{
    #ifdef DEBUGMODE
        cout << "*****MENU HAS BEEN CALLED*****\n";
    #endif
    cout << "Here are your options\n\n";
    cout << "add:             Add a new record in the database\n";
    cout << "printall:        Print all records in the database\n";
    cout << "find:            Find record(s) with a specified account #\n";
    cout << "delete:          Delete existing record(s) from the database using the account #\n";
    cout << "quit:            Quit the program\n\n";
    cout << "Please choose an option:";
}

/****************************************************************
//
//  Function name: getaddress
// 
//  DESCRIPTION:   asks the user for their address
//                 press ! to be finished
//             
//  Parameters:    address (char[]): The array that holds the
//                 address for the user
//                 transfer (int): The integer that helps with
//                 fgetc
//  
//  Return values: none
//  
****************************************************************/

void getaddress(char address[], int transfer)
{
    cin.getline(address, 100, '!');
    #ifdef DEBUGMODE
        cout << "*****GETADDRESS:" << address << " IS PASSED*****\n";
        cout << "*****GETADDRESS:" << transfer << " IS PASSED*****\n";
    #endif
}
