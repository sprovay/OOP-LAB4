#include <gtest/gtest.h>
#include <sstream>
#include "point.h"
#include "triangle.h"
#include "hexagon.h"
#include "octagon.h"
#include "array.h"

TEST(PointTest, DefaultConstructor) {
    Point<int> p;
    EXPECT_EQ(p.x, 0);
    EXPECT_EQ(p.y, 0);
}

TEST(PointTest, ParameterizedConstructor) {
    Point<double> p(3.5, 4.2);
    EXPECT_DOUBLE_EQ(p.x, 3.5);
    EXPECT_DOUBLE_EQ(p.y, 4.2);
}

TEST(PointTest, EqualityOperator) {
    Point<int> p1(1, 2);
    Point<int> p2(1, 2);
    Point<int> p3(3, 4);
    
    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

TEST(PointTest, InputOutput) {
    Point<int> p;
    std::istringstream iss("10 20");
    iss >> p;
    
    EXPECT_EQ(p.x, 10);
    EXPECT_EQ(p.y, 20);
    
    std::ostringstream oss;
    oss << p;
    EXPECT_EQ(oss.str(), "(10, 20)");
}

TEST(PointTest, ScalarConcept) {
    // Должно компилироваться для скалярных типов
    Point<int> p1;
    Point<double> p2;
    Point<float> p3;
    
    // Не должно компилироваться для нескалярных типов
    // Point<std::string> p4; // Ошибка компиляции
}

class FigureTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Тестовые данные для треугольников
        triangle_points = {0, 0, 4, 0, 2, 3};
        triangle_points2 = {1, 1, 5, 1, 3, 4};
        
        // Тестовые данные для шестиугольника
        hexagon_points = {0, 2, 1, 1, 2, 1, 3, 2, 2, 3, 1, 3};
        
        // Тестовые данные для восьмиугольника
        octagon_points = {0, 1, 1, 0, 2, 0, 3, 1, 3, 2, 2, 3, 1, 3, 0, 2};
    }
    
    std::vector<int> triangle_points;
    std::vector<int> triangle_points2;
    std::vector<int> hexagon_points;
    std::vector<int> octagon_points;
};

TEST_F(FigureTest, TriangleCreation) {
    auto triangle = std::make_shared<Triangle<int>>();
    
    std::stringstream ss;
    for (size_t i = 0; i < triangle_points.size(); i += 2) {
        ss << triangle_points[i] << " " << triangle_points[i + 1] << " ";
    }
    
    ss >> *triangle;
    
    EXPECT_EQ(triangle->getAmountOfPoints(), 3);
    
    auto center = triangle->center();
    EXPECT_NEAR(center.x, 2.0, 0.001);
    EXPECT_NEAR(center.y, 1.0, 0.001);
}

TEST_F(FigureTest, TriangleArea) {
    auto triangle = std::make_shared<Triangle<int>>();
    
    std::stringstream ss;
    for (auto val : triangle_points) ss << val << " ";
    ss >> *triangle;
    
    double area = triangle->area();
    EXPECT_NEAR(area, 6.0, 0.001); // Площадь треугольника (0,0)-(4,0)-(2,3)
    
    // Проверка оператора приведения
    double casted_area = (double)*triangle;
    EXPECT_NEAR(casted_area, 6.0, 0.001);
}

TEST_F(FigureTest, FigureEquality) {
    auto triangle1 = std::make_shared<Triangle<int>>();
    auto triangle2 = std::make_shared<Triangle<int>>();
    
    std::stringstream ss1, ss2;
    for (auto val : triangle_points) ss1 << val << " ";
    for (auto val : triangle_points) ss2 << val << " "; // те же точки
    
    ss1 >> *triangle1;
    ss2 >> *triangle2;
    
    EXPECT_TRUE(*triangle1 == *triangle2);
}

TEST_F(FigureTest, FigureInequality) {
    auto triangle1 = std::make_shared<Triangle<int>>();
    auto triangle2 = std::make_shared<Triangle<int>>();
    
    std::stringstream ss1, ss2;
    for (auto val : triangle_points) ss1 << val << " ";
    for (auto val : triangle_points2) ss2 << val << " "; // разные точки
    
    ss1 >> *triangle1;
    ss2 >> *triangle2;
    
    EXPECT_FALSE(*triangle1 == *triangle2);
}

TEST_F(FigureTest, CopyConstructor) {
    auto triangle1 = std::make_shared<Triangle<int>>();
    
    std::stringstream ss;
    for (auto val : triangle_points) ss << val << " ";
    ss >> *triangle1;
    
    Triangle<int> triangle2 = *triangle1; // копирование
    
    EXPECT_TRUE(*triangle1 == triangle2);
}

class ArrayTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Создаем тестовые фигуры
        triangle1 = std::make_shared<Triangle<int>>();
        triangle2 = std::make_shared<Triangle<int>>();
        hexagon = std::make_shared<Hexagon<int>>();
        
        std::stringstream ss1, ss2, ss3;
        ss1 << "0 0 4 0 2 3";     // площадь = 6
        ss2 << "1 1 5 1 3 4";     // площадь = 6  
        ss3 << "0 2 1 1 2 1 3 2 2 3 1 3"; // площадь правильного шестиугольника
        
        ss1 >> *triangle1;
        ss2 >> *triangle2;
        ss3 >> *hexagon;
    }
    
    std::shared_ptr<Triangle<int>> triangle1;
    std::shared_ptr<Triangle<int>> triangle2;
    std::shared_ptr<Hexagon<int>> hexagon;
};

TEST_F(ArrayTest, DefaultConstructor) {
    Array<Figure<int>> array;
    
    EXPECT_EQ(array.getSize(), 0);
    EXPECT_GE(array.getCapacity(), 10); // минимальная емкость по умолчанию
    EXPECT_TRUE(array.isEmpty());
}

TEST_F(ArrayTest, AddFigures) {
    Array<Figure<int>> array;
    
    array.add(triangle1);
    EXPECT_EQ(array.getSize(), 1);
    EXPECT_FALSE(array.isEmpty());
    
    array.add(triangle2);
    EXPECT_EQ(array.getSize(), 2);
    
    array.add(hexagon);
    EXPECT_EQ(array.getSize(), 3);
}

TEST_F(ArrayTest, TotalAreaCalculation) {
    Array<Figure<int>> array;
    
    array.add(triangle1); // площадь = 6
    array.add(triangle2); // площадь = 6
    
    // Вычисли реальную площадь шестиугольника
    double hexagon_area = hexagon->area();
    
    array.add(hexagon);
    
    double total_area = array.totalArea();
    double expected_total = 6 + 6 + hexagon_area;
    
    EXPECT_NEAR(total_area, expected_total, 0.001);
}

TEST_F(ArrayTest, RemoveFigure) {
    Array<Figure<int>> array;
    
    array.add(triangle1);
    array.add(triangle2);
    array.add(hexagon);
    
    EXPECT_EQ(array.getSize(), 3);
    
    array.remove(1); // удаляем второй треугольник
    EXPECT_EQ(array.getSize(), 2);
    
    // Проверяем, что остались первая и третья фигуры
    EXPECT_TRUE(*array[0] == *triangle1);
    EXPECT_TRUE(*array[1] == *hexagon);
}

TEST_F(ArrayTest, AccessOperators) {
    Array<Figure<int>> array;
    
    array.add(triangle1);
    
    // Проверяем доступ к элементу
    EXPECT_TRUE(*array[0] == *triangle1);
    
    // Проверяем константный доступ
    const Array<Figure<int>>& const_array = array;
    EXPECT_TRUE(*const_array[0] == *triangle1);
}

TEST_F(ArrayTest, ArrayResize) {
    Array<Figure<int>> array(2); // начальная емкость = 2
    
    EXPECT_EQ(array.getCapacity(), 2);
    
    array.add(triangle1);
    array.add(triangle2);
    
    // Добавляем третью фигуру - должен произойти resize
    array.add(hexagon);
    
    EXPECT_GE(array.getCapacity(), 3); // емкость должна увеличиться
    EXPECT_EQ(array.getSize(), 3);
}

TEST_F(ArrayTest, ClearArray) {
    Array<Figure<int>> array;
    
    array.add(triangle1);
    array.add(triangle2);
    
    EXPECT_EQ(array.getSize(), 2);
    EXPECT_FALSE(array.isEmpty());
    
    array.clear();
    
    EXPECT_EQ(array.getSize(), 0);
    EXPECT_TRUE(array.isEmpty());
}

TEST_F(ArrayTest, DifferentTemplateTypes) {
    // Тестируем с разными скалярными типами
    
    Array<Figure<double>> doubleArray;
    auto doubleTriangle = std::make_shared<Triangle<double>>();
    
    std::stringstream ss;
    ss << "0.5 0.5 4.5 0.5 2.5 3.5";
    ss >> *doubleTriangle;
    
    doubleArray.add(doubleTriangle);
    EXPECT_EQ(doubleArray.getSize(), 1);
    
    // Тестируем с конкретным типом фигуры
    Array<Triangle<float>> triangleArray;
    auto floatTriangle = std::make_shared<Triangle<float>>();
    
    std::stringstream ss2;
    ss2 << "1.0 1.0 3.0 1.0 2.0 2.0";
    ss2 >> *floatTriangle;
    
    triangleArray.add(floatTriangle);
    EXPECT_EQ(triangleArray.getSize(), 1);
}