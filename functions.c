#define _CRT_SECURE_NO_WARNINGS  

#include <stdio.h>
#include "functions.h"

extern int start_month;
extern int start_year;
extern int grad_date;
extern int grad_month;
extern int grad_year;
extern int course_years;
extern char placement;
extern float first_payment;
extern int first_payment_month;
extern int first_payment_year;
extern int maintenance_loan;
extern int duration = 0;
extern double tuition_loan = 0;
extern double total_loan;
extern double loan_amount;
extern float repayment_rate;
extern float salary_threshold;
extern float salary;
extern float initial_salary = 20000;
extern float monthly_salary;
extern float salary_growth;
extern float payment;
extern float interest_rate;
extern float rpi=3.3;
extern int n = 0;
extern int month;
extern float total_payment = 0;
extern float total_interest = 0;
extern float difference;
extern int years;
extern float final_payment;
extern int final_payment_month;
extern int final_payment_year;
extern int last_payment_date;
extern int i;
extern float monthly_interest;
extern int actual_months;
//extern month_array[7];

extern int month_array[360];
extern int year_array[360];
extern float salary_array[360];
extern float threshold_diff_array[360];
extern float interest_array[360];
extern float month_interest[360];
extern float payment_array[360];
extern float balance_array[360];

//extern FILE*loancalc;

int course()
{
	printf("Enter start date(mm/yyyy):");
	scanf("%d/%d", &start_month, &start_year);

	printf("How long is your course(years):");
	scanf("%d", &course_years);

	placement_calc();

	grad_month = 07;
	grad_year = (start_year + duration);

	printf("Your graduation is %i/%i \n\n", grad_month, grad_year);
	first_payment_month = 04;
	first_payment_year = grad_year + 1;

	printf("Your first payment date is on %i / %i \n", first_payment_month, first_payment_year);
	maintenance_loan = 8700; //derived from https://www.gov.uk/student-finance-calculator
	total_loan = tuition_loan + (maintenance_loan * course_years);

	loan_amount = total_loan;
	printf("Total loan is %lf \n\n", total_loan);
}

int placement_calc()
{
	printf("Will you undergo a placement year:(Y/N)");
	getchar();
	scanf("%c", &placement);
	if (placement == 'Y' || placement == 'y')
	{
		duration = course_years + 1;
		//maximum placement fee is 20% of tuition fee so i assumed that it was 20 
		tuition_loan = (course_years * 9250) + (0.2 * 9250);
	}

	else if (placement == 'N' || placement == 'n')
	{
		duration = course_years;
		tuition_loan = course_years * 9250;
	}
	else
	{
		printf("Enter either 'Y' or 'N'.\n");
		placement_calc();
	}
	
}

int salary_growth_calc()
{
	salary_growth = rpi + 3.0;
	if (month % 12 == 0)
	{
		salary = salary + (salary*salary_growth / 100);
		years++;
	}
	
}

int interest_from_salary()
{
	

	if (salary <= 25000)
	{
		interest_rate = rpi;
		
	}
	else if (salary > 25000 && salary < 45000)
	{
		interest_rate = rpi + (((salary - 25000) / 20000) * 3);
		
	}

	else if (salary >= 45000)
	{
		interest_rate = rpi + 3;
		
	}	

}

int payment_calc()
{
	salary_threshold = 25000;
	payment = (((salary / 12) - (salary_threshold / 12))*0.09);

	total_payment = total_payment + payment;
	
}


int interest()
{
	total_interest = total_interest + (total_loan*interest_rate/12 / 100);
	total_loan = total_loan + (total_loan*interest_rate / 12 / 100);
	total_loan = total_loan - payment;
	
}

extern FILE*txtfile;
extern FILE*csvfile;

int major_function()
{
	
	for (initial_salary = 20000; initial_salary <= 50000; initial_salary = initial_salary + 5000)
	{
		total_loan = loan_amount;
		month = 0;
		years = 0;
		total_payment = 0;
		total_interest = 0;
		actual_months = 1;
		salary = initial_salary;
		printf("Initial salary: %f \n", initial_salary);

		while (total_loan> 0.00)
		{
			if (month % 12 == 0)
			{
			years++;
			actual_months = 1;
	
			}
			actual_months++;
			month++;
			interest_from_salary();
			payment_calc();
			interest();
			salary_growth_calc();
	
			if (month == 360)
			{
				printf("30 years have been reached. Your debt is wiped\n\n");
				break;
			}
			if (total_loan < 0.00)
			{
				total_loan = 0;

			}
			
			month_array[month]=actual_months;
			year_array[month]=years;
			salary_array[month]=salary;
			threshold_diff_array[month] = (salary-salary_threshold);
			interest_array[month]= interest_rate;
			month_interest[month]=(interest_rate/12)*total_loan;
			payment_array[month]=payment;
			balance_array[month]=total_loan;

		}
	
		printf("It will take %d months to pay \n\n", month);
		printf("%d", years);

		fprintf(txtfile, "Initial Salary(£) is %.2f \n", initial_salary);
		fprintf(txtfile, "Final Salary(£) is %.2f \n", salary);
		fprintf(txtfile, "Total loan(£) is %.2f \n", loan_amount);
		fprintf(txtfile, "Last Payment Date(mm/yyyy) is %i/%i \n", final_payment_month, final_payment_year );
		fprintf(txtfile, "Closing Balance(£): %.2f \n", total_loan);
		fprintf(txtfile, "Total Interest (£): %.2f \n", total_interest);
		fprintf(txtfile, "Total Paid (£): %.2f \n\n", total_payment);


		fprintf(csvfile, "Date:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%i/%i,", year_array[n], month_array[n]);
		}
		fprintf(csvfile, "\n");
	

		fprintf(csvfile, " Salary:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", salary_array[n]);
		}
		fprintf(csvfile, "\n");
	

		fprintf(csvfile, "Salary Above Threshold:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", threshold_diff_array[n]);
		}
		fprintf(csvfile, "\n");
	

		fprintf(csvfile, "Interest Rate:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", interest_array[n]);
		}
		fprintf(csvfile, "\n");
		

		fprintf(csvfile, "Monthly interest:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", month_interest[n]);
		}
		fprintf(csvfile, "\n");
		

		fprintf(csvfile, "Monthly Repayment:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", payment_array[n]);
		}
		fprintf(csvfile, "\n");
		

		fprintf(csvfile, "Balance:,");
		for (n = 1; n <= month; n++)
		{
			fprintf(csvfile, "%.2f,", balance_array[n]);
		}
		fprintf(csvfile, "\n");
		fprintf(csvfile, "\n");
		

	}
	

}