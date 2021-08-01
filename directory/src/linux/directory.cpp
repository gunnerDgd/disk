#include <disk/directory/directory.hpp>

bool io::disk::directory::open(std::string dir_path)
{
    directory_handle    = opendir(dir_path.c_str());
    if(!directory_handle) return false;
    
    this            ->update();
    return true;
}

bool io::disk::directory::update()
{
    while(directory_entry = readdir(directory_handle))
        directory_list.push_back(std::string());
}