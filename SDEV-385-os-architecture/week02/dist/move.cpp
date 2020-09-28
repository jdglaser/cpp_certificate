#include <unistd.h>
#include <libgen.h>
#include <sys/stat.h>
#include <iostream>
#include <cerrno>
#include <cstring>
#include <string>

using namespace std;

//=============================================
// README
//=============================================
/*

# SDEV-385 Homework 2

## Description:
This program moves a file from one location to another directory. The program allows the user to change 
the name of the file and change permissions if necessary. The program also includes graceful error handling
and printing for Linux system call errors.

## Information
- OS: Ubuntu 20.04.1 LTS
- Compiler: gcc versoin 9.3.0 (Ubuntu 9.3.0-10ubuntu2)
- Last Updated: 2020-09-13

*/

//=============================================
// Function to check Linux errorno gracefully
//=============================================
void handle_error(int errnum) {
    cout << "ERROR " << errnum << " " << strerror(errnum) << endl;
    exit(EXIT_FAILURE);
}

//=============================================
// Copies string into new memory location for
// dirname and basename system calls to use
// since these may edit the original string
//=============================================
string copy_str(string str) {
    return str;
}

int main () {
    //=============================================
    // Variables
    //=============================================

    int errnum; // Stores errno from Linux system calls
    int res; // Stores result codes for Linux system calls
    
    string source; // Source file
    string source_path; // Source path name
    string source_base_name; // Source base bane

    string dest; // New destination for file

    //=============================================
    // Get user input
    //=============================================

    // Get the source file and set base name and path
    cout << "Enter a file to move (include full path): ";
    cin >> source;

    source_base_name = basename(&(copy_str(source))[0]);
    source_path = dirname(&(copy_str(source))[0]);

    // Get destination path
    cout << "Enter a new destination for file " << source << ": ";
    cin >> dest;

    //=============================================
    // Check Access on dest and handle permission 
    // change
    //=============================================

    // Check if proper access exists - Linux system call ACCESS(2)
    res = access(&dest[0], F_OK | W_OK);

    // Check response code
    if (res != 0) {
        errnum = errno;
        if (errnum == 13) {
            string response;
            cout << "Permission denied on dir " << dest << ". Would you like to change permissions? [Y/n]" << endl;
            cin >> response;
            if (response == "Y") {
                res = chmod(&dest[0], S_IWUSR | S_IRUSR | S_IXUSR);
                if (res != 0) {
                    cout << "Failed to change permission" << endl;
                    handle_error(errno);
                }
            } else {
                cout << "Permissions not changed. File will not be moved. Closing program." << endl;
                exit(0);
            }
        } else {
            cout << "Failed to check destination" << endl;
            handle_error(errno);
        }
    }

    //=============================================
    // Ask user if file needs to be renamed
    //=============================================
    string response;
    cout << "Do you want to rename the source file " << source_base_name << "? [Y/n]" << endl;
    cin >> response;
    
    if (response == "Y") {
        cout << "What do you want to rename file to?" << endl;
        cin >> response;
        source_base_name = response;
    } else {
        cout << "Not renaming file." << endl;
    }

    //=============================================
    // Move file with rename system call
    //=============================================

    // Use linux system call RENAME(2)
    res = rename(&source[0], &(dest + "/" + source_base_name)[0]);
    cout << "Moving " << source << " to " << dest + "/" + source_base_name << endl;
    
    // Check response code and handle error if there is one
    if (res != 0) {
        cout << "Failed to move file" << endl;
        handle_error(errno);
    } else {
        cout << "File moved successfully" << endl;
    }

    // RETURN SUCCESS
    exit(0);
}