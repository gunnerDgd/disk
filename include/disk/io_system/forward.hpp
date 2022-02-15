#pragma once
#include <type_traits>

namespace disk {
	template <typename IoType, typename IoTrait>
	class basic_reader;

	template <typename IoType, typename IoTrait>
	class basic_writer;
}