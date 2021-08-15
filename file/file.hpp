#pragma once
#include <disk/file/operation/file_operation.hpp>
#include <disk/file/file_type.hpp>

namespace file {

    enum state : uint8_t
    { 
        normal         = 0,
        io_error       = (1 << 0),
        internal_error = (1 << 1)
    };

    template <typename file_data_t      = uint8_t  ,
              typename file_type_t      = file_type, 
              typename file_operation_t = file_operation<file_data_t, file_type_t>>
    class file_base
    {
    public:
        file_base(std::string, typename file_type_t::open_mode_t);
        file_base();

        typename file_type_t::output_size_t read  (file_data_t*, typename file_type_t::input_size_t);
        typename file_type_t::output_size_t write (file_data_t*, typename file_type_t::input_size_t);

        bool                                open  (std::string&, typename file_type_t::open_mode_t);
        bool                                close ();
        
        typename file_type_t::offset_size_t offset(typename file_type_t::offset_size_t);
    
    protected:
        typename file_type::handle_t file_handle;
        uint8_t                      file_state ;
    };
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
file::file_base<file_data_t, file_type_t, file_operation_t>::file_base(std::string name, typename file_type_t::open_mode_t mode)
    : file_handle(this->open(name, mode))
{
    if(file_handle == file_type_t::invalid_handle)
        file_state |= state::internal_error;
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
file::file_base<file_data_t, file_type_t, file_operation_t>::file_base()
    : file_state(state::normal) { }

template <typename file_data_t, typename file_type_t, typename file_operation_t>
typename file_type_t::output_size_t file::file_base<file_data_t, file_type_t, file_operation_t>::read (file_data_t* read_context , typename file_type_t::input_size_t read_size)
{
    if(file_handle == file_type_t::invalid_handle)
        return file_type_t::invalid_output_size;
    
    auto read_res  = file_operation_t::read(file_handle, read_context, read_size);
    if  (read_res == file_type_t::invalid_output_size)
        file_state |= state::io_error;
    
    return read_res;
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
typename file_type_t::output_size_t file::file_base<file_data_t, file_type_t, file_operation_t>::write(file_data_t* write_context, typename file_type_t::input_size_t write_size)
{
    if(file_handle == file_type_t::invalid_handle || file_state != state::normal)
        return file_type_t::invalid_output_size;
    
    auto write_res  = file_operation_t::write(file_handle, write_context, write_size);
    if  (write_res == file_type_t::invalid_output_size)
        file_state |= state::io_error;
    
    return write_res;
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
bool file::file_base<file_data_t, file_type_t, file_operation_t>::open (std::string& file_name, typename file_type_t::open_mode_t file_mode)
{
    file_handle          = file_operation_t::open(file_name, file_mode);
    return (file_handle == file_type_t::invalid_handle) ? false : true;
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
typename file_type_t::offset_size_t file::file_base<file_data_t, file_type_t, file_operation_t>::offset(typename file_type_t::offset_size_t offset_value) 
{ 
    return file_operation_t::offset(file_handle, offset_value); 
}