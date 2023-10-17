#include <iostream>
#include <complex>
#include <cmath>

using namespace std;
template<typename T>

class Polynomial {
private:
	T* coefficients;
	int size;
	int degree;

public:
	Polynomial() :degree(-1), coefficients(nullptr) {	};
	Polynomial(const int& degree):degree(degree) {
		size = degree + 1;
		coefficients = new T[size];
		for (int i = 0; i <= degree; i++) {
			coefficients[i] = T();
		}
	};
	Polynomial(const Polynomial& other) {
		degree = other.degree;
		size = other.size;
		coefficients = new T[degree + 1];
		for (int i = 0; i <= degree; i++) {
			coefficients[i] = other.coefficients[i];
		}
	};

	~Polynomial() {
		delete[] coefficients;
	}

	T& operator[](const int& degree) {
		if (degree < 0 || degree > Polynomial::degree)
			throw "ERROR";
		return coefficients[degree];
	}

	const T& operator[](const int& degree) const {
		if (degree < 0 || degree> Polynomial::degree )
			throw "ERROR";
		return coefficients[degree];
	}

	int get_size() const {
		return size;
	}

	int get_degree() const {
		return degree;
	}


	void set(const int& degree, const T& coefficient) const {
		if (degree < 0 || degree> this.degree)
			throw "ERROR";
		coefficients[degree] = coefficient;
	}


	Polynomial<T> operator+(const Polynomial<T>& other) const {
		int size = std::max(this->get_size(), other.get_size());
		Polynomial<T> result(size - 1);

		for (int i = 0; i < size; i++) {
			T a = (i < this->get_size()) ? coefficients[i] : T();
			T b = (i < other.get_size()) ? other.coefficients[i] : T();
			result[i] = a + b;
		}

		return result;
	}

	Polynomial<T> operator-(const Polynomial<T>& other) const {
		int size = std::max(this->get_size(), other.get_size());
		Polynomial<T> result(size - 1);

		for (int i = 0; i < size; i++) {
			T a = (i < this->get_size()) ? coefficients[i] : T();
			T b = (i < other.get_size()) ? other.coefficients[i] : T();
			result[i] = a - b;
		}

		return result;
	}



	Polynomial<T> operator*(const T& number) const {
		int size = this->get_size();
		Polynomial<T> result(size - 1);

		for (int i = 0; i < size; i++) {
			result[i] = coefficients[i] * number;
		}

		return result;
	}

	T& calc(const T& x) const {
		int size = this->get_size();
		T result = T();
		for (int i = 0; i < size; i++) {
			result += coefficients[i] * std::pow(x, i);
		}

		return result;
	}

	void shrink_to_fit() {
		int temp = get_degree();
		while (temp > 0 && coefficients[temp] == T()) {
			temp--;
		}
		size = temp+1;
		degree = temp;
		T* result= new T[size];
		for (int i = 0; i < size; i++) {
			result[i] = coefficients[i];
		}
		delete[] coefficients;
		coefficients = result;
	}


	void expand(int newDegree) {
		if (newDegree < 0)
			throw "ERROR";
		if (newDegree <= degree)
			return;
		int newSize = get_size() + (newDegree - degree);
		T* newCoefficients = new T[newSize];
		for (int i = 0; i < size; i++) {
			newCoefficients[i] = coefficients[i];
		}
		for (int i = size; i < newSize; i++) {
			newCoefficients[i] = T();
		}
		delete[] coefficients;
		coefficients = newCoefficients;
		degree = newDegree;
		size = newSize;
	}

	Polynomial<T> derivate() {
		int size = this->get_size() - 1;
		Polynomial<T> result(size-1);
		for (int i = 0; i < size; i++) {
			result.coefficients[i] = coefficients[i + 1] * (i + 1);
		}
		return result;
	}


	friend ostream& operator<<(ostream& os, const Polynomial<T>& item) {
		int size = item.get_size();
		int degree = item.get_degree();
		int tmp =  degree - size + 1;
		int n = 0;
		for (int i = size-1; i >=0; --i) {
			if (item.coefficients[i] != T())
				n++;
			if (item.coefficients[i] == T() && n!=0)
				continue;
			else if (i == size - 1)
				os << item.coefficients[i] << "x^" << i;
			else if (i == 0)
				os << " + " << item.coefficients[i];

			else if (i == 1)
				os <<" + "<< item.coefficients[i] << "x";
			else
				os << " + " << item.coefficients[i] << "x^" << i;
		};
		return os;
	}
};



int main() {
	Polynomial<int> poly1(4);
	poly1[1] = 45;
	poly1[2] = 6;
	poly1[3] = 1;
	cout << "\nPoly 1: "<< poly1 << "\n";
	Polynomial<int> poly1_derivate = poly1.derivate();
	cout << "Poly 1 after derivate: " << poly1_derivate << "\n";

	int calc = poly1.calc(3);
	cout <<"poly1(3)="<< calc << endl;

	Polynomial<int> poly2(2);
	poly2[0] = 6;
	poly2[1] = 2;
	poly2[2] = 4;
	cout << "\nPoly 2: " << poly2 << "\n";

	Polynomial<int> sub = poly2-poly1;
	cout << "\nPoly sub: " << sub << "\n";
	Polynomial<int> sum = poly1+poly2;
	cout << "Poly sum: " << sum << "\n";
	Polynomial<int> multi = poly1*5;
	cout << "Poly multi: " << multi << "\n";

	Polynomial<double> poly3(6);
	poly3[0] = 0;
	poly3[1] = 0;
	poly3[3] = 3.0;
	poly3[4] = 2.5;
	poly3[5] = 1.2;
	poly3[6] = 0;
	cout << "\nPoly 3: " << poly3 << "\n";
	poly3.shrink_to_fit();
	cout << "Poly 3 after shrink to fit: " << poly3 << "\n";
	poly3.expand(8); 

	cout << "Poly 3 after expand(8): " << poly3 << endl;

	Polynomial<std::complex<float>> complexPoly(3);
	complexPoly[0] = std::complex<float>(1.0, 2.0);
	complexPoly[1] = std::complex<float>(-1.0, 1.0);
	complexPoly[2] = std::complex<float>(2.5, -0.5);
	complexPoly[3] = std::complex<float>(-3.0, 0.0);

	std::cout << "\nComplex polynomial float: " << complexPoly << std::endl;
	return 0;
}



