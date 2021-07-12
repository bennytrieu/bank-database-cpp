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
//  FILE:        record.h
//
//  DESCRIPTION:
//  Creates the structure for record.
//
****************************************************************/

#ifndef RECORD_H
#define RECORD_H
struct record
{
    int                accountno;
    char               name[25];
    char               address[80];
    struct record*     next;
};
#endif
