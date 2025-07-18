#include <iostream>
#include <string>
#include <windows.h>


using namespace std;


class FigureException {
private:
    string message;
public:
    FigureException(const string& msg) : message(msg) {}
    const string& what() const { return message; }
};


class Figure {
protected:
    int sides_count = 0;
    string name = "Фигура";

public:
    Figure() = default;
    virtual ~Figure() = default;

    virtual string get_name() const { return name; }
    virtual int get_sides_count() const { return sides_count; }
    virtual bool check() const { return sides_count == 0; }
    virtual void print_info() const {
        cout << get_name() << ":\n";
        cout << (check() ? "Правильная" : "Неправильная") << "\n";
        cout << "Количество сторон: " << get_sides_count() << "\n";
    }
};


class Triangle : public Figure {
protected:
    int a, b, c;
    int A, B, C;

public:
    Triangle(int a, int b, int c, int A, int B, int C)
        : a(a), b(b), c(c), A(A), B(B), C(C) {
        name = "Треугольник";
        sides_count = 3;

        if (A + B + C != 180) {
            throw FigureException("Сумма углов не равна 180");
        }
    }

    string get_name() const override { return name; }

    bool check() const override {
        return (A + B + C) == 180;
    }

    void print_info() const override {
        Figure::print_info();
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << "\n";
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << "\n\n";
    }
};


class RightTriangle : public Triangle 
{
public:
    RightTriangle(int a, int b, int c, int A, int B)
        : Triangle(a, b, c, A, B, 90) 
    {
        name = "Прямоугольный треугольник";

        if (C != 90) 
        {
            throw FigureException("Угол C не равен 90 градусам");
        }
    }

    bool check() const override 
    {
        return Triangle::check() && (C == 90);
    }
};


class IsoscelesTriangle : public Triangle 
{
public:
    IsoscelesTriangle(int ab, int c, int AB, int C)
        : Triangle(ab, ab, c, AB, AB, C) 
    {
        name = "Равнобедренный треугольник";

        if (a != c || A != C) 
        {
            throw FigureException("Стороны a и c или углы A и C не равны");
        }
    }

    bool check() const override 
    {
        return Triangle::check() && (a == c) && (A == C);
    }
};


class EquilateralTriangle : public Triangle 
{
public:
    EquilateralTriangle(int a)
        : Triangle(a, a, a, 60, 60, 60) 
    {
        name = "Равносторонний треугольник";

        if (a != b || b != c || A != 60 || B != 60 || C != 60) 
        {
            throw FigureException("Не все стороны равны или не все углы равны 60 градусам");
        }
    }

    bool check() const override 
    {
        return Triangle::check() && (a == b && b == c) && (A == 60 && B == 60 && C == 60);
    }
};


class Quadrangle : public Figure 
{
protected:
    int a, b, c, d;
    int A, B, C, D;

public:
    Quadrangle(int a, int b, int c, int d, int A, int B, int C, int D)
        : a(a), b(b), c(c), d(d), A(A), B(B), C(C), D(D) 
    {
        name = "Четырёхугольник";
        sides_count = 4;

        if (A + B + C + D != 360) 
        {
            throw FigureException("Сумма углов не равна 360");
        }
    }

    string get_name() const override { return name; }

    bool check() const override 
    {
        return (A + B + C + D) == 360;
    }

    void print_info() const override 
    {
        Figure::print_info();
        cout << "Стороны: a=" << a << " b=" << b << " c=" << c << " d=" << d << "\n";
        cout << "Углы: A=" << A << " B=" << B << " C=" << C << " D=" << D << "\n\n";
    }
};


class Rectangle : public Quadrangle 
{
public:
    Rectangle(int width, int height)
        : Quadrangle(width, height, width, height, 90, 90, 90, 90) 
    {
        name = "Прямоугольник";

        if (a != c || b != d) 
        {
            throw FigureException("Противоположные стороны не равны");
        }
        if (A != 90 || B != 90 || C != 90 || D != 90)
        {
            throw FigureException("Не все углы равны 90 градусам");
        }
    }

    bool check() const override 
    {
        return Quadrangle::check() && (a == c && b == d) && (A == 90 && B == 90 && C == 90 && D == 90);
    }
};


class Square : public Rectangle 
{
public:
    Square(int a) : Rectangle(a, a) 
    {
        name = "Квадрат";

        if (a != b || b != c || c != d) 
        {
            throw FigureException("Не все стороны равны");
        }
    }

    bool check() const override 
    {
        return Rectangle::check() && (a == b && b == c && c == d);
    }
};

class Parallelogram : public Quadrangle 
{
public:
    Parallelogram(int a, int b, int A, int B)
        : Quadrangle(a, b, a, b, A, B, A, B) 
    {
        name = "Параллелограмм";

        if (a != c || b != d) 
        {
            throw FigureException("Противоположные стороны не равны");
        }
        if (A != C || B != D) 
        {
            throw FigureException("Противоположные углы не равны");
        }
    }

    bool check() const override 
    {
        return Quadrangle::check() && (a == c && b == d) && (A == C && B == D);
    }
};

class Rhomb : public Parallelogram 
{
public:
    Rhomb(int a, int A, int B)
        : Parallelogram(a, a, A, B) 
    {
        name = "Ромб";

        if (a != b || b != c || c != d) 
        {
            throw FigureException("Не все стороны равны");
        }
    }

    bool check() const override 
    {
        return Parallelogram::check() && (a == b && b == c && c == d);
    }
};


int main() 
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    try 
    {

        cout << "=== Правильные фигуры ===\n";
        RightTriangle rt(3, 4, 5, 30, 60);
        rt.print_info();

        EquilateralTriangle et(10);
        et.print_info();

        Square sq(5);
        sq.print_info();

        cout << "\n=== Неправильные фигуры ===\n";

        try {
            Triangle bad_triangle(1, 1, 1, 60, 60, 70);
        }
        catch (const FigureException& e) {
            cout << "Ошибка создания треугольника: " << e.what() << endl;
        }

        try {
            RightTriangle bad_rt(3, 4, 5, 45, 45);
        }
        catch (const FigureException& e) {
            cout << "Ошибка создания прямоугольного треугольника: " << e.what() << endl;
        }

        try {
            Square bad_sq(0);
        }
        catch (const FigureException& e) {
            cout << "Ошибка создания квадрата: " << e.what() << endl;
        }
    }
    catch (const FigureException& e) {
        cout << "Неожиданная ошибка: " << e.what() << endl;
    }

    return 0;
}