#include <disk/handle/file/file_nonblock.hpp>

disk::handle::file_nonblock disk::handle::file_nonblock::from_new(std::string  path)
{
	native_handle		 hnd = ::CreateFileA(path.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	return file_nonblock(hnd);
}

disk::handle::file_nonblock disk::handle::file_nonblock::from_new(std::wstring path)
{
	native_handle		 hnd = ::CreateFileW(path.c_str(), GENERIC_ALL, 0, NULL, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, NULL);
	return file_nonblock(hnd);
}

disk::handle::file_nonblock disk::handle::file_nonblock::from_existing(std::string  path)
{
	native_handle		 hnd = ::CreateFileA(path.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	return file_nonblock(hnd);
}

disk::handle::file_nonblock disk::handle::file_nonblock::from_existing(std::wstring path)
{
	native_handle		 hnd = ::CreateFileW(path.c_str(), GENERIC_ALL, 0, NULL, OPEN_EXISTING, FILE_FLAG_OVERLAPPED, NULL);
	return file_nonblock(hnd);
}

disk::handle::file_nonblock::file_nonblock (native_handle hnd) : __M_hnd_native(hnd) {  }
disk::handle::file_nonblock::~file_nonblock()										 { ::CloseHandle(__M_hnd_native); }

disk::handle::file_nonblock::operator bool()										 { return __M_hnd_native != INVALID_HANDLE_VALUE; }