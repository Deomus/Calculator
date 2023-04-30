//3.10.–азработка калькул€тора.ѕрограмма должна
//обеспечивать ввод пользователем с клавиатуры строки символов,
//заканчивающейс€ символом Ђ¬озврат кареткиї(0x0D в шестнадцатиричной форме),
//далее осуществл€ть синтаксический разбор полученной строки,
//выдел€€ из нее такие операции, как УsinФ,
//УcosФ, УtgФ, УlnФ, УsqrtФ(квадратный корень), У ^Ф(возведение в степень),
//У *Ф, У / Ф, У + Ф, У - Ф, У(Ф, У)Ф и операнды(числа участвующие в операци€х).
//ƒалее, в соответствии с полученным выражением,
//программе необходимо реализовать математические действи€ и
//вывести на экран результат
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <map>

using namespace std;

int precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	if (op == '^')
		return 3;
	return 0;
}

double applyOp(double a, double b, char op)
{
	switch (op)
	{
	case '+':
		return a + b;
	case '-':
		return a - b;
	case '*':
		return a * b;
	case '/':
		return a / b;
	case '^':
		return pow(a, b);
	}
}

double evaluate(string tokens)
{
	stack<double> values;
	stack<char> ops;

	for (int i = 0; i < tokens.length(); i++)
	{
		if (tokens[i] == ' ')
			continue;

		else if (tokens[i] == '(')
		{
			ops.push(tokens[i]);
		}

		else if (isdigit(tokens[i]))
		{
			double val = 0;

			while (i < tokens.length() && isdigit(tokens[i]))
			{
				val = (val * 10) + (tokens[i] - '0');
				i++;
			}

			values.push(val);

			i--;
		}

		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				double val2 = values.top();
				values.pop();

				double val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			if (!ops.empty())
				ops.pop();
		}

		else
		{
			while (!ops.empty() && precedence(ops.top()) >= precedence(tokens[i]))
			{
				double val2 = values.top();
				values.pop();

				double val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}

			ops.push(tokens[i]);
		}
	}

	while (!ops.empty())
	{
		double val2 = values.top();
		values.pop();

		double val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

int main()
{
	while (1)
	{
		setlocale(LC_ALL, "RU");
		string expression;
		cout << "¬ведите выражение: ";
		getline(cin, expression);
		cout << "–езультат: " << evaluate(expression) << endl;
	}
}
