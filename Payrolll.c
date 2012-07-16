//
//  payroll.cpp       
//  Purpose: including data struct and records and such 
//
//  Created by Virshawn King Hammonds<Virshawn@me.com> on 4/30/12
//  Copyright (c) 2012 Pointdexter11. All rights reserved.
//
//  Hierarchy Chart 
//  ========================
//  3.0  Payroll
//  	3.1 InputData(out validatedFirstname as string
//  							out validated lastname as string,
//  							out validateHours as float
//  							out validatedPayrate as float)
//  		3.1.1 validateString(in a string as string, out boolean)
//  		3.1.1.1 isDigit(in a char as character, out boolean)
//  		3.1.2 validateNumber(in number, lowrange, hirange as float, out boolean)
//  	3.2 calculateGross(in hours, payrate as float, out gross as float)
//  	3.3 calculateTax(in gross as float, out tax as float)
//  	3.4 calculateNet(in gross, tax as float, out net as float)
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

typedef struct employeeRecord {
		char firstName[10+1];
		char lastName[15+1];
		float payrate;
		float hours;
		float tax;
}   employeeRecord;

employeeRecord rec;

float calculateGross(float hour, float payrate);
float calculateTax(float gross);
float calculateNet(float gross, float tax);

BOOLEAN validateString(char inputString[]);
BOOLEAN validateNumber(float number,float lowRange,float hiRange);
BOOLEAN isDigit(char aChar);

void sortByLastname(employeeRecord rec[MAX], int size);

int main(void) {
		float gross,net;
		float totalRate,totalHours,totalGross,totalNet,totalTax;
		int empCount;
		char answer;
		char fullName [10+15+2+1];
		BOOLEAN validString, validNumber;
		int retryCount;
		FILE *reportFile;

							
		reportFile = fopen("/File.txt", "wt"); //Choose your path
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
						scanf("%s",addr(rec.firstName[0]));
						validString = validateString(rec.firstName);
						if (!validString) retryCount++;
				} while (retryCount < RETRYMAX && !validString);
				if (!validString) strcpy(rec.firstName, "BadName");

				retryCount = 0;  
				do {
						printf("Enter employee's last name ");  
						scanf("%s",addr(rec.lastName[0]));
						validString = validateString(rec.lastName);
						if (!validString) retryCount++;
				} while (retryCount < RETRYMAX && !validString);
				if (!validString) strcpy(rec.lastName, "BadName");

				retryCount = 0;
				do {
						printf("Enter hourly pay rate ");
						scanf("%f",addr(rec.payrate));
						validNumber = validateNumber(rec.payrate, 0, 99.99);
						if (!validNumber) retryCount++;
				} while (retryCount < RETRYMAX && !validNumber);
				if (!validNumber) rec.payrate = 0.0;

				retryCount = 0;
				do {
						printf("Enter hours worked this pay period ");
						scanf("%f",addr(rec.hours));
						validNumber = validateNumber(rec.hours, 0, 112);
						if (!validNumber) retryCount++;
				} while (retryCount < RETRYMAX && !validNumber);
				if (!validNumber) rec.hours = 0.0;




				gross = calculateGross(rec.hours, rec.payrate);
				totalRate = totalRate + rec.payrate; 
				totalHours += rec.hours;
				totalGross += gross;
				empCount++;

				rec.tax = calculateTax(gross);
				net = calculateNet(gross, rec.tax);
				totalTax += rec.tax;
				totalNet += net;
				strcpy(fullName,rec.lastName); 
				strcat(fullName,", ");
				strcat(fullName,rec.firstName);

				sortByLastname(&rec, MAX);

				printf(format,fullName,rec.payrate,rec.hours,gross,net,rec.tax);
				fprintf(reportFile, format,fullName,rec.payrate,rec.hours,gross,net,rec.tax);
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

} //End main

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

void sortByLastname(employeeRecord rec[MAX], int size)
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

