#include <io/io.hpp>
#include <file/file_flag.hpp>
#include <file/file_define.hpp>

namespace io   {
namespace disk {
    class file : public io
    {
    public:
        file (std::string f_name, io_type f_io_type);			
        ~file();

		bool open (disk::file_access_mode f_ac = disk::file_access_mode::all,
                   disk::file_open_mode   f_op = disk::file_open_mode::create);
                
		bool close();

    public:
        io_size   read  (uint8_t* r_ctx, io_size r_size) override;
        io_size   write (uint8_t* w_ctx, io_size w_size) override;

    public:
        size_t        size  ();
		std::size_t   offset(std::size_t f_ptr) ;

    public:
        std::string   name         () { return file_name  ; }
        file_handle_t native_handle() { return file_handle; }

    protected:
        std::string   file_name  ;
        file_handle_t file_handle;
    };
}
}

io::disk::file::file(std::string f_name, io_type f_io_type)
	         : io       (f_io_type),
               file_name(std::move(f_name)) { }

io::disk::file::~file() { this->close(); }