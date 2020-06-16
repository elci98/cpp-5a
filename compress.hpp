#include <iostream>
#include <typeinfo>
#include "range.hpp"
using namespace std;
namespace itertools
{
    template <typename T, typename V>
    class compress
    {
        T container_1;
        V container_2;
        class iterator
        {
            typename T::iterator it1;
            typename T::iterator _end;
            typename V::iterator it2;

        public:
            explicit iterator(typename T::iterator i1, typename T::iterator e, typename V::iterator i2)
                : it1(i1), _end(e), it2(i2){};
            // iterator(const iterator& o) = default;
            bool operator==(const iterator &other)
            {
                return this->it1 == other.it1;
            }
            bool operator!=(const iterator &other)
            {
                return !(this->it1 == other.it1);
            }
            iterator operator++()
            {
                do
                {
                    ++(this->it1);
                    ++(this->it2);
                } while (it1 != _end && !(*it2));
                return *this;
            }
            iterator operator++(int)
            {
                iterator t = *this;
                ++(*this);
                return t;
            }
            auto operator*()
            {
                if (!(*it2))
                {
                    do
                    {
                        ++(this->it1);
                        ++(this->it2);
                    } while (it1 != _end && !(*it2));
                }
                return *(this->it1);
            }
        };

    public:
        explicit compress(T t, V v)
        {
            // typename T::iterator i;
            // typename V::iterator j;
            int s1 = 1, s2 = 1;
            // const type_info &t1 = typeid(bool);
            // const type_info &t2 = typeid(*(v.begin()));
            // cout << "t1: "<< t1.name() << ", t2: "<< t2.name() << endl;
            for (auto i : v)
            {
                s2++;
            }
            for (auto j : t)
            {
                s1++;
            }
            //containers must be same size, container_2 must contain bool variables
            // if (t1 != t2 && s1 != s2)
            //     throw std::invalid_argument("1\n");
            // if (t1 != t2)
            //     throw std::invalid_argument("2\n");
            this->container_1 = t;
            if (s1 != s2)
            {
                std::cout << "s1 length= " << s1 << ", s2 length= " << s2 << std::endl;
                throw std::invalid_argument("invalid argument\n");
            }
            this->container_1 = t;
            this->container_2 = v;
        }
        iterator begin()
        {
            return iterator(container_1.begin(), container_1.end(), container_2.begin());
        }
        iterator end()
        {
            return iterator(container_1.end(), container_1.end(), container_2.end());
        }
    };

}