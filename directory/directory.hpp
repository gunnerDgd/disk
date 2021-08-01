#include <disk/file/file.hpp>
#include <list>

namespace io   {
namespace disk {

    class directory
    {
    public:
        using directory_handle_t = DIR*  ;
        using directory_entry_t  = dirent;
    public:
        directory(std::string dir_path) : directory_path(std::move(dir_path)) { this->open(directory_path); }
        directory()                     { }
    
    public:
        bool open  (std::string dir_path);
        bool close ();

    public:
        void               update     ();
        const std::string& operator[] (uint32_t it) { return directory_list[it % directory_list.size()]; }

    protected:
        std::string            directory_path  ;
        std::list<std::string> directory_list  ;
    
    protected:
        directory_handle_t     directory_handle;
        directory_entry_t      directory_entry ;
    };
}
}