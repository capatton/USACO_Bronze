/*
ID: casey.a1
LANG: C++
TASK: friday
*/

#include <iostream>
#include <fstream>

using namespace std;
	
const int START_YEAR = 1900;
const int NUM_DAYS = 7;

typedef enum Weekday{
	SAT,
	SUN,
	MON,
	TUE,
	WED,
	THU,
	FRI
} Weekday;


typedef enum Month{
	JAN,
	FEB,
	MAR,
	APR,
	MAY,
	JUN,
	JUL,
	AUG,
	SEP,
	OCT,
	NOV,
	DEC
} Month;

void printResults(int *thirteenthCountPerDay)
{
	ofstream fout("friday.out");

	for (int day = SAT; day <= FRI; ++day)
	{
		fout << thirteenthCountPerDay[day] << " ";
	}
	fout << endl;
}

bool isLeapYear(int year)
{
	if (year % 400 == 0 || (year % 4 == 0 && year % 100 != 0))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void calcDayOfThirteenth(int month, int year, int &firstDay int *thirteenthCountPerDay)
{
	const int DISTANCE_TO_13TH = 12;
	const int DAYS_IN_WEEK = 7;

	Weekday dayOfThirteenth = (firstDay + DISTANCE_TO_13TH) % DAYS_IN_WEEK;
	thirteenthCountPerDay[dayOfThirteenth]++;

	switch (month)
	{
		case JAN:
		case MAR:
		case MAY:
		case JUL:
		case AUG:
		case OCT:
		case DEC:
			firstDay += 31 % 7;
			break;
		case APR:
		case JUN:
		case SEP:
		case NOV:
			firstDay += 30 % 7;
			break;
		case FEB:
			if (isLeapYear(year))
			{
				firstDay += 29 % 7;
			}
			else
			{
				firstDay += 28 % 7;
			}
			break;
		default:
			break;
	}
}

int getEndYear()
{
	ifstream fin("friday.in");
	int numYears;
	fin >> numYears;
	return START_YEAR + numYears - 1;
}

int main()
{
	int endYear = getEndYear();

	//Stores the number of times that the thirteen shows up for each day.  SAT = 0, SUN = 1, ... FRI = 6.
	// Ex: If there have been 10 times that the thirteenth shows up on a Thursday, then 
	// thirteenthCountPerDay[THU] = 10 
	int thirteenthCountPerDay[NUM_DAYS];

	int firstDayOfMonth = MON;
	for (int year = START_YEAR; year <= endYear; ++year)
	{
		for (int month = JAN; month <= DEC; ++month)
		{
			calcDayOfThirteenth(month, year, firstDayOfMonth, thirteenthCountPerDay);
		}
	}

	printResults(thirteenthCountPerDay);

	return 0;
}