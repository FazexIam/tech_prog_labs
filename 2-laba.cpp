#include <iostream>

class vect;

class matr {
public:
    int dim;
    double* a;
    int num;
    static int count;

    matr(int d) : dim(d), num(count++) {
        a = new double[dim * dim];
        std::cout << "matrix created " << num << " dimension " << dim << "x" << dim << std::endl;
    }

    matr(const matr& other) : dim(other.dim), num(count++) {
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = other.a[i];
        }
        std::cout << "copied matrix " << other.num << " in matrix " << num << std::endl;
    }

    ~matr() {
        delete[] a;
        std::cout << "deleted matrix " << num << std::endl;
    }

    matr operator+(const matr& other) const;
    matr operator*(const matr& other) const;
    matr& operator=(const matr& other);
    vect operator*(const vect& v) const;

    friend std::ostream& operator<<(std::ostream& os, const matr& m);
};

class vect {
public:
    int dim;
    double* b;
    int num;
    static int count;

    vect(int d) : dim(d), num(count++) {
        b = new double[dim];
        std::cout << "vector created " << num << " dimension " << dim << std::endl;
    }

    vect(const vect& other) : dim(other.dim), num(count++) {
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = other.b[i];
        }
        std::cout << "vector copied " << other.num << " vector " << num << std::endl;
    }

    ~vect() {
        delete[] b;
        std::cout << "vector deleted " << num << std::endl;
    }

    vect operator+(const vect& other) const;
    vect operator*(double k) const;
    vect& operator=(const vect& other);

    friend std::ostream& operator<<(std::ostream& os, const vect& v);
    friend class matr; // Дружественный класс для доступа к приватным членам
};

int vect::count = 0;
int matr::count = 0;

// Определения методов класса vect

vect vect::operator+(const vect& other) const {
    vect result(dim);
    for (int i = 0; i < dim; i++) {
        result.b[i] = b[i] + other.b[i];
    }
    std::cout << "sum of vector " << num << " and " << other.num << " vector " << result.num << std::endl;
    return result;
}

vect vect::operator*(double k) const {
    vect result(dim);
    for (int i = 0; i < dim; i++) {
        result.b[i] = k * b[i];
    }
    std::cout << "multiplication vector " << num << " on scalar " << k << " vector " << result.num << std::endl;
    return result;
}

vect& vect::operator=(const vect& other) {
    if (this != &other) {
        delete[] b;
        dim = other.dim;
        b = new double[dim];
        for (int i = 0; i < dim; i++) {
            b[i] = other.b[i];
        }
    }
    std::cout << "vector assighnment " << other.num << " vector " << num << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const vect& v) {
    os << "Vector is " << v.num << " (" << v.dim << "dimensional): ";
    for (int i = 0; i < v.dim; i++) {
        os << v.b[i] << " ";
    }
    return os;
}

// Определения методов класса matr

matr matr::operator+(const matr& other) const {
    matr result(dim);
    for (int i = 0; i < dim * dim; i++) {
        result.a[i] = a[i] + other.a[i];
    }
    std::cout << "matrix sum " << num << " and " << other.num << " matrix " << result.num << std::endl;
    return result;
}

matr matr::operator*(const matr& other) const {
    matr result(dim);
    for (int i = 0; i < dim; i++) {
        for (int j = 0; j < dim; j++) {
            result.a[i * dim + j] = 0;
            for (int k = 0; k < dim; k++) {
                result.a[i * dim + j] += a[i * dim + k] * other.a[k * dim + j];
            }
        }
    }
    std::cout << "matrix multiplication " << num << " on matrix " << other.num << " matrix " << result.num << std::endl;
    return result;
}

vect matr::operator*(const vect& v) const {
    vect result(dim);
    for (int i = 0; i < dim; i++) {
        result.b[i] = 0;
        for (int j = 0; j < dim; j++) {
            result.b[i] += a[i * dim + j] * v.b[j];
}
    }
    std::cout << "matrix multiplication " << num << " on vector " << v.num << " vector " << result.num << std::endl;
    return result;
}

matr& matr::operator=(const matr& other) {
    if (this != &other) {
        delete[] a;
        dim = other.dim;
        a = new double[dim * dim];
        for (int i = 0; i < dim * dim; i++) {
            a[i] = other.a[i];
        }
    }
    std::cout << "matrix assighnment " << other.num << " matrix " << num << std::endl;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const matr& m) {
    os << "Matrix " << m.num << " (" << m.dim << "x" << m.dim << "): " << std::endl;
    for (int i = 0; i < m.dim; i++) {
        for (int j = 0; j < m.dim; j++) {
            os << m.a[i * m.dim + j] << " ";
        }
        os << std::endl;
    }
    return os;
}

int main() {
    vect v1(3);
    v1.b[0] = 1.0;
    v1.b[1] = 2.0;
    v1.b[2] = 3.0;

    vect v2(v1);

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;

    vect v3 = v1 + v2;
    std::cout << v3 << std::endl;

    matr m1(2);
    m1.a[0] = 1.0; m1.a[1] = 2.0;
    m1.a[2] = 3.0; m1.a[3] = 4.0;

    matr m2(m1);

    std::cout << m1 << std::endl;
    std::cout << m2 << std::endl;

    matr m3 = m1 + m2;
    std::cout << m3 << std::endl;

    vect v4 = m1 * v1;
    std::cout << v4 << std::endl;

    return 0;
}
