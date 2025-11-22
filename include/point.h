#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <concepts>

template<typename T>
concept Scalar = std::is_scalar_v<T>;

template<Scalar T>
class Point {
public:
    T x, y;

    Point() : x(0), y(0) {}
    Point(T x, T y) : x(x), y(y) {}
    
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Point<T>& p) {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Point<T>& p) {
        is >> p.x >> p.y;
        return is;
    }
};

#endif