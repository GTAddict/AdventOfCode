#pragma once

#include <fstream>

enum class SplitType
{
	LOWER,
	UPPER
};

void Split(int& low, int& high, SplitType splitType)
{
	if (splitType == SplitType::LOWER)
	{
		high = (low + high) / 2;
	}
	else if (splitType == SplitType::UPPER)
	{
		low = ((low + high) / 2) + 1;
	}
}

void Day5()
{
	using namespace std;

	int highestSeatId = 0;

	ifstream filin("Day5Numbers.txt", ios::in);
	if (filin.is_open())
	{
		std::vector<int> seats;

		while (!filin.eof())
		{
			string boardingPass;
			getline(filin, boardingPass);

			int rowLow = 0;
			int rowHigh = 127;
			int i = 0;

			for (; i < 7; ++i)
			{
				char c = boardingPass.at(i);
				Split(rowLow, rowHigh, c == 'F' ? SplitType::LOWER : SplitType::UPPER);
			}
			
			int columnLow = 0;
			int columnHigh = 7;

			for (; i < 10; ++i)
			{
				char c = boardingPass.at(i);
				Split(columnLow, columnHigh, c == 'L' ? SplitType::LOWER : SplitType::UPPER);
			}

			int seatId = rowLow * 8 + columnLow;
			seats.push_back(seatId);
			// highestSeatId = std::max(highestSeatId, seatId);
		}

		std::sort(seats.begin(), seats.end());
		for (int i = 0; i < seats.size() - 1; ++i)
		{
			if (seats[i] + 1 != seats[i + 1])
			{
				cout << seats[i] << ", " << seats[i + 1] << endl;
			}
		}
	}

	// cout << highestSeatId;
}