//Niall Boyd
//2392483b
//Systems Programming Assessed Exercise 1
//This is my own work as defined in the Acedemic Ethics agreement I have signed. 

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "date.h"

struct date{
	int day;
	int month;
	int year;
};

//date_create - creates a Date structure from 'datestr'
////
Date *date_create(char *datestr){
	Date *date = (Date *) malloc(sizeof(Date));
	char *token;
	const char del[2] = "/";	
	
	if (datestr == NULL){
		return NULL;
	}else{
		token = strtok(datestr, del);
		date->day = atoi(token);
		token = strtok(NULL, del);
		date->month = atoi(token);
		token = strtok(NULL,del);
		date->year = atoi(token);
	}
	return date;
};

//creates duplicate of d
Date *date_duplicate(Date *date){
	Date *datePointer = (Date *) malloc(sizeof(Date));
	if (datePointer != NULL){
		datePointer->day = date->day;
		datePointer->month = date->month;
		datePointer->year = date->year;
	}else{
		return NULL;
	}
	return datePointer;
};

int date_compare(Date *date1, Date *date2){
	if (date1->year > date2->year){
		return 1;
	}else if (date1->year <date2->year){
		return -1;
	//if years are the same check months
	}else{ 
		if(date1->month > date2->month){
			return 1;
		}else if (date1->month < date2->month){
			return -1;
		//if year and month are the same check the day
		}else{ 
			if (date1->day > date2->day){
				return 1;
			}else if (date1->day < date2->day){
				return -1;
			}else{
				return 0; //if days are the same return 0
			}
		}
	}
};

void date_destroy(Date *d){
	if (d != NULL){
		free(d);	
	}	
};




	
