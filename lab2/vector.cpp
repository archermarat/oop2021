#include "vector.h"

int show(int i, std::ostream &out) {
    std::cout << i << ",";
    return 0;
}

namespace lab3 {
    Vector::Vector(int num) : my_size(1) {
        my_capacity = 3;
        vec = new int[my_capacity];
        vec[0] = num;
    }

    //конструктор копирования
    Vector::Vector(const Vector &a)
    :vec(nullptr), my_size(a.my_size), my_capacity(a.my_capacity)
    {
        vec = new int[a.my_capacity];
        memcpy(vec, a.vec, my_size * sizeof(int));
        std::cout << "\ncopy constructor" << std::endl;
    }

    //конструктор перемещения
    Vector::Vector(Vector &&a) : vec(a.vec), my_size(a.my_size), my_capacity(a.my_capacity) {
        a.vec = nullptr;
        std::cout << "\nmove constructor" << std::endl;
    }

    Vector::Vector(int *mas, size_t size) {
        my_size = size;
        my_capacity = size + 3;
        try {
            vec = new int[my_capacity];
        }
        catch (std::bad_alloc &ba) {
            throw std::out_of_range("too many elements in vector");
        }
        for (size_t i = 0; i < my_size; i++) {
            vec[i] = mas[i];
        }
    }

    int Vector::getElem(size_t i) const {
        if (i >= my_size || i < 0) {
            throw std::logic_error("element doesn't exist");
        }
        return vec[i];
    }

    void Vector::reserve(size_t capacity) {
        if (vec == nullptr) {
            my_size = 0;
            my_capacity = 0;
        }
        int *Newvec;
        try {
            Newvec = new int[capacity];
        }
        catch (std::bad_alloc &ba) {
            throw std::out_of_range("too many elements in vector");
        }
        unsigned int l_Size = capacity < my_size ? capacity : my_size;

        for (unsigned int i = 0; i < l_Size; i++)
            Newvec[i] = vec[i];

        my_capacity = capacity;
        delete[] vec;
        vec = Newvec;
    }

    size_t Vector::push(int elem) {
        if (my_size >= my_capacity)
            reserve(my_capacity + 3);
        vec[my_size++] = elem;
        return my_size;
    }

    Vector &Vector::sort() {
        if (my_size < 2) {
            throw std::logic_error("not enough elements to sort");
        }
        std::sort(vec, vec + my_size, std::greater<>());
        return *this;
    }

    int Vector::findMax() const {
        if (my_size == 0) {
            throw std::logic_error("vector is empty");
        }
        int max = vec[0];
        for (size_t i = 1; i < my_size; ++i) {
            if (max < vec[i])
                max = vec[i];
        }
        return max;
    }

    void Vector::task(int num) const {
        Vector *a;
        if (num <= 0) {
            throw std::logic_error("incorrect number");
        }

        try {
            a = new Vector[num];
        }
        catch (std::bad_alloc &ba) {
            throw std::out_of_range("too many rows in matrix");
            // ?
        }

        for (size_t i = 0; i < my_size; i++) {
            int elem = getElem(i);
            a[abs(elem) % num].push(elem);
        }
        for (size_t i = 0; i < num; i++) {
            if (a[i].my_size != 0) std::cout << a[i];
        }
        delete[] a;
    }

    Vector &Vector::operator=(const Vector &a) { //копирование
        if (&a == this)
            return *this;
        std::cout << "\ncopy operator" << std::endl;
        destroy();
        my_size = a.my_size;
        my_capacity = a.my_capacity;
        vec = new int[my_size];
        memcpy(vec, a.vec, my_size * sizeof(int));
        return *this;
    }

    Vector &Vector::operator=(Vector &&a)  noexcept { //перемещение
        if (&a == this)
            return *this;
        std::cout << "\nmove operator" << std::endl;
        destroy();
        my_size = a.my_size;
        my_capacity = a.my_capacity;
//        try {
//            vec = new int[my_size];
//        }
//        catch (std::bad_alloc &ba) {
//            throw std::out_of_range("too many elements in vector");
//        }
//        for (unsigned int i = 0; i < my_size; i++)
//            vec[i] = a.vec[i];
        vec = a.vec;
        a.vec = nullptr;
        return *this;
    }

    Vector &Vector::operator+=(const Vector &a) {
        if(my_size < a.my_size) {
            for(size_t i = 0; i < my_size; ++i) {
                vec[i] += a.vec[i];
            }
            for(size_t i = my_size; i < a.my_size; ++i) {
                push(a.vec[i]);
            }
        } else {
            for(size_t i = 0; i < a.my_size; ++i) {
                vec[i] += a.vec[i];
            }
        }
        return *this;
    }

    Vector operator+(const Vector &a, const Vector &b) {
//        size_t size1, size2, k;
//        if (a.getSize() <= b.getSize()) {
//            size1 = a.getSize();
//            size2 = b.getSize();
//            k = 0;
//        } else {
//            size1 = b.getSize();
//            size2 = a.getSize();
//            k = 1;
//        }
//        int *mas = new int[a.my_size];
//        for (size_t i = 0; i < size1; ++i) {
//            mas[i] = a.getElem(i) + b.getElem(i);
//        }
//        for (size_t i = size1; i < size2; ++i) {
//            if (k == 0) mas[i] = b.getElem(i);
//            else mas[i] = a.getElem(i);
//        }
//        Vector c(mas, size2);
//        delete[] mas;
        std::cout << "First vector is: " << a << std::endl;
        std::cout << "Second vector is: " << b << std::endl;
        Vector c;
        c += a;
        c += b;
        std::cout << "Result vec is : " << c << std::endl;
        return c;
    }

    int &Vector::operator[](const size_t index) {
        if (index > my_size || index < 0)
            throw std::logic_error("incorrect index");
        return vec[index];
    }

    const int &Vector::operator[](const size_t index) const {
        if (index > my_size || index < 0)
            throw std::logic_error("incorrect index");
        return vec[index];
    }

    std::ostream &operator<<(std::ostream &out, const Vector &a) {
        if (a.my_size == 0) {
            out << "Vector is empty";
        } else {
            out << "\nCurrent Size = " << a.my_size << "\n";
            out << "{";
            std::for_each(a.vec, a.vec + a.my_size, show); //лямбда захват
        }
        out << "}" << std::endl;
        return out;
    }

    std::istream &operator>>(std::istream &in, Vector &a) {
        size_t size;
        in >> size;
        in.clear();
        in.ignore();
        int fl = in.good();
//        if (size > a.my_capacity && fl) {
//            a.reserve(a.my_capacity + 3);
//        }
//        for (size_t i = 0; i < size; ++i) {
//            in >> a[a.my_size++];
//        }
        if(fl && size > 0) {
            for(size_t i = 0; i < size; ++i) {
                int num;
                in >> num;
                in.clear();
                in.ignore();
                int fl2 = in.good();
                if(fl2) {
                    a.push(num);
                }
                else throw std::logic_error("incorrect num");
            }
        } else throw std::logic_error("incorrect size");
        return in;
    }

}