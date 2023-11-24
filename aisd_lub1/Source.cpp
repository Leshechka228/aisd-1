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

	//Конструктор с параметрами: Максимальная степень многочлена
	Polynomial(int maxDegree) {
		coefficients.resize(maxDegree + 1, 0);
	}

	//Конструктор с параметрами: Вектор значений при соответствующих степенях
	Polynomial(const std::vector& coeffs) {
		coefficients = coeffs;

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

	//Метод shrink_to_fit, уменьшающий размер многочлена до минимально возможного при наличии ведущих нулей
	void shrink_to_fit() {
		int newSize = 0;
		for (int i = coefficients.size() - 1; i >= 0; --i) {
			if (coefficients[i] != 0) {
				newSize = i + 1;
				break;
			}
		}
		coefficients.resize(newSize);
	}

	//Метод expand, резервирующих память под более высокие степени с коэффициентом 0
	void expand(size_t degree) {
		if (degree >= coefficients.size()) {
			coefficients.resize(degree + 1, 0);
		}
	}

	// Изменение коэффициента при заданной степени
	void set(size_t degree, T value) {
		expand(degree);
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

	// Перегрузка оператора вычитания
	Polynomial operator-(const Polynomial& other) const {
		T resultSize = std::max(coefficients.size(), other.coefficients.size());
		std::vector resultCoeffs(resultSize, 0); // Заполняем нулями вектор коэффициентов для результата
		for (int i = 0; i < resultSize; ++i) {
			double coef1 = (i < coefficients.size()) ? coefficients[i] : 0; // Если i-й коэффициент существует в первом многочлене, берем его, иначе 0
			double coef2 = (i < other.coefficients.size()) ? other.coefficients[i] : 0; // Аналогично для второго многочлена
			resultCoeffs[i] = coef1 - coef2; // Разность коэффициентов
		}
		return Polynomial(resultCoeffs);
	}
	};

	// Оператор умножения многочлена на скаляр
	Polynomial operator*(const T& scalar, const Polynomial& poly) {
		Polynomial result = poly;
		for (int i = 0; i < result.coefficients.size(); i++) {
			result.coefficients[i] *= scalar;
		}
		return result;
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

	// Метод для вычисления значения многочлена при указанном значении x
	T evaluate(T x) const {
		T result = 0;
		for (int i = 0; i < coefficients.size(); i++) {
			result += coefficients[i] * std::pow(x, i);
		}
		return result;
	}
};

	//оператор [] для чтения коэффициента при заданной степени
	T operator[](int power) const {
		if (power < 0 || power >= coefficients.size()) {
			return 0; // Если степень отрицательная или больше или равна размеру вектора коэффициентов, вернем 0
		}
		else {
			return coefficients[power]; // В противном случае вернем коэффициент при заданной степени
		}
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
	};
};

template <typename T>
T pair findRootQuadraticPolynomial(const T& a, const T& b, const T& c) {
	T discriminant = b * b - 4 * a * c;
	if (discriminant < 0) {
		throw std::invalid_argument("The quadratic polynomial has no real roots");
	}
	else if (discriminant == 0) {
		T root = -b / (2 * a);
		return std::make_pair(root, root);
	}
	else {
		T sqrtDiscriminant = std::sqrt(discriminant);
		return std::make_pair((-b + sqrtDiscriminant) / (2 * a), (-b - sqrtDiscriminant) / (2 * a));
	}

template <typename T>
T findRootLinearPolynomial(const T & a, const T & b) {
	if (a == 0) {
		throw std::invalid_argument("Coefficient 'a' in a linear polynomial cannot be zero");
	}
	return -b / a;
}

int main()
{
	// Example for linear polynomial x + 5 = 0
	int a1 = 1, b1 = 5;
	try {
		int root1 = findRootLinearPolynomial(a1, b1);
		std::cout << "Root of linear polynomial x + 5 = 0 is " << root1 << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	// Example for quadratic polynomial x^2 - 4x + 3 = 0
	int a2 = 1, b2 = -4, c2 = 3;
	try {
		std::pair roots2 = findRootQuadraticPolynomial(a2, b2, c2);
		std::cout << "Roots of quadratic polynomial x^2 - 4x + 3 = 0 are " << roots2.first << " and " << roots2.second << std::endl;
	}
	catch (std::invalid_argument& e) {
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}