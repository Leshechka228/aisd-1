#include <complex>
#include <utility>
#include <cmath>
#include <limits>
#include <memory>
#include <iostream>

using namespace std;

template<typename T>
class Polynomial {
private:
    T* coefficients;
    int degree;
    static constexpr double epsilon = 1e-6;

public:

    Polynomial(int maxDegree = 0) : degree(maxDegree) {
        coefficients = new T[degree + 1]{};
    }

    Polynomial(const Polynomial<T>& other) : degree(other.degree) {
        coefficients = new T[degree + 1];

        for (int i = 0; i <= degree; i++)
            coefficients[i] = other.coefficients[i];
    }

    ~Polynomial() {
        delete[] coefficients;
    }

    T operator[](int degree) const {
        if (degree < 0 || degree > this->degree)
            return 0;

        return coefficients[degree];
    }

    void set(int degree, T value) {
        if (degree < 0)
            return;

        if (degree > this->degree)
            resize(degree);

        coefficients[degree] = value;
    }

    Polynomial<T> operator+(const Polynomial<T>& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial<T> result(maxDegree);

        for (int i = 0; i <= maxDegree; i++)
            result.set(i, (*this)[i] + other[i]);

        return result;
    }

    Polynomial<T> operator-(const Polynomial<T>& other) const {
        int maxDegree = max(degree, other.degree);
        Polynomial<T> result(maxDegree);

        for (int i = 0; i <= maxDegree; i++)
            result.set(i, (*this)[i] - other[i]);

        return result;
    }

    Polynomial<T> operator*(T scalar) const {
        Polynomial<T> result(degree);

        for (int i = 0; i <= degree; i++)
            result.set(i, (*this)[i] * scalar);

        return result;
    }

    T evaluate(T x) const {
        T result = 0;
        T xPower = 1;

        for (int i = 0; i <= degree; i++) {
            result += coefficients[i] * xPower;
            xPower *= x;
        }

        return result;
    }

    void shrink_to_fit() {
        int newDegree = degree;

        for (int i = degree; i >= 0; i--) {
            if (coefficients[i] != 0)
                continue;

            newDegree--;
        }

        resize(newDegree);
    }

    void expand(int newDegree) {
        if (newDegree <= degree)
            return;

        T* newCoefficients = new T[newDegree + 1]{};

        for (int i = 0; i <= degree; i++)
            newCoefficients[i] = coefficients[i];

        delete[] coefficients;
        coefficients = newCoefficients;
        degree = newDegree;
    }

    void resize(int newDegree) {
        T* newCoefficients = new T[newDegree + 1]{};

        for (int i = 0; i <= degree && i <= newDegree; i++)
            newCoefficients[i] = coefficients[i];

        delete[] coefficients;
        coefficients = newCoefficients;
        degree = newDegree;
    }

    int getDegree() const {
        return degree;
    }

    bool operator==(const Polynomial<T>& other) const {
        if (degree != other.degree)
            return false;

        for (int i = 0; i <= degree; i++) {
            if (abs(coefficients[i] - other.coefficients[i]) > epsilon)
                return false;
        }

        return true;
    }

    bool operator!=(const Polynomial<T>& other) const {
        return !(*this == other);
    }

    friend ostream& operator<<(ostream& os, const Polynomial<T>& polynomial) {
        for (int i = polynomial.degree; i >= 0; i--) {
            T coefficient = polynomial.coefficients[i];

            if (abs(coefficient) > polynomial.epsilon) {
                if (coefficient > 0 && i != polynomial.degree)
                    os << " + ";
                else if (coefficient < 0)
                    os << " - ";

                os << abs(coefficient);

                if (i > 0)
                    os << "x";

                if (i > 1)
                    os << "^" << i;
            }
        }
        return os;
    }
};

template<typename T>
double findRoot(const Polynomial<T>& poly) {
    if (poly[1] == 0)
        return numeric_limits<double>::quiet_NaN();

    return -poly[0] / poly[1];
}

template<typename T>
pair<float, float> findRoots(const Polynomial<T>& poly) {
    pair<float, float> roots;

    if (poly[2] == 0) {
        float root = findRoot(poly);
        roots.first = root;
        roots.second = root;
    }
    else {
        float discriminant = poly[1] * poly[1] - 4 * poly[2] * poly[0];

        if (discriminant < 0) {
            roots.first = numeric_limits<float>::quiet_NaN();
            roots.second = numeric_limits<float>::quiet_NaN();
        }
        else {
            roots.first = (-poly[1] + sqrt(discriminant)) / (2 * poly[2]);
            roots.second = (-poly[1] - sqrt(discriminant)) / (2 * poly[2]);
        }
    }

    return roots;
}

int main() {
    Polynomial<int> poly1(1);
    poly1.set(1, 3);
    poly1.set(0, -3);
    cout << poly1 << endl;

    Polynomial<int> poly2(2);
    poly2.set(2, 1);
    poly2.set(1, 3);
    poly2.set(0, -5);
    cout << poly2 << endl;

    float root1 = findRoot(poly1);
    pair<double, double> roots2 = findRoots(poly2);

    cout << "Root of poly1: " << root1 << endl;
    cout << "Roots of poly2: " << roots2.first << ", " << roots2.second << endl;

    return 0;
}