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
    void addInArrById(Node<string>**& arr);
    void balanceArr(Node<string>**& arr);
    void sortArr(Node<string>**& arr);

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

    void balanceArr(Node<string>**& arr) {
        // fix ��� ��������� �� ������
        int i = 0;
        while (!possibleInsert(arr[i])) { 
            if (i + 1 >= arrSize) { // ������� �� ������������� �������
                resizeArr(arr); // ������
                possibleInsertList++;
            }

            unsigned int counter = 1;
            Node<string>* tmp = arr[i];
            Node<string>* prev = tmp;
            while (tmp->getNext() != nullptr) {
                counter++;
                prev = tmp;
                tmp = tmp->getNext();
                if (counter > List::COUNT_NODE) { // ��� ������ ���� ���������� � ������ ���������� ������
                    prev->setNext(nullptr); // ���� �� ����� ������� COUNT_NODE �������� ���������
                    Node<string>* tmpHead = new Node<string>;
                    if (i + 1 >= arrSize) { // ������� �� ������������� �������
                        resizeArr(arr); // ������
                        possibleInsertList++;
                    }
                    tmpHead = arr[i + 1];
                    arr[i + 1] = tmp;
                    while (tmp->getNext() != nullptr) { // ��� �� ������ ���������� ������� ����
                        prev = tmp;
                        tmp = tmp->getNext();
                    }
                    tmp->setNext(tmpHead); // ������������� ������ ���������� ������� ���� next_ = tmpHead (arr[i+1])

                    break;
                }

            }
            i++;
        }
    }
    void addAtArr(Node<string>** &arr) {
        Node<string>* newNode = new Node<string>;
        cout << "������� str_: ";
        cin >> newNode;
        if (possibleInsert(arr[possibleInsertList])) {
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }
        else {
            possibleInsertList++;
            if (possibleInsertList >= arrSize) { // ������� �� ������������� �������
                resizeArr(arr); // ������
            }
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }        
    }   
    void addInArrByIdWithOrder(Node<string>**& arr) {
        Node<string>* newNode = new Node<string>;
        cout << "������� str_: ";
        cin >> newNode;
        unsigned int insertId = 0; unsigned int nowId = 0;
        cout << "������� id: ";
        cin >> insertId;
        cin.ignore(); // ���������� ��������� cin � getline
        // ��������� ����� ����, �������� ��� ���������

        int i = 0; bool hit = false;
        for (int i = 0; i <= possibleInsertList; ++i) {
            Node<string>* node = arr[i];
            if (i > 0) { nowId++; }
            while (node != nullptr) { // ���� �� ���������� �������                
                if (nowId == insertId) {
                    hit = true;
                }
                if (hit) {
                    string tmp = node->getStr();
                    node->setStr(newNode->getStr());
                    newNode->setStr(tmp);
                }
                node = node->getNext();
                nowId++;
            }
        }

        if (possibleInsert(arr[possibleInsertList])) {
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }
        else {
            possibleInsertList++;
            if (possibleInsertList >= arrSize) { // ������� �� ������������� �������
                resizeArr(arr); // ������
            }
            insertNodeAtEnd(arr, possibleInsertList, newNode);
        }
    }
    void delInArrById(Node<string>** &arr) {
        unsigned int delId = 0; unsigned int nowId = 0;
        cout << "������� id: ";
        cin >> delId;
        cin.ignore(); // ���������� ��������� cin � getline
        int i = 0;
        for (i; i < possibleInsertList; ++i) {
            if (delNodeById(arr, i, delId, nowId)) { // ������� �� ������� ���� � id = delId
                if (arr[i]->getNext() == nullptr && arr[i]->getStr().empty()) { // ���� �� ������� ������ ���� � ������
                    if (!arr[i + 1]->getStr().empty() || arr[i + 1]->getNext() != nullptr) { // ���� � ��������� ������� ���� �� ������ ����, �������� �������
                        int j = 0;
                        for (j = i; j <= possibleInsertList; j++) {
                            arr[j] = arr[j + 1];
                        }
                        /*j++;
                        if (j < arrSize) {
                            arr[j]->setNext(nullptr);
                            arr[j]->setStr("");
                        } */                       
                        
                        possibleInsertList--;
                    }
                }
                return;
            }
            
        }

        if (i == possibleInsertList) { // ���� �� ���-�� � ��������� ������
            if (possibleDel(arr[i])) {
                // �������, �������� ������, ��������� possibleInsertList ���� ������� ����� ���� ������
                if (delNodeById(arr, i, delId, nowId)) {
                    if (arr[i]->getNext() == nullptr && arr[i]->getStr().empty()) { // ���� �� ������� ������ ���� � ������, �������� ������ �� ����� ��� ��� i == possibleInsertList(���������� ������������� ������)
                        possibleInsertList--;
                    }
                    return;
                }                
            }
        }
        cout << "id ������ ���� �� ������ 0 � �� ������ " << nowId+1 << endl;
    }

    void addInArrById(Node<string>**& arr) {
        Node<string>* newNode = new Node<string>;
        cout << "������� str_: ";
        cin >> newNode;

        unsigned int insertId = 0; unsigned int nowId = 0;
        cout << "������� id: ";
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
                if (possibleInsertList >= arrSize) { // ������� �� ������������� �������
                    resizeArr(arr); // ������
                }
                insertNodeAtEnd(arr, possibleInsertList, newNode);
            }
        }
        else {
            cout << "id ������ ���� �� ������ 0 � �� ������ " << nowId + 1 << endl;
        }

    }
    void delInArr(Node<string>** arr) {
        if (possibleDel(arr[possibleInsertList])) { // �������� �� �������
            int res = delLastNode(arr[possibleInsertList]);
            if (res == 1 && possibleInsertList >= 1) { // ���� �� ������� ������ ������� ������, �� ��������� possibleInsertList
                possibleInsertList--;
            }
        } else {
            if (possibleInsertList >= 1) { // ���� ������� � ������� ������ ������, �� ��������� possibleInsertList
                possibleInsertList--;
                int res = delLastNode(arr[possibleInsertList]);
            } else { // ���� ��������� possibleInsertList ��� ������
                if (possibleDel(arr[possibleInsertList])) {
                    int res = delLastNode(arr[possibleInsertList]);
                }
                else {
                    cout << "������ �������" << endl;
                }
            }
        }
    }
    
    void showArr(Node<string>** arr) {
        unsigned int id = 0;
        for (int i = 0; i < arrSize; ++i) {
            if (showList(arr[i], id)) {
                cout << endl;
                //cout << "- - - - - - - - - -" << endl; // ������� ������
            }            
        }
    }    

    void sortArr(Node<string>**& arr) {
        for (int i = 0; i <= possibleInsertList; ++i) {
            Node<string>* node = arr[i]; // �������� ������� �������
            while (node != nullptr) {                    
                for (int j = i; j <= possibleInsertList; ++j) {
                     Node<string>* nodeNext = arr[j]; 
                    if (j == i) {
                        while (nodeNext != node) { // �������� ��������� �������
                            nodeNext = nodeNext->getNext();
                        }
                        nodeNext = nodeNext->getNext();
                    }                        
                    while (nodeNext != nullptr) {                        
                        if (nodeNext != nullptr) {
                            if (*node > *nodeNext) {
                                string tmp = node->getStr();
                                node->setStr(nodeNext->getStr());
                                nodeNext->setStr(tmp);
                            }
                        }
                        nodeNext = nodeNext->getNext();
                    }
                }   
                node = node->getNext();
            }
        }
    }
    void showArrByN(Node<string>** arr) {
        unsigned int n;
        cout << "������� ����� ���������� ����� �� ������ �������� �� ���: ";
        cin >> n;
        cin.ignore();

        unsigned int id = 0, counter = 0;
        for (int i = 0; i < arrSize; ++i) {
            if (arr[i]->getStr().empty() && arr[i]->getNext() == nullptr) { continue;  }
            Node<string>* node = arr[i];
            while (node != nullptr) {
                if (!node->getStr().empty()) {
                    cout << "id: " << id++ << endl;
                    cout << node;
                }
                node = node->getNext();

                counter++;
                if (counter == n) {
                    counter = 0;
                    cout << "������� ����� ������� ����� ����������, ��� Esc ����� ����� �� �������" << endl;
                    int ch = 0;
                    ch = _getch();
                    if (ch==27) { return; }
                }
            }
            cout << endl;
        }
    }
    void writeToBin(Node<string>** arr) {
        string fName;
        cout << "������ ��� �����: ";
        cin >> fName;
        cin.ignore();
        int length = fName.length();
        if (length - 4 > 0) {
            string fileExtension = fName.substr(fName.length() - 4, fName.length());
            if (fileExtension.find(".dat") == string::npos) {
                fName += ".dat";
            }
        }
        else {
            fName += ".dat";
        }
        
        ofstream fout(fName, ofstream::binary | ios::out);  
        if (!fout.is_open())
        {
            cout << "���� �� ����� ���� ������ ��� ������"; // throw
            return;
        }
        
        for (int i = 0; i < arrSize; ++i) {
            if (arr[i]->getStr().empty() && arr[i]->getNext() == nullptr) { continue; }

            Node<string>* node = arr[i];
            while (node != nullptr) {
                if (!node->getStr().empty()) {
                    //cout << node;
                    string text = node->getStr();
                    int size = (text.size());
                    fout.write(reinterpret_cast<char*>(&size), sizeof(int));
                    fout.write(text.c_str(), size);
                }
                node = node->getNext();

            }
            //cout << endl;
        }
        fout.flush();
        fout.close();
    }
    void readFromBin(Node<string>**& arr) {
        string fName, tmp;
        cout << "������ ��� �����: ";
        cin >> fName;
        cin.ignore();
        int length = fName.length();
        if (length - 4 > 0) {
            string fileExtension = fName.substr(fName.length() - 4, fName.length());
            if (fileExtension.find(".dat") == string::npos) { //
                fName += ".dat";
            }
        }
        else {
            fName += ".dat";
        }

        ifstream fin(fName, ios::in | ios::binary);
        if (!fin.is_open())
        {
            cout << "���� �� ����� ���� ������ ��� ������"; // throw
            return;
        }

        while (!fin.eof()) {


            int size;
            fin.read(reinterpret_cast<char*>(&size), sizeof(int));
            char* buf = new char[size];
            fin.read(buf, size);
            tmp = "";
            tmp.append(buf, size);
            delete[] buf;
            if (!tmp.empty()) {
                //cout << tmp << endl;
                Node<string>* newNode = new Node<string>{ tmp };
                //addAtEndList(head, newNode);
                if (possibleInsert(arr[possibleInsertList])) {
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
                else {
                    possibleInsertList++;
                    if (possibleInsertList >= arrSize) { // ������� �� ������������� �������
                        resizeArr(arr); // ������
                    }
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
            }
            fin.peek(); // �������� �� ����� �����
        }

        fin.close();
    }
    void writeToTxtANSI(Node<string>** arr) {
        string fName;
        cout << "������ ��� �����: ";
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
            cout << "���� �� ����� ���� ������ ��� ������"; // throw
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
        cout << "������ ��� �����: ";
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
            cout << "���� �� ����� ���� ������ ��� ������"; // throw
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
                    if (possibleInsertList >= arrSize) { // ������� �� ������������� �������
                        resizeArr(arr); // ������
                    }
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
            } 
        }
    
        fin.close();
    }
}