/*
3.10.���������� ������������.��������� ������
������������ ���� ������������� � ���������� ������ ��������,
��������������� �������� �������� �������(0x0D � ����������������� �����),
����� ������������ �������������� ������ ���������� ������,
������� �� ��� ����� ��������, ��� �sin�,
�cos�, �tg�, �ln�, �sqrt�(���������� ������), � ^�(���������� � �������),
� *�, � / �, � + �, � - �, �(�, �)� � ��������(����� ����������� � ���������).
�����, � ������������ � ���������� ����������,
��������� ���������� ����������� �������������� �������� �
������� �� ����� ���������
*/

#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <map>
#define M_PI 3.141592
using namespace std;

// ������� ��� �������� ���������� ����������
int priority(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '^') return 3;
	return -1;
}

// ������� ��� ���������� �������� ��������
double applyOp(double a, double b, char op)
{
	switch (op)
	{
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	case '^': return pow(a, b);
	}
}

// ������� ��� ���������� ������� ��������
double applyFunc(double x, string func)
{
	double radians = x * M_PI / 180;
	if (func == "sin") return round(sin(radians) * 1000) / 1000;
	if (func == "cos") return round(cos(radians) * 1000) / 1000;
	if (func == "tg") return round(tan(radians) * 1000) / 1000;
	if (func == "ln") return log(x);
	if (func == "sqrt") return sqrt(x);
}

// ������� ��� ���������� ��������������� ���������
double evaluate(string tokens)
{
	// ����� ��� �������� ��������� � ����������
	stack <double> values;
	stack <char> ops;
	stack <string> funcs;

	// ������� ��� �������� ������� �������
	map <string, bool> functions;
	functions["sin"] = true;
	functions["cos"] = true;
	functions["tg"] = true;
	functions["ln"] = true;
	functions["sqrt"] = true;

	// ���������� ��� �������� ������� �������
	string curr_func = "";

	for (int i = 0; i < tokens.length(); i++)
	{
		// ���������� �������
		if (tokens[i] == ' ') continue;

		// ���� ������� ������ - ����� ��� �����, �� ��������� �����
		if (isdigit(tokens[i]) || tokens[i] == '.')
		{
			double val = 0.0;
			int dot = 0; // ���������� ������ ����� �������
			while (i < tokens.length() && (isdigit(tokens[i]) || tokens[i] == '.'))
			{
				if (tokens[i] == '.')
				{
					dot++;
				}
				else
				{
					val = val * 10 + (tokens[i] - '0');
					if (dot > 0) dot++;
				}
				i++;
			}
			i--;
			// ����� ����� �� 10 � ������� ���������� ������ ����� �������
			val /= pow(10, dot);

			// ���� ���� ������� �������, �� ��������� �� � ����� � ������ ��������� � ����
			if (curr_func != "")
			{
				val = applyFunc(val, curr_func);
				curr_func = "";
			}

			// ������ ����� � ����
			values.push(val);
		}

		// ���� ������� ������ - �����, �� ��������� �������
		else if (isalpha(tokens[i]))
		{
			string func = "";
			while (i < tokens.length() && isalpha(tokens[i]))
			{
				func += tokens[i];
				i++;
			}
			i--;
			// ���������, ��� ������� ���������� � ������ �� � ���� �������
			if (functions.count(func) > 0)
			{
				funcs.push(func);
				curr_func = func;
			}
			else
			{
				cout << "�������� �������: " << func << endl;
				return NAN;
			}
		}

		// ���� ������� ������ - ����������� ������, �� ������ �� � ���� ����������
		else if (tokens[i] == '(')
		{
			ops.push(tokens[i]);
		}
		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				// ��������� ��� �������� �� �����
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// ��������� �������� �� �����
				char op = ops.top();
				ops.pop();

				// ��������� ��������� � ������ ��� � ����
				values.push(applyOp(val1, val2, op));
			}
			// ������� ����������� ������ �� �����
			if (!ops.empty()) ops.pop();
		}

		// ���� ������� ������ - ��������, �� ��������� ��� �������� � ������� ��� ������ �����������
		else
		{
			while (!ops.empty() && priority(ops.top()) >= priority(tokens[i]))
			{
				// ��������� ��� �������� �� �����
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// ��������� �������� �� �����
				char op = ops.top();
				ops.pop();

				// ��������� ��������� � ������ ��� � ����
				values.push(applyOp(val1, val2, op));
			}
			// ������ ������� �������� � ����
			ops.push(tokens[i]);
		}
	}

	// ��������� ��� ���������� �������� � �����
	while (!ops.empty())
	{
		// ��������� ��� �������� �� �����
		double val2 = values.top();
		values.pop();
		double val1 = values.top();
		values.pop();

		// ��������� �������� �� �����
		char op = ops.top();
		ops.pop();

		// ��������� ��������� � ������ ��� � ����
		values.push(applyOp(val1, val2, op));
	}

	// ���������� ������� ������� ����� ��� ��������� ���������
	return values.top();
}

// ������� ������� ���������
int main()
{
	setlocale(LC_ALL, "RU");
	string expression;

	while (1)
	{
		cout << "������� �������������� ���������: ";
		getline(cin, expression);
		cout << "���������: " << evaluate(expression) << endl; // ������� ��������� �� �����
	}
	return 0;
}