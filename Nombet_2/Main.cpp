#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct ret { // Структура возвращаемых данных
	string type; // Тип
	string word; // Найденный объект
};

struct letter { // Структура буквы в слове
	int id; // Айди
	int next; // Указатель на переход к другому айди
	string symbol; // Символ
};

struct lexer { // Структура объекта
	string Type; // Тип
	int start; // Входной айди
	int end; // Выходной айди
	int level; // Уровень объекта
	vector <letter> elements; // Все буквы объекта
};

struct lvl { // Структура уровня объекта
	string input; // Название входного файла
	int level; // Уровень объекта
};

vector<ret>MaxString(string str, vector <lexer> A) {
	vector <ret> sup; // Вектор для возврата данных
	int min = 1, max = 1;
	for (int i = 0; i < A.size(); i++) // Получаем максимальный уровень объекта
		if (max < A[i].level)
			max = A[i].level;
	for (int i = 0; i < str.size(); i++) { // Пробегаемся по всей строке
		int MAX = max; // Уровень поиска объекта
		vector <lexer> B; // Вспомогательный векторный массив
		for (int j = 0; j < A.size(); j++) { // Выгружаются только те объекты, у которых входные символы совпадают с проверяемым элементом строки
			if (str.substr(i, 1) == A[j].elements[0].symbol)
				B.push_back(A[j]); // Сохраняем все возможные слова
		}
		while (MAX > 0) { // Проверяем каждый уровень объекта
			bool fl = false;
			for (int j = 0; j < B.size(); j++) { // Работаем с выгруженными массивом
				int V = 0;
				if (!fl) { // Если уже элемент проверен
					for (int l = 0; l < B[j].elements.size(); l++) { // Пробегаемся по переходам
						if (str.substr(i + B[j].elements[l].id, 1) == B[j].elements[l].symbol && B[j].level == MAX) // Если по переходу символ совпадает и уровень соотвествующий
							V++;
						else
							break;
					}
					if (V == B[j].end) { // Регистрируем найденный объект
						fl = true; // True - элемент найден и в повторной обработке не нуждается
						ret b; // Переменная для возврата
						b.type = B[j].Type; // Заполняем ее
						b.word = str.substr(i, V);
						sup.push_back(b); // Отправляем в результирующий вектор
						i += V - 1; // Смещаем каретку в строке
						break;
					}
				}
				else 
					break;
			}
			MAX--;
		}
		B.clear();
	}
	return sup;
}

int main() {
	setlocale(LC_ALL, "RUS");
	vector <lvl> inputs;
	vector <lexer> A;
	vector <ret> sup;
	string str;
	ifstream in("input.txt");
	while (in.peek() != EOF) { // Считываем файлы, из которых нам нужно получить данные
		lvl X;
		in >> X.input;
		in >> X.level;
		inputs.push_back(X);
	}
	in.close();

	for (int i = 0; i < inputs.size(); i++) { // Получаем данные из указаных файлов
		ifstream in(inputs[i].input + ".txt");
		while (in.peek() != EOF) { // Сканируем входной файл
			lexer B;
			string x;
			letter X;
			B.Type = inputs[i].input;
			B.level = inputs[i].level;
			in >> x;
			if (x == "start:")
				in >> B.start;
			in >> x;
			if (x == "end:")
				in >> B.end;
			for (int j = 0; j < B.end; j++) {
				string l;
				in >> X.id;
				in >> X.symbol;
				in >> X.next;
				if (X.symbol == "/s")
					X.symbol = " ";
				B.elements.push_back(X);
			}
			A.push_back(B);
		}
		in.close();
	}
	cout << "Введите строку для проверки: "; // Выводим результирующие данные
	getline(cin, str);
	sup = MaxString(str, A);
	system("cls");
	cout << "===Результат после обработки строки===\n" << endl;
	cout << str << endl;
	cout << "\n======================================\n" << endl;
	for (int i = 0; i < sup.size(); i++)
		cout << "<'" << sup[i].word << "', " << sup[i].type << ">" << endl;
	cout << endl;
	//for (int i = 0; i < inputs.size(); i++) // Проверка импортированных данных
	//	cout << inputs[i].input << " LVL: "  << inputs[i].level << endl;
	//cout << endl;
	//for (int i = 0; i < A.size(); i++) {
	//	cout << "Type: " << A[i].Type << endl;
	//	cout << "Start: " << A[i].start << endl;
	//	cout << "End: " << A[i].end << endl;
	//	for (int j = 0; j < A[i].elements.size(); j++)
	//		cout << A[i].elements[j].id << " " << A[i].elements[j].symbol << " " << A[i].elements[j].next << endl;
	//	cout << endl;
	//}
	system("pause");
	return 0;
}