#include <iostream>
#include "astroid.h"

namespace Lab {

    Astroid::Astroid(double rad) {
        if (rad < 0)
            throw std::logic_error("invalid radius");
        r = rad;
    }

    Astroid &Astroid::setR(double r0) {
        if (r0 < 0)
            throw std::logic_error("invalid radius");
        r = r0;
        return *this;
    }

    double Astroid::init_angle(double t) {
        if (t < 0 || t > M_PI / 2.0)
            throw std::logic_error("invalid angle");
        return t;
    }

    double Astroid::y_of_x(double x) const {
        double y0 = pow(4.0 * r, 2.0 / 3.0) - pow(x, 2.0 / 3.0);
        if (y0 < 0)
            throw std::logic_error("illegal argument x");
        return pow(y0, 3.0 / 2.0);
    }
}

