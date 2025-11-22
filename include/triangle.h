#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "figure.h"

template<Scalar T>
class Triangle : public Figure<T> {
public:
    Triangle() : Figure<T>(3) {}

    void print(std::ostream& os) const {
        os << "Треугольник: ";
        for (unsigned int i = 0; i < this->amountOfPoints; ++i) {
            os << *this->points[i];
            if (i < this->amountOfPoints - 1) os << " ";
        }
    }

    void read(std::istream& is) {
        for (unsigned int i = 0; i < this->amountOfPoints; ++i) {
            is >> *this->points[i];
        }
    }
};

#endif