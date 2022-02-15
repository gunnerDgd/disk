#pragma once
#include <disk/io_system/forward.hpp>

namespace disk {
	template <typename IoType, typename IoTrait>
	class basic_writer
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
		basic_writer (executor&, handle&);
		~basic_writer();

	public:
		template <typename WriteType>
		size_type write_to(WriteType&&);
		template <typename WriteType, size_type WriteCount>
		size_type write_to(WriteType(&)[WriteCount]);

	private:
		trait_type __M_writer_trait   ;
	};
}

template <typename IoType, typename IoTrait>
disk::basic_writer<IoType, IoTrait>::basic_writer(executor& exec, handle& hnd) : __M_writer_trait(exec, hnd) {  }

template <typename IoType, typename IoTrait>
disk::basic_writer<IoType, IoTrait>::~basic_writer()														 {  }

template <typename IoType, typename IoTrait>
template <typename WriteType>
disk::basic_writer<IoType, IoTrait>::size_type disk::basic_writer<IoType, IoTrait>::write_to(WriteType&& wr)
{
	return __M_writer_trait.write_to(&wr, sizeof(value_type));
}

template <typename IoType, typename IoTrait>
template <typename WriteType, typename IoTrait::size_type WriteCount>
disk::basic_writer<IoType, IoTrait>::size_type disk::basic_writer<IoType, IoTrait>::write_to(WriteType(&wr_array)[WriteCount])
{
	return __M_writer_trait.write_to(wr_array, WriteCount * sizeof(value_type));
}