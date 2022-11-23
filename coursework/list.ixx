export module list;
import <iostream>;
import <string>;

export namespace List {
    using namespace std;
    const unsigned int COUNT_NODE = 5; // стандартное количество узлов в списке

    //template <typename U> class Test;
    //template <typename U> std::ostream& operator<<(std::ostream&, const Test<U>&);
    //template <typename U>
    //class Test {
    //    U d_;
    //    friend std::ostream& operator<< <U>(std::ostream&, const Test<U>&);
    //public:
    //    Test(U d) : d_{ d } { }
    //};
    //// Implement the operator
    //template <typename U>
    //std::ostream& operator<<(std::ostream& o, const Test<U>& t) {
    //    o << "DDD: ";
    //    return o;
    //}

    template <class T> class Node;
    template <class T> ostream& operator<<(ostream&, const Node<T>&);
    template <class T> ostream& operator<<(ostream&, const Node<T>*);
    template <class T>
    class Node {
    private:
        T str_;
        Node* next_;
        friend ostream& operator<< <T>(std::ostream&, const Node<T>&);
        friend ostream& operator<< <T>(std::ostream&, const Node<T>*);
    public:        
        Node() : next_{ nullptr } { }
        Node(T str) : str_{ str }, next_{ nullptr } { }                
        const T getStr() const;
        Node<T>* getNext() const;
        void setNext(Node<T>* newNode);
        
        
    };
    template <class T>
    ostream& operator<< (ostream& out, const Node<T>& obj) {
        out << "str_: " << obj.str_ << endl;
        /*if (obj.next_ == nullptr) {
            out << "next_: " << "nullptr" << endl;
        }
        else {
            out << "next_: " << obj.next_ << endl;
        }*/
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
    /*template <class T>
    ostream& operator<<(ostream& out, const Node<T>& obj) {
        if (obj == nullptr) {
            out << "Объект не инициализирован: nullptr" << endl;
        }
        else {
            out << "str_: " << obj.getStr() << endl;
            if (obj.getNext() == nullptr) {
                out << "next_: " << "nullptr" << endl;
            }
            else {
                out << "next_: " << obj.getNext() << endl;
            }
        }
    }*/

    template <class T>
    const T Node<T>::getStr() const {
        return str_;
    }
    template <class T>
    Node<T>* Node<T>::getNext() const {
        return next_;
    }
    template <class T>
    void  Node<T>::setNext(Node<T>* newNode) {
        next_ = newNode;
    }

    void showList(Node<string>* node, unsigned int& id) {
        while (node != nullptr) {
            cout << "id: " << id++ << endl;
            cout << node;
            //cout << node->getStr() << endl;
            node = node->getNext();
        }
    }
    void addAtEndList(Node<string>* list, Node<string>* newNode) {
        while (list->getNext() != nullptr) {
            list = list->getNext();
        }
        list->setNext(newNode);
    }
}