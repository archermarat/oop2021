#include <iostream>
#include "vector.h"
#include <cmath>

/*
1. Разработать класс "вектор целых чисел" в соответствии со следующим заданием:
Состояние класса -
Вектор включает в себя элементы типа int и определяется размером (количество элементов в векторе)
 и значениями своих элементов, например: вектор из 6 элементов {12, 8, 5, -3, 11, 5}.
 Память под вектор выделяется статически, во время компиляции, и задается массивом фиксированного
 предельного значения (например, максимальный размер вектора 100 элементов).
Протокол класса -
Определяет возможности создания и инициализации экземпляров класса и правила использования их (методы класса).
Предусмотреть следующие возможности:
· пустой конструктор для инициализации экземпляров и массивов экземпляров класса по умолчанию;
· создание экземпляров класса с инициализацией единственным элементом вектора;
· создание экземпляров класса с инициализацией размером и массивом значений элементов вектора;
· ввод экземпляров класса из входного потока и вывод их значений в выходной поток;
· выполнение операции сложения двух векторов (реализуется как покомпонентное сложение двух векторов);
· выделение части вектора указанной длины, начиная с элемента, заданного его порядковым номером в векторе;
· выполнение операции включения в вектор нового элемента;
· упорядочение вектора по возрастанию;
· нахождение максимального элемента в векторе.
*/

using namespace lab3;

Vector selectPart(Vector &a, size_t len, size_t num) {
    if (len + num > a.getSize())
        throw std::logic_error("incorrect range");
    int *mas;
    int k = 0;
    mas = new int[len];
    for (size_t i = num; i < num + len; ++i) {
        mas[k++] = a.getElem(i);
    }
    Vector b(mas, len);
    delete[]mas;
    return b;
}



int main() {
    try {

        int mas[] = {5, 3, 7, 6, 1};
        size_t size = sizeof(mas) / sizeof(int);
        Vector a, b(6), c(mas, size), g(c), d, e, f;
        std::cout << "Vector <g> (copy of <c>) : ";
        std::cout << g;
        std::cout << "1. Push into vector\n";
        try {
            for (size_t i = 0; i < 14; ++i)
                a.push((i + 1) * pow(-1, i));
        }
        catch (const std::exception &msg) {
            std::cout << msg.what() << std::endl;
        }
        std::cout << "Vector <a> : ";
        std::cout << a;
        std::cout << "2. Max element is : " << a.findMax() << std::endl;
        a.sort();
        std::cout << "3. Sorted vector <a> : ";
        std::cout << a;
        std::cout << "Vector <b> : ";
        std::cout << b;
        std::cout << "Vector <c> : ";
        std::cout << c;
        std::cout << "4." << std::endl;
        d = a + b;
        std::cout << d;
        int len = 4, num = 2;
        std::cout << "5. Part of a+b vector from " << num + 1 << " to " << len + num << " elements: ";
        e = selectPart(d, len, num);
        std::cout << e;
        std::cout << "6. Enter new vector:\n";
        std::cin >> f;
        std::cout << f;
        std::cout << "7. New task:\n";
        a.task(4);
    }
    catch (const std::exception &msg) {
        std::cout << msg.what() << std::endl;
    }

    return 0;
}
