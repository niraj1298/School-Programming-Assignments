#include <iostream>
#include <random>
#include <math.h>
using namespace std;

class Shape {
    public:
    string name;
    double length, radius;
    Shape(string name) {
        this->name = name;
    }
    double  get_area (double length);

    double  get_circumference(double radius);
//create an operator overload for << that will print the shape and  the length or radius depending on the shape then the area or circumference depending on the shape
    friend ostream& operator<<(ostream& os, const Shape& shape);
};

double Shape::get_area(double length) {
    return length * length;
}

double Shape::get_circumference(double radius) {
    return 2 * M_PI * radius;
}

ostream& operator<<(ostream& os,  Shape& shape) {
    if (shape.name == "Circle") {
        os << shape.name << " " << shape.radius << " " << shape.get_circumference(shape.radius);
    } else if (shape.name == "Triangle") {
        os << shape.name << " " << shape.length << " " << shape.get_area(shape.length);
    } else if (shape.name == "Square") {
        os << shape.name << " " << shape.length << " " << shape.get_area(shape.length);
    }
    return os;
}

class Triangle : public Shape {
    public:
    Triangle() : Shape("Triangle") {
        double length = 0;
    }
    double get_area(double length) {
        return (sqrt(3) / 4) * pow(length, 2);
    }
    double get_circumference(double length) {
        return 3 * length;
    }
};



class Square : public Shape {
    public:
    Square() : Shape("Square") {
        double length = 0;
    }
    double get_area(double length) {
        return pow(length, 2);
    }
    double get_circumference(double length) {
        return 4 * length;
    }

    };

class Circle : public Shape{
    public:
    Circle() : Shape("Circle") {
        double radius = 0;
    }
    double get_area(double radius) {
        return M_PI * pow(radius, 2);
    }
    double get_circumference(double radius) {
        return 2 * M_PI * radius;
    }
};


void sort_by_area(Shape **low, Shape **high) {
    //sort the array of shapes by lowest area to highest
    Shape *temp;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (low[i]->get_area(low[i]->length) > low[j]->get_area(low[j]->length)) {
                temp = low[i];
                low[i] = low[j];
                low[j] = temp;
            }
        }

    }
}


    /*Shape *temp;
    for (int i = 0; i < high - low; i++) {
        for (int j = 0; j < high - low - i - 1; j++) {
    if (low[j]->get_area(low[j]->length) > low[j + 1]->get_area(low[j + 1]->length)) {
                temp = low[j];
                low[j] = low[j + 1];
                low[j + 1] = temp;
            }

            }
        }
    }*/

void sort_by_circumference(Shape **low, Shape **high){
    //sort the array of shapes by lowest circumference to highest
    Shape *temp;
    for (int i = 0; i < high - low; i++) {
        for (int j = 0; j < high - low - i - 1; j++) {
    if (low[j]->get_circumference(low[j]->radius) > low[j + 1]->get_circumference(low[j + 1]->radius)) {
                temp = low[j];
                low[j] = low[j + 1];
                low[j + 1] = temp;
            }

                }
            }
        }
    /*
    Shape *temp;
    for (int i = 0; i < high - low; i++) {
        for (int j = 0; j < high - low - i - 1; j++) {
        if (low[j]->get_circumference(low[j]->radius) > low[j + 1]->get_circumference(low[j + 1]->radius)) {
            temp = low[j];
            low[j] = low[j + 1];
            low[j + 1] = temp;
        }
            }
        }*/

int main(){

    Shape *shapes[25];
    for (int i = 0; i < 25; i++) {
        int random = rand() % 3;
        if (random == 0) {
            shapes[i] = new Triangle();
            shapes[i]->length = rand() % 10 + 1;
        } else if (random == 1) {
            shapes[i] = new Square();
            shapes[i]->length = rand() % 10 + 1;
        } else if (random == 2) {
            shapes[i] = new Circle();
            shapes[i]->radius = rand() % 10 + 1;
        }
    }

    sort_by_area(shapes, shapes + 25);
    for (int i = 0; i < 25; i++) {
        cout << *shapes[i] << endl;
    }
    sort_by_circumference(shapes, shapes + 25);
    for (int i = 0; i < 25; i++) {
        cout << *shapes[i] << endl;
    }

    for (int i = 0; i < 25; i++) {
        delete shapes[i];
    }
    return 0;
}
