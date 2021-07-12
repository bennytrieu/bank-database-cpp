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
//  FILE:        llist.h
//
//  DESCRIPTION:
//  The header file for llist.
//
****************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include "record.h"

class llist
{
    private:
        record *    start;
        char        filename[16];
        int         readfile();
        int         writefile();
        void        cleanup();

    public:
        llist();
        llist(char[]);
        ~llist();
        int addRecord(int, char[], char[]);
        int findRecord(int);
        void printAllRecords();
        int deleteRecord(int);
};

#endif
