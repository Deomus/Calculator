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
#include <string>
#include <stack>
#include <cmath>
using namespace std;

// Функция для проверки приоритета операторов
int priority(char op)
{
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	if (op == '^') return 3;
	return 0;
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
	if (func == "sin") return sin(x);
	if (func == "cos") return cos(x);
	if (func == "tg") return tan(x);
	if (func == "ln") return log(x);
	if (func == "sqrt") return sqrt(x);
}

// Функция для вычисления арифметического выражения
double evaluate(string expression)
{
	// Стеки для хранения чисел и операторов
	stack <double> values;
	stack <char> ops;

	// Перебираем символы выражения слева направо
	for (int i = 0; i < expression.length(); i++)
	{

		// Пропускаем пробелы
		if (expression[i] == ' ') continue;

		// Если текущий символ - открывающая скобка,
		// то помещаем его в стек операторов
		else if (expression[i] == '(')
		{
			ops.push(expression[i]);
		}

		// Если текущий символ - цифра или точка,
		// то считываем все последующие цифры и точки
		// и формируем из них число, которое помещаем в стек чисел
		else if (isdigit(expression[i]) || expression[i] == '.')
		{
			double val = 0;
			int point = -1; // Позиция десятичной точки в числе
			while (i < expression.length() &&
				   (isdigit(expression[i]) || expression[i] == '.'))
			{
				if (expression[i] == '.')
				{
					point = 0; // Нашли десятичную точку
				}
				else
				{
					val = (val * 10) + (expression[i] - '0');
					if (point >= 0) point++; // Увеличиваем количество знаков после точки
				}
				i++;
			}
			if (point > 0)
			{ // Если число дробное, то делим его на 10 в степени point
				val = val / pow(10, point);
			}
			values.push(val); // Помещаем число в стек чисел

			// Так как цикл for увеличит i на 1, то уменьшаем его на 1,
			// чтобы не пропустить следующий символ
			i--;
		}

		// Если текущий символ - буква,
		// то считываем все последующие буквы и формируем из них строку,
		// которая может быть названием унарной функции или переменной
		else if (isalpha(expression[i]))
		{
			string func = "";
			while (i < expression.length() && isalpha(expression[i]))
			{
				func += expression[i];
				i++;
			}
			// Если строка совпадает с одной из унарных функций,
			// то помещаем ее в стек операторов
			if (func == "sin" || func == "cos" || func == "tg" ||
				func == "ln" || func == "sqrt")
			{
				ops.push(func[0]); // Помещаем первую букву функции в стек
			}
			// Иначе, если строка не совпадает ни с одной из унарных функций,
			// то считаем ее переменной и выводим сообщение об ошибке
			else
			{
				cout << "Неверное выражение: неизвестная переменная " << func << endl;
				return 0;
			}

			// Так как цикл for увеличит i на 1, то уменьшаем его на 1,
			// чтобы не пропустить следующий символ
			i--;
		}

		// Если текущий символ - закрывающая скобка,
		// то вычисляем все операции внутри скобок,
		// пока не встретим открывающую скобку в стеке операторов
		else if (expression[i] == ')')
		{
			while (!ops.empty() && ops.top() != '(')
			{
				// Извлекаем два числа из стека чисел
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// Извлекаем оператор из стека операторов
				char op = ops.top();
				ops.pop();

				// Вычисляем результат и помещаем его в стек чисел
				values.push(applyOp(val1, val2, op));
			}
			// Извлекаем открывающую скобку из стека операторов
			if (!ops.empty()) ops.pop();
		}

		// Если текущий символ - оператор,
		// то вычисляем все предыдущие операции с большим или равным приоритетом,
		// пока не встретим оператор с меньшим приоритетом или открывающую скобку в стеке операторов
		else
		{
			while (!ops.empty() && priority(ops.top()) >= priority(expression[i]))
			{
				// Извлекаем два числа из стека чисел
				double val2 = values.top();
				values.pop();
				double val1 = values.top();
				values.pop();

				// Извлекаем оператор из стека операторов
				char op = ops.top();
				ops.pop();

				// Вычисляем результат и помещаем его в стек чисел
				values.push(applyOp(val1, val2, op));
			}
			// Помещаем текущий оператор в стек операторов
			ops.push(expression[i]);
		}
	}

	// Вычисляем все оставшиеся операции в стеке операторов
	while (!ops.empty())
	{
		// Извлекаем два числа из стека чисел
		double val2 = values.top();
		values.pop();
		double val1 = values.top();
		values.pop();

		// Извлекаем оператор из стека операторов
		char op = ops.top();
		ops.pop();

		// Вычисляем результат и помещаем его в стек чисел
		values.push(applyOp(val1, val2, op));
	}

	// Возвращаем верхний элемент стека чисел как результат выражения
	return values.top();
}

// Главная функция программы
int main()
{
	setlocale(LC_ALL, "RU");
	while (true)
	{
		cout << "Введите арифметическое выражение: ";
		string expression;
		getline(cin, expression); // Считываем строку с клавиатуры до символа «Возврат каретки»
		cout << "Результат вычисления: ";
		cout << evaluate(expression) << endl;
	}
}