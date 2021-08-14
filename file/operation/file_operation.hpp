#include <sys/types.h>
#include <fcntl.h>

namespace file {

    template <typename file_data_t, typename file_type_t>
    class file_operation
    {
    public:
        static typename file_type_t::hanldle_t     open (std::string&, typename file_type_t::open_mode_t);
        static typename bool                       close(file_type_t::handle_t file_handle)                                                       { return ::close(file_handle); }

    public:
        static typename file_type_t::output_size_t read (typename file_type_t::handle_t     read_handle , 
                                                         file_data_t*                       read_context, 
                                                         typename file_type_t::input_size_t read_size)  ;

        static typename file_type_t::output_size_t write(typename file_type_t::handle_t     write_handle , 
                                                         file_data_t*                       write_context, 
                                                         typename file_type_t::input_size_t write_size)  ;

    public:
        static typename file_type_t::offset_size_t offset(typename file_type_t::handle_t      offset_handle,
                                                          typename file_type_t::offset_size_t offset_value );

    };
}

template <typename file_data_t, typename file_type_t>
typename file_type_t::hanldle_t file::file_operation<file_data_t, file_type_t>::open (std::string& file_name, typename file_type_t::open_mode_t file_mode)
{
    if(file_mode & mode::create)
        return ::open(file_name.c_str(), file_mode, 0666);
    else
        return ::open(file_name.c_str(), file_mode);
}

template <typename file_data_t, typename file_type_t>
typename file_type_t::output_size_t file::file_operation<file_data_t, file_type_t>::read (typename file_type_t::handle_t     read_handle ,
                                                                                          file_data_t*                       read_context, 
                                                                                          typename file_type_t::input_size_t read_size)
{ 
    return ::read (read_handle, read_context, read_size); 
}

template <typename file_data_t, typename file_type_t>
typename file_type_t::output_size_t file::file_operation<file_data_t, file_type_t>::write(typename file_type_t::handle_t     write_handle , 
                                                                                          file_data_t*                       write_context, 
                                                                                          typename file_type_t::input_size_t write_size)  
{ 
    return ::write(read_handle, read_context, read_size); 
}

template <typename file_data_t, typename file_type_t>
typename file_type_t::offset_size_t file::file_operation<file_data_t, file_type_t>::offset(typename file_type_t::handle_t      offset_handle,
                                                                                           typename file_type_t::offset_size_t offset_value )
{
    return ::lseek(offset_handle, offset_value, SEEK_SET);
}