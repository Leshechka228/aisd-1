#include <cmath>
#include <cstdlib> 
#include <iostream> 
#include <vector>

using namespace std;

template <typename T>
class Polynomial {
private:
	vector coefficients; // коэффициенты многочлена

public:
	// Конструктор по умолчанию (создает нулевой многочлен)
	Polynomial() {
		coefficients.push_back(0);
	}

	// Конструктор с заданными коэффициентами
	Polynomial(const vector& coeffs) {
		coefficients = coeffs;
	}

	// Получение степени многочлена
	int getDegree() const {
		return coefficients.size() - 1;
	}

	// Получение коэффициента при заданной степени
	T set (int degree) const {
		if (degree >= coefficients.size())
			return 0;
		return coefficients[degree];
	}

	// Изменение коэффициента при заданной степени
	void setCoefficient(int degree, T value) {
		if (degree >= coefficients.size()) {
			coefficients.resize(degree + 1, 0);
		}
		coefficients[degree] = value;
	}

	// Перегрузка оператора сложения
	Polynomial operator+(const Polynomial& other) const {
		int maxDegree = max(getDegree(), other.getDegree());
		vector resultCoeffs(maxDegree + 1, 0);

		for (int degree = 0; degree <= maxDegree; degree++) {
			T sum = getCoefficient(degree) + other.getCoefficient(degree);
			resultCoeffs[degree] = sum;
		}

		return Polynomial(resultCoeffs);
	}

	// Перегрузка оператора умножения
	Polynomial operator*(const Polynomial& other) const {
		int productDegree = getDegree() + other.getDegree();
		vector productCoeffs(productDegree + 1, 0);

		for (int i = 0; i <= getDegree(); i++) {
			for (int j = 0; j <= other.getDegree(); j++) {
				T product = getCoefficient(i) * other.getCoefficient(j);
				productCoeffs[i + j] += product;
			}
		}

		return Polynomial(productCoeffs);
	}

	// Перегрузка оператора вывода
	friend ostream& operator<<(ostream& os, const Polynomial& poly) {
		int degree = poly.getDegree();
		for (int i = degree; i >= 0; i--) {
			T coeff = poly.getCoefficient(i);
			if (coeff != 0) {
				if (coeff > 0 && i != degree)
					os << "+";
				if (i == 0) {
					os << coeff;
				}
				else if (i == 1) {
					os << coeff << "x";
				}
				else {
					os << coeff << "x^" << i;
				}
			}
		}
		return os;
	}
};

