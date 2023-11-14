#include <iostream>
#include <cstdlib> 
#include <exception>
using namespace std;

template<typename T>
struct Node {
    T coefficient;
    int exponent;
    Node* next;

    Node(T coeff, int exp) : coefficient(coeff), exponent(exp), next(nullptr) {}
};


template<typename T>
class Polynomial {
private:
    Node<T>* head;

public:
    Polynomial() : head(nullptr) {};

    Polynomial(const Polynomial<T>& other) {
        head = nullptr;
        if (other.head) {
            Node<T>* temp = other.head;
            do {
                push_tail(temp->coefficient,temp->exponent);
                temp = temp->next;
            } while (temp != other.head);
        }
    }

    Polynomial(int max_exp, int range = 100) : head(nullptr) {
        for (int i = max_exp; i >=0; --i) {
            push_tail(rand() % range,i);
        }
    }

    ~Polynomial() {
        clear();
    }

    Polynomial<T>& operator=(const Polynomial<T>& other) {
        if (this != &other) {//
            clear();
            Node* temp = other.head;
            do {
                push_tail(temp->coefficient, temp->exponent);
                temp = temp->next;
            } while (temp != other.head);
        }
        return *this;
    }

    int size() const{
        int size = 0;
        if (!head)
            return 0;
        Node<T>* temp = head;
        do {
            size++;
            temp = temp->next;
        } while (temp != head);
        return size;
    }

    void push_tail(T coeff,int exp) {
        if (!coeff) {
            return;
        }

        Node<T>* newNode = new Node<T>(coeff, exp);
        if (!head) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
        }
    }

    void push_tail(const Polynomial<T>& other) {
        if (!other.head) {
            return;
        }

        Node<T>* temp = other.head;
        do {
            push_tail(temp->coefficient, temp->exponent);
            temp = temp->next;
        } while (temp != other.head);
    }

    void push_head(T coeff,int exp) {
        if (!coeff) {
            return;
        }
        Node<T>* newNode = new Node<T>(coeff,exp);
        if (!head) {
            head = newNode;
            head->next = head;
        }
        else {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->next = head;
            head = newNode;
        }
    }

    void push_head(Polynomial<T> other) {
        if (!other.head) {
            return;
        }
        if (!head) {
            head = other.head;
            Node<T>* temp = other.head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = head;
            return;
        }
        int size = other.size();
        for (int i = size - 1; i >= 0; --i) {
            push_head(other[i].coefficient,other[i].exponent);
        }
    }


    void pop_head() {
        if (head) {
            Node<T>* temp = head;
            while (temp->next != head) {
                temp = temp->next;
            }
            temp->next = head->next;
            temp = head;
            head = head->next;
            delete temp;
        }
    }

    void pop_tail() {
        if (head) {
            if (!head->next) {
                delete head;
                head = nullptr;
            }
            else {
                Node<T>* temp = head;
                while (temp->next->next != head) {
                    temp = temp->next;
                }
                temp->next = head;
                delete temp->next->next;
                temp->next->next = nullptr;
            }
        }
    }

    void delete_node(T coeff) {
        if (!head) {
            cout << "Список пуст." << endl;
            return;
        }

        Node<T>* current = head;
        Node<T>* previous = nullptr;
        Node<T>* next = nullptr;

        do {
            next = current->next;

            if (current->coefficient == coeff) {
                if (current == head) {
                    if (head->next == head) {
                        delete head;
                        head = nullptr;
                        return;
                    }
                    else {
                        Node<T>* temp = head;
                        while (temp->next != head) {
                            temp = temp->next;
                        }
                        temp->next = head->next;
                        Node<T>* temp_head = head;
                        head = head->next;
                        delete temp_head;
                        current = head;
                    }
                }
                else {
                    previous->next = current->next;
                    delete current;
                    current = next;
                }
            }
            else {
                previous = current;
                current = next;
            }
        } while (current != head);
    }

    Node<T> operator[](int index) const {
        if (index < 0 && index >= size())
            throw std::out_of_range("Error");
        if (index == 0)
            return *head;
        Node<T>* temp = head;
        do {
            temp = temp->next;
        } while (temp != head );
        return *temp;
    }

    Node<T>& operator[](int index) {
        if (index < 0 && index >= size())
            throw std::out_of_range("Error");
        if (index == 0)
            return *head;
        Node<T>* temp = head;
        do {
            temp = temp->next;
        } while (temp != head);
        return *temp;
    }

    void clear() {
        if (!head) {
            return;
        }

        Node<T>* current = head;
        Node<T>* next = nullptr;

        do {
            next = current->next;
            delete current;
            current = next;
        } while (current != head);

        head = nullptr;
    }

    T evaluate(T x) {
        T result = 0;
        if (!head) {
            cout << "Polynomial is empty." << endl;
            return result;
        }

        Node<T>* temp = head;
        do {
            result += (temp->coefficient) * pow(x, temp->exponent);
            temp = temp->next;
        } while (temp != head && temp != nullptr);
        return result;
    }


    void display() {
        if (!head) {
            cout << "Polynomial is empty." << endl;
            return;
        }

        Node<T>* temp = head;
        do {
            if (temp == head || temp->coefficient < 0) {
                cout << temp->coefficient << "x^" << temp->exponent << " ";
            } else {
                cout <<"+ "<< temp->coefficient << "x^" << temp->exponent << " ";
            }
            temp = temp->next;
        } while (temp != head);
        cout << endl;
    }

};

