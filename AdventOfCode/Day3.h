#pragma once

#include <fstream>

void Day3()
{
	using namespace std;

	int multiplied = 1;

	ifstream filin("Day3Numbers.txt", ios::in);
	if (filin.is_open())
	{
		vector<string> locations;
		
		while (!filin.eof())
		{
			string singleLine;
			getline(filin, singleLine);
			locations.push_back(std::move(singleLine));
		}

		int width = locations[0].size();
		int height = locations.size();

		int x = 0;
		int y = 0;

		int treesEncountered = 0;

		auto checkTree = [&]()
		{
			if (x < width && y < height)
			{
				if (locations.at(y).at(x) == '#')
				{
					++treesEncountered;
				}
			}
		};

		auto advanceX = [&]()
		{
			++x;
			if (x == width)
			{
				x = 0;
			}
		};

		auto advanceY = [&]()
		{
			++y;
		};

		while (y < height)
		{
			advanceX();
			advanceX();
			advanceX();
			advanceY();
			checkTree();
		}

		multiplied *= treesEncountered;

		x = y = treesEncountered = 0;

		while (y < height)
		{
			advanceX();
			advanceY();
			checkTree();
		}

		multiplied *= treesEncountered;

		x = y = treesEncountered = 0;

		while (y < height)
		{
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceY();
			checkTree();
		}

		multiplied *= treesEncountered;

		x = y = treesEncountered = 0;

		while (y < height)
		{
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceX();
			advanceY();
			checkTree();
		}

		multiplied *= treesEncountered;

		x = y = treesEncountered = 0;

		while (y < height)
		{
			advanceX();
			advanceY();
			advanceY();
			checkTree();
		}

		multiplied *= treesEncountered;
	}

	cout << multiplied;
}