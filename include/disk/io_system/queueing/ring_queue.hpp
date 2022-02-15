#pragma once
#include <type_traits>

namespace disk::queueing {
	template <typename QueueType>
	class ring_queue
	{
	public:
		typedef std::remove_pointer_t<std::decay_t<QueueType>> value    ;
		typedef value*										   pointer  ;
		typedef value&										   reference;
		
	public:
		class chain;
	};

	template <typename QueueType>
	class ring_queue<QueueType>::chain
	{
	public:
		
	};
}