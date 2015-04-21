#include <iostream>
#include <string.h>
#include <dirent.h> // struct dirent is defined in this header
#include <errno.h>
using namespace std;

bool is_bizzaro (DIR* dir)
{
    
}
void readingdir( string loc, int level, string bizzaro )
{
    
    DIR *dir;
    struct dirent *entry;
    errno = 0;
    dir = opendir(loc.c_str()); // string to c string conversion
    if (errno != 0)
    {
        cout << "opendir error. " << strerror(errno) << "\t--Level: " <<level<< endl;
    }
    else if (dir)
    {
        errno = 0;
        while((entry = readdir(dir)) != NULL)
        {
            cout << "Entry name: " << entry->d_name << "\t--Level: " << level << endl;
            if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
            {
                cout << "recursively diving in " <<entry->d_name<<": " <<endl;
                readingdir (loc + "/" + entry->d_name, level+1);
            }
        }
        if(errno != 0)
        {
            cout << "readdir error. " << strerror(errno) <<"\t--Level: "<<level<< endl;
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[])
{
    if (argc <2)
    { cout<< "Error: no argument provided...program halted!" <<endl; return 0; }
    
    string bizzaro = argv[1];
    string loc = ".";
    readingdir (loc, 1, bizzaro);
    return 0;
}