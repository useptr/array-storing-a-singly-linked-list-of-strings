export module list;

import <iostream>;
import <string>;

export namespace List {
    using namespace std;
    //setlocale(LC_ALL, "rus");
    unsigned int COUNT_NODE = 5; // стандартное количество узлов в списке



    template <class T> class Node;
    template <class T> ostream& operator<<(ostream&, const Node<T>&);
    template <class T> ostream& operator>>(ostream&, const Node<T>*);
    template <class T> istream& operator>>(istream&, Node<T>*);
    template <class T> bool operator< (const Node<T>&, const Node<T>&);
    template <class T> bool operator> (const Node<T>&, const Node<T>&);
    template <class T> class Node {
    private:
        T str_;
        Node* next_;
        friend ostream& operator<< <T>(ostream&, const Node<T>&);
        friend ostream& operator<< <T>(ostream&, const Node<T>*);
        friend istream& operator>> <T>(istream&, Node<T>*);
        friend bool operator< <T>(const Node<T>&, const Node<T>&);
        friend bool operator> <T>(const Node<T>&, const Node<T>&);
    public:        
        Node() : next_{ nullptr } { }
        Node(T str) : str_{ str }, next_{ nullptr } { }                
        const T getStr() const;
        void setStr(T str);
        Node<T>* getNext() const;
        void setNext(Node<T>* newNode);      
                
    };
    void insertNodeAtEnd(Node<string>** head, const unsigned int insertId, Node<string>* newNode);
    unsigned int insertNodeAtEnd(Node<string>* nowNode);
    bool showList(Node<string>* node, unsigned int& id);
    bool possibleInsert(Node<string>* head);
    bool possibleDel(Node<string>* head);

    template <class T>
    ostream& operator<< (ostream& out, const Node<T>& obj) {
        out << "str_: " << obj.str_ << endl;
        return out;
    }
    template <class T>
    ostream& operator<< (ostream& out, const Node<T>* obj) {
        if (obj == nullptr) {
            out << "Объект не инициализирован (= nullptr)" << endl;
        }
        else {
            /*Node<T> copyObj = *obj;
            out << copyObj;*/
            out << "str_: " << obj->getStr() << endl;
        }
        return out;
    }
    template <class T> istream& operator>>(istream& in, Node<T>* obj) {
        T str;
        if (!in) {
            in.ignore(numeric_limits<streamsize>::max(), '\n'); //Выкидываем все что ввел пользователь до конца строки
            in.clear();  //Убираем флаг ошибки. Теперь состояние потока снова good
            //throw exception("Ошибка, введённая строка не может быть преобразована в int");
        }
        getline(in, str);
        obj->setStr(str);
        return in;
    }
    template <class T> bool operator< (const Node<T>& lhs, const Node<T>& rhs) {
        string str1 = lhs.getStr();
        string str2 = rhs.getStr();
        if (str1.compare(str2) < 0) {
            return true;
        }
        return false;
    }
    template <class T> bool operator> (const Node<T>& lhs, const Node<T>& rhs) {
        string str1 = lhs.getStr();
        string str2 = rhs.getStr();
        if (str1.compare(str2) > 0) {
            return true;
        }
        return false;
    }
    template <class T>
    const T Node<T>::getStr() const {
        return str_;
    }
    template <class T>
    void Node<T>::setStr(T str) {
        str_ = str;
    }
    template <class T>
    Node<T>* Node<T>::getNext() const {
        return next_;
    }
    template <class T>
    void  Node<T>::setNext(Node<T>* newNode) {
        next_ = newNode;
    }

    bool showList(Node<string>* node, unsigned int& id) { // выводит список
        bool hit = false;
        while (node != nullptr) {
            if (!node->getStr().empty()) {
                hit = true;
                cout << "id: " << id++ << endl;
                cout << node;
                //cout << node->getStr() << endl;
            }            
            node = node->getNext();
        }
        return hit;
    }

    void insertNodeAtEnd(Node<string>** head, const unsigned int insertId, Node<string>* newNode) { // добавляет узел в конец списка
        if (head[insertId]->getStr().empty()) {
            Node<string>* tmp = head[insertId];
            head[insertId] = newNode;
            delete tmp;
            return;
        }
        Node<string>* tmp = head[insertId];
        while (tmp->getNext() != nullptr) {
            tmp = tmp->getNext();
        }
        tmp->setNext(newNode);
    }

    bool insertNodeById(Node<string>** head, int listtId, const unsigned int insertId, unsigned int& nowId, Node<string>* newNode) { // добавляет узел в конец списка
        if (listtId > 0) { nowId++; }
        if (insertId == nowId) {
            newNode->setNext(head[listtId]);
            head[listtId] = newNode;
            return true;
        }

        
        Node<string>* tmp = head[listtId]; Node<string>* prev = head[listtId];
        while (tmp->getNext() != nullptr) {
            prev = tmp;
            tmp = tmp->getNext();
            nowId++;
            if (nowId == insertId) {
                prev->setNext(newNode);
                newNode->setNext(tmp);
                return true;
            }

        }
        return false;
        
    }
    bool delNodeById(Node<string>** head, const int listtId, const unsigned int delId, unsigned int& nowId) {
        if (listtId > 0) { nowId++; }

        if (delId == nowId) {
            if (head[listtId]->getNext() == nullptr) {
                if (!head[listtId]->getStr().empty()) {
                    head[listtId]->setStr("");
                }
            } else {
                Node<string>* tmp = head[listtId]->getNext();
                delete head[listtId];
                head[listtId] = tmp;
            }
            return true;
        }

        Node<string>* tmp = head[listtId];
        Node<string>* prev = head[listtId];
        while (tmp->getNext() != nullptr) {
            nowId++;
            prev = tmp;
            tmp = tmp->getNext();
            if (delId == nowId) {
                prev->setNext(tmp->getNext());
                delete tmp;
                break;
            }
        }

    }
    unsigned int delLastNode(Node<string>* nowNode) {
        unsigned int counter = 1;
        Node<string>* tmp = nowNode;
        Node<string>* prev = nowNode;
        while (tmp->getNext() != nullptr) {
            counter++;
            prev = tmp;
            tmp = tmp->getNext();
        }
        if (counter <= 1) {
            if (!tmp->getStr().empty()) {
                tmp->setStr("");
            }
        } else {
            prev->setNext(nullptr);
            delete tmp;
        }
        return counter;
    }
    bool possibleInsert(Node<string>* head) { // если в списке количество элементов больше или равно COUNT_NODE возвращает false иначе true
        unsigned int counter = 1;
        while (head->getNext() != nullptr) {
            counter++;
            if (counter >= COUNT_NODE) {
                return false;
            }
            head = head->getNext();
        }
        return true;
    }

    bool possibleDel(Node<string>* head) {
        if (head != nullptr && !head->getStr().empty()) {
            return true;
        }       
        return false;
    }
}