#include <cmath>
#include <cstdlib> 
#include <iostream> 
#include <vector> 

using namespace std;


template <typename T>
class Polynomial {
private:
    vector<T> coefficients;

public:
    Polynomial() {}

    //Конструктор с параметрами: Максимальная степень многочлена
    Polynomial(size_t maxDegree) : coefficients(maxDegree + 1, 0) {}

    //Конструктор с параметрами: Вектор значений при соответствующих степенях
    Polynomial(const vector<T>& values) : coefficients(values.size()) {
        for (size_t i = 0; i < values.size(); ++i) {
            coefficients[i] = values[i];
        }
    }

    //Метод set для установки коэффициента при заданной степени
    void set_сoefficient(size_t power, T value) {
        if (power <= coefficients.size() - 1) { 
            coefficients[power] = value;
        }
        else {
            throw out_of_range("Invalid power value");
        }
    }

    //Метод shrink_to_fit, уменьшающий размер многочлена до минимально возможного при наличии ведущих нулей
    void shrink_to_fit() {
        int leadingZeros = 0;
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            if (coefficients[i] == 0) {
                leadingZeros++;
            }
        }
        coefficients.resize(coefficients.size() - leadingZeros);
    }

    //Метод expand, резервирующих память под более высокие степени с коэффициентом 0
    void expand(size_t new_size) {
        if (new_size > coefficients.size()) {
            coefficients.resize(new_size, T{ 0 }); // Заполняем новые элементы нулями
        }
    }

    //Вычисление значения многочлена при указанном значении х
    T calculation(T x) {
        T result = T{ 0 };
        T power = T{ 1 };
        for (const auto& coef : coefficients) {
            result += coef * power;
            power *= x;
        }
        return result;
    }

    //оператор [] для чтения коэффициента при заданной степени
    T operator[](size_t power) const {
        if (power >= 0 && power < coefficients.size()) {
            return coefficients[power];
        }
        else {
            return 0; // Если степень отсутствует, вернем 0
        }
    }

    //оператор сложения
    Polynomial operator+(const Polynomial& other) const {
        Polynomial result;
        size_t minSize = min(coefficients.size(), other.coefficients.size());
        size_t maxSize = max(coefficients.size(), other.coefficients.size());

        result.coefficients.resize(maxSize);

        for (size_t i = 0; i < minSize; ++i) {
            result.coefficients[i] = coefficients[i] + other.coefficients[i];
        }

        const auto& largerCoeff = (coefficients.size() > other.coefficients.size()) ? coefficients : other.coefficients;

        for (size_t i = minSize; i < maxSize; ++i) {
            result.coefficients[i] = largerCoeff[i];
        }

        return result;
    }

    //оператор вычитания
    Polynomial operator-(const Polynomial& other) const {
        Polynomial result;
        size_t minSize = min(coefficients.size(), other.coefficients.size());
        size_t maxSize = max(coefficients.size(), other.coefficients.size());

        result.coefficients.resize(maxSize);

        for (size_t i = 0; i < minSize; ++i) {
            result.coefficients[i] = coefficients[i] - other.coefficients[i];
        }

        const auto& largerCoeff = (coefficients.size() > other.coefficients.size()) ? coefficients : other.coefficients;

        for (size_t i = minSize; i < maxSize; ++i) {
            result.coefficients[i] = largerCoeff[i];
        }

        return result;
    }

    //оператор умножения многочлена на скаляр
    Polynomial operator*(const T& scalar) {
        Polynomial result = *this;
        for (auto& coeff : result.coefficients) {
            coeff *= scalar;
        }
        return result;
    }
};

//перегрука оператора вывода
template <typename T>
ostream& operator<<(ostream& os, const Polynomial<T>& poly) {
    for (int i = poly.coefficients.size() - 1; i >= 0; --i) {
        if (poly.coefficients[i] != 0) {
            if (i < poly.coefficients.size() - 1) {
                os << " + ";
            }
            os << poly.coefficients[i];
            if (i > 0) {
                os << "x";
                if (i > 1) {
                    os << "^" << i;
                }
            }
        }
    }
    return os;
}

// Перегрузка оператора равенства (==)
bool operator==(const Polynomial& other) const {
    return coefficients == other.coefficients;
};

// Перегрузка оператора неравенства (!=)
bool operator!=(const Polynomial& other) const {
    return coefficients != other.coefficients;
}
};


int main() {
    // Создаем объект многочлена без коэффициентов
    Polynomial<int> poly1;

    // Создаем объект многочлена с максимальной степенью 3
    Polynomial<int> poly2(3);

    // Создаем объект многочлена со значениями коэффициентов
    vector<float> values = { 2.0, 3.0, 1.0 };
    Polynomial<float> poly3(values);

    // Используем метод set_сoefficient для установки коэффициента при заданной степени
    poly3.set_сoefficient(2, 5.0);

    cout << poly1 << endl << poly2 << endl;

    return 0;
}