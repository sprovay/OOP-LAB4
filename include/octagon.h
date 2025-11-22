#ifndef OCTAGON_H
#define OCTAGON_H

#include "figure.h"

template<Scalar T>
class Octagon : public Figure<T> {
public:
    Octagon() : Figure<T>(8) {}

    void print(std::ostream& os) const {
        os << "Восьмиугольник: ";
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