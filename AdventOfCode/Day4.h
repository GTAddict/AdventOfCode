#pragma once

#include <fstream>
#include <map>
#include <functional>
#include <unordered_set>

void Day4()
{
	using namespace std;

	auto isValidNum = [](char c) { return (c >= '0' && c <= '9'); };
	auto isValidHex = [&isValidNum](char c) { return isValidNum(c) || (c >= 'a' && c <= 'f'); };

	enum class Field
	{
		begin = 0,

		byr = begin,
		iyr,
		eyr,
		hgt,
		hcl,
		ecl,
		pid,
		// cid,

		count
	};

	map<Field, string> fieldToString = 
	{
		{ Field::byr, "byr:" },
		{ Field::iyr, "iyr:"  },
		{ Field::eyr, "eyr:"  },
		{ Field::hgt, "hgt:" },
		{ Field::hcl, "hcl:"  },
		{ Field::ecl, "ecl:"  },
		{ Field::pid, "pid:"  },
		// { Field::cid, "cid"  }

	};

	map<Field, std::function<bool(std::string&, int)>> fieldFunctionValidation =
	{
		{ Field::byr, [](std::string& record, int position) {	int birthYear = stoi(record.substr(position, 4)); return birthYear >= 1920 && birthYear <= 2002; } },
		{ Field::iyr, [](std::string& record, int position) {	int issueYear = stoi(record.substr(position, 4)); return issueYear >= 2010 && issueYear <= 2020; } },
		{ Field::eyr, [](std::string& record, int position) {	int expirationYear = stoi(record.substr(position, 4)); return expirationYear >= 2020 && expirationYear <= 2030; } },
		{ Field::hgt, [&isValidNum](std::string& record, int position) { string number;  while (isValidNum(record.at(position))) { if (position >= record.size()) return false; number += record.at(position); ++position; } int height = stoi(number);  if (number.size() == 2) { if (record.substr(position, 2) == "in") { if (height >= 59 && height <= 76) return true; } } else if (number.size() == 3) { if (record.substr(position, 2) == "cm") { if (height >= 150 && height <= 193) return true; } }  return false; }},
		{ Field::hcl, [&isValidHex](std::string& record, int position) {	if (record.at(position) != '#') return false; ++position; for (int i = position; i < position + 6; ++i) { if (!isValidHex(record.at(i))) return false; } return true; } },
		{ Field::ecl, [](std::string& record, int position) {	unordered_set<string> colors = {"amb", "blu", "brn", "gry" , "grn" , "hzl", "oth" }; string eyeColor = record.substr(position, 3); return colors.find(eyeColor) != colors.end(); } },
		{ Field::pid, [&isValidNum](std::string& record, int position) {	int i = position;  for (; i < position + 9; ++i) { if (!isValidNum(record.at(i))) return false; } return record.at(i) == ' '; } }
	};

	struct Record
	{
		bool isValid[static_cast<int>(Field::count)];
	};

	int validCount = 0; string s;

	ifstream filin("Day4Numbers.txt", ios::in);
	if (filin.is_open())
	{
		string currentRecord;
		bool recordFail = false;

		while (!filin.eof())
		{
			recordFail = false;
			currentRecord.clear();

			string singleLine;
			do
			{
				singleLine.clear();
				getline(filin, singleLine);
				currentRecord.append(singleLine);
				currentRecord += " ";
			} while (singleLine.size() > 0);

			if (currentRecord.size())
			{
				for (Field f = Field::begin; f < Field::count; f = static_cast<Field>(static_cast<int>(f) + 1))
				{
					int position = currentRecord.find(fieldToString[f]);
					if (position == string::npos)
					{
						recordFail = true;
						break;
					}
					
					if (!fieldFunctionValidation[f](currentRecord, position + fieldToString[f].size()))
					{
						recordFail = true;
						break;
					}
				}
			}

			if (recordFail)
			{
				recordFail = false;
				continue;
			}

			++validCount;
			cout << currentRecord << endl;
		}
	}

	cout << validCount;
}