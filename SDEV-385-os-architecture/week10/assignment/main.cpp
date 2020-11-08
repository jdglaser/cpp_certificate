#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<errno.h>
#include<string.h>
#include<iostream>
#include<fcntl.h>
#include<vector>
#include<tuple>
#include<map>
#include <dirent.h>

//=============================================
// SDEV-385 Homework 10
//=============================================
/*
Description:
File utility program. User can select 1 or more files, show file(s) details, change file(s) permissions, and copy file(s)

OS: Ubuntu 20.04.1 LTS
Compiler: g++-9 (Ubuntu 9.3.0-10ubuntu2) 9.3.0
Last Updated: 2020-11-08

*/

using namespace std;

// Use for mapping permissions
map<string, mode_t> permMap = {
    {"r", S_IRUSR},
    {"w", S_IWUSR},
    {"x", S_IXUSR}
};

// Generalized error handling function
int handleError(int res) {
  if (res == -1) {
    perror(strerror(errno));
    exit(EXIT_FAILURE);
  }
  return res;
}

// Check if file is not a dir
bool isFile(string &path) {
    struct stat path_stat;
    stat(path.c_str(), &path_stat);
    return S_ISREG(path_stat.st_mode);
}

// Show selected files
void printSelectedFiles(vector<tuple<int, string>> &selectedFiles) {
    cout << "Selected files: ";
    if ( selectedFiles.empty() ) {
        cout << "No files selected" << endl;
        return;
    }
    for (tuple<int, string> i: selectedFiles) {
        cout << get<1>(i) << " | ";
    }
    cout << endl;
}

// Show file stats
void printFileStats(string filePath) {
    struct stat fileStat;
    stat(filePath.c_str(), &fileStat);
    cout << "\n-----------------------\n" << filePath << "\n-----------------------\n";
    cout << "File Size: \t\t" << fileStat.st_size << " bytes\n";
    cout << "Number of Links: \t" << fileStat.st_nlink << "\n";
    cout << "File inode: \t\t" << fileStat.st_ino << "\n";

    printf("File Permissions: \t");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf("\n");
}

// Change file permissions
void changeFilePermissions(vector<tuple<int, string>> &selectedFiles) {
    bool add;
    mode_t perm;

    string choice;
    while (true) {
        cout << "Would you like to add or remove permissions?\n1) Add\n2) Remove" << endl;
        cin >> choice;
        if (choice == "1") {
            add = true;
        } else if (choice == "2") {
            add = false;
        } else {
            cout << "Please select a valid option" << endl;
            continue;
        }

        cout << "Which permission do you want to " << (add ? "add" : "remove") << "? (r, w, or x)? ";
        cin >> choice;
        if (choice != "r" && choice != "w" && choice != "x") {
            cout << choice << endl;
            cout << "Please select a valid option (r,w,x)" << endl;
            continue;
        } else {
            perm = permMap[choice];
            break;
        }
    }

    for (tuple<int, string> f: selectedFiles) {
        string path = get<1>(f);
        struct stat st;
        stat(path.c_str(), &st);
        mode_t mode = st.st_mode & 07777;

        if (add) {
            mode = mode | perm;
        } else {
            mode = mode & ~(perm);
        }
        chmod(path.c_str(), mode);
    }
}

// Copy a single file to new dir
void copyFile(int src, int dest, size_t srcSize) {
    // Set the buffer size and create the buffer
    int BUFFER_SIZE = 100;
    char buffer[BUFFER_SIZE];

    // Start at beginning of file
    lseek(src,0,SEEK_SET);

    // Initially read as many bytes as possible into the buffer
    ssize_t bytesRead = handleError(read(src, buffer, BUFFER_SIZE));

    while (bytesRead > 0) {
        ssize_t bytesWritten = handleError(write(dest, buffer, bytesRead));
        bytesRead = handleError(read(src, buffer, BUFFER_SIZE));
    }
}

// Copy files to new dir
void copyFiles(vector<tuple<int, string>> &selectedFiles) {
    int count;
    struct stat theStatus;
    string dirName;
    while (true) {
        cout << "Select the directory to copy to: ";
        cin >> dirName;
        DIR *dir = opendir(dirName.c_str());
        if (dir == NULL) {
            if (errno == ENOENT) {
                cout << dirName + " is not a valid directory." << endl;
                continue;
            } else {
                perror(strerror(errno));
                exit(EXIT_FAILURE);
            }
        } else {
            closedir(dir);
            break;
        }
    }

    for (tuple<int, string> i: selectedFiles) {
        string fileName = (string) basename(get<1>(i).c_str());
        handleError(fstat(get<0>(i), &theStatus));
        int outputFileDescriptor = handleError(open((dirName + "/" + fileName).c_str(),O_RDWR | O_CREAT, S_IRWXU));
        handleError(ftruncate(outputFileDescriptor, 0));
        copyFile(get<0>(i), outputFileDescriptor, theStatus.st_size);
        handleError(close(outputFileDescriptor));
    }
}

// Close selected files
void closeSelectedFiles(vector<tuple<int, string>> &selectedFiles) {
    for (tuple<int, string> i: selectedFiles) {
        close(get<0>(i));
    }
}

// Show menu
void printMenu() {
    cout << 
        "1) Select a file\n"
        "2) Show file(s) details\n"
        "3) Change file(s) permissions\n"
        "4) Copy file(s) to new directory\n"
        "5) Cancel\n"
        "6) Quit\n"
        "Select an option: ";
}

int main() {
    cout << "=================================" << endl;
    cout << "Linux File Utility" << endl;
    cout << "=================================" << endl;
    cout << "\n";

    vector<tuple<int,string>> selectedFiles;

    string choice;
    string fileName;
    int file;
    while (true) {
        printSelectedFiles(selectedFiles);
        printMenu();
        cin >> choice;
        if (choice == "1") {
            cout << "Select a file to open: ";
            cin >> fileName;
            file = open(fileName.c_str(), O_RDONLY);
            if (file == -1) {
                cout << "Could not open file " << fileName << "\n";
                continue;
            }
            if (!isFile(fileName)) {
                cout << fileName << " is not a file" << endl;
                continue;
            }
            selectedFiles.push_back(make_tuple(file, fileName));
        } else if (choice == "2") {
            for (tuple<int, string> t: selectedFiles) {
                printFileStats(get<1>(t));
            }
        } else if (choice == "3") {
            changeFilePermissions(selectedFiles);
        } else if (choice == "4") {
            copyFiles(selectedFiles);
        } else if (choice == "5") {
            cout << "De-selecting all files...";
            closeSelectedFiles(selectedFiles);
            selectedFiles.clear();
            cout << endl;
        } else if (choice == "6") {
            closeSelectedFiles(selectedFiles);
            cout << "Quitting program, goodbye.\n";
            break;
        } else {
            cout << "Please select a valid option...\n";
        }
        
    }
}