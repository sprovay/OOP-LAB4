#include <iostream>
#include <memory>
#include "array.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"

int main() {
    Array<Figure<int>> figureArray1;
    
    auto triangle1 = std::make_shared<Triangle<int>>();
    std::cout << "Введите 3 точки треугольника (целые числа): ";
    std::cin >> *triangle1; // 0 0 4 0 2 3
    figureArray1.add(triangle1);

    auto triangle2 = std::make_shared<Triangle<int>>();
    std::cout << "Введите 3 точки второго треугольника (целые числа): ";
    std::cin >> *triangle2; // 1 1 5 1 3 4
    figureArray1.add(triangle2);

    auto hexagon = std::make_shared<Hexagon<int>>();
    std::cout << "Введите 6 точек шестиугольника (целые числа): ";
    std::cin >> *hexagon; // 0 2 1 1 2 1 3 2 2 3 1 3
    figureArray1.add(hexagon);

    auto octagon = std::make_shared<Octagon<int>>();
    std::cout << "Введите 8 точек восьмиугольника (целые числа): ";
    std::cin >> *octagon; // 0 1 1 0 2 0 3 1 3 2 2 3 1 3 0 2
    figureArray1.add(octagon);

    figureArray1.printAll();
    std::cout << "Общая площадь всех фигур: " << figureArray1.totalArea() << std::endl;

    bool areEqual = (*triangle1 == *triangle2);
    std::cout << "Треугольники равны: " << areEqual << std::endl;

    double triangleArea = (double)*triangle1;
    std::cout << "Площадь первого треугольника: " << triangleArea << std::endl;

    std::cout << "\nУдаляем фигуру с индексом 1..." << std::endl;
    figureArray1.remove(1);
    
    figureArray1.printAll();
    std::cout << "Общая площадь после удаления: " << figureArray1.totalArea() << std::endl;

    Array<Triangle<double>> triangleArray;
    
    auto doubleTriangle = std::make_shared<Triangle<double>>();
    std::cout << "\nВведите 3 точки треугольника (вещественные числа): ";
    std::cin >> *doubleTriangle; // 0.5 0.5 4.5 0.5 2.5 3.5
    triangleArray.add(doubleTriangle);
    
    triangleArray.printAll();

    return 0;
}