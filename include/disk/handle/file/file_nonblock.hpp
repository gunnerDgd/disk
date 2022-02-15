#pragma once
#include <Windows.h>
#include <string>

#include <disk/io_system/forward.hpp>

namespace disk::handle {
	class file_nonblock
	{
		template <typename T, typename U>
		friend class disk::basic_reader;

		template <typename T, typename U>
		friend class disk::basic_writer;
	public:
		typedef HANDLE	   native_handle;
		typedef OVERLAPPED native_async_handle;

	public:
		static file_nonblock from_new	  (std::string) ;
		static file_nonblock from_new	  (std::wstring);
		
		static file_nonblock from_existing(std::string) ;
		static file_nonblock from_existing(std::wstring);
	
	public:
		operator bool();

	private:
		file_nonblock (native_handle);
		~file_nonblock();

	private:
		native_handle		__M_hnd_native		;
		native_async_handle __M_hnd_async_native;
	};
}