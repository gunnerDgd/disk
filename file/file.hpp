#pragma once

#include "operation/file_operation.hpp"
#include "traits/file_type.hpp"

namespace file {

    enum class state 
    { 
        normal         = (1 << 0),
        io_error       = (1 << 1),
        internal_error = (1 << 2)
    };

    template <typename file_data_t      = uint8_t  ,
              typename file_type_t      = file_type, 
              typename file_operation_t = file_operation<file_data_t, file_type_t>>
    class file
    {
    public:
        typename file_type_t::output_size_t read  (file_data_t*, typename file_type_t::input_size_t) ;
        typename file_type_t::output_size_t write (file_data_t*, typename file_type_t::input_size_t);

        bool                                open  (std::string&, typename file_type_t::open_mode_t);
        bool                                close ();

        typename file_type_t::offset_size_t offset(file_type_t::offset_size_t offset_value) { return file_operation_t::offset(file_handle, offset_value); }
    
    protected:
        typename file_type::handle_t file_handle;
        state                        file_state ;
    };
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
typename file_type_t::output_size_t file::file<file_data_t, file_type_t, file_operation_t>::read (file_data_t* read_context , typename file_type_t::input_size_t read_size)
{
    if(file_handle == file_type_t::invalid_handle)
        return file_type_t::invalid_output_size;
    else
        return file_operation_t::read(file_handle, read_context, read_size);
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
typename file_type_t::output_size_t file::file<file_data_t, file_type_t, file_operation_t>::write(file_data_t* write_context, typename file_type_t::input_size_t write_size)
{
    if(file_handle == file_type_t::invalid_handle)
        return file_type_t::invalid_output_size;
    
    auto    write_res  = file_operation_t::write(file_handle, write_context, write_size);
    
}

template <typename file_data_t, typename file_type_t, typename file_operation_t>
bool file::file<file_data_t, file_type_t, file_operation_t>::open (std::string& file_name, typename file_type_t::open_mode_t file_mode)
{
    file_handle          = file_operation_t::open(file_name.c_str(), file_mode);
    return (file_handle == file_type_t::invalid_handle) ? false : true;
}