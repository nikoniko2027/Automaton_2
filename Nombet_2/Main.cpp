#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct ret { // ��������� ������������ ������
	string type; // ���
	string word; // ��������� ������
};

struct letter { // ��������� ����� � �����
	int id; // ����
	int next; // ��������� �� ������� � ������� ����
	string symbol; // ������
};

struct lexer { // ��������� �������
	string Type; // ���
	int start; // ������� ����
	int end; // �������� ����
	int level; // ������� �������
	vector <letter> elements; // ��� ����� �������
};

struct lvl { // ��������� ������ �������
	string input; // �������� �������� �����
	int level; // ������� �������
};

vector<ret>MaxString(string str, vector <lexer> A) {
	vector <ret> sup; // ������ ��� �������� ������
	int min = 1, max = 1;
	for (int i = 0; i < A.size(); i++) // �������� ������������ ������� �������
		if (max < A[i].level)
			max = A[i].level;
	for (int i = 0; i < str.size(); i++) { // ����������� �� ���� ������
		int MAX = max; // ������� ������ �������
		vector <lexer> B; // ��������������� ��������� ������
		for (int j = 0; j < A.size(); j++) { // ����������� ������ �� �������, � ������� ������� ������� ��������� � ����������� ��������� ������
			if (str.substr(i, 1) == A[j].elements[0].symbol)
				B.push_back(A[j]); // ��������� ��� ��������� �����
		}
		while (MAX > 0) { // ��������� ������ ������� �������
			bool fl = false;
			for (int j = 0; j < B.size(); j++) { // �������� � ������������ ��������
				int V = 0;
				if (!fl) { // ���� ��� ������� ��������
					for (int l = 0; l < B[j].elements.size(); l++) { // ����������� �� ���������
						if (str.substr(i + B[j].elements[l].id, 1) == B[j].elements[l].symbol && B[j].level == MAX) // ���� �� �������� ������ ��������� � ������� ��������������
							V++;
						else
							break;
					}
					if (V == B[j].end) { // ������������ ��������� ������
						fl = true; // True - ������� ������ � � ��������� ��������� �� ���������
						ret b; // ���������� ��� ��������
						b.type = B[j].Type; // ��������� ��
						b.word = str.substr(i, V);
						sup.push_back(b); // ���������� � �������������� ������
						i += V - 1; // ������� ������� � ������
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
	while (in.peek() != EOF) { // ��������� �����, �� ������� ��� ����� �������� ������
		lvl X;
		in >> X.input;
		in >> X.level;
		inputs.push_back(X);
	}
	in.close();

	for (int i = 0; i < inputs.size(); i++) { // �������� ������ �� �������� ������
		ifstream in(inputs[i].input + ".txt");
		while (in.peek() != EOF) { // ��������� ������� ����
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
	cout << "������� ������ ��� ��������: "; // ������� �������������� ������
	getline(cin, str);
	sup = MaxString(str, A);
	system("cls");
	cout << "===��������� ����� ��������� ������===\n" << endl;
	cout << str << endl;
	cout << "\n======================================\n" << endl;
	for (int i = 0; i < sup.size(); i++)
		cout << "<'" << sup[i].word << "', " << sup[i].type << ">" << endl;
	cout << endl;
	//for (int i = 0; i < inputs.size(); i++) // �������� ��������������� ������
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