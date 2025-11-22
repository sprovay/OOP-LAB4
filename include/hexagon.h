#ifndef HEXAGON_H
#define HEXAGON_H

#include "figure.h"

template<Scalar T>
class Hexagon : public Figure<T> {
public:
    Hexagon() : Figure<T>(6) {}

    void print(std::ostream& os) const {
        os << "Шестиугольник: ";
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