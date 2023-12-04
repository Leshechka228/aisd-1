#include <cmath>
#include <cstdlib> 
#include <iostream> 
#include <vector> 

using namespace std;


template <typename T>
class Polynomial {
private:
    std::vector<T> coefficients;

public:
    Polynomial() {}

    //����������� � �����������: ������������ ������� ����������
    Polynomial(size_t maxDegree) : coefficients(maxDegree + 1, 0) {}

    //����������� � �����������: ������ �������� ��� ��������������� ��������
    Polynomial(const std::vector<T>& values) : coefficients(values.size()) {
        for (size_t i = 0; i < values.size(); ++i) {
            coefficients[i] = values[i];
        }
    }

    //����� set ��� ��������� ������������ ��� �������� �������
    void set_�oefficient(size_t power, T value) {
        if (power <= coefficients.size() - 1) { 
            coefficients[power] = value;
        }
        else {
            throw std::out_of_range("Invalid power value");
        }
    }

    //����� shrink_to_fit, ����������� ������ ���������� �� ���������� ���������� ��� ������� ������� �����
    void shrink_to_fit() {
        int leadingZeros = 0;
        for (int i = coefficients.size() - 1; i >= 0; i--) {
            if (coefficients[i] == 0) {
                leadingZeros++;
            }
        }
        coefficients.resize(coefficients.size() - leadingZeros);
    }

    //����� expand, ������������� ������ ��� ����� ������� ������� � ������������� 0
    void expand(size_t new_size) {
        if (new_size > coefficients.size()) {
            coefficients.resize(new_size, T{ 0 }); // ��������� ����� �������� ������
        }
    }

    T get_coefficient(int degree) const {
        if (degree < coefficients.size()) {
            return coefficients[degree];
        }
        return T();
    }

    int get_degree() const {
        return coefficients.size() - 1;
    }

};

int main() {
    std::vector<int> coeffs1 = { 1, 2, 3 }; // ��������� 1 + 2x + 3x^2
    Polynomial<int> poly1(coeffs1);

    std::vector<int> coeffs2 = { 4, 5 }; // ��������� 4 + 5x
    Polynomial<int> poly2(coeffs2);

    //Polynomial<int> sum = poly1 + poly2; // �������� �����������

    return 0;
}