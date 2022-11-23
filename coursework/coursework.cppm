#include <Windows.h>
import <iostream>;
import <string>;
import <fstream>;
import <conio.h>;
import list;
import pArrFunc;
//using namespace std;
//import func;
//using std::cout;
//using std::unique_ptr;


int main()
{
	//setlocale(LC_ALL, "rus");
    using namespace std;
	using namespace List;
	using namespace pArrFunc;
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    

	/*Node<string>** pArray = nullptr;
    
	pArray = new Node<string>*[arrSize];
	for (int i = 0; i < arrSize; ++i)
	{
		pArray[i] = new Node<string>[25];
	}
	for (int i = 0; i < arrSize; ++i)
	{
		delete[] pArray[i];
	}
	delete[] pArray;*/

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
	

	/*Node<string> node1{ "Строка 1" };
	cout << node1;*/
	
	/*Node<string>* node1 = new Node<string>{ "Строка 1" };
	Node<string>* node2 = new Node<string>{ "Строка 2" };
	addAtEndList(node1, node2);
	Node<string>* node3 = new Node<string>{ "Строка 3" };
	addAtEndList(node1, node3);
	Node<string>* node4 = new Node<string>{ "Строка 4" };
	addAtEndList(node1, node4);
	unsigned int id = 0;
	showList(node1, id);
	cout << id;*/

	//Node<string>* head = nullptr;

	int ch = 0;
	while (ch != 27) {
		system("cls");
		showArr(arr);
		cout << "0 - загрузка строк из txt(ANSI) файла" << endl;
		cout << "1 - сохранение строк в txt(ANSI) файл" << endl;
		cout << "2 - загрузка строк из бинарного файла" << endl;
		cout << "3 - сохранение строк в бинарный файл" << endl;
		cout << "4 - добавить строку" << endl;
		cout << "5 - удалить строку" << endl;
		cout << "6 - включение строки по логическому номеру" << endl;
		cout << "7 - включение строки по логическому номеру с сохранением порядка" << endl;
		cout << "8 - извлечение строки по логическому номеру" << endl;
		cout << "9 - сортировка всей структуры" << endl;
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
			break;
		}
		case 51: // 3
		{
			break;
		}
		case 52: // 4
		{
			addAtArr(arr);
			break;
		}
		case 53: // 5
		{
			break;
		}
		case 54: // 6
		{
			break;
		}
		default:
			break;
		}
		system("pause");
	}    
	for (int i = 0; i < arrSize; ++i) { // освобождения элементов динамического массива Node
		delete arr[i];
	}
	delete[] arr; // освобождения динамического массива Node

    //cout << node1->getStr() << endl;
    //Node<string> node1{ "Строка" };
    //cout << node1.getNext() << endl;
    //cout << node1.getStr() << endl;

    //unique_ptr<int> ptr(new int()); // умные указатели bad
    //auto ptr1(new int()); // good
    ///*auto str = "Hello world";
    //auto p = make_shared<int>(2);

    
	
	/*Node<string>* objPtr = new Node<string>[COUNT_NODE];*/
	

    //Node<string>* head = new Node<string>{ "Строка 1" };

    //string fName = "отрывок.txt", tmp;
    //ifstream fin;
    //fin.open(fName);
    //if (!fin.is_open())
    //{
    //    cout << "Файл не может быть открыт или создан"; // throw
    //    return 1;
    //}

    //while (!fin.eof()) {
    //    getline(fin, tmp);
    //    if (!tmp.empty()) {
    //        //cout << tmp << endl;
    //        Node<string>* newNode = new Node<string>{ tmp };
    //        addAtEndList(head, newNode);
    //    } 
    //}
    //
    //fin.close();

    //showList(head);
    /*Node<string>* objPtr = static_cast<Node<string>*>(operator new[](COUNT_OBJ * sizeof(Node<string>)));
    for (int i = 0; i < COUNT_OBJ; ++i) new (objPtr + i) Node<string>(i + 5);*/
    return 0;
}
