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
#include <iomanip>
using namespace std;

class Shape{
public:
    int count;
    string name;
    double length, radius;
    Shape(string name, int count){this->name = name; count = 0;}
    virtual double  get_area ();
    virtual double  get_circumference();
    friend ostream& operator<<(ostream& os, const Shape& shape);
};

double Shape::get_area(){return length * length;}
double Shape::get_circumference(){return 2 * M_PI * radius;}

 ostream& operator<<(ostream& os,  Shape& shape){
        int shapeNum = 0;
        if(shape.name == "Circle"){ shapeNum = 0;
        }
        else if(shape.name == "Triangle"){
            shapeNum = 1;
        }
        else if(shape.name == "Square"){
            shapeNum = 2;
        }

    switch(shapeNum){
        case 0:
            os <<fixed <<setprecision(2) <<shape.name<<""<<shape.count<<":  " << shape.radius << "   "<<shape.get_area()<<"    " <<shape.get_circumference();
            break;
        case 1:
            os  <<fixed <<setprecision(2) << shape.name <<""<<shape.count<< ":  " << shape.length << "   " << shape.get_area() <<"    "   << shape.get_circumference();
            break;
        case 2:
            os <<fixed <<setprecision(2) << shape.name<<""<<shape.count<<":  " << shape.length << "   "  << shape.get_area()<<"    "  << shape.get_circumference();
            break;
    }
    return os;
}



class Triangle : public Shape{
public:
    Triangle() : Shape("Triangle", 0) {}
    double get_area(){return floor((sqrt(3)/4) * pow(length, 2));}
    double get_circumference(){return floor(3 * length);}

};

class Square : public Shape{
public:
    Square() : Shape("Square", 0) { }
    double get_area(){return floor(pow(length, 2));}
    double get_circumference(){return floor(4 * length);}

};



class Circle : public Shape{
public:
    Circle() : Shape("Circle", 0) { }
    double get_area(){return floor(M_PI * pow(radius, 2));}
    double get_circumference(){return floor(2 * M_PI * radius);}
};

void sort_by_area(Shape **low, Shape **high) {
    Shape *temp;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 25; j++) {
            if (low[i]->get_area() > low[j]->get_area()) {
                temp = low[i];
                low[i] = low[j];
                low[j] = temp;
            }
        }
    }
}



void sort_by_circumference(Shape **low, Shape **high) {
    Shape *temp;
    for (int i = 0; i < 25; i++) {
        for (int j = i + 1; j < 25; j++) {
            if (low[i]->get_circumference() > low[j]->get_circumference()) {
                temp = low[i];
                low[i] = low[j];
                low[j] = temp;
            }
        }
    }
}


int main(){
    Shape *shapes[25];
    int length = sizeof(shapes)/sizeof(shapes[0]);
    for (int i = 0; i < 25; i++) {
        int random = rand() % 3;
        switch (random) {
            case 0:
                shapes[i] = new Triangle();
                shapes[i]->length = rand() % 100 +1;
                shapes[i]->count = i;
                break;
            case 1:
                shapes[i] = new Square();
                shapes[i]->length = rand() % 100+1;
                shapes[i]->count = i;
                break;
            case 2:
                shapes[i] = new Circle();
                shapes[i]->radius = rand() % 100+1;
                shapes[i]->count = i;
                break;
        }
    }

    sort_by_area(shapes, shapes + length-1);
    for (int i = 0; i < 25; i++) {
        cout << *shapes[i] << endl;
    }
    cout << endl;
    sort_by_circumference(shapes, shapes + length-1);
    for (int i = 0; i < 25; i++) {
        cout << *shapes[i] << endl;
    }
    return 0;
/*
    sort_by_area(shapes, shapes+length-1);
    cout<< "Shape L/R Area" << endl;
     for(int i = 0; i < 25; i++) {
        cout <<*shapes[i] << endl;
    }


    cout << endl;
    sort_by_circumference(shapes, shapes + 25);
    cout<<"Shape L/R Circumference" <<endl;
    for (int i = 0; i < 25; i++) { cout <<*shapes[i] << endl; }

    for (int i = 0; i < 25; i++) { delete shapes[i]; }
    return 0;

*/
}
