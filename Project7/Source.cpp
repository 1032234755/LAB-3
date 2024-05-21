#include <iostream>
#include <cmath>
#include <locale> // Подключаем библиотеку для setlocale

using namespace std;

// Абстрактный класс Точка
class Point {
protected:
    double x, y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {} // Конструктор с параметрами по умолчанию
    virtual ~Point() {} // Виртуальный деструктор
    virtual void draw() const = 0; // Чисто виртуальная функция для рисования
    virtual void remove() const = 0; // Чисто виртуальная функция для удаления
    virtual void move(double dx, double dy) { // Метод для перемещения точки
        x += dx;
        y += dy;
    }
    virtual void rotate(double angle) = 0; // Чисто виртуальная функция для поворота
};

// Класс Линия, наследуется от Точки
class Line : public Point {
protected:
    double x2, y2;
public:
    Line(double x1, double y1, double x2, double y2) : Point(x1, y1), x2(x2), y2(y2) {}
    void draw() const override {
        cout << "Рисуем линию от (" << x << ", " << y << ") до (" << x2 << ", " << y2 << ")\n";
    }
    void remove() const override {
        cout << "Удаляем линию\n";
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

// Класс Прямоугольник, наследуется от Точки
class Rectangle : public Point {
protected:
    double width, height;
public:
    Rectangle(double x, double y, double width, double height) : Point(x, y), width(width), height(height) {}
    void draw() const override {
        cout << "Рисуем прямоугольник в (" << x << ", " << y << ") с шириной " << width << " и высотой " << height << "\n";
    }
    void remove() const override {
        cout << "Удаляем прямоугольник\n";
    }
    void rotate(double angle) override {
        cout << "Поворачиваем прямоугольник на " << angle << " градусов\n";
    }
};

// Класс Квадрат, наследуется от Прямоугольника
class Square : public Rectangle {
public:
    Square(double x, double y, double side) : Rectangle(x, y, side, side) {}
    void draw() const override {
        cout << "Рисуем квадрат в (" << x << ", " << y << ") со стороной " << width << "\n";
    }
    void remove() const override {
        cout << "Удаляем квадрат\n";
    }
};

// Класс Параллелограмм, использует виртуальное наследование от Прямоугольника
class Parallelogram : public virtual Rectangle {
protected:
    double angle; // Угол между основанием и смежной стороной
public:
    Parallelogram(double x, double y, double width, double height, double angle) : Rectangle(x, y, width, height), angle(angle) {}
    void draw() const override {
        cout << "Рисуем параллелограмм в (" << x << ", " << y << ") с шириной " << width << ", высотой " << height << " и углом " << angle << "\n";
    }
    void remove() const override {
        cout << "Удаляем параллелограмм\n";
    }
    void rotate(double angle) override {
        cout << "Поворачиваем параллелограмм на " << angle << " градусов\n";
    }
};

// Класс Ромб, наследуется от Параллелограмма
class Rhombus : public Parallelogram {
public:
    Rhombus(double x, double y, double side, double angle) : Parallelogram(x, y, side, side, angle) {}
    void draw() const override {
        cout << "Рисуем ромб в (" << x << ", " << y << ") со стороной " << width << " и углом " << angle << "\n";
    }
    void remove() const override {
        cout << "Удаляем ромб\n";
    }
};

int main() {
    setlocale(LC_ALL, "ru"); // Устанавливаем локализацию на русский язык

    // Создание массива указателей на объекты классов
    Point* objects[] = {
        new Line(0, 0, 5, 5),
        new Rectangle(1, 1, 4, 3),
        new Square(2, 2, 2),
        new Parallelogram(3, 3, 4, 2, 30),
        new Rhombus(4, 4, 3, 45)
    };

    // Итерация по массиву объектов и вызов методов
    for (Point* obj : objects) {
        obj->draw();
        obj->move(1, 1);
        obj->rotate(45);
        obj->remove();
        delete obj; // Удаление объекта для освобождения памяти
    }

    return 0;
}
