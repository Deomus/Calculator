/*
3.10.Разработка калькулятора.Программа должна
обеспечивать ввод пользователем с клавиатуры строки символов,
заканчивающейся символом «Возврат каретки»(0x0D в шестнадцатиричной форме),
далее осуществлять синтаксический разбор полученной строки,
выделяя из нее такие операции, как “sin”,
“cos”, “tg”, “ln”, “sqrt”(квадратный корень), “ ^”(возведение в степень),
“ *”, “ / ”, “ + ”, “ - ”, “(”, “)” и операнды(числа участвующие в операциях).
Далее, в соответствии с полученным выражением,
программе необходимо реализовать математические действия и
вывести на экран результат
*/

#include <iostream>
#include <cmath>
#include <stack>
#include <string>
#include <map>
#define M_PI 3.141592
using namespace std;

// Функция для проверки приоритета операторов
int priority(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '^') return 3;
	return -1;
}

// Функция для вычисления бинарной операции
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

// Функция для вычисления унарной операции
double applyFunc(double x, string func)
{
	double radians = x * M_PI / 180;
	if (func == "sin") return round(sin(radians) * 1000) / 1000;
	if (func == "cos") return round(cos(radians) * 1000) / 1000;
	if (func == "tg") return round(tan(radians) * 1000) / 1000;
	if (func == "ln") return log(x);
	if (func == "sqrt") return sqrt(x);
}

// Функция для вычисления арифметического выражения
double evaluate(string tokens)
{
	// Стеки для хранения операндов и операторов
	stack <double> values;
	stack <char> ops;
	stack <string> funcs;

	// Словарь для хранения унарных функций
	map <string, bool> functions;
	functions["sin"] = true;
	functions["cos"] = true;
	functions["tg"] = true;
	functions["ln"] = true;
	functions["sqrt"] = true;

	// Переменная для хранения текущей функции
	string curr_func = "";

	for (int i = 0; i < tokens.length(); i++)
	{
		// Пропускаем пробелы
		if (tokens[i] == ' ') continue;

		// Если текущий символ - цифра или точка, то считываем число
		if (isdigit(tokens[i]) || tokens[i] == '.')
		{
			double val = 0.0;
			int dot = 0; // Количество знаков после запятой
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
			// Делим число на 10 в степени количества знаков после запятой
			val /= pow(10, dot);

			// Если есть текущая функция, то применяем ее к числу и кладем результат в стек
			if (curr_func != "")
			{
				val = applyFunc(val, curr_func);
				curr_func = "";
			}

			// Кладем число в стек
			values.push(val);
		}

		// Если текущий символ - буква, то считываем функцию
		else if (isalpha(tokens[i]))
		{
			string func = "";
			while (i < tokens.length() && isalpha(tokens[i]))
			{
				func += tokens[i];
				i++;
			}
			i--;
			// Проверяем, что функция существует и кладем ее в стек функций
			if (functions.count(func) > 0)
			{
				funcs.push(func);
				curr_func = func;
			}
			else
			{
				cout << "Неверная функция: " << func << endl;
				return NAN;
			}
		}

		// Если текущий символ - открывающая скобка, то кладем ее в стек операторов
		else if (tokens[i] == '(')
		{
			ops.push(tokens[i]);
		}
		else if (tokens[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				// Извлекаем два операнда из стека
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// Извлекаем оператор из стека
				char op = ops.top();
				ops.pop();

				// Вычисляем результат и кладем его в стек
				values.push(applyOp(val1, val2, op));
			}
			// Удаляем открывающую скобку из стека
			if (!ops.empty()) ops.pop();
		}

		// Если текущий символ - оператор, то вычисляем все операции с большим или равным приоритетом
		else
		{
			while (!ops.empty() && priority(ops.top()) >= priority(tokens[i]))
			{
				// Извлекаем два операнда из стека
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// Извлекаем оператор из стека
				char op = ops.top();
				ops.pop();

				// Вычисляем результат и кладем его в стек
				values.push(applyOp(val1, val2, op));
			}
			// Кладем текущий оператор в стек
			ops.push(tokens[i]);
		}
	}

	// Вычисляем все оставшиеся операции в стеке
	while (!ops.empty())
	{
		// Извлекаем два операнда из стека
		double val2 = values.top();
		values.pop();
		double val1 = values.top();
		values.pop();

		// Извлекаем оператор из стека
		char op = ops.top();
		ops.pop();

		// Вычисляем результат и кладем его в стек
		values.push(applyOp(val1, val2, op));
	}

	// Возвращаем верхний элемент стека как результат выражения
	return values.top();
}

// Главная функция программы
int main()
{
	setlocale(LC_ALL, "RU");
	string expression;

	while (1)
	{
		cout << "Введите арифметическое выражение: ";
		getline(cin, expression);
		cout << "Результат: " << evaluate(expression) << endl; // Выводим результат на экран
	}
	return 0;
}