#pragma once

#include <vector>
#include <iostream>
#include <fstream>

void Day1()
{
	using namespace std;

	vector<int> numbers;

	ifstream filin("Day1Numbers.txt", ios::in);
	if (filin.is_open())
	{
		int number;
		while (!filin.eof())
		{
			filin >> number;
			numbers.push_back(number);
		}
	}
	filin.close();

	// Part 1
	for (int i = 0; i < numbers.size(); ++i)
	{
		for (int j = i + 1; j < numbers.size(); ++j)
		{
			for (int k = j + 1; k < numbers.size(); ++k)
			{
				if (numbers[i] + numbers[j] + numbers[k] == 2020)
				{
					cout << numbers[i] * numbers[j] * numbers[k];
				}
			}
		}
	}

	// Part 2

}