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
        if (entry->d_name[0] != '.' && entry->d_name == arg && entry->d_type == DT_DIR)
        {return true;}
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
    
    string bizzaro = to_bizzaro(arg);
    while((entry = readdir(dir)) != NULL)
    {
        if (entry->d_name == bizzaro) //Already exist
        {
            closedir(dir);
            return true;
        }
    }
    closedir(dir);
    cout <<endl;
    return false;
}

//Checks if the file is already a Bizzaro version (e.g. txt.xyz)
bool is_BizzaroFile (string name)
{
    if (name.substr(0,4) == "txt.")
    {
        return true;
    }
    return false;
}


//Recursively applies Bizzaro coding on the all subdir and files
void readDir( string argDir, string argBizzaroDir, int level )
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
        string name;
        while((entry = readdir(dir)) != NULL)
        {
            /* //turns out that Bizzaro is applied for sub-directories as well

            if (entry->d_name[0] != '.' && is_Bizzaro(entry->d_name, argDir))
            {
                //copy it to argBizzaroDir
                continue;
            }*/
            
            if (entry->d_type == DT_DIR && entry->d_name[0] != '.')
            {
                string new_argDir = argDir + "/" + entry->d_name;
                string new_argBizzaroDir = argBizzaroDir + "/" + to_bizzaro(entry->d_name);
                readDir (new_argDir, new_argBizzaroDir, level+1);
            }
            
            else if (entry->d_name[0] != '.') //it's a file
            {
                if (is_BizzaroFile(entry->d_name))
                {
                    //copy it exactly the same to the new directory
                    string readFilePath = argDir + "/" + entry->d_name;
                    ifstream inFile (readFilePath);
                    stringstream strStream;
                    strStream << inFile.rdbuf(); //read the file
                    inFile.close();
                    string str = strStream.str(); //str holds the content of the file
                    
                    string outFilePath = argBizzaroDir + "/" + entry->d_name;
                    ofstream out (outFilePath); //creates a file with the same name
                    out << str;
                    out.close();
                }
                else
                {
                    //otherwise apply Bizzaro on it
                    string readFilePath = argDir + "/" + entry->d_name;
                    ifstream inFile (readFilePath);
                    stringstream strStream;
                    strStream << inFile.rdbuf(); //read the file
                    inFile.close();
                    string str = strStream.str(); //str holds the content of the file
                    string BizzaroStr = to_bizzaro(str); //reverse the content of the file
                    
                    string BizzaroName = to_bizzaro(entry->d_name);
                    string outFilePath = argBizzaroDir + "/" + BizzaroName;
                    ofstream out (outFilePath); //creates a file with the same name
                    out << BizzaroStr;
                    out.close();
                }

                
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
        string argDir = "./" + arg;
        string argBizzaroDir = "./" + argBizzaro;
        readDir (argDir, argBizzaroDir, 1);
    }
    else //it's a file
    {
        if (is_BizzaroFile(arg))
        {
            cout << "Error: can't create Bizarro file "<<arg<< "; it's already a Bizarro file!! "<<endl;
            return 0;
        }
        else
        {
            //otherwise apply Bizzaro on it
            string readFilePath = loc + "/" + arg;
            ifstream inFile (readFilePath);
            stringstream strStream;
            strStream << inFile.rdbuf(); //read the file
            inFile.close();
            string str = strStream.str(); //str holds the content of the file
            string BizzaroStr = to_bizzaro(str); //reverse the content of the file
            
            string outFilePath = loc + "/" + argBizzaro;
            ofstream out (outFilePath); //creates a file with the same name
            out << BizzaroStr;
            out.close();
        }

    }
    cout << "Operation finished succesfully! " <<endl;
    return 0;
}






