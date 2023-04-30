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
#include <string>
#include <stack>
#include <cmath>
using namespace std;

// ������� ��� �������� ���������� ����������
int priority(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '^') return 3;
	return 0;
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
	if (func == "sin") return sin(x);
	if (func == "cos") return cos(x);
	if (func == "tg") return tan(x);
	if (func == "ln") return log(x);
	if (func == "sqrt") return sqrt(x);
}

// ������� ��� ���������� ��������������� ���������
double evaluate(string expression)
{
	// ����� ��� �������� ����� � ����������
	stack <double> values;
	stack <char> ops;

	// ���������� ������� ��������� ����� �������
	for (int i = 0; i < expression.length(); i++)
	{

		// ���������� �������
		if (expression[i] == ' ') continue;

		// ���� ������� ������ - ����������� ������,
		// �� �������� ��� � ���� ����������
		else if (expression[i] == '(')
		{
			ops.push(expression[i]);
		}

		// ���� ������� ������ - ����� ��� �����,
		// �� ��������� ��� ����������� ����� � �����
		// � ��������� �� ��� �����, ������� �������� � ���� �����
		else if (isdigit(expression[i]) || expression[i] == '.')
		{
			double val = 0;
			int point = -1; // ������� ���������� ����� � �����
			while (i < expression.length() &&
				   (isdigit(expression[i]) || expression[i] == '.'))
			{
				if (expression[i] == '.')
				{
					point = 0; // ����� ���������� �����
				}
				else
				{
					val = (val * 10) + (expression[i] - '0');
					if (point >= 0) point++; // ����������� ���������� ������ ����� �����
				}
				i++;
			}
			if (point > 0)
			{ // ���� ����� �������, �� ����� ��� �� 10 � ������� point
				val = val / pow(10, point);
			}
			values.push(val); // �������� ����� � ���� �����

			// ��� ��� ���� for �������� i �� 1, �� ��������� ��� �� 1,
			// ����� �� ���������� ��������� ������
			i--;
		}

		// ���� ������� ������ - �����,
		// �� ��������� ��� ����������� ����� � ��������� �� ��� ������,
		// ������� ����� ���� ��������� ������� ������� ��� ����������
		else if (isalpha(expression[i]))
		{
			string func = "";
			while (i < expression.length() && isalpha(expression[i]))
			{
				func += expression[i];
				i++;
			}
			// ���� ������ ��������� � ����� �� ������� �������,
			// �� �������� �� � ���� ����������
			if (func == "sin" || func == "cos" || func == "tg" ||
				func == "ln" || func == "sqrt")
			{
				ops.push(func[0]); // �������� ������ ����� ������� � ����
			}
			// �����, ���� ������ �� ��������� �� � ����� �� ������� �������,
			// �� ������� �� ���������� � ������� ��������� �� ������
			else
			{
				cout << "�������� ���������: ����������� ���������� " << func << endl;
				return 0;
			}

			// ��� ��� ���� for �������� i �� 1, �� ��������� ��� �� 1,
			// ����� �� ���������� ��������� ������
			i--;
		}

		// ���� ������� ������ - ����������� ������,
		// �� ��������� ��� �������� ������ ������,
		// ���� �� �������� ����������� ������ � ����� ����������
		else if (expression[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				// ��������� ��� ����� �� ����� �����
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// ��������� �������� �� ����� ����������
				char op = ops.top();
				ops.pop();

				// ��������� ��������� � �������� ��� � ���� �����
				values.push(applyOp(val1, val2, op));
			}
			// ��������� ����������� ������ �� ����� ����������
			if (!ops.empty()) ops.pop();
		}

		// ���� ������� ������ - ��������,
		// �� ��������� ��� ���������� �������� � ������� ��� ������ �����������,
		// ���� �� �������� �������� � ������� ����������� ��� ����������� ������ � ����� ����������
		else
		{
			while (!ops.empty() && priority(ops.top()) >= priority(expression[i]))
			{
				// ��������� ��� ����� �� ����� �����
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// ��������� �������� �� ����� ����������
				char op = ops.top();
				ops.pop();

				// ��������� ��������� � �������� ��� � ���� �����
				values.push(applyOp(val1, val2, op));
			}
			// �������� ������� �������� � ���� ����������
			ops.push(expression[i]);
		}
	}

	// ��������� ��� ���������� �������� � ����� ����������
	while (!ops.empty())
	{
		// ��������� ��� ����� �� ����� �����
		double val2 = values.top();
		values.pop();
		double val1 = values.top();
		values.pop();

		// ��������� �������� �� ����� ����������
		char op = ops.top();
		ops.pop();

		// ��������� ��������� � �������� ��� � ���� �����
		values.push(applyOp(val1, val2, op));
	}

	// ���������� ������� ������� ����� ����� ��� ��������� ���������
	return values.top();
}

// ������� ������� ���������
int main()
{
	setlocale(LC_ALL, "RU");
	while (true)
	{
		cout << "������� �������������� ���������: ";
		string expression;
		getline(cin, expression); // ��������� ������ � ���������� �� ������� �������� �������
		cout << "��������� ����������: ";
		cout << evaluate(expression) << endl;
	}
}