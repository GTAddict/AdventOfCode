#pragma once

#include <fstream>

void Day8()
{
	using namespace std;

	struct Instruction
	{
		string operation;
		int operand;
		bool executed = false;
		bool opChanged = false;
	};

	ifstream filin("Day8Numbers.txt", ios::in);
	if (filin.is_open())
	{
		vector<Instruction> instructions;

		while (!filin.eof())
		{
			string singleLine;
			getline(filin, singleLine);

			Instruction i;
			char oper[4];
			sscanf(singleLine.c_str(), "%s %d", oper, &i.operand);
			i.operation = oper;
			instructions.push_back(i);
		}

		while (1)
		{
			auto foundIt = std::find_if(instructions.begin(), instructions.end(), [](const Instruction& i) { return (i.operation == "jmp" || i.operation == "nop") && i.opChanged == false; });
			if (foundIt != instructions.end())
			{
				if (foundIt->operation == "nop")
				{
					foundIt->operation = "jmp";
				}
				else if (foundIt->operation == "jmp")
				{
					foundIt->operation = "nop";
				}

				foundIt->opChanged = true;

				std::for_each(instructions.begin(), instructions.end(), [](Instruction& i) { i.executed = false; });

				int accumulator = 0;
				int instructionPointer = 0;
				bool fail = false;

				while (instructionPointer < instructions.size())
				{
					if (instructions[instructionPointer].executed)
					{
						fail = true;
						break;
					}

					instructions[instructionPointer].executed = true;

					string& op = instructions[instructionPointer].operation;
					int operand = instructions[instructionPointer].operand;
					if (op == "nop")
					{
						++instructionPointer;
					}
					else if (op == "acc")
					{
						accumulator += operand;
						++instructionPointer;
					}
					else if (op == "jmp")
					{
						instructionPointer += operand;
					}
				}

				if (foundIt->operation == "nop")
				{
					foundIt->operation = "jmp";
				}
				else if (foundIt->operation == "jmp")
				{
					foundIt->operation = "nop";
				}

				if (!fail)
				{
					cout << accumulator;
					break;
				}
			}
			else
			{
				break;
			}
		}
	}
}