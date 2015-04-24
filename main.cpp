/******************************************************
 ** FILE: main.cpp
 **
 ** CLASS:
 ** CSE410
 **
 ** PROJECT03 -- Extra Credits
 **
 ** AUTHOR:
 ** Yousef Gtat
 **
 ** CREATION DATE:
 ** 04/22/2015
 **
 ** Fucntions
 ** - is_Dir: returns a bool whether it's a directory or not
 ** - to_bizzaro: returns a reversed string of the passed argument
 ** - is_Bizzaro: checks if the file/dir is already reversed
 ** - BizzFile: reverse a file name and its content, then save
 **             them in the given output file path
 ** - BizzDir: recursively reverse a directory and all of
 **            its sub-files and sub-directories
 ** - main: checks if the dir/file name is given with command line.
 **         checks if the dir/file is already reversed
 **         if none, it creates Bizzaro version of the dir/file
 *******************************************************/

#include <iostream>
#include <string.h>
#include <dirent.h> // struct dirent is defined in this header
#include <errno.h>
#include <sys/stat.h>
#include <fstream>
#include <sstream>

using namespace std;

//Determines what type is the passed argument from the command line (i.e. file or dir)
bool is_Dir (string arg, string loc)
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir(loc.c_str());
    while((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR && entry->d_name == arg) {return true;closedir(dir);}
    }
    closedir(dir);
    return false;
}

//Function used to convert a string to a Bizzaro string (reversed string)
string to_bizzaro (string str)
{
    string reversed = "";
    for (auto itr=str.rbegin(); itr!=str.rend(); itr++)
    {
        reversed += *itr;
    }
    return reversed;
}

//Checks if there are two reversed names exist in the same dir (e.g. test and tset)
bool is_Bizzaro (string arg, string loc)
{
    DIR *dir;
    struct dirent *entry;
    dir = opendir(loc.c_str());
    
    string bizzaro = to_bizzaro(arg);  //reversed name of arg
    while((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name == bizzaro) //Already exist
        {
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    return false;
}


//Reads in a file and reverse its contents which will be written in another output file
void BizzFile (string readFilePath, string writeFilePath)
{
    ifstream inFile (readFilePath);
    stringstream strStream;
    strStream << inFile.rdbuf(); //read the file
    inFile.close();
    string str = strStream.str(); //str holds the content of the file
    string BizzaroStr = to_bizzaro(str); //reverse the content of the file
    
    ofstream out (writeFilePath);
    out << BizzaroStr;
    out.close();

}

//Recursively applies Bizzaro on all subdir and files
void BizzDir( string argDir, string argBizzaroDir, int level )
{
    //level was mostly used in debuging
    
    DIR *dir;
    struct dirent *entry;
    errno = 0;
    dir = opendir(argDir.c_str()); // string to c string conversion
    if (errno != 0)
    {
        cout << "opendir error. " << strerror(errno) << "\t--Level: " <<level<< endl;
        return;
    }
    else if (dir)
    {
        mkdir(argBizzaroDir.c_str(), S_IRWXU);

        errno = 0;
        while((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
            {
                string new_argDir = argDir + "/" + entry->d_name;
                string new_argBizzaroDir = argBizzaroDir + "/" + to_bizzaro(entry->d_name);
                BizzDir (new_argDir, new_argBizzaroDir, level+1);
            }
            
            else if (entry->d_name[0] != '.') //it's a file
            {
                //apply Bizzaro on it even if it was already reversed
                string readFilePath = argDir + "/" + entry->d_name;
                string BizzaroName = to_bizzaro(entry->d_name); //reversed name
                string writeFilePath = argBizzaroDir + "/" + BizzaroName;
                
                //creates a file with reversed name and content of the read file
                BizzFile(readFilePath, writeFilePath);
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

//Main function takes care of the passed argument and generate the appropiate results
int main(int argc, char* argv[])
{
    if (argc <2)
    { cout<< "Error: no arguments provided...program halted!" <<endl; return 0; }
    
    string loc = ".";
    string arg = argv[1];
    if (is_Bizzaro(arg, loc) )
    {
         cout << "Error: can't create Bizarro file/directory; " << to_bizzaro(arg)<< " already exists!! "<<endl;
        return 0;
    }
    string argBizzaro = to_bizzaro(arg);
    
    
    if (is_Dir(arg, loc))
    {
        cout << "The argument provided is a directory" <<endl;
        string argDir = "./" + arg;
        string argBizzaroDir = "./" + argBizzaro;
        BizzDir (argDir, argBizzaroDir, 1);
    }
    else //it's a file
    {
        cout << "The argument provided is a file" << endl;
        string readFilePath = loc + "/" + arg;
        string writeFilePath = loc + "/" + argBizzaro;
        
        //creates a file with reversed name and content of the read file
        BizzFile(readFilePath, writeFilePath);
    }
    
    cout << "Operation finished succesfully! " <<endl;
    return 0;
}






