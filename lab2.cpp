#include "lab2.h"
#include <iostream>
#include <cstdlib> 

template<typename T>
T evaluate(T x);

int main() {
    Polynomial<float> poly1;

    poly1.push_tail(3.5, 3); 
    poly1.push_tail(0, 2); 
    poly1.push_tail(-5.2, 1); 
    poly1.push_tail(2, 0);  

    cout << "Poly1: ";
    poly1.display();

    float x = 2.1;
    float result = poly1.evaluate(x);
    cout << "Value of the Poly1 at x = " << x << " is: " << result << endl;

    Polynomial<float> poly2(poly1);
    cout << "Poly2 (copy of Poly1): ";
    poly2.display();

    Polynomial<int> poly3(5, 50);
    cout << "Poly3 (random values): ";
    poly3.display();


    Polynomial<int> poly5;
    poly5.push_tail(10,9);
    poly5.push_tail(8,8);
    poly5.push_tail(2,7);
    cout << "Poly5: ";
    poly5.display();

    poly5.push_tail(poly3);
    cout << "Poly5 after push_tail with Poly3: ";
    poly5.display();
    poly5.delete_node(2);
    cout << "Poly2 after delete node have coefficient=2: ";
    poly5.display();

    return 0;
}


