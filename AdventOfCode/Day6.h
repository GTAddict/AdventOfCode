#pragma once
#include <fstream>
#include <unordered_set>
#include <unordered_map>

// Part 1
//void Day6()
//{
//	using namespace std;
//
//	int totalYeses = 0;
//
//	ifstream filin("Day6Numbers.txt", ios::in);
//	if (filin.is_open())
//	{
//		while (!filin.eof())
//		{
//			std::unordered_set<char> occurrences;
//
//			string singleLine;
//			do
//			{
//				singleLine.clear();
//				getline(filin, singleLine);
//
//				for (char c : singleLine)
//				{
//					occurrences.insert(c);
//				}
//
//			} while (singleLine.size() > 0);
//
//			int currentYeses = occurrences.size();
//			totalYeses += currentYeses;
//		}
//	}
//
//	cout << totalYeses;
//}

// Part 2
void Day6()
{
	using namespace std;

	int totalYeses = 0;

	ifstream filin("Day6Numbers.txt", ios::in);
	if (filin.is_open())
	{
		while (!filin.eof())
		{
			std::unordered_map<char, int> occurrences;
			for (char c = 'a'; c <= 'z'; c++)
			{
				occurrences.insert(std::pair<char, int>(c, 0));
			}
			int numPeople = 0;

			string singleLine;
			do
			{
				singleLine.clear();
				getline(filin, singleLine);

				if (singleLine.size() > 0)
				{
					++numPeople;

					for (char c : singleLine)
					{
						++occurrences[c];
					}
				}

			} while (singleLine.size() > 0);

			int currentYeses = 0;
			for (auto pair : occurrences)
			{
				if (pair.second == numPeople)
				{
					++currentYeses;
				}
			}

			totalYeses += currentYeses;
		}
	}

	cout << totalYeses;
}