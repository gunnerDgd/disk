#pragma once
#include <disk/io_system/forward.hpp>

namespace disk {
	template <typename IoType, typename IoTrait>
	class basic_reader
	{
	public:
		typedef std::remove_pointer_t<std::decay_t<IoType>> value_type;
		typedef IoType&										reference ;
		typedef IoType*										pointer   ;

		typedef			 IoTrait							trait_type;
		typedef typename IoTrait::executor					executor  ;
		typedef typename IoTrait::handle					handle	  ;
		typedef typename IoTrait::size_type				    size_type ;

	public:
		basic_reader (executor&, handle&);
		~basic_reader();

	public:
		template <typename ReadType>
		size_type read_from(ReadType&&);
		template <typename ReadType, size_type ReadCount>
		size_type read_from(ReadType(&)[ReadCount]);

	private:
		trait_type __M_reader_trait	  ;
	};
}

template <typename IoType, typename IoTrait>
disk::basic_reader<IoType, IoTrait>::basic_reader(executor& exec, handle& hnd) : __M_reader_trait(exec, hnd) {  }

template <typename IoType, typename IoTrait>
disk::basic_reader<IoType, IoTrait>::~basic_reader()											  			 {  }

template <typename IoType, typename IoTrait>
template <typename ReadType>
disk::basic_reader<IoType, IoTrait>::size_type disk::basic_reader<IoType, IoTrait>::read_from(ReadType&& rd)
{
	return __M_reader_trait.read_from(&rd, sizeof(value_type));
}

template <typename IoType, typename IoTrait>
template <typename ReadType, typename IoTrait::size_type ReadCount>
disk::basic_reader<IoType, IoTrait>::size_type disk::basic_reader<IoType, IoTrait>::read_from(ReadType(&rd_array)[ReadCount])
{
	return __M_reader_trait.read_from(rd_array, ReadCount * sizeof(value_type));
}