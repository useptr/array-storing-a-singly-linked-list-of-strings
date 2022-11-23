export module list;

import <iostream>;
import <string>;

export namespace List {
    using namespace std;
    //setlocale(LC_ALL, "rus");
    const unsigned int COUNT_NODE = 2; // стандартное количество узлов в списке



    template <class T> class Node;
    template <class T> ostream& operator<<(ostream&, const Node<T>&);
    template <class T> ostream& operator>>(ostream&, const Node<T>*);
    template <class T> istream& operator>>(istream&, Node<T>*);
    template <class T> class Node {
    private:
        T str_;
        Node* next_;
        friend ostream& operator<< <T>(ostream&, const Node<T>&);
        friend ostream& operator<< <T>(ostream&, const Node<T>*);
        friend istream& operator>> <T>(istream&, Node<T>*);
    public:        
        Node() : next_{ nullptr } { }
        Node(T str) : str_{ str }, next_{ nullptr } { }                
        const T getStr() const;
        void setStr(T str);
        Node<T>* getNext() const;
        void setNext(Node<T>* newNode);      
                
    };
    void insertNodeAtEnd(Node<string>** head, const unsigned int insertId, Node<string>* newNode);
    bool showList(Node<string>* node, unsigned int& id);

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
        getline(in, str);
        obj->setStr(str);
        return in;
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

    bool showList(Node<string>* node, unsigned int& id) {
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

    void insertNodeAtEnd(Node<string>** head, const unsigned int insertId, Node<string>* newNode) {
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

    bool possibleInsert(Node<string>* head) {
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
}