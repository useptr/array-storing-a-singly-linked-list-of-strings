export module pArrFunc;
import <iostream>;
import <string>;
import <fstream>;
import <conio.h>;
import list;
export namespace pArrFunc {
    using namespace std;
    using namespace List;
    unsigned int arrSize = List::COUNT_NODE;
    unsigned int possibleInsertList = 0;

    void addAtArr(Node<string>** &arr);
    void resizeArr(Node<string>**& arr);
    void showArr(Node<string>** arr);
    void writeToTxtANSI(Node<string>** arr);
    void readFromTxtANSI(Node<string>**& arr);
    void delInArr(Node<string>** arr);

    void resizeArr(Node<string>** &arr)
    {
        Node<string>** resize;        
        resize = new Node<string>*[arrSize*2];
        for (int i = 0; i < arrSize; ++i) {
            //resize[i] = new Node<string>;
            resize[i] = arr[i];
            //delete arr[i];
        }
        for (int i = arrSize; i < arrSize*2; ++i) {
            //resize[i] = new Node<string>arr[i];
            resize[i] = new Node<string>;
        }
        delete[] arr;
        arr = resize;
        arrSize *= 2;
    }

    void addAtArr(Node<string>** &arr) {
        Node<string>* newNode = new Node<string>;
        cout << "Введите str_: ";
        cin >> newNode;
        if (possibleInsert(arr[possibleInsertList])) {
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }
        else {
            possibleInsertList++;
            if (possibleInsertList >= arrSize) { // хватает ли динамического массива
                resizeArr(arr); // ресайз
            }
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }        
    }   
    void addInArrById(Node<string>**& arr) {
        Node<string>* newNode = new Node<string>;
        cout << "Введите str_: ";
        cin >> newNode;

        unsigned int insertId = 0; unsigned int nowId = 0;
        cout << "Введите id: ";
        cin >> insertId;
        cin.ignore();

        for (int i = 0; i <= possibleInsertList; ++i) {
            if (insertNodeById(arr, i, insertId, nowId, newNode)) {
                return;
            }
        }
        if (insertId == nowId + 1) {
            if (possibleInsert(arr[possibleInsertList])) {
                insertNodeAtEnd(arr, possibleInsertList, newNode);
            }
            else {
                possibleInsertList++;
                if (possibleInsertList >= arrSize) { // хватает ли динамического массива
                    resizeArr(arr); // ресайз
                }
                insertNodeAtEnd(arr, possibleInsertList, newNode);
            }
        }
        else {
            cout << "id должен быть не меньше 0 и не больше " << nowId + 1 << endl;
        }

    }
    void delInArr(Node<string>** arr) {
        if (possibleDel(arr[possibleInsertList])) { // возможно ли удалить
            int res = delLastNode(arr[possibleInsertList]);
            if (res == 1 && possibleInsertList >= 1) { // если мы удалили первый элемент списка, то уменьшаем possibleInsertList
                possibleInsertList--;
            }
        } else {
            if (possibleInsertList >= 1) { // если удалять в текущем списке нечего, то уменьшаем possibleInsertList
                possibleInsertList--;
                int res = delLastNode(arr[possibleInsertList]);
            } else { // если уменьшать possibleInsertList уже нельзя
                if (possibleDel(arr[possibleInsertList])) {
                    int res = delLastNode(arr[possibleInsertList]);
                }
                else {
                    cout << "Нечего удалять" << endl;
                }
            }
        }
    }
    
    void showArr(Node<string>** arr) {
        unsigned int id = 0;
        for (int i = 0; i < arrSize; ++i) {
            if (showList(arr[i], id)) {
                cout << endl;
                //cout << "- - - - - - - - - -" << endl; // граница списка
            }            
        }
    }
    void writeToTxtANSI(Node<string>** arr) {
        string fName;
        cout << "Введие имя файла: ";
        cin >> fName;
        cin.ignore();
        int length = fName.length();
        if (length - 4 > 0) {
            string fileExtension = fName.substr(fName.length() - 4, fName.length());
            if (fileExtension.find(".txt") == string::npos) { //
                fName += ".txt";
            }
        }
        else {
            fName += ".txt";
        }

        ofstream fout;
        fout.open(fName);
        if (!fout.is_open())
        {
            cout << "Файл не может быть открыт или создан"; // throw
            return;
        }

        for (int i = 0; i < arrSize; ++i) {
            Node<string>* tmp = arr[i];
            while (tmp != nullptr) {
                if (!tmp->getStr().empty()) {
                    fout << tmp->getStr() << endl;
                }
                tmp = tmp->getNext();
            }
        }

        fout.close();
    }

    void readFromTxtANSI(Node<string>**& arr) {
        
        string fName, tmp;
        cout << "Введие имя файла: ";
        cin >> fName;
        cin.ignore();
        int length = fName.length();
        if (length - 4 > 0) {
            string fileExtension = fName.substr(fName.length() - 4, fName.length());
            if (fileExtension.find(".txt") == string::npos) { //
                fName += ".txt";
            }
        }
        else {
            fName += ".txt";
        }       
                
        ifstream fin;
        fin.open(fName);
        if (!fin.is_open())
        {
            cout << "Файл не может быть открыт или создан"; // throw
            return;
        }

        while (!fin.eof()) {
            getline(fin, tmp);
            if (!tmp.empty()) {
                //cout << tmp << endl;
                Node<string>* newNode = new Node<string>{tmp};
                //addAtEndList(head, newNode);
                if (possibleInsert(arr[possibleInsertList])) {
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
                else {
                    possibleInsertList++;
                    if (possibleInsertList >= arrSize) { // хватает ли динамического массива
                        resizeArr(arr); // ресайз
                    }
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
            } 
        }
    
        fin.close();
    }
}