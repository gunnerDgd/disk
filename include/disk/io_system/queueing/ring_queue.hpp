#pragma once
#include <type_traits>
#include <atomic>

#define RQUEUE_READ(it, rptr, wptr, size)  for(size_type it = 0 ;\
														 it < size && rptr != wptr ; it++, rptr = rptr->__M_chain_next)

#define RQUEUE_WRITE(it, rptr, wptr, size) for(size_type it = 0 ;\
														 it < size && wptr != rptr ; it++, wptr = wptr->__M_chain_next)

#define RQUEUE_READ_UNTIL(it, rptr, wptr, size)  for(size_type it = 0 ; it < size ; it++, rptr = rptr->__M_chain_next)

#define RQUEUE_WRITE_UNTIL(it, rptr, wptr, size) for(size_type it = 0 ; it < size ; it++, wptr = wptr->__M_chain_next)

namespace disk::queueing {
	template <typename QueueType>
	class ring_queue
	{
	public:
		typedef std::remove_pointer_t<std::decay_t<QueueType>> value    ;
		typedef value*										   pointer  ;
		typedef value&										   reference;
		typedef std::size_t									   size_type;
		
	public:
		class					    chain			  ;
		typedef std::atomic<chain*> atomic_read_point ;
		typedef std::atomic<chain*> atomic_write_point;

	public:
		ring_queue ();
		~ring_queue();

	public:
		void read	    (pointer, size_type);
		void read_until (pointer, size_type);
		void write	    (pointer, size_type);
		void write_until(pointer, size_type);

	private:
		atomic_read_point  __M_rq_reader;
		atomic_write_point __M_rq_writer;
		chain*			   __M_rq_start = nullptr;
	};

	template <typename QueueType>
	class ring_queue<QueueType>::chain
	{
		friend class ring_queue<QueueType>;
	public:
		typedef ring_queue<QueueType>::chain chain_type     ;
		typedef chain_type*					 chain_pointer  ;
		typedef chain_type&					 chain_reference;

	public:
		chain (chain_reference);
		chain ();
		~chain();

	private:
		chain_pointer __M_chain_prev, __M_chain_next;
	};
}

template <typename QueueType>
disk::queueing::ring_queue<QueueType>::ring_queue() : __M_rq_start()
{

}

template <typename QueueType>
disk::queueing::ring_queue<QueueType>::~ring_queue()
{

}

template <typename QueueType>
void disk::queueing::ring_queue<QueueType>::read(pointer ptr, size_type size)
{
	RQUEUE_READ(r_it, __M_rq_reader, __M_rq_writer, size)
		ptr[r_it] = *(__M_rq_reader.load());
}

template <typename QueueType>
void disk::queueing::ring_queue<QueueType>::read_until(pointer ptr, size_type size)
{
	RQUEUE_READ_UNTIL(r_it, __M_rq_reader, __M_rq_writer, size)
	{
		if (__M_rq_reader == __M_rq_writer)
			__M_rq_reader.wait();

		ptr[r_it] = *(__M_rq_reader.load());
	}
}

template <typename QueueType>
void disk::queueing::ring_queue<QueueType>::write(pointer ptr, size_type size)
{
	RQUEUE_WRITE(r_it, __M_rq_reader, __M_rq_writer, size)
		ptr[r_it] = *(__M_rq_reader.load());
}

template <typename QueueType>
void disk::queueing::ring_queue<QueueType>::write_until(pointer ptr, size_type size)
{
	RQUEUE_WRITE_UNTIL(r_it, __M_rq_reader, __M_rq_writer, size)
	{
		if (__M_rq_reader == __M_rq_writer)
			__M_rq_reader.wait();

		ptr[r_it] = *(__M_rq_reader.load());
	}
}