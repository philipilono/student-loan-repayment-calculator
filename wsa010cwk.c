#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h> 
#include "functions.h"



int start_month;
int start_year;
int grad_date;
int grad_month;
int grad_year;
int course_years;
char placement;
float first_payment;
int first_payment_month;
int first_payment_year;
float maintenance_loan;
int duration ;
double tuition_loan ;
double total_loan;
double loan_amount;
float repayment_rate;
float salary_threshold;
float salary;
float initial_salary;
float monthly_salary;
float salary_growth;
float payment;
float interest_rate;
float rpi;
int n ;
int month ;
float total_payment;
float total_interest;
float difference;
int years;
float final_payment;
int final_payment_month;
int final_payment_year;
int last_payment_date;
int i;
int actual_months;



int year_array[360] = { 0 };
int month_array[360] = { 0 };
float salary_array[360] = { 0.0 };
float threshold_diff_array[360] = { 0.0 };
float interest_array[360] = { 0.0 };
float month_interest[360] = { 0.0 };
float payment_array[360] = { 0.0 };
float balance_array[360] = { 0.0 };

FILE*txtfile;
FILE*csvfile;



main()

{

	txtfile = fopen("loancalc.txt","w");
	csvfile = fopen("loancalc.csv", "w");
	fclose(txtfile);
	if (txtfile = NULL)
	{
		printf("\n File can not be opened or does not exist");
	}
	else
	{
		printf("\n File opened \n");
	}
	txtfile = fopen("loancalc.txt","a");
	csvfile = fopen("loancalc.csv", "a");
	course();

	major_function();
	
	fclose(txtfile);
	fclose(csvfile);
	scanf("%*s");
}
