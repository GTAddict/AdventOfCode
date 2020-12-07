#pragma once

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_set>

void Day7()
{
	using namespace std;

	struct Bag
	{
		string ID;
		unordered_set<Bag*> parents;
		map<Bag*, int> children;
	};

	map<string, Bag*> bagLookup;

	ifstream filin("Day7Numbers.txt", ios::in);
	if (filin.is_open())
	{
		while (!filin.eof())
		{
			string singleLine;
			getline(filin, singleLine);

			stringstream ss(singleLine);
			string token;
			vector<string> tokens;
			while (getline(ss, token, ' '))
			{
				tokens.push_back(token);
			}

			string ID = tokens[0] + tokens[1];
			if (bagLookup.find(ID) == bagLookup.end())
			{
				Bag* bag = new Bag();
				bag->ID = ID;
				bagLookup[ID] = bag;
			}

			for (int i = 4; i < tokens.size(); i += 4)
			{
				if (tokens[i] != "no")
				{
					int num = stoi(tokens[i]);
					string childBagID = tokens[i + 1] + tokens[i + 2];
					if (bagLookup.find(childBagID) == bagLookup.end())
					{
						Bag* childBag = new Bag();
						childBag->ID = childBagID;
						bagLookup[childBagID] = childBag;
					}

					Bag* parentBag = bagLookup[ID];
					Bag* childBag = bagLookup[childBagID];
					childBag->parents.insert(parentBag);
					parentBag->children[childBag] = num;
				}
			}
		}

		string searchID = "shinygold";

		unordered_set<Bag*> visited;
		vector<Bag*> frontier;

		frontier.push_back(bagLookup[searchID]);
		
		while (!frontier.empty())
		{
			Bag* bag = frontier.back();
			frontier.pop_back();
			visited.insert(bag);

			for (Bag* parent : bag->parents)
			{
				if (visited.find(parent) == visited.end())
				{
					frontier.push_back(parent);
				}
			}
		}

		visited.erase(bagLookup[searchID]);
		cout << visited.size() << endl;

		std::function<int(Bag*)> countChildren = [&countChildren](Bag* bag)
		{
			int totalChildren = 0;

			for (auto pair : bag->children)
			{
				totalChildren += countChildren(pair.first) * pair.second;
			}

			return totalChildren + 1;
		};

		cout << countChildren(bagLookup[searchID]) - 1;
	}

}