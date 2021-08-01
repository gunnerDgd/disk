
#define FILE_HANDLE_SUCCESS(ret_value) return ret_value
#define FILE_HANDLE_IO_ERROR(device, message, ret_value){\
    device->set_state(io_state::io_error);\
    std::cerr << "## ERROR ## [I/O ERROR] : " <<  message << std::endl;\
    return ret_value;\
}

#define FILE_HANDLE_INTERNAL_ERROR(device, message, ret_value){\
    device->set_state(io_state::internal_error);\
    std::cerr << "## ERROR ## [I/O Internal Error] : " << message << std::endl;\
    return ret_value;\
}