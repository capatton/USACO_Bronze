/*
ID: casey.a1
LANG: C++
TASK: beads
*/

//NOTE: Not proud of this solution...basic algorithm seems wrong and this came out very hacky.

#include <iostream>
#include <fstream>

using namespace std;
int countSameBeadsLeft(string &necklace, int position)
{
	char beadColor = necklace[position];
	int numSameColor = 1;

	for (;;)
	{
		//wrap around
		--position;
		if (position == -1)
		{
			position = necklace.length() - 1;
		}

		if (beadColor == 'w')
		{	
			beadColor = necklace[position];
		}

		if (necklace[position] == beadColor || necklace[position] == 'w')
		{
			necklace[position] = beadColor; //Color the white beads
			++numSameColor;
		}
		else
		{
			return numSameColor;
		}
	}
} 

int countSameBeadsRight(string &necklace, int position)
{
	if (position >= necklace.length())
	{
		position = 0;
	}
	char beadColor = necklace[position];
	int numSameColor = 1;

	for (;;)
	{
		//wrap around
		++position;
		if (position == necklace.length())
		{
			position = 0;
		}

		if (beadColor == 'w')
		{	
			beadColor = necklace[position];
		}

		if (necklace[position] == beadColor || necklace[position] == 'w')
		{
			necklace[position] = beadColor; //color the white beads
			++numSameColor;
		}
		else
		{
			return numSameColor;
		}
	}
}

bool necklaceIsOneColor(string necklace)
{
	if (necklace.find("b") == string::npos || necklace.find("r") == string::npos)
	{
		return true;
	}

	return false;
}

int main()
{
	ifstream fin ("beads.in");
	ofstream fout ("beads.out");

	int numBeads;
	fin >> numBeads;
	string necklace;
	fin >> necklace;

	if (numBeads <= 1)
	{
		fout << numBeads << endl;
		return 0;
	}

	if (necklaceIsOneColor(necklace))
	{
		fout << numBeads << endl;
		return 0;
	}

	int localLongest = 1;
	int absoluteLongest = 1;
	for (int i = 0; i < numBeads; ++i)
	{
		//The "countSameBeads" functions modify the necklace by painting the white beads.
		//We want to return it to the same state after every count, hence originalNecklace.
		string originalNecklace = necklace;
		localLongest = countSameBeadsLeft(necklace, i) + countSameBeadsRight(necklace, i + 1);
		necklace = originalNecklace;

		cout << localLongest << " i: " << i << endl;
		if (localLongest > absoluteLongest)
		{
			absoluteLongest = localLongest;
		}
	}

	fout << absoluteLongest << endl;
	return 0;
}