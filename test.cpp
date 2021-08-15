#include <disk/file/file>
#include <iostream>

template <typename T>
concept bool is_readable = T::read;

template <typename T>
void test_file(T& a) requires is_readable<T>;
{
    std::cout << "Read\n";
}

template <typename T>
void test_file(T& a)
{
    std::cout << "Not Read\n";
}

int main()
{
    file::file a("test.txt", file::mode::create | file::mode::all);
    int b;

    test_file(a);
    test_file(b);
}