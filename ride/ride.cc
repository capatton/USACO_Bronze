/*
ID: casey.a1
LANG: C++
TASK: ride
*/

#include <iostream>
#include <fstream>

using namespace std;
int getNumFromName(string name)
{
	int groupNum = 1;
	const size_t ASCII_INTEGER_OFFSET = 64;

	for (size_t i = 0; i < name.length(); ++i)
	{
		groupNum *= (name[i] - ASCII_INTEGER_OFFSET);
	}
	return groupNum;
}

int main()
{
	ifstream fin ("ride.in");
	ofstream fout ("ride.out");

	string cometName, groupName;
	fin >> cometName >> groupName;

	int cometNum = getNumFromName(cometName);
	int groupNum = getNumFromName(groupName);

	if (groupNum % 47 == cometNum % 47)
	{
		fout << "GO" << endl;
	}
	else
	{
		fout << "STAY" << endl;
	}

	return 0;
}
