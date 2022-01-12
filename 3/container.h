#ifndef LAB4_CONTAINER_H
#define LAB4_CONTAINER_H

#include <iostream>
#include <list>
#include <algorithm>
#include <initializer_list>
#include <stack>


namespace container {

    /*!
	\brief Структура описателя узла дерева
	\date Декабрь 2021 года

     \tparam TKey Первый параметр в паре, ключ.
     \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
     \param element Узел дерева, пара элементов, 1й - ключ, 2й - информация.
     \param height Высота поддерева узла.
     \param left Указатель на вершину левого поддерева.
     \param right Указатель на вершину правого поддерева.

	Структура, описывающая узел AVL дерева
*/
    template<class TKey, class TElement>
    struct Node {
        std::pair<TKey, TElement> element;
        int height;
        Node *left;
        Node *right;

        /*!
     Конструктор структуры по умолчанию.
    */
        Node() {
            left = nullptr;
            right = nullptr;
            height = 0;
        }

        /*!
     Конструктор структуры от ключа и информации.
*/
        Node(TKey key, TElement element) : element(key, element) {
            left = nullptr;
            right = nullptr;
            height = 0;
        }
    };

    /*!
\brief Класс, описывающий AVL дерево
\date Декабрь 2021 года

 \tparam TKey Первый параметр в паре, ключ.
 \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
 \param root Указатель на корень дерева.

Структура, описывающая узел AVL дерева
*/
    template<class TKey, class TElement>
    class AVLTree {
    public:
        typedef Node<TKey, TElement> Node;
        Node *root;

        /*!
Конструктор по умолчанию.
*/
        AVLTree() { root = nullptr; };
        /*!
Копирующий конструктор.
*/
        AVLTree(AVLTree<TKey, TElement> const &that) {
            if (that.root == nullptr) {
                this->root = nullptr;
                return;
            }
            copy(this->root, that.root);
        }
        /*!
Перемещающий конструктор.
*/
        AVLTree(AVLTree<TKey, TElement> &&that):root(that.root)  {
            that.root = nullptr;
        }
        /*!
Перегруженный оператор присваивания копированием
*/
        AVLTree<TKey, TElement>& operator=(AVLTree<TKey, TElement> const& that) {
            if (&that == this)
                return *this;
            AVLTree<TKey, TElement> tmp = AVLTree<TKey, TElement>(that);
            std::swap(this->root, tmp.root);
            return *this;
        }
        /*!
Перегруженный оператор присваивания перемещением
*/
        AVLTree<TKey, TElement>& operator=(AVLTree<TKey, TElement> &&that) {
            if (&that == this)
                return *this;
            this->root = that.root;
            that.root = nullptr;
            return *this;
        }
        /*!
Деструктор.
*/
        ~AVLTree() { makeEmpty(root); };

    private:
        /*!
Копирование
*/
        void copy(Node *&node1, Node const *const &node2) {
            if (node2 == nullptr) {
                node1 = nullptr;
                return;
            }

            node1 = new Node;
            node1->element.first = node2->element.first;
            node1->element.second = node2->element.second;
            node1->height = node2->height;

            copy(node1->left, node2->left);
            copy(node1->right, node2->right);
        }
//        /*!
//Перемещение
//*/
//        void move(Node *&node1, Node *&&node2) {
//            if (node2 == nullptr) {
//                node1 = nullptr;
//                return;
//            }
//
//            node1->element.first = node2->element.first;
//            node1->element.second = node2->element.second;
//            node1->height = node2->height;
//            node2 = nullptr;
//
//            move(node1->left, node2->left);
//            move(node1->right, node2->right);
//        }
        /*!
        Добавляет вершину в дерево
        \param elem Вставляемый элемент.
        \param node Указатель на поддерево, куда производится вставка.
        \return Указатель на вставленный узел
        */
        Node *insert(std::pair<TKey, TElement> elem, Node *node) {
            if (node == NULL) {
                node = new Node(elem.first, elem.second);
            } else if (elem.first < node->element.first) {
                node->left = insert(elem, node->left);
                if (height(node->left) - height(node->right) == 2) {
                    if (elem.first < node->left->element.first)
                        node = singleRightRotate(node);
                    else
                        node = doubleRightRotate(node);
                }
            } else if (elem.first > node->element.first) {
                node->right = insert(elem, node->right);
                if (height(node->right) - height(node->left) == 2) {
                    if (elem.first > node->right->element.first)
                        node = singleLeftRotate(node);
                    else
                        node = doubleLeftRotate(node);
                }
            } else if (elem.first == node->element.first) {
                throw std::logic_error("element with that key is already exists");
            }
            node->height = std::max(height(node->left), height(node->right)) + 1;
            return node;
        }

        /*!
Малое правое вращение
\param node Вершина поддерева
\return Указатель на новую вершину поддерева
*/
        Node *singleRightRotate(Node *&node) {
            Node *tmp = node->left;
            node->left = tmp->right;
            tmp->right = node;
            node->height = std::max(height(node->left), height(node->right)) + 1;
            tmp->height = std::max(height(tmp->left), node->height) + 1;
            return tmp;
        }

        /*!
Малое левое вращение
\param node Вершина поддерева
\return Указатель на новую вершину поддерева
*/
        Node *singleLeftRotate(Node *&node) {
            Node *tmp = node->right;
            node->right = tmp->left;
            tmp->left = node;
            node->height = std::max(height(node->left), height(node->right)) + 1;
            tmp->height = std::max(height(node->right), node->height) + 1;
            return tmp;
        }

        /*!
Большое левое вращение
\param node Вершина поддерева
\return Указатель на новую вершину поддерева
*/
        Node *doubleLeftRotate(Node *&node) {
            node->right = singleRightRotate(node->right);
            return singleLeftRotate(node);
        }

        /*!
Большое правое вращение
\param node Вершина поддерева
\return Указатель на новую вершину поддерева
*/
        Node *doubleRightRotate(Node *&node) {
            node->left = singleLeftRotate(node->left);
            return singleRightRotate(node);
        }

        /*!
Удаление вершины
\param elem Удаляемый элемент
\param node Указатель на поддерево, где проходит поиск удаляемого элемента
\return Указатель на новую вершину поддерева
*/
        Node *remove(std::pair<TKey, TElement> elem, Node *node) {
            Node *temp;

            if (node == NULL)
                return NULL;

            else if (elem.first < node->element.first)
                node->left = remove(elem, node->left);
            else if (elem.first > node->element.first)
                node->right = remove(elem, node->right);

            else if (node->left && node->right) {
                temp = findMin(node->right);
                node->element = temp->element;
                node->right = remove(node->element, node->right);
            } else {
                temp = node;
                if (node->left == NULL)
                    node = node->right;
                else if (node->right == NULL)
                    node = node->left;
                delete temp;
            }
            if (node == NULL)
                return node;

            node->height = std::max(height(node->left), height(node->right)) + 1;

            // Если дерево не сбалансировано
            if (height(node->left) - height(node->right) == 2) {
                if (height(node->left->left) - height(node->left->right) == 1)
                    return singleLeftRotate(node);
                else
                    return doubleLeftRotate(node);
            }
            else if (height(node->right) - height(node->left) == 2) {
                if (height(node->right->right) - height(node->right->left) == 1)
                    return singleRightRotate(node);
                else
                    return doubleRightRotate(node);
            }
            return node;
        }


    public:

        /*!
Публичная функция вставки
\param elem Добавляемый элемент
*/
        void insert(std::pair<TKey, TElement> elem) {
            root = insert(elem, root);
        }

        /*!
Публичная функция удаления
\param elem Удаляемый элемент
*/
        void remove(std::pair<TKey, TElement> elem) {
            root = remove(elem, root);
        }

        /*!
Нахождение наименьшего элемента дерева
\param node Указатель на поддерево, где проходит поиск элемента
\return Указатель найденный узел
*/
        Node *findMin(Node *node) const {
            if (node == NULL)
                return NULL;
            else if (node->left == NULL)
                return node;
            else
                return findMin(node->left);
        }

        /*!
Нахождение наибольшего элемента дерева
\param node Указатель на поддерево, где проходит поиск элемента
\return Указатель найденный узел
*/
        Node *findMax(Node *node) const {
            if (node == NULL)
                return NULL;
            else if (node->right == NULL)
                return node;
            else
                return findMax(node->right);
        }

        /*!
Поиск элемента по заданному ключу
\param node Указатель на поддерево, где проходит поиск элемента
\param key Ключ, по которому происходит поиск элемента
\return Указатель найденный узел
*/
        Node *find(Node *node, TKey key) const {
            if (node == NULL)
                return nullptr;
            else if (node->element.first == key) {
                return node;
            } else if (key < node->element.first)
                return find(node->left, key);
            else if (key > node->element.first)
                return find(node->right, key);
        }

        /*!
Вывод элементов дерева во возрастанию значений ключа
\param node Указатель на выводимое поддерево
\param out Выходной поток
*/
        void inorder(Node *node, std::ostream &cout = std::cout) {
            if (node == NULL)
                return;
            inorder(node->left, cout);
            cout << node->element.first << ". " << node->element.second << " ";
            inorder(node->right, cout);
        }

        Node *GetRoot() const {
            return root;
        }
        /*!
Высота поддерева
\param node Указатель на вершину поддерева
\return Высота поддерева
*/
        int height(Node *node) {
            return (node == NULL ? -1 : node->height);
        }

        /*!
Удаление дерева
\param node Указатель на вершину удаляемого поддерева
*/
        void makeEmpty(Node *a) {
            if (a == NULL)
                return;
            makeEmpty(a->left);
            makeEmpty(a->right);
            delete a;
        }
    };


    template<class TKey, class TElement>
    class const_iterator {
    private:
        Node<TKey, TElement> *ptr;
        std::stack<Node<TKey, TElement> *> parents;


        Node<TKey, TElement> *FindMin(Node<TKey, TElement> *node) {
            if (node == nullptr) {
                return nullptr;
            } else if (node->left == nullptr) {
                return node;
            } else {
                parents.push(node);
                return FindMin(node->left);
            }
        }

        Node<TKey, TElement> *FindNext(Node<TKey, TElement> *node) {
            if (node->right != nullptr) {
                parents.push(node);
                return FindMin(node->right);
            }

            Node<TKey, TElement>* parent = parents.top();
            parents.pop();
            while (parent && node == parent->right) {
                node = parent;
                parent = parents.top();
                parents.pop();
            }
            return parent;
        }

    public:
        const_iterator(Node<TKey, TElement> *a = nullptr) {
            ptr = FindMin(a);
        };

        const_iterator(const const_iterator<TKey, TElement> &a) : ptr(a.ptr), parents(a.parents) {};

        const_iterator<TKey, TElement> operator++(int) { //постфиксный инкремент
            const_iterator<TKey, TElement> tmp(*this);
            ++(*this);
            return tmp;
        };

        const_iterator<TKey, TElement> &operator++() { //префиксный инкремент
            Node<TKey, TElement> *tmp = FindNext(ptr);
            if (tmp == nullptr) ptr = nullptr;
            else ptr = tmp;
            return *this;
        };

        std::pair<TKey, TElement> *operator->() const { return ptr->element; };

        bool operator==(const const_iterator<TKey, TElement> &a) const { return ptr == a.ptr; };

        bool operator!=(const const_iterator<TKey, TElement> &a) const { return ptr != a.ptr; };

        const std::pair<TKey, TElement> &operator*() const { return ptr->element; };
    private:
    };

    /*!
	\brief Шаблон класса итератора контейнера
	\date Декабрь 2021 года

     \tparam TKey Первый параметр в паре, ключ.
     \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
     \param ptr Указатель на узел дерева, соответствующий значению итератора.
     \param parents Стек родительских элементов узла дерева, соответствующего значению итератора.

	Итератор для работы шаблона контейнера с AVL деревом.
*/
    template<class TKey, class TElement>
    class iterator {
    private:
        friend const_iterator<TKey, TElement>;
        Node<TKey, TElement> *ptr;
        std::stack<Node<TKey, TElement> *> parents;

        /*!
\brief Поиск минимального элемента поддерева
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
\param node Указатель на вершину поддерева
\return Указатель на минимальный элемент

В процессе поиска минимального элемента поддерева, в стек заносятся все родительские узлы этого элемента
*/
        Node<TKey, TElement> *FindMin(Node<TKey, TElement> *node) {
            if (node == nullptr) {
                return nullptr;
            } else if (node->left == nullptr) {
                return node;
            } else {
                parents.push(node);
                return FindMin(node->left);
            }
        }

        /*!
Поиск следующего по значению ключа элемента дерева
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
\param node Указатель на элемент
\return Указатель на найденный элемент

*/
        Node<TKey, TElement> *FindNext(Node<TKey, TElement> *node) {
            if (node->right != nullptr) {
                parents.push(node);
                return FindMin(node->right);
            }
            //if(parents.empty()) return nullptr;

            Node<TKey, TElement> *parent = parents.top();
            parents.pop();
            while (parent && node == parent->right) {
                node = parent;
                parent = parents.top();
                parents.pop();
            }
            return parent;
        }

    public:
        /*!
            Конструктор класса от узла дерева.
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \param a Указатель на узел дерева
*/
        iterator(Node<TKey, TElement> *node = nullptr) {
            parents.push(nullptr);
            ptr = FindMin(node);
        };

        /*!
    Перегруженный оператор постфиксного инкремента
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
*/
        iterator<TKey, TElement> operator++(int) {
            iterator<TKey, TElement> tmp(*this);
            ++(*this);
            return tmp;
        };

        /*!
    Перегруженный оператор префиксного инкремента
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
*/
        iterator<TKey, TElement> &operator++() {
            ptr = FindNext(ptr);
            return *this;
        };

        /*!
Перегруженный оператор равенства
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
         \param a Сравниваемый элемент
         \return True, если равно. False, если неравно
*/
        bool operator==(const iterator<TKey, TElement> &a) const { return ptr == a.ptr; };

        /*!
Перегруженный оператор неравенства
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
 \param a Сравниваемый элемент
 \return True, если неравно. False, если авно
*/
        bool operator!=(const iterator<TKey, TElement> &a) const { return ptr != a.ptr; };

        /*!
Перегруженный оператор разыменовывания
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
\return Пара значений, 1ое - ключ, 2ое - информация.
*/
        const std::pair<TKey, TElement> &operator*() const { return ptr->element; };

        /*!
Перегруженный оператор разыменовывания константного итератора
\tparam TKey Первый параметр в паре, ключ.
\tparam TElement Второй параметр в паре, информация, соответствующая ключу.
\return Пара значений, 1ое - ключ, 2ое - информация.
*/
        std::pair<const TKey, TElement> &
        operator*() { return reinterpret_cast<std::pair<const TKey, TElement> &>(ptr->element); };
    };

    /*!
	\brief Шаблон класса контейнера
	\date Декабрь 2021 года

     \tparam TKey Первый параметр в паре, ключ.
     \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
     \param tree_ AVL дерево

	Итератор для работы шаблона контейнера с AVL деревом.
*/
    template<class TKey, class TElement>
    class MyContainer {
    private:
        AVLTree<TKey, TElement> tree_;
    public:
        using Iterator = iterator<TKey, TElement>;
        using constIterator = const_iterator<TKey, TElement>;
        /*!
        Конструктор по умолчанию
        */
        MyContainer() = default;

        /*!
        Деструктор по умолчанию
        */
        ~MyContainer() = default;

        /*!
        Поиск элемента контейнера по ключу
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \param key Ключ.
        \return Итератор на найденный элемент.
*/
        iterator<TKey, TElement> find(const TKey &key) const {
            Node<TKey, TElement> *tmp = tree_.find(tree_.root, key);
            if (tmp == nullptr) {
                return end();
            } else {
                return iterator<TKey, TElement>(tmp);
            }
        }
        /*!
        Вставка элемента
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \param key Элемент.
        \return Итератор на вставленный элемент.
*/
        iterator<TKey, TElement> emplace(std::pair<TKey, TElement> elem) {
            tree_.insert(elem);
            return iterator<TKey, TElement>(tree_.find(tree_.root, elem.first));
        }

                /*!
        Удаление элемента контейнера.
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \param a Итератор на удаляемый элемент.
        */
        void erase(iterator<TKey, TElement> a) {
            tree_.remove(*a);
        };

        /*!
        Нахождение итератора на начало контейнера
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \return Итератор на первый элемент.
*/
        iterator<TKey, TElement> begin() const {
            return Iterator(tree_.root);
        };

        /*!
        Нахождение итератора на конец контейнера
        \tparam TKey Первый параметр в паре, ключ.
        \tparam TElement Второй параметр в паре, информация, соответствующая ключу.
        \return Итератор на элемент, следующий за последним.
*/
        iterator<TKey, TElement> end() const {
            return iterator<TKey, TElement>(nullptr);
        };

        /*!
        Перегруженный оператор доступа по ключу
        \param key Ключ.
        \return Информация по ключу.
*/
        TElement &operator[](const TKey &key) { return tree_.find(tree_.root, key)->element.second; };

        /*!
        Перегруженный оператор доступа по ключу (const)
        \param key Ключ.
        \return Информация по ключу.
*/
        const TElement &operator[](const TKey &key) const { return tree_.find(tree_.root, key)->element.second; };
    };

}
#endif