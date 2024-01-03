#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct Date {
	int day, month, year;
	Month ToMonth() {
		return Month{ month, year };
	}
};
struct Month {
	int month, year;
};
bool operator<(Date lhs, Date rhs) {
	if (lhs.year < rhs.year) { return true; }
	else if (lhs.year == rhs.year)
	{
		if (lhs.month < rhs.month)
		{
			return true;
		}
		else if (lhs.month == rhs.month)
		{
			if (lhs.day < rhs.day)
			{
				return true;
			}
		}
	}
	return false;
}


vector<vector<string>> parts;

int CSVReader()
{
	cout << "Please enter file path> ";
	string path;
	getline(cin, path);
	if (path[0] == '\"' && path.back() == '\"')
	{
		path.pop_back();
		path.erase(path.begin());
	}
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
			vector<string> fields;
			size_t pos = line.find(DELIM);
			for (size_t i = 0; pos != string::npos && i < 8; i++)
			{
				fields.push_back(line.substr(0, pos));
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

	vector<vector<Date>> permonth;
	float ph = 0, mcd = 0, pr = 0, myki = 0, asg = 0, swin = 0;
	
	for (auto& f : parts)
	{
		if (f[2].find("MICHAEL RENN") != string::npos)
		{
			ph += stof(f[4]);
		}
		else if (f[2].find("McD Somerville") != string::npos)
		{
			mcd += stof(f[4]);
		}
		else if (f[2].find("MARC FARES") != string::npos && stof(f[4]) != 40)
		{
			pr += stof(f[4]);
		}
		else if (f[2].find("MYKI") != string::npos)
		{
			myki += stof(f[3]);
		}
		else if (f[2].find("ASG") != string::npos)
		{
			asg += stof(f[4]);
		}
		else if (f[2].find("PURCHASE Swinburne") != string::npos)
		{
			swin += stof(f[3]);
		}
	}
	cout << "Total income from Proffessional Hire: $" << ph << endl;
	cout << "Totol income from McDonalds: $" << mcd << endl;
	cout << "Total income from paper rounds: $" << pr << endl;
	cout << "Total income from ASG: $" << asg << endl;
	cout << "Total expenses on myki travel: -$" << myki << endl;
	cout << "Total Swinburne fees: -$" << swin << endl;
}
