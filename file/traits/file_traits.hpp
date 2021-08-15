#include <disk/file/file.hpp>

namespace traits {
    template <typename T>
    struct is_file                      { static constexpr bool value = false; };

    template <typename T, typename U, typename V>
    struct is_file<file::file_base<T, U, V>> { static constexpr bool value = true ; };
}