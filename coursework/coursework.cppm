#include <Windows.h>
import <iostream>;
import <string>;
import <fstream>;
import <conio.h>;
import <limits>;
import list;
import pArrFunc;
//using namespace std;
//import func;
//using std::cout;
//using std::unique_ptr;
#if defined(max)
#undef max
#endif

int main()
{
	//setlocale(LC_ALL, "rus");
    using namespace std;
	using namespace List;
	using namespace pArrFunc;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	List::COUNT_NODE = 0; // default 5
	while (List::COUNT_NODE < 3) {
		system("cls");
		cout << "введите максимальное значение списка(не меньше 3): ";
		cin >> List::COUNT_NODE;
		cin.ignore();
		if (!cin) {
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cin.clear();
			cin.get();
		}
	}
	

	Node<string>** arr = nullptr;
	arr = new Node<string>*[arrSize]; // инициализирование динамического массива Node
	for (int i = 0; i < arrSize; ++i) {
		arr[i] = new Node<string>;
		cout << arr[i];
		// считывание в массив из файла
	}
	//for (int i = 0; i < arrSize; ++i) { // освобождения элементов динамического массива Node
	//	delete arr[i];
	//}
	//delete[] arr; // освобождения динамического массива Node	
	/*Node<string>* node1 = new Node<string>{ "Строка 1" };
	Node<string>* node2 = new Node<string>{ "Строка 2" };
	if (*node1 < *node2) {
		cout << "Da";
	}*/
	/*addAtEndList(node1, node2);
	Node<string>* node3 = new Node<string>{ "Строка 3" };
	addAtEndList(node1, node3);
	Node<string>* node4 = new Node<string>{ "Строка 4" };
	addAtEndList(node1, node4);
	unsigned int id = 0;
	showList(node1, id);
	cout << id;*/

	int ch = 0; bool debug = true;
	while (ch != 27) {
		system("cls");
		cout << "d - выводить весь список по умолчанию: "; if (debug) { cout << "true"; } else { cout << "false"; } cout << endl;
		if (debug) { showArr(arr); }			
		
		
		cout << "0 - загрузка строк из txt(ANSI) файла" << endl;
		cout << "1 - сохранение строк в txt(ANSI) файл" << endl;
		cout << "2 - загрузка строк из бинарного файла" << endl;
		cout << "3 - сохранение строк в бинарный файл" << endl; 
		cout << "4 - добавить строку в конец" << endl;
		cout << "5 - удалить последнюю строку" << endl;
		cout << "6 - включение строки по логическому номеру с сохранением порядка" << endl;
		cout << "7 - включение строки по логическому номеру" << endl; //
		cout << "8 - извлечение строки по логическому номеру" << endl;
		cout << "9 - сортировка" << endl; //
		cout << "b - балансировка " << endl;
		cout << "p - вывод по n" << endl;
		//балансировка
		
		cout << "Esc - выход" << endl;
		//head->print();
		ch = _getch();
		switch (ch)
		{
		case 48: // 0
		{
			readFromTxtANSI(arr);
			break;
		}
		case 49: // 1
		{
			writeToTxtANSI(arr);
			break;
		}
		case 50: // 2
		{
			readFromBin(arr);
			break;
		}
		case 51: // 3
		{
			writeToBin(arr);
			break;
		}
		case 52: // 4
		{
			addAtArr(arr);
			break;
		}
		case 53: // 5
		{
			delInArr(arr);
			break;
		}
		case 54: // 6
		{
			addInArrByIdWithOrder(arr);
			break;
		}
		case 55: // 7
		{
			addInArrById(arr);
			break;
		}
		case 56: // 8
		{
			delInArrById(arr);
			break;
		}
		case 57: // 9
		{
			sortArr(arr);
			break;
		} 
		case 98: // b
		{
			balanceArr(arr);
			break;
		}
		case 112: // p
		{
			showArrByN(arr);
			break;
		}		
		case 100: // d
		{
			if (debug) {
				debug = false;
			}
			else {
				debug = true;
			}
			break;
		}
		default:
			break;
		}
		system("pause");
	}    
	//for (int i = 0; i < arrSize; ++i) { // освобождения элементов динамического массива Node
	//	delete arr[i];
	//}
	//delete[] arr; // освобождения динамического массива Node
    return 0;
}