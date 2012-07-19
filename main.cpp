//
//  main.cpp        A4
//  Purpose: A4 Valadation
//
//  Created by Virshawn King Hammonds on 7/19/12
//  Copyright (c) 2012 Pointdexter11. All rights reserved.
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

float calculateGross(float hour, float payrate);
float calculateTax(float gross);
float calculateNet(float gross, float tax);

BOOLEAN validateString(char inputString[]);
BOOLEAN validateNumber(float number,float lowRange,float hiRange);
BOOLEAN isDigit(char aChar);


int main(void) {
    char firstName[10+1];
    char lastName[15+1];
    float payrate,hours,gross,tax,net;
    float totalRate,totalHours,totalGross,totalNet,totalTax;
    int empCount;
    char answer;
    char fullName [10+15+2+1];
    BOOLEAN validString, validNumber;
    int retryCount;
    FILE *reportFile;
    
    reportFile = fopen("/Users/virshawn/Dropbox/CISP 301/Week 9,10 - Data Validation/A4/A4/A4File.txt", "wt");
    if (reportFile == NULL) {
        printf("Report File Open Failed ... \n");
        while (getchar() != '\n');  //fflush(stdin);
        getchar();
        exit(-100);
    }
    fprintf(reportFile, REPORTHEADINGS);
    fprintf(reportFile, HEADER3);
    totalRate = totalHours = totalGross = empCount = totalTax = totalNet = 0;
    do {    
        retryCount = 0;
        do {
            printf("Enter employee's first name "); 
            scanf("%s",addr(firstName[0]));
            validString = validateString(firstName);
            if (!validString) retryCount++;
        } while (retryCount < RETRYMAX && !validString);
        if (!validString) strcpy(firstName, "BadName");
        
        retryCount = 0;  
        do {
            printf("Enter employee's last name ");  
            scanf("%s",addr(lastName[0]));
            validString = validateString(lastName);
            if (!validString) retryCount++;
        } while (retryCount < RETRYMAX && !validString);
        if (!validString) strcpy(lastName, "BadName");
        
        retryCount = 0;
        do {
            printf("Enter hourly pay rate ");
            scanf("%f",addr(payrate));
            validNumber = validateNumber(payrate, 0, 99.99);
            if (!validNumber) retryCount++;
        } while (retryCount < RETRYMAX && !validNumber);
        if (!validNumber) payrate = 0.0;
        
        retryCount = 0;
        do {
            printf("Enter hours worked this pay period ");
            scanf("%f",addr(hours));
            validNumber = validateNumber(hours, 0, 112);
            if (!validNumber) retryCount++;
        } while (retryCount < RETRYMAX && !validNumber);
        if (!validNumber) hours = 0.0;
        
        
        gross = calculateGross(hours, payrate);
        totalRate = totalRate + payrate; 
        totalHours += hours;
        totalGross += gross;
        empCount++;
        
        tax = calculateTax(gross);
        net = calculateNet(gross, tax);
        totalTax += tax;
        totalNet += net;
        strcpy(fullName,lastName); 
        strcat(fullName,", ");
        strcat(fullName,firstName);
        
        printf(format,fullName,payrate,hours,gross,net,tax);
        fprintf(reportFile, format,fullName,payrate,hours,gross,net,tax);
        printf("     Repeat (Y/N)? ");
        while (getchar() != '\n');  //fflush(stdin);
        scanf("%c",addr(answer));
    } while (answer == 'Y' || answer == 'y');
    fprintf(reportFile, "\n");
    fprintf(reportFile,totalAndAverage,"Totals",totalRate,totalHours,totalGross,totalNet,totalTax);
    fprintf(reportFile,totalAndAverage,"Averages",totalRate/empCount,totalHours/empCount,totalGross/empCount,totalNet/empCount,totalTax/empCount); 
    
    fclose(reportFile);
    printf("Press any key...  ");
    while (getchar() != '\n');  //fflush(stdin);
    getchar();
    return 0;
    
}//Main

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

BOOLEAN isDigit(char inputChar){ 
    if ( inputChar >= '0' && inputChar <= '9')
        return TRUE;
    else
        return FALSE;
}

BOOLEAN validateString(char inputString[]){
    int i;
    
    for (i=0; i < strlen(inputString); i++){
        if (isDigit(inputString[i])) 
            return FALSE;   
    }	
    return TRUE;
}

BOOLEAN validateNumber(float number,float lowRange,float hiRange){
    if (number >= lowRange && number <= hiRange)
        return TRUE;
    else
        return FALSE;
}



