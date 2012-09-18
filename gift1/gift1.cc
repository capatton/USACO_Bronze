/*
ID: casey.a1
LANG: C++
TASK: gift1
*/

#include <iostream>
#include <vector>
#include <fstream>
#include <map>

using namespace std;

ofstream fout ("gift1.out");
ifstream fin ("gift1.in");

void initializeNameLists(vector<string> &ordering, map<string, int> &nameNetPair, int numFriends)
{
	string currentName;
	for (int i = 0; i < numFriends; ++i)
	{
		fin >> currentName;
		ordering.push_back(currentName);
		nameNetPair[currentName] = 0;
	}
}

void handleGiving(string giverName, map<string, int> &nameNetPair){
	int totalMoney = 0, numPeople = 0;
	fin >> totalMoney >> numPeople;

	// Divides money evenly amongst friends.  There are no fractions, so he gives the remainder to himself
	int amtPerPerson = totalMoney / numPeople;
	int amtForSelf = totalMoney % numPeople;
	nameNetPair[giverName] -= totalMoney;
	nameNetPair[giverName] += amtForSelf;

	string personReceiving;
	for (int i = 0; i < numPeople; ++i)
	{
		fin >> personReceiving;
		nameNetPair[personReceiving] += amtPerPerson;
	}
}
void calculateNetValues(map<string, int> &nameNetPair, int numFriends)
{
	string currentName;
	for (int i = 0; i < numFriends; ++i)
	{
		fin >> currentName;
		handleGiving(currentName, nameNetPair);
	}
}

void outputInOrder(map<string, int> &nameNetPair, vector<string> &ordering, int numFriends)
{
	for (int i = 0; i < ordering.size(); ++i)
	{
		fout << ordering[i] << " " << nameNetPair[ordering[i]];
	}
	fout << endl;
}

int main()
{

	int numFriends = 0;
	fin >> numFriends;

	vector<string> ordering;
	map<string, int> nameNetPair;
	initializeNameLists(ordering, nameNetPair, numFriends);
	calculateNetValues(nameNetPair, numFriends);
	
	outputInOrder(nameNetPair, ordering, numFriends);

	return 0;
}