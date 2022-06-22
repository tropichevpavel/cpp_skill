#pragma once
#include <iostream>

namespace humans {

    enum HumanAge {
        YANG = 10,
        MIDDLE = 40,
        OLD = 80
    };

    struct Human {
        private:
        int age;

        public:
        const char* name;
        const char* sur;
        double height;
        double weight;

        Human() = default;
        Human(const int& age);
        Human(const char*& name);

        ~Human();

        Human(const Human& other);

        Human& operator++();
        Human& operator--();

        Human operator++(int);
        Human operator--(int);

        bool operator<(const Human& h);
        bool operator>(const Human& h);

        friend std::ostream &operator<<(std::ostream &out, const Human& h);

        void setName(const char* &n);

        void setAge(const int& a);
        int getAge() const;
    };
}