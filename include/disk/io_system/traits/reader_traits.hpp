#pragma once
#include <execution/branch.hpp>
#include <execution/executor.hpp>

#include <disk/handle/file/file_nonblock.hpp>

namespace disk {
	template <typename ReadType, typename ReadQueueing>
	class reader_traits
	{
	public:
		typedef std::size_t									  size_type ;
		typedef std::remove_pointer_t<std::decay_t<ReadType>> value_type;
		typedef value_type*									  pointer   ;
		typedef value_type&									  reference ;

		typedef execution::executor							  executor  ;
		typedef handle::file_nonblock						  handle    ;

	public: 
		reader_traits (handle&);
		~reader_traits();

	public:
		size_type read_from(pointer, size_type);

	private:
		handle& __M_rtrait_handle;
	};
}

template <typename ReadType, typename ReadQueueing>
disk::reader_traits<ReadType, ReadQueueing>::reader_traits(handle& hnd) : __M_rtrait_handle(hnd) {  }

template <typename ReadType, typename ReadQueueing>
disk::reader_traits<ReadType, ReadQueueing>::~reader_traits()									 {  }

