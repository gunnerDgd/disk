#include <sys/types.h>
#include <fcntl.h>

namespace file {

    enum mode
    {
        create = O_CREAT,
        open   = 0,

        read   = O_RDONLY,
        write  = O_WRONLY,
        all    = O_RDWR
    };

    int  operator|  (mode l, mode r) { return (int)l  | (int)r; }
    int  operator&  (mode l, mode r) { return (int)l  & (int)r; }
    int  operator^  (mode l, mode r) { return (int)l  ^ (int)r; }
    bool operator== (int  l, mode r) { return      l == (int)r;}

    class file_type
    {
    public:
        using            handle_t                          = int    ;
        using            output_size_t                     = ssize_t;
        using            input_size_t                      = size_t ;
        using            offset_size_t                     = off_t  ;
        using            open_mode_t                       = int    ;
    
    public:
        static constexpr output_size_t invalid_output_size = -1;
        static constexpr handle_t      invalid_handle      = -1;
    };
}