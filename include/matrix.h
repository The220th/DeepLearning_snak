#ifndef MATRIX_H

#define MATRIX_H

#include <iostream>
#include <string>

using namespace std;

template <typename T>
class Matrix
{
    private:
    //Matrix();
    T **a;
    const size_t n, m;
    string printOutOfBound(string ij, size_t ij_val) const;

    public:
    Matrix(size_t n_row, size_t m_column);
    Matrix(const Matrix& clonner);
    ~Matrix();

    size_t get_n() const;
    size_t get_m() const;

    T get(size_t i, size_t j) const;
    void set(T value, size_t i, size_t j);

    static Matrix multiply(const Matrix& one, const Matrix& two);
    static Matrix add(const Matrix& one, const Matrix& two);

    Matrix multiply(const Matrix& other) const;
    Matrix add(const Matrix& other) const;

    // Не меняет текущую. Создаёт новую
    Matrix inverse() const;

    string toString();
    string str();

    //template<T> friend ostream& operator<< (ostream &out, const Matrix<T> &ma);
};

// Функция, производящая обращение матрицы.
// Принимает:
//     matrix - матрица для обращения
//     result - матрица достаточного размера для вмещения результата
//     size   - размерность матрицы
// Возвращает:
//     true в случае успешного обращения, false в противном случае
bool matrix_inverse(double **matrix, double **result, const int size);

#endif // MATRIX_H
