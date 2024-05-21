#include <iostream>
#include <cmath>
#include <locale> // ���������� ���������� ��� setlocale

using namespace std;

// ����������� ����� �����
class Point {
protected:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {} // ����������� � ����������� �� ���������
    virtual ~Point() {} // ����������� ����������
    virtual void draw() const = 0; // ����� ����������� ������� ��� ���������
    virtual void remove() const = 0; // ����� ����������� ������� ��� ��������
    virtual void move(double dx, double dy) { // ����� ��� ����������� �����
        x += dx;
        y += dy;
    }
    virtual void rotate(double angle) = 0; // ����� ����������� ������� ��� ��������
};

// ����� �����, ����������� �� �����
class Line : public Point {
protected:
    double x2, y2;
public:
    Line(double x1, double y1, double x2, double y2) : Point(x1, y1), x2(x2), y2(y2) {}
    void draw() const override {
        cout << "������ ����� �� (" << x << ", " << y << ") �� (" << x2 << ", " << y2 << ")\n";
    }
    void remove() const override {
        cout << "������� �����\n";
    }
    void move(double dx, double dy) override {
        Point::move(dx, dy);
        x2 += dx;
        y2 += dy;
    }
    void rotate(double angle) override {
        double rad = angle * M_PI / 180;
        double nx2 = x + (x2 - x) * cos(rad) - (y2 - y) * sin(rad);
        double ny2 = y + (x2 - x) * sin(rad) + (y2 - y) * cos(rad);
        x2 = nx2;
        y2 = ny2;
    }
};

// ����� �������������, ����������� �� �����
class Rectangle : public Point {
protected:
    double width, height;
public:
    Rectangle(double x, double y, double width, double height) : Point(x, y), width(width), height(height) {}
    void draw() const override {
        cout << "������ ������������� � (" << x << ", " << y << ") � ������� " << width << " � ������� " << height << "\n";
    }
    void remove() const override {
        cout << "������� �������������\n";
    }
    void rotate(double angle) override {
        cout << "������������ ������������� �� " << angle << " ��������\n";
    }
};

// ����� �������, ����������� �� ��������������
class Square : public Rectangle {
public:
    Square(double x, double y, double side) : Rectangle(x, y, side, side) {}
    void draw() const override {
        cout << "������ ������� � (" << x << ", " << y << ") �� �������� " << width << "\n";
    }
    void remove() const override {
        cout << "������� �������\n";
    }
};

// ����� ��������������, ���������� ����������� ������������ �� ��������������
class Parallelogram : public virtual Rectangle {
protected:
    double angle; // ���� ����� ���������� � ������� ��������
public:
    Parallelogram(double x, double y, double width, double height, double angle) : Rectangle(x, y, width, height), angle(angle) {}
    void draw() const override {
        cout << "������ �������������� � (" << x << ", " << y << ") � ������� " << width << ", ������� " << height << " � ����� " << angle << "\n";
    }
    void remove() const override {
        cout << "������� ��������������\n";
    }
    void rotate(double angle) override {
        cout << "������������ �������������� �� " << angle << " ��������\n";
    }
};

// ����� ����, ����������� �� ���������������
class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double side, double angle) : Parallelogram(x, y, side, side, angle) {}
    void draw() const override {
        cout << "������ ���� � (" << x << ", " << y << ") �� �������� " << width << " � ����� " << angle << "\n";
    }
    void remove() const override {
        cout << "������� ����\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // ������������� ����������� �� ������� ����

    // �������� ������� ���������� �� ������� �������
    Point* objects[] = {
        new Line(0, 0, 5, 5),
        new Rectangle(1, 1, 4, 3),
        new Square(2, 2, 2),
        new Parallelogram(3, 3, 4, 2, 30),
        new Rhombus(4, 4, 3, 45)
    };

    // �������� �� ������� �������� � ����� �������
    for (Point* obj : objects) {
        obj->draw();
        obj->move(1, 1);
        obj->rotate(45);
        obj->remove();
        delete obj; // �������� ������� ��� ������������ ������
    }

    return 0;
}
