#ifndef LAB2_ASTROID_H
#define LAB2_ASTROID_H

#include <iostream>
#include <cmath>
#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"

namespace Lab {
    class Astroid {
    private:
        double r; //радиус окружности
    public:
        Astroid(double rad = 1);
        //сеттеры
        Astroid &setR(double r0);
        //геттеры
        double getR() const {return r;}
        //другие методы
        double area() const {return 3.0 / 8.0 * M_PI * 4 * 4 *r * r;} //площадь ограниченная кривой
        double curve_len() const {return 6.0 * 4 * r;} //длина кривой
        static double init_angle(double t) ; //ввод угла
        double curve_rad(double t) const {return 3.0 / 2.0 * 4 * 4 * r * sin(2.0 * t);} //радиус кривизны
        double arc_len(double t) const {return 3.0 / 2.0 * 4 * 4 * r * sin(t) * sin(t);} //длина дуги от 0 до t
        double x_of_t(double t) const {return r * 4 * cos(t) * cos(t) * cos(t);} //вернуть x(t)
        double y_of_t(double t) const {return r * 4 * sin(t) * sin(t) * sin(t);} //вернуть y(t)
        double y_of_x(double x) const; //вернуть y(x)
    };
}

#endif //LAB2_ASTROID_H
