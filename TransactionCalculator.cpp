// TransactionCalculator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

vector<string[8]> parts;

int CSVReader()
{
	cout << "Please enter file path> " << endl;
	string path;
	getline(cin, path);
	ifstream file(path);
	if (!file)
	{
		cout << "This is not a valid file path." << endl;
		return 1;
	}

	string line;
	getline(file, line);
	if (line != "Bank Account,Date,Narrative,Debit Amount,Credit Amount,Balance,Categories,Serial")
	{
		cout << "File in wrong format" << endl;
		return 1;
	}

	
	const string DELIM = ",";
	while (getline(file, line))
	{
		if (!line.empty())
		{
			string fields[8];
			size_t pos = line.find(DELIM);
			for (size_t i = 0; pos != string::npos && i < 8; i++)
			{
				fields[i] = line.substr(0, pos);
				line.erase(0, pos + 1);
				pos = line.find(DELIM);
			}
			parts.push_back(fields);
		}
	}
}

int main()
{
	int val = CSVReader();
	if (val == 1)
	{
		return 1;
	}


	float ph = 0, mcd = 0, osko = 0, myki = 0, asg = 0, swin = 0;
	for (auto& f : parts)
	{
		if (f[2].find("MICHAEL RENN") != string::npos)
		{
			ph += stof(f[4]);
		}
		else if	(f[2].find("McD Somerville") != string::npos)
		{
			mcd += stof(f[4]);
		}
		else if	(f[2].find("OSKO") != string::npos)
		{
			osko += stof(f[4]);
		}
		else if	(f[2].find("MYKI") != string::npos)
		{
			myki += stof(f[3]);
		}
		else if	(f[2].find("ASG") != string::npos)
		{
			asg += stof(f[4]);
		}
		else if	(f[2].find("PURCHASE Swinburne") != string::npos)
		{
			swin += stof(f[3]);
		}

	}
}
