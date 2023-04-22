#include <iostream>
#include <string>
using namespace std;

void fine(string raw)
{
	if (raw == "+")
	{
	}
	else if (raw == "-")
	{
	}
	else if (raw == "/")
	{
	}
	else if (raw == "*")
	{
	}
	else if (raw == "")
	{

	}
}

int main()
{
	string entered;
	cin >> entered;

	string current;
	for (int i = 0; i < entered.size(); i++)
	{
		if (entered[i] == ' ')
			fine(current);
		else
			current += entered[i];
	}
}