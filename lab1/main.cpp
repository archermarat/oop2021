#include <iostream>
#include "astroid.h"


//Вариант 18. Астроида
//Разработать класс, определяющий кривую – астроиду.
//Астроида – плоская кривая, описываемая точкой окружности радиуса r, катящейся по внутренней стороне окружности радиуса
// R = 4r.
// 1) Определить состояние класса.
// 2) Разработать необходимые конструкторы и методы получения и изменения параметров, определяющих кривую.
// 3) Вернуть длину дуги от точки 0 до заданного угла t.
// 4) Вернуть длину всей кривой.
// 5) Вернуть радиус кривизны в зависимости от заданного угла t.
// 6) Вернуть площадь, ограниченную кривой.
// 7) Вернуть значения координат x и y в зависимости от заданного параметра t.
// 8) Вернуть значение координаты y в декартовой системе координат в зависимости от заданного значения x.

//ищи другие файлы в папке Google_tests

using namespace Lab;

int main() {
    Astroid r;
    double rad, angle = -1;
    int fl1 = 1;
    while (fl1) {
        std::cout << "area: " << r.area() << std::endl;
        std::cout << "length of curve: " << r.curve_len() << std::endl;

        int fl2 = 1;
        while (fl2) {
            std::cout << "Enter angle for calculate values or press ctrl+Z to quit:" <<
                      std::endl;
            std::cin >> angle;
            fl2 = std::cin.good();
            if (!fl2)
                continue;
            try {
                Lab::Astroid::init_angle(angle);
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        }

        std::cout << "radius of curve: " << r.curve_rad(angle) << std::endl;
        std::cout << "arc length: " << r.arc_len(angle) << std::endl;
        std::cout << "x(t): " << r.x_of_t(angle) << std::endl;
        std::cout << "y(t): " << r.y_of_t(angle) << std::endl;
        int fl3 = 1;
        while (fl3) {
            std::cout << "Enter x for calculate y(t) or press ctrl+Z to quit:" <<
                      std::endl;
            double x;
            std::cin >> x;
            fl3 = std::cin.good();
            if (!fl3)
                continue;
            try {
                double y = r.y_of_x(x);
                std::cout << "y = " << y << std::endl;
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        }
        std::cin.clear();
        std::cout << "Enter radius and angle to continue or press ctrl+Z to quit:" << std::endl;
        std::cin >> rad >> angle;
        if (std::cin.good()) {
            try {
                r.setR(rad);
                Lab::Astroid::init_angle(angle);
            }
            catch (std::exception &ex) {
                std::cout << ex.what() << std::endl;
            }
        } else
            fl1 = 0;
    }
    return 0;
}

