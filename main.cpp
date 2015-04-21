#include <iostream>
#include <string.h>
#include <dirent.h> // struct dirent is defined in this header
#include <errno.h>
using namespace std;

string reverse (string str)
{
    string reversed = "";
    for (auto itr=str.rbegin(); itr!=str.rend(); itr++)
    {
        reversed += *itr;
    }
    return reversed;
}


bool is_AlreadyBizzaro (string arg)
{
    string loc = ".";
    DIR *dir;
    struct dirent *entry;
    errno = 0;
    dir = opendir(loc.c_str());
    
    string bizzaro = reverse(arg);
    while((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name == bizzaro)
        {
            cout << "Error: can't create Bizarro file/directory; " << bizzaro<< " already exists!! "<<endl;
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    return false;
}


void readingdir( string arg, int level )
{
    if (level == 1 && is_AlreadyBizzaro (arg) ) {return;}
    
    if (level==1) { arg = "./" + arg;}
    DIR *dir;
    struct dirent *entry;
    errno = 0;
    dir = opendir(arg.c_str()); // string to c string conversion
    if (errno != 0)
    {
        cout << "opendir error. " << strerror(errno) << "\t--Level: " <<level<< endl;
        return;
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
                readingdir (arg + "/" + entry->d_name, level+1);
            }
        }
        if(errno != 0)
        {
            cout << "readdir error. " << strerror(errno) <<"\t--Level: "<<level<< endl;
            return;
        }
    }
    closedir(dir);
}

int main(int argc, char* argv[])
{
    if (argc <2)
    { cout<< "Error: no argument provided...program halted!" <<endl; return 0; }
    
    string arg = argv[1];
    readingdir (arg, 1);
    return 0;
}