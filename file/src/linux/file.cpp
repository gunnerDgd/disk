#include <file/file.hpp>

bool io::disk::file::open (disk::file_access_mode f_ac, disk::file_open_mode f_op)
{
    if(f_op == disk::file_open_mode::create)
        file_handle = ::open(file_name.c_str(), f_ac | f_op,
                             S_IRWXU | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
    else
        file_handle = ::open(file_name.c_str(), (int)f_ac);

    if (file_handle < 0)
        FILE_HANDLE_INTERNAL_ERROR(this, "Failed to Open File", false)

    return true;
}

bool  io::disk::file::close()
{
	int cl_res = ::close(file_handle);
    if (cl_res < 0)
        FILE_HANDLE_INTERNAL_ERROR(this, "Failed to Close File", false)

    return true;
}

io::io_size io::disk::file::read(uint8_t* c, io_size s)
{
    ssize_t r_res = ::read(file_handle, reinterpret_cast<void*>(c), s);
    if     (r_res < 0)
        FILE_HANDLE_IO_ERROR(this, "Failed to Read File", 0)
    return  r_res;
}

io::io_size io::disk::file::write(uint8_t* c, io_size s)
{
    ssize_t w_res = ::write(file_handle, (void*)c, s);
    if     (w_res < 0)
        FILE_HANDLE_IO_ERROR(this, "Failed to Write File", 0)
    return w_res;
}

std::size_t io::disk::file::offset(std::size_t f_ptr)
{
	off_t off_res = lseek(file_handle, f_ptr, SEEK_SET);
    if   (off_res == -1)
        IO_HANDLE_INTERNAL_ERROR(this, "Failed to Change Offset", 0)
    return off_res;
}

std::size_t io::disk::file::size  ()
{
    struct stat st_ctx;
    int         st_res = fstat(file_handle, &st_ctx);

    if(st_res < 0)
        FILE_HANDLE_INTERNAL_ERROR(this, "Failed to Get File Size", 0)
    else
	    return st_ctx.st_size;
}