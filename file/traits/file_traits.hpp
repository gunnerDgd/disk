#include "file.hpp"

namespace traits {
    template <typename T>
    struct is_file                      { static constexpr bool value = false; };

    template <typename T, typename U, typename V>
    struct is_file<file::file<T, U, V>> { static constexpr bool value = true ; };

    template <typename T>
    struct file_data_type                      {};

    template <typename T, typename U, typename V>
    struct file_data_type<file::file<T, U, V>> { using type = T; }
}