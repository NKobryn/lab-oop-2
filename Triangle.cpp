#include "Triangle.h"
#include <cmath>
#include <iostream>

using namespace std;

double distance(const Point &p1, const Point &p2) {
    return sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2));
}

double heronArea(const Triangle &t) {
    double a = distance(t.A, t.B);
    double b = distance(t.B, t.C);
    double c = distance(t.C, t.A);
    double s = (a + b + c) / 2;
    return sqrt(s * (s - a) * (s - b) * (s - c));
}

double Triangle::area() const {
    return heronArea(*this);
}

bool Triangle::contains(const Point &P) const {
    Triangle T1 = {A, B, P};
    Triangle T2 = {B, C, P};
    Triangle T3 = {C, A, P};

    double S_main = area();
    double S_sum = T1.area() + T2.area() + T3.area();

    return fabs(S_main - S_sum) < 1e-9;
}

bool Triangle::isDegenerate() const {
    return (crossProduct(A, B, C) / 2) < 1e-9;
}

bool Triangle::isOnEdge(const Point &P) const {
    double d1 = crossProduct(A, B, P);
    double d2 = crossProduct(B, C, P);
    double d3 = crossProduct(C, A, P);

    return (fabs(d1) < 1e-9 || fabs(d2) < 1e-9 || fabs(d3) < 1e-9);
}

double crossProduct(const Point &A, const Point &B, const Point &P) {
    return (B.x - A.x) * (P.y - A.y) - (B.y - A.y) * (P.x - A.x);
}

bool Triangle::containsByCross(const Point &P) const {
    double d1 = crossProduct(A, B, P);
    double d2 = crossProduct(B, C, P);
    double d3 = crossProduct(C, A, P);

    bool has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
    bool has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

    return !(has_neg && has_pos);
}

void showMenu() {
    Triangle t;
    cout << "Введіть координати трикутника (x y для кожної вершини):" << endl;
    cout << "A: ";
    cin >> t.A.x >> t.A.y;
    cout << "B: ";
    cin >> t.B.x >> t.B.y;
    cout << "C: ";
    cin >> t.C.x >> t.C.y;

    if (t.isDegenerate()) {
        cout << "Це вироджений трикутник (S=0)." << endl;
    }
    int method;
    cout << "Оберіть метод: " << endl;
    cout << "1 - векторний добуток" << endl;
    cout << "2 - барицентричні координати" << endl;
    cin >> method;

    if (method != 1 && method != 2) {
        cout << "Невірний вибір методу!" << endl;
        return;
    }

    int numPoints;
    cout << "Скільки точок ви хочете перевірити? ";
    cin >> numPoints;

    for (int i = 1; i <= numPoints; ++i) {
        Point p;
        cout << "Введіть координати точки #" << i << ": ";
        cin >> p.x >> p.y;

        if (method == 1) {
            if (t.isOnEdge(p)) {
                cout << "Точка #" << i << " лежить на межі трикутника." << endl;
            } else if (t.containsByCross(p)) {
                cout << "Точка #" << i << " належить трикутнику (векторний добуток)." << endl;
            } else {
                cout << "Точка #" << i << " не належить трикутнику." << endl;
            }
        } else if (method == 2) {
            if (t.isOnEdge(p)) {
                cout << "Точка #" << i << " лежить на межі трикутника." << endl;
            } else if (t.contains(p)) {
                cout << "Точка #" << i << " належить трикутнику (барицентричні координати)." << endl;
            } else {
                cout << "Точка #" << i << " не належить трикутнику." << endl;
            }
        }
    }
}