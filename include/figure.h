#ifndef FIGURE_H
#define FIGURE_H

#include "point.h"
#include <iostream>
#include <memory>
#include <cmath>

template<Scalar T>
class Figure {
public:
    Figure(unsigned int pointsAmount) : amountOfPoints(pointsAmount) {
        points = std::make_unique<std::unique_ptr<Point<T>>[]>(pointsAmount);
        for (unsigned int i = 0; i < pointsAmount; ++i) {
            points[i] = std::make_unique<Point<T>>();
        }
    }
    
    Figure(const Figure& other) : amountOfPoints(other.amountOfPoints) {
        points = std::make_unique<std::unique_ptr<Point<T>>[]>(amountOfPoints);
        for (unsigned int i = 0; i < amountOfPoints; ++i) {
            points[i] = std::make_unique<Point<T>>(*other.points[i]);
        }
    }
    
    Figure(Figure&& other) noexcept 
        : amountOfPoints(other.amountOfPoints), points(std::move(other.points)) {
        other.amountOfPoints = 0;
    }
    
    ~Figure() = default;

    double area() const {
        double area = 0.0;
        for (unsigned int i = 0; i < amountOfPoints; ++i) {
            unsigned int j = (i + 1) % amountOfPoints;
            area += points[i]->x * points[j]->y - points[j]->x * points[i]->y;
        }
        return std::abs(area) / 2.0;
    }

    explicit operator double() const {
        return area();
    }

    unsigned int getAmountOfPoints() const { return amountOfPoints; }
    
    Point<T> getPoint(unsigned int index) const {
        return *points[index];
    }

    Point<T> center() const {
        T X = 0, Y = 0;
        for (unsigned int i = 0; i < amountOfPoints; ++i) {
            X += points[i]->x;
            Y += points[i]->y;
        }
        return Point<T>(X / amountOfPoints, Y / amountOfPoints);
    }

    bool operator==(const Figure& otherFig) const {
        if (amountOfPoints != otherFig.amountOfPoints) return false;
        for (unsigned int i = 0; i < amountOfPoints; ++i) {
            if (!(*points[i] == *otherFig.points[i])) return false;
        }
        return true;
    }

    Figure& operator=(const Figure& otherFig) {
        if (this != &otherFig) {
            amountOfPoints = otherFig.amountOfPoints;
            points = std::make_unique<std::unique_ptr<Point<T>>[]>(amountOfPoints);
            for (unsigned int i = 0; i < amountOfPoints; ++i) {
                points[i] = std::make_unique<Point<T>>(*otherFig.points[i]);
            }
        }
        return *this;
    }

    Figure& operator=(Figure&& otherFig) noexcept {
        if (this != &otherFig) {
            amountOfPoints = otherFig.amountOfPoints;
            points = std::move(otherFig.points);
            otherFig.amountOfPoints = 0;
        }
        return *this;
    }
    
    virtual void print(std::ostream& os) const = 0;
    virtual void read(std::istream& is) = 0;

    friend std::ostream& operator<<(std::ostream& os, const Figure<T>& fig) {
        fig.print(os);
        return os;
    }
    
    friend std::istream& operator>>(std::istream& is, Figure<T>& fig) {
        fig.read(is);
        return is;
    }

protected:
    unsigned int amountOfPoints = 0;
    std::unique_ptr<std::unique_ptr<Point<T>>[]> points = nullptr;
};

#endif