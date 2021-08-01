#include <sys/types.h>
#include <sys/stat.h>

#include <fcntl.h>
#include <unistd.h>

namespace io   {
namespace disk {

#ifdef ENVIRONMENT_UNIX
    using file_handle_t    = int;
    enum  file_access_mode : int
    {
        read_only  = O_RDONLY,
        write_only = O_WRONLY,
        all        = O_RDWR 
    };

    enum  file_open_mode   : int
    {
        create = O_CREAT,
        open
    };

    int operator| (file_access_mode& a, file_open_mode  & o) { return (int)a | (int)o; }
    int operator| (file_access_mode& l, file_access_mode& r) { return (int)l | (int)r; }
#elif ENVIRONMENT_WINDOWS
    using file_handle_t = HANDLE;
#endif
}
}