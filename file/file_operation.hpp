#include <sys/types.h>
#include <fcntl.h>

namespace file {

namespace mode 
{

}
    int operator| (access_mode l, access_mode r) { return (int)l | (int)r; }

    template <typename file_data_t, typename file_type_t>
    class file_operation
    {
    public:
        static typename file_type_t::hanldle_t     open (std::string& file_name, typename file_type_t::open_mode_t file_open, open_mode file_open);
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
typename file_type_t::hanldle_t file::file_operation<file_data_t, file_type_t>::open (std::string& file_name, typename file_type_t::open_mode_t file_open, open_mode file_open)
{
    if(file_open == open_mode::open)
        return ::open(file_name.c_str(), file_access);
    else
        return ::open(file_name.c_str(), file_access | O_CREAT, 0666);
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