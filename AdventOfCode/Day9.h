#include <fstream>

void Day9()
{
	using namespace std;

	ifstream filin("Day9Numbers.txt", ios::in);
	if (filin.is_open())
	{
		uint64_t preambleSize = 25;

		vector<uint64_t> numbers;

		while (!filin.eof())
		{
			string singleLine;
			getline(filin, singleLine);
			numbers.push_back(stoll(singleLine));
		}

		uint64_t invalidNum = 0;
		uint64_t invalidNumIndex = 0;

		for (uint64_t i = preambleSize; i < numbers.size(); ++i)
		{
			bool found = false;

			for (uint64_t j = i - preambleSize; j < i; ++j)
			{
				uint64_t difference = numbers[i] - numbers[j];
				if (numbers[j] != difference)
				{
					for (uint64_t k = j; k < i; ++k)
					{
						if (numbers[k] == difference)
						{
							found = true;
							break;
						}
					}
				}
			}

			if (!found)
			{
				invalidNum = numbers[i];
				invalidNumIndex = i;
				break;
			}
		}

		std::cout << invalidNum;

		uint64_t lowerBound = 0;
		uint64_t upperBound = 0;

		for (uint64_t i = 0; i < invalidNumIndex; ++i)
		{
			int sumSoFar = numbers[i];
			bool found = false;

			for (uint64_t j = i + 1; j < invalidNumIndex; ++j)
			{
				sumSoFar += numbers[j];

				if (sumSoFar == invalidNum)
				{
					found = true;
					upperBound = j;
					break;
				}
				else if (sumSoFar > invalidNum)
				{
					break;
				}
			}

			if (found)
			{
				lowerBound = i;
			}
		}

		uint64_t lowestNum = UINT64_MAX;
		uint64_t highestNum = 0;

		for (uint64_t i = lowerBound; i <= upperBound; ++i)
		{
			lowestNum = min(lowestNum, numbers[i]);
			highestNum = max(highestNum, numbers[i]);
		}

		cout << endl << lowestNum + highestNum;
	}
}