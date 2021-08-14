#include <iostream>

template <typename T, typename U>
struct test { };

template <>
struct test<int, float> { static constexpr int value = 1; };

template <typename T>
struct test_wrapper;

template <class T, typename U, typename V>
struct test_wrapper<T<U, V>> { static constexpr int value = T::value; };

int main()
{
    
}