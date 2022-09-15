/**
 Developer: Niraj Nepal
 Date: 09/22/2022
 Description: This program creates uses the rand() function to generate random shapes, giving them randomly lengths from 1-99 inclusive and then takes the randomly generated shapes,
 calculates area/circumference then sorts them by area/circumference, finally printing them out sorted into the console.
 Credits: Programiz( For indepth help in understanding inheritence and how to implement subclasses, Cplusplus.org for helping with syntax and better formatting and uses of pointers.
 **/
#include <iostream>
#include <random>
#include <math.h>
using namespace std;

class Shape {
    public:
    int count;
    string name;
    double length, radius;
    Shape(string name, int count) { this->name = name; count = 0; }
    double  get_area (double length);
    double  get_circumference(double radius);
    friend ostream& operator<<(ostream& os, const Shape& shape);
};

double Shape::get_area(double length) { return length * length;}
double Shape::get_circumference(double radius) { return 2 * M_PI * radius; }


ostream& operator<<(ostream& os,  Shape& shape) {
    if (shape.name == "Circle") {
        os << shape.name<<""<< shape.count<<":  " << shape.radius << " " << shape.get_circumference(shape.radius);
    } else if (shape.name == "Triangle") {
        os << shape.name <<""<<shape.count<< ":  " << shape.length << " " << shape.get_area(shape.length);
    } else if (shape.name == "Square") {
        os << shape.name<<""<<shape.count<<":  " << shape.length << " " << shape.get_area(shape.length);
    }
    return os;
}


class Triangle : public Shape {
    public:

    Triangle() : Shape("Triangle", 0) {count =0; length = 0; }
    double get_area(double length) { return (sqrt(3) / 4) * pow(length, 2);}
    double get_circumference(double length) { return 3 * length; }
};


class Square : public Shape {
    public:
    Square() : Shape("Square", 0) { count=0; length = 0; }
    double get_area(double length) { return pow(length, 2);}
    double get_circumference(double length) { return 4 * length;}
    };




class Circle : public Shape{
    public:
    Circle() : Shape("Circle",0) { radius = 0; count = 0; }
    double get_area(double radius) { return M_PI * pow(radius, 2);}
    double get_circumference(double radius) { return 2 * M_PI * radius; }
};


/*void sort_by_area(Shape **low, Shape **high) {
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
}*/
void sort_by_area(Shape **low, Shape **high) {
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

/*
void sort_by_circumference(Shape **low, Shape **high){
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
*/

void sort_by_circumference(Shape **low, Shape **high) {
    Shape *temp;
    for (int i = 0; i < 10; i++) {
        for (int j = i + 1; j < 10; j++) {
            if (low[i]->get_circumference(low[i]->radius) > low[j]->get_circumference(low[j]->radius)) {
                temp = low[i];
                low[i] = low[j];
                low[j] = temp;
            }
        }
    }
}

int main(){
    Shape *shapes[25];

for (int i = 0; i < 25; i++) {
        int random = rand() % 3;
        if (random == 0) {
            shapes[i] = new Triangle();
            shapes[i]->length = rand() % 99 + 1;
            shapes[i]->count = i;
        } else if (random == 1) {
           shapes[i] = new Square();
           shapes[i]->length = rand() % 99 + 1;
              shapes[i]->count = i;
        } else if (random == 2) {
            shapes[i] = new Circle();
            shapes[i]->radius = rand() % 99 + 1;
            shapes[i]->count = i;
        }
    }

   sort_by_area(shapes, shapes + 25);
    cout<< "Shape L/R Area" << endl;
    for (int i = 0; i < 25; i++) { cout <<*shapes[i] << endl; }

    cout << endl;
    sort_by_circumference(shapes, shapes + 25);
    cout<<"Shape L/R Circumference" <<endl;
    for (int i = 0; i < 25; i++) { cout <<*shapes[i] << endl; }

    for (int i = 0; i < 25; i++) { delete shapes[i]; }
    return 0;
}
