#ifndef LAB3A_VECTOR_H
#define LAB3A_VECTOR_H

#include <iostream>
#include "cmake-build-debug/_deps/googletest-src/googletest/include/gtest/gtest_prod.h"


namespace lab3 {

    class Vector {
    private:
        void destroy() {
            if(vec) {
                delete[] vec;
                my_size = 0;
                my_capacity = 0;
            }
        }
        size_t my_size; //количество элементов вектора
        size_t my_capacity; //выделенная память / sizeof(int) (>= my_size)
        int *vec;
    public:
        //конструкторы
        Vector() { my_size = 0; my_capacity = 3; vec = new int[my_capacity]; };
        Vector(int num);
        Vector(const Vector& a); //конструктор копирования
        Vector(Vector&& a); //конструктор перемещения
        Vector(int* mas, size_t size);
        ~Vector() { destroy(); };
        //геттеры
        size_t getSize() const { return my_size; };
        size_t getCapacity() const { return my_capacity; };
        int getElem(size_t i) const;
        //другие методы
        void reserve(size_t capacity);
        size_t push(int); //включение нового элемента
        Vector& sort(); //упорядочение вектора по возрастанию
        int findMax() const; //нахождение максимального элемента в векторе
        //перегрузка операторов
        int& operator[](size_t index); //перегрузка оператора индекса
        const int& operator[](size_t index) const; //перегрузка оператора индекса для константных
        Vector& operator=(const Vector &a);
        Vector& operator=(Vector &&a) noexcept;
        Vector& operator+=(const Vector &a);
        friend std::ostream& operator<<(std::ostream &out, const Vector &a); //перегрузка оператора вывода
        friend std::istream& operator>>(std::istream &in, Vector &a);//перегрузка оператора ввода
        friend Vector operator+(const Vector &a, const Vector &b);

        //написать метод, принимающий целое положительное число Н и формирующий массив векторов размера Н,
        //где каждый массив содержит элементы с одинаковыми остатком от деления на Н
        void task(int num) const;


    };




}

#endif //LAB3A_VECTOR_H
