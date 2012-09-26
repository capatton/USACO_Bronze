/*
ID: casey.a1
LANG: C++
TASK: milk2
*/

/* Explanation of solution:
Time complexity: O(n log n)
 - Sorting is O (n log n) 
 - Figuring out the solution from the sorted list is O(n)
Greedy algorithm: 
 - Trying to calculate two values: longestMilking, longestAbsence
 - Goal: Scroll through each span and try to create the longest span possible.  Every time you reach a span with a start time after the 
 	previous span's end time, check to see if this is the longestAbsence.
 - Sort the spans by start time of milking
 - tempLongestSpan <- first span in list
 - Foreach (newSpan in list)
 		if (newSpan extends the tempLongestSpan)
 		    tempLongestSpan.endTime <-- newSpan.endTime
 		    if (duration(tempLongestSpan) > currentMax)
 		         longestMilking = duration(tempLongestSpan)
 		else if (newSpan is contained inside tempLongestSpan)
 			do nothing
 		else //doesn't fall inside previous span
 			tempLongestSpan = newSpan
 			check to see if longestAbsence is now larger

	Output longestMilking and longestAbsence
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

typedef struct milkSpan
{
	int startTime;
	int endTime;
} milkSpan;


void getListOfSpans(vector<milkSpan> &listOfSpans)
{
	ifstream fin ("milk2.in");
	int numRecords;
	fin >> numRecords;

	milkSpan currentSpan;

	for (int i = 0; i < numRecords; ++i)
	{
		fin >> currentSpan.startTime;
		fin >> currentSpan.endTime;
		listOfSpans.push_back(currentSpan);
	}
}
bool startTimeComparison(milkSpan m1, milkSpan m2)
{
	return (m1.startTime < m2.startTime);
}

void sortByStartTime(vector<milkSpan> &listOfSpans)
{
	sort(listOfSpans.begin(), listOfSpans.end(), startTimeComparison);
	return;
}

bool extendsCurrentSpan(milkSpan newSpan, milkSpan oldSpan)
{
	if (newSpan.startTime >= oldSpan.startTime && newSpan.startTime <= oldSpan.endTime && newSpan.endTime >= oldSpan.endTime)
	{
		return true;
	}

	return false;
}

bool containedInCurrentSpan(milkSpan newSpan, milkSpan oldSpan)
{
	if (newSpan.startTime >= oldSpan.startTime && newSpan.startTime <= oldSpan.endTime && newSpan.endTime <= oldSpan.endTime)
	{
		return true;
	}

	return false;
}

int duration(milkSpan span)
{
	return span.endTime - span.startTime;
}

int main()
{
	ofstream fout ("milk2.out");

	vector<milkSpan> listOfSpans;
	getListOfSpans(listOfSpans);
	sortByStartTime(listOfSpans);

	milkSpan tempSpan = listOfSpans[0];
	int longestMilking = duration(tempSpan);
	int longestAbsence = 0;

	for (int i = 1; i < listOfSpans.size(); ++i)
	{
		if (extendsCurrentSpan(listOfSpans[i], tempSpan))
		{
			tempSpan.endTime = listOfSpans[i].endTime;
			if (duration(tempSpan) > longestMilking)
			{
				longestMilking = duration(tempSpan);
			} 
		}
		else if (containedInCurrentSpan(listOfSpans[i], tempSpan))
		{
			continue;
		}
		else // falls outside current span
		{
			if (listOfSpans[i].startTime - tempSpan.endTime > longestAbsence)
			{
				longestAbsence = listOfSpans[i].startTime - tempSpan.endTime;
			}

			tempSpan = listOfSpans[i];
		}
	}

	fout << longestMilking << " " << longestAbsence << endl;

	return 0;
}