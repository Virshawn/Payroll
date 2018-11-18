//
//  main.cpp        A5
//
//  Created by Virshawn King Hammonds on 7/30/12
//  Really created by CISP teacher at sac city college
//  Copyright (c) 2012 Pointdexter11. All rights reserved.
//
//  Hierarchy Chart
//  ================
//  3.0  Main
//    3.1 validateString(in a string as string, out boolean)
//      3.1.1 isDigit(in a char as character, out boolean)
//    3.2 validateNumber(in number, lowrange, hirange as float, out boolean)
//    3.3 calculateGross(in hours, payrate as float, out gross as float)
//    3.4 calculateTax(in gross as float, out tax as float)
//    3.5 calculateNet(in gross, tax as float, out net as float)
//    3.6 sortByLastname(in size as integer, out employeeRecord as array of records)
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define addr(var) &var
#define REPORTHEADINGS "     Employee's Name          Pay Rate     Hours       Gross       Net       Tax\n"
#define HEADER3        "     ===============          ========     =====       =====       ===       ===\n\n"
#define format         "     %-20s%10.2f%13.2f%12.2f%10.2f%10.2f\n"
#define totalAndAverage "     %-20s%10.2f%13.2f%12.2f%10.2f%10.2f\n"
#define TRUE 1
#define FALSE 0
#define BOOLEAN short
#define RETRYMAX 3
#define MAX 10

typedef struct employeeRecord{
    char fullName[10+15+2+1];
    char firstName[10+1];
    char lastName[15+1];
    float payrate,hours,gross,tax,net;
}   employeeRecord;

float calculateGross(float hour, float payrate);
float calculateTax(float gross);
float calculateNet(float gross, float tax);

BOOLEAN validateString(char inputString[]);
BOOLEAN validateNumber(float number,float lowRange,float hiRange);
BOOLEAN isDigit(char inputChar);

void sortByLastname(employeeRecord rec[], int size);

int main(void) {
    
    employeeRecord rec[MAX];
    
    float totalRate,totalHours,totalGross,totalNet,totalTax;
    int empCounter;
    char answer;
    int retryCount;
    FILE *reportFile;
    BOOLEAN validString, validNumber;
    
    
    reportFile = fopen("/Users/virshawn/Desktop/A5File.txt", "wt");
    if (reportFile == NULL) {
        printf("Report File Open Failed ... \n");
        while (getchar() != '\n');  //fflush(stdin);
        getchar();
        exit(-100);
    }
    fprintf(reportFile, REPORTHEADINGS);
    fprintf(reportFile, HEADER3);
    totalRate = totalHours = totalGross = empCounter = totalTax = totalNet = 0;
    do {
        retryCount = 0;
        do {
            printf("Enter employee's first name ");
            scanf("%s",rec[empCounter].firstName);
            validString = validateString(rec[empCounter].firstName);
            if (!validString) retryCount++;
        } while (retryCount < RETRYMAX && !validString);
        if (!validString) strcpy(rec[empCounter].firstName, "BadName");
        
        retryCount = 0;
        do {
            printf("Enter employee's last name ");
            scanf("%s",rec[empCounter].lastName);
            validString = validateString(rec[empCounter].lastName);
            if (!validString) retryCount++;
        } while (retryCount < RETRYMAX && !validString);
        if (!validString) strcpy(rec[empCounter].lastName, "BadName");
        
        retryCount = 0;
        do {
            printf("Enter hourly pay rate ");
            scanf("%f",addr(rec[empCounter].payrate));
            validNumber = validateNumber(rec[empCounter].payrate, 0, 99.99);
            if (!validNumber) retryCount++;
        } while (retryCount < RETRYMAX && !validNumber);
        if (!validNumber) rec[empCounter].payrate = 0.0;
        
        retryCount = 0;
        do {
            printf("Enter hours worked this pay period ");
            scanf("%f",addr(rec[empCounter].hours));
            validNumber = validateNumber(rec[empCounter].hours, 0, 112);
            if (!validNumber) retryCount++;
        } while (retryCount < RETRYMAX && !validNumber);
        if (!validNumber) rec[empCounter].hours = 0.0;
        
        strcpy(rec[empCounter].fullName,rec[empCounter].lastName);
        strcat(rec[empCounter].fullName,", ");
        strcat(rec[empCounter].fullName,rec[empCounter].firstName);
        
        rec[empCounter].gross = calculateGross(rec[empCounter].hours, rec[empCounter].payrate);
        totalRate = totalRate + rec[empCounter].payrate;
        totalHours += rec[empCounter].hours;
        totalGross += rec[empCounter].gross;
        
        rec[empCounter].tax = calculateTax(rec[empCounter].gross);
        rec[empCounter].net = calculateNet(rec[empCounter].gross, rec[empCounter].tax);
        totalTax += rec[empCounter].tax;
        totalNet += rec[empCounter].net;

        printf("     Repeat (Y/N)? ");
        empCounter++;
        while (getchar() != '\n');  //fflush(stdin);
        scanf("%c",addr(answer));
        
    } while (answer == 'Y' || answer == 'y');
    
    sortByLastname(rec, empCounter);    
    
    int counter;
     for (counter = 0; counter <  empCounter ; counter++) {

     fprintf(reportFile, format,rec[counter].fullName,rec[counter].payrate,rec[counter].hours,rec[counter].gross,rec[counter].net,rec[counter].tax);
     }
    fprintf(reportFile, "\n");
    fprintf(reportFile,totalAndAverage,"Totals",totalRate,totalHours,totalGross,totalNet,totalTax);
    fprintf(reportFile,totalAndAverage,"Averages",totalRate/empCounter,totalHours/empCounter,totalGross/empCounter,totalNet/empCounter,totalTax/empCounter);
    //}
    fclose(reportFile);
    printf("Press any key...  ");
    while (getchar() != '\n');  //fflush(stdin);
    getchar();
    return 0;
}//main

float calculateGross(float hour, float payrate){
    if (hour <= 40)
        return hour * payrate;
    else
        return 40 * payrate + (hour-40)*1.5*payrate;
}
float calculateTax(float gross){
    return .15*gross;
}
float calculateNet(float gross, float tax){
    return gross - tax;
}

BOOLEAN validateString(char inputString[]){
    int i;
    
    for (i=0; i < strlen(inputString); i++){
        if (isDigit(inputString[i]))
            return FALSE;
    }
    return TRUE;
}
BOOLEAN isDigit(char inputChar){
    if ( inputChar >= '0' && inputChar <= '9')
        return TRUE;
    else
        return FALSE;
}
BOOLEAN validateNumber(float number,float lowRange,float hiRange){
    if (number >= lowRange && number <= hiRange)
        return TRUE;
    else
        return FALSE;
}
void sortByLastname(employeeRecord rec[], int size)
{
    
    int outer, inner;
    for (outer=0; outer < size; outer++)
    {
        for (inner=0; inner < size-1; inner++)
        {
            if (strcmp(rec[inner].lastName, rec[inner+1].lastName)>0)
            {    employeeRecord tempRec = rec[inner];
                rec[inner] = rec[inner+1];
                rec[inner+1] = tempRec;
            }
        }
    }
}
