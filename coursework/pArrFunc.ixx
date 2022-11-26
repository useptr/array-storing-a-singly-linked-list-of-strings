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
        unsigned int listCounter = 1, nodeCounter = 1;
        for (int i = 0; i <= possibleInsertList; ++i) {            
            Node<string>* node = arr[i]; // получили текущий элемент  
            if (i != 0) { nodeCounter++; listCounter++; }
            while (node != nullptr) { // проходимся по списку и получаем его nodeCounter
                node = node->getNext();
                if (node != nullptr) {
                    nodeCounter++;
                }
            }            
        }
        
        unsigned int nListLength = nodeCounter/ listCounter;
        while (nListLength * listCounter < nodeCounter) {
            nListLength++;
        }
        
        Node<string>** tArr = new Node<string>*[nodeCounter]; // инициализирование динамического массива Node
        for (int i = 0; i < nodeCounter; ++i) {
            tArr[i] = new Node<string>;
            // считывание в массив из файла
        }

        int c = 0;
        for (int i = 0; i <= possibleInsertList; ++i) { // скопировали структуру в массив
            Node<string>* node = arr[i];  
            tArr[c]->setStr(arr[i]->getStr()); c++;
            arr[i]->setStr("");
            Node<string>* prevNode = node;
            while (node != nullptr) { 
                prevNode = node;
                node = node->getNext();
                if (node != nullptr) {
                    tArr[c]->setStr(node->getStr()); c++;
                }                
                if (prevNode != arr[i]) {
                    delete prevNode;
                }
            }
            arr[i]->setNext(nullptr);
        }
        c = 0;
        for (int i = 0; i < listCounter; ++i) {
            if (c == nodeCounter) { break; }
            arr[i]->setStr(tArr[c]->getStr()); c++;
            Node<string>* node = arr[i];            
            for (int j = 1; j < nListLength; ++j) {
                if (c == nodeCounter) { break; }
                Node<string>* newNode = new Node(tArr[c]->getStr()); c++;
                node->setNext(newNode);
                node = node->getNext();
                
            }
        }
        for (int i = 0; i < nodeCounter; ++i) { // освобождения элементов динамического массива Node
    	    delete tArr[i];
        }
        delete[] tArr;
        // если в списке меньше nListLength вставляем из следующего, если больше вставляем в следующий
        //for (int i = 0; i <= possibleInsertList; ++i) {
        //    Node<string>* node = arr[i]; // получили текущий элемент  
        //    Node<string>* prevNode = node;
        //    unsigned int сounter = 1;
        //    while (node != nullptr) { // проходимся по списку и получаем его nodeCounter
        //        prevNode = node;
        //        node = node->getNext();
        //        if (node != nullptr) {
        //            сounter++;
        //        }
        //        if (сounter > nListLength) {
        //            prevNode->setNext(nullptr);
        //            if (i+1 >= arrSize) {
        //                resizeArr(arr);
        //            }
        //            Node<string>* oldHead = arr[i+1];
        //            arr[i + 1] = node;
        //            while (node->getNext() != nullptr) {
        //                node = node->getNext();
        //            }
        //            node->setNext(oldHead);
        //            //showArr(arr);
        //            break;
        //        }
        //    }
        //    if (сounter < nListLength) {
        //        // не смог реализовать
        //    }
        //}
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
        cin >> newNode; // проверка на пустую строку
        unsigned int insertId = 0; unsigned int nowId = 0;
        cout << "Введите id: ";
        cin >> insertId;
        cin.ignore(); // разрешения конфликта cin и getline
        
        unsigned int nodeCounter = 1;
        for (int i = 0; i <= possibleInsertList; ++i) {
            Node<string>* node = arr[i]; // получили текущий элемент  
            if (i != 0) { nodeCounter++; }
            while (node != nullptr) { // проходимся по списку и получаем его nodeCounter
                node = node->getNext();
                if (node != nullptr) {
                    nodeCounter++;
                }
            }
        }

        bool hit = false;
        for (int i = 0; i <= possibleInsertList; ++i) {
            Node<string>* node = arr[i]; // получили текущий элемент
            Node<string>* prevNode = node;
            unsigned int сounter = 1;
            if (i > 0) { nowId++; }
            while (node != nullptr) {
                if (nowId == insertId) {
                    hit = true;
                }
                if (hit) {
                    string tmp = node->getStr();
                    node->setStr(newNode->getStr());
                    newNode->setStr(tmp);
                }
                prevNode = node;
                node = node->getNext();
                if (node != nullptr) {
                    сounter++;
                }
                if (node != nullptr) {
                    nowId++;
                }
                
            }
            if (nowId - сounter + 1 + List::COUNT_NODE >= insertId) {
                if (сounter < List::COUNT_NODE) {
                    //if () {}
                    if (!prevNode->getStr().empty()) {
                        if (prevNode != node) {
                            prevNode->setNext(newNode);
                            return;
                        }
                    }
                }
            }
            
        }
        //int i = 0; bool hit = false;
        //for (int i = 0; i <= possibleInsertList; ++i) {
        //    Node<string>* node = arr[i];
        //    if (i > 0) { nowId++; }
        //    while (node != nullptr) { // цикл по заголовкам списков                
        //        if (nowId == insertId) {
        //            hit = true;
        //        }
        //        if (hit) {
        //            string tmp = node->getStr();
        //            node->setStr(newNode->getStr());
        //            newNode->setStr(tmp);
        //        }
        //        node = node->getNext();
        //        nowId++;
        //    }
        //}
        /*if (insertId == 1 && arr[0]->getStr().empty()) {
            cout << "id должен быть не меньше 0 и не больше " << nowId-1 << endl;
            return;
        }*/
        /*if (nowId < List::COUNT_NODE) {
            if (nowId!=0) {
                nowId--;
            }
        }*/
        /*if (nowId == 1 && arr[0]->getStr().empty() && arr[0]->getNext() == nullptr) {
            cout << "id должен быть не меньше 0 и не больше 0" << endl;
            return;
        }*/
        if (hit || nowId == insertId) {
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
        } else {
            //if (nowId == )
            cout << "id должен быть не меньше 0 и не больше " << nowId << endl;

        }
    }
    void delInArrById(Node<string>** &arr) {
        if (arr[0]->getStr().empty() && arr[0]->getNext() == nullptr) {
            cout << "нечего извлекать" << endl;
            return;
        }
        unsigned int delId = 0; unsigned int nowId = 0;
        cout << "Введите id: ";
        cin >> delId;
        cin.ignore(); // разрешения конфликта cin и getline
        int i = 0;
        for (i; i < possibleInsertList; ++i) {
            if (delNodeById(arr, i, delId, nowId)) { // удалось ли удалить узел с id = delId
                if (arr[i]->getNext() == nullptr && arr[i]->getStr().empty()) { // если мы удалили первый узел в списке
                    if (!arr[i + 1]->getStr().empty() || arr[i + 1]->getNext() != nullptr) { // если в следующих списках есть не пустые узлы, сдвигаем списоки
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

        if (i == possibleInsertList) { // есть ли что-то в последнем списке
            if (possibleDel(arr[i])) {
                // удалить, сдвинуть список, уменьшить possibleInsertList если удалили первй узел списка
                if (delNodeById(arr, i, delId, nowId)) {
                    if (arr[i]->getNext() == nullptr && arr[i]->getStr().empty()) { // если мы удалили первый узел в списке, сдвигать ничего не нужно так как i == possibleInsertList(последнему используемому списку)
                        possibleInsertList--;
                    }
                    return;
                }                
            }
        }
        cout << "id должен быть не меньше 0 и не больше " << nowId-1 << endl;
    }

    void addInArrByIdWithOrder(Node<string>**& arr) {
        int ch = 0;
        cout << "при выплнении этой функции структура будет отсортирована, если хотите продолжить нажмите любую клавишу кроме - Esc" << endl;
        ch = _getch();
        if (ch == 27) {
            return;
        }
        
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
        sortArr(arr);
        
        //for (int i = 0; i <= possibleInsertList; ++i) {
        //    Node<string>* node = arr[i]; // получили текущий элемент
        //    while (node != nullptr) {                
        //            if (*node > *newNode) {
        //                string tmp = node->getStr();
        //                node->setStr(newNode->getStr());
        //                newNode->setStr(tmp);
        //            }
        //            node = node->getNext();
        //    
        //    }
        //}
        //
        //if (possibleInsert(arr[possibleInsertList])) {
        //    insertNodeAtEnd(arr, possibleInsertList, newNode);
        //}
        //else {
        //    possibleInsertList++;
        //    if (possibleInsertList >= arrSize) { // хватает ли динамического массива
        //        resizeArr(arr); // ресайз
        //    }
        //    insertNodeAtEnd(arr, possibleInsertList, newNode);
        //}

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

    void sortArr(Node<string>**& arr) {
        for (int i = 0; i <= possibleInsertList; ++i) {
            Node<string>* node = arr[i]; // получили текущий элемент
            while (node != nullptr) {                    
                for (int j = i; j <= possibleInsertList; ++j) {
                     Node<string>* nodeNext = arr[j]; 
                    if (j == i) {
                        while (nodeNext != node) { // получили следующий элемент
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
        cout << "Введите какое количество строк вы хотите выводить за раз: ";
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
                    cout << "Нажмите любую клавишу чтобы продолжить, или Esc чтобы выйти из функции" << endl;
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
        cout << "Введие имя файла: ";
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
            cout << "Файл не может быть открыт или создан"; // throw
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
        cout << "Введие имя файла: ";
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
            cout << "Файл не может быть открыт или создан"; // throw
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
                    if (possibleInsertList >= arrSize) { // хватает ли динамического массива
                        resizeArr(arr); // ресайз
                    }
                    insertNodeAtEnd(arr, possibleInsertList, newNode);
                }
            }
            fin.peek(); // проверка на конец файла
        }

        fin.close();
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