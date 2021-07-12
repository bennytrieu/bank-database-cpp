/*****************************************************************
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
//  FILE:        llist.cpp
//
//  DESCRIPTION:
//  The database for the bank
//
****************************************************************/

#include <string.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include "llist.h"
#include "record.h"
using namespace std;

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   The constructor for llist
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

llist::llist()
{
    #ifdef DEBUGMODE
        cout << "*****LLIST HAS BEEN PASSED*****\n";
        cout << "*****CONSTRUCTING A LIST*****\n\n";
    #endif
    start = NULL;
    readfile();
}

/*****************************************************************
//
//  Function name: llist
//
//  DESCRIPTION:   The alternative constructor for llist
//
//  Parameters:    fileinput(char[]): the text file that will
//                 be put into readfile.
//
//  Return values:  none
//
****************************************************************/

llist::llist(char fileinput[])
{
    int checker = 0;
    #ifdef DEBUGMODE
        cout << "*****LLIST HAS BEEN PASSED*****\n";
        cout << "*****CONSTRUCTING A LIST*****\n\n";
    #endif
    start = NULL;
    while (checker < 16)
    {
        filename[checker] = fileinput[checker];
        checker++;
    }
    readfile();
}

/*****************************************************************
//
//  Function name: ~llist
//
//  DESCRIPTION:   The destructor for llist
//
//  Parameters:    none
//
//  Return values:  none
//
****************************************************************/

llist::~llist()
{
    #ifdef DEBUGMODE
        cout << "*****~LLIST HAS BEEN PASSED*****\n";
        cout << "*****DESTRUCTING A LIST*****\n\n";
    #endif
    writefile();
    cleanup();
}

/*****************************************************************
//
//  Function name: addRecord
//
//  DESCRIPTION:   Adds a record of an account, name, and address
//                 
//  Parameters:    uacc (int): Contains the account #
//                 uname (char[]): Contains the name
//                 uaddress (char[]): Contains the address
//
//  Return values:  0 : gives it the all clear
//
****************************************************************/

int llist::addRecord(int uacc, char uname[], char uaddress[])
{
    struct record * temp;
    struct record * prevrecord;
    struct record * input;
    int button = 1;
    int lone = 0;
    temp = NULL;
    prevrecord = NULL;
    input = new record;
    (*input).accountno = uacc;
    strcpy((*input).name, uname);
    strcpy((*input).address, uaddress);
    (*input).next = NULL;
    #ifdef DEBUGMODE
        cout << "*****ADD:" << uacc << " IS PASSED*****\n";
        cout << "*****ADD:" << uname << " IS PASSED*****\n";
        cout << "*****ADD:" << uaddress << " IS PASSED*****\n";
    #endif
    if (start == NULL)
    {
        start = input;
    }
    else if (start != NULL)
    {
        temp = start;
        if (((*temp).next == NULL) && (uacc < (*temp).accountno))
        {
            (*temp).next = input;
            temp = NULL;
            lone++;
        }
        else if (((*temp).next == NULL) && (uacc >= (*temp).accountno))
        {
            (*input).next = temp;
            start = input;
            temp = NULL;
            lone++;
        }
        else
        {
            while (temp != NULL)
            {
                if (uacc >= (*temp).accountno)
                {
                    if (start == temp)
                    {
                        (*input).next = start;
                        start = input;
                        temp = NULL;
                        button = 0;
                        lone++;
                    }
                    else if (start != temp)
                    {
                        (*input).next = (*prevrecord).next;
                        (*prevrecord).next = input;
                        temp = NULL;
                        prevrecord = NULL;
                        button = 0;
                        lone++;
                    }
                }
                button++;
                if (prevrecord != NULL)
                {
                    prevrecord = (*prevrecord).next;
                    temp = (*temp).next;
                }
                if (button == 2)
                {
                    prevrecord = start;
                    temp = (*temp).next;
                }
                if ((temp == NULL) && (lone == 0))
                {
                    (*prevrecord).next = input;
                    lone++;
                }
            }
        }
    }
    return 0;
}

/*****************************************************************
//
//  Function name: printAllRecords
// 
//  DESCRIPTION:   Prints all the records for an object called
//                 llist.
// 
//  Parameters:    none
//                  
//  Return values:  none
// 
****************************************************************/

void llist::printAllRecords()
{
    struct record * temp = start;
    #ifdef DEBUGMODE
        cout << "*****PRINTALLRECORDS IS CALLED*****\n";
    #endif
    while (temp != NULL)
    {
        cout << "accountno:" << (*temp).accountno << endl;
        cout << "name:" << (*temp).name << endl;
        cout << "address:" << (*temp).address << endl;
        temp = (*temp).next;
    }
}

/*****************************************************************
//
//  Function name: findRecord
//  
//  DESCRIPTION:   Finds the record using an account #
//  
//  Parameters:    acc (int) : Contains the account #
//                  
//  Return values:  status : gives -1 or 0
//                  0 : gives it the all clear
//                  -1 : the function returns not clear
//  
****************************************************************/

int llist::findRecord(int acc)
{
    int find;
    int status;
    struct record * temp = start;
    find = 0;
    status = 0;
    #ifdef DEBUGMODE
        cout << "*****FINDRECORD:" << acc << " IS PASSED*****\n";
    #endif
    while (temp != NULL)
    {
        if (acc == (*temp).accountno)
        {
            cout << "account #" << acc << " has been found\n";
            cout << "accountno:" << (*temp).accountno << endl;
            cout << "name:" << (*temp).name << endl;
            cout << "address:" << (*temp).address << endl;
            find++;
        }
        temp = (*temp).next;
    }
    if (find == 0)
    {
        cout << "account #" << acc << " has not been found\n\n";
        status = -1;
    }
    return status;
}

/*****************************************************************
//
//  Function name: deleteRecord
//  
//  DESCRIPTION:   Deletes the record using an account #
//  
//  Parameters:    acc (int) : Contains the account #
//                  
//  Return values:  status : gives -1 or 0
//                  0 : gives it the all clear
//                  -1 : the function returns not clear
//  
****************************************************************/

int llist::deleteRecord(int acc)
{
    struct record * temp;
    struct record * prevrecord;
    int status, button, find;

    #ifdef DEBUGMODE
        cout << "*****DELETERECORD:" << acc << " IS PASSED*****\n";
    #endif

    prevrecord = NULL;
    button = 1;
    find = 0;
    status = 0;

    if (start == NULL)
    {
        status = -1;
        cout << "Nothing is in the list\n\n";
    }
    else
    {
        temp = start;
        while (temp != NULL)
        {
            if ((*temp).accountno == acc)
            {
                if ((temp == start) && (button == 1))
                {
                    start = (*start).next;
                    delete temp;
                    temp = start;
                    button = 0;
                    find++;
                }
                else if (start != temp)
                {
                    while ((*temp).accountno == acc)
                    {
                        (*prevrecord).next = (*temp).next;
                        delete temp;
                        temp = (*prevrecord).next;
                        find++;
                        if (temp == NULL)
                        {
                            temp = prevrecord;
                        }
                    }
                }
            }
            button++;
            if ((temp == NULL) && (prevrecord != NULL))
            {
                prevrecord = NULL;
            }
            if (prevrecord != NULL)
            {
                prevrecord = (*prevrecord).next;
                if (temp != NULL)
                {
                    temp = (*temp).next;
                }
            }
            if (button == 2)
            {
                prevrecord = start;
                temp = (*temp).next;
            }
        }
        if (find == 0)
        {
            status = -1;
            cout << "Could not find account #" << acc << endl << endl;
        }
        else if (find >= 0)
        {
            cout << "account #" << acc << " has been deleted\n\n";
        }
    }
    return status;
}

/****************************************************************
//
//  Function name: readfile
//
//  DESCRIPTION:   Reads the file and loads in the bank's
//                 database
//
//  Parameters:    pbegin (struct record **) : Contains the structure
//                 address of a record named pbegin
//                 loadfile (char[]) : the file that will contain
//                 the database of the bank
//
//  Return values:  status: determines the return value of the program
//                  0 means its all clear and -1 means it failed
//
//  ****************************************************************/

int llist::readfile()
{
    struct record * load;
    struct record * temp;
    char input[100];
    int number;
    int status;
    ifstream read;

    #ifdef DEBUGMODE
        cout << "*****READFILE HAS BEEN CALLED*****\n";
    #endif
    temp = NULL;
    status = 0;
    strcpy(filename, "loadfile.txt");
    read.open(filename);
    if (read.fail())
    {
        status = -1;
    }
    else
    {
        while (!read.eof())
        {
            load = new record;
            read >> input;
            number = atoi(input);
            (*load).accountno = number;
            read >> input;
            strcpy((*load).name, input);
            read.ignore(100, '\n');
            read.getline(input, 100, '!');
            strcpy((*load).address, input);
            (*load).next = NULL;
            if (start == NULL)
            {
                start = load;
                if ((*load).accountno <= 0)
                {
                    temp = start;
                    start = NULL;
                    delete temp;
                    temp = NULL;
                }
            }
            else
            {
                if (temp == NULL)
                {
                    temp = start;
                }
                (*temp).next = load;
                if ((*load).accountno <= 0)
                {
                    delete (*temp).next;
                    (*temp).next = NULL;
                }
                temp = (*temp).next;
            }
        }
        read.close();
    }
    return status;
}

/****************************************************************
//
//  Function name: writefile
//
//  DESCRIPTION:   writes into the file and saves the bank's
//                 database
//
//  Parameters:    none
//
//  Return values:  0: it means all clear
//
****************************************************************/

int llist::writefile()
{
    struct record * current = start;
    int characters;
    #ifdef DEBUGMODE
        cout << "*****WRITEFILE IS CALLED*****\n\n";
    #endif
    strcpy(filename, "loadfile.txt");
    ofstream write;
    write.open(filename);
    while (current != NULL)
    {
        write << (*current).accountno << endl;
        write << (*current).name << endl;
        characters = strlen((*current).address);
        (*current).address[characters] = '!';
        (*current).address[characters+1] = '\n';
        write << (*current).address;
        current = (*current).next;
    }
    write.close();
    return 0;
}

/****************************************************************
//
//  Function name: cleanup
//
//  DESCRIPTION:   cleans up the heap
//
//  Parameters:    none
//
//  Return values: none
//
//  ****************************************************************/

void llist::cleanup()
{
    struct record * temp;
    struct record * prev;
    int status = 1;

    #ifdef DEBUGMODE
        cout << "*****CLEANUP IS CALLED*****\n\n";
    #endif
    while (status == 1)
    {
        if (start == NULL)
        {
            status = 0;
        }
        else
        {
            temp = start;
            if ((*temp).next == NULL)
            {
                delete temp;
                start = NULL;
                status = 0;
            }
            else
            {
                while (temp != NULL)
                {
                    prev = temp;
                    temp = (*temp).next;
                    delete prev;
                }
                status = 0;
                start = NULL;
            }
        }
    }
}
