#pragma once

#include <fstream>
#include <string>
#include <algorithm>

void Day2()
{
#pragma warning (disable:4996)
	using namespace std;

	int validPasswords = 0;

	int minCount = 0;
	int maxCount = 0;
	char letter = '\0';
	string password;

	char pass[100];
	ifstream filin("Day2Numbers.txt", ios::in);
	if (filin.is_open())
	{
		while (!filin.eof())
		{
			string singleLine;
			getline(filin, singleLine);
			if (!singleLine.empty())
			{
				sscanf(singleLine.c_str(), "%d-%d %c: %s", &minCount, &maxCount, &letter, pass);
				password = pass;

				// Part 1
				// int currentCount = count(password.begin(), password.end(), letter);
				// if (currentCount >= minCount && currentCount <= maxCount)
				// {
				// 	++validPasswords;
				// }

				// Part 2
				bool foundAPass = false;
				if (password.at(minCount - 1) == letter)
				{
					foundAPass = true;
				}

				if (password.at(maxCount - 1) == letter)
				{
					if (foundAPass)
					{
						continue;
					}
					else
					{
						foundAPass = true;
					}
				}

				if (foundAPass)
				{
					++validPasswords;
				}
			}
		}
	}
	filin.close();

	cout << validPasswords;

}
