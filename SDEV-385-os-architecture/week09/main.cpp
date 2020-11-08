#include <string>
#include <iostream>
#include <filesystem>
#include <vector>
#include <map>
#include <fstream>
#include <unistd.h>

namespace fs = std::filesystem;
using namespace std;

/*
Description:
This program parses the /proc dir for information about processes.

This program was built using g++-9 including the C++17 standard library.

OS: Ubuntu 20.04.1 LTS
Compiler: g++-9 (Ubuntu 9.3.0-10ubuntu2) 9.3.0
 - Special compiler tags: -std=c++17
Last Updated: 2020-11-01
*/


//================================
// String utility functions
//================================

// Split a string on character
vector<string> split_str(string str, char split_char) {
    vector<string> parts;

    string word = "";
    for (auto s:str) {
        if (s != split_char) {
            word += s;
        } else {
            parts.push_back(word);
            word = "";
        }
    }
    parts.push_back(word);

    return parts;
}

// Trim trailing and leading whitespace from string
string trim_str(const string& str)
{
    size_t first = str.find_first_not_of("  \t");
    if (string::npos == first)
    {
        return str;
    }
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, (last - first + 1));
}

// Check if string is a number
bool is_number(const string& s)
{
    string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

// Convert contents of a file to a string
string file_to_string(string path) {
    ifstream ifs(path);
    string content;
    content.assign((std::istreambuf_iterator<char>(ifs)),
        (std::istreambuf_iterator<char>()));
    return content;
}

//================================
// /proc functions
//================================

// Check if user has read access to dir (used for testing only)
bool has_access(string pathname) {
    int ac = access(pathname.c_str(), R_OK);
    return ac == 0 ? true : false;
} 

// Get pid from path
int get_pid(string pid_path) {
    vector<string> pid_spl = split_str(pid_path, '/');
    string pid = pid_spl[pid_spl.size()-1];

    if(is_number(pid)) {
        return stoi(pid);
    } else {
        return -1;
    }
}

// Get a vector of all processes
vector<int> get_pids() {
    string path = "/proc";
    vector<int> pids;
    int pid;
    for (const auto & entry : fs::directory_iterator(path)) {
        pid = get_pid(entry.path());
        if(pid != -1) {
            //cout << pid << ": " << ((has_access(entry.path())) == true ? "yes" : "no") << endl;
            pids.push_back(pid);
        }
    }
    return pids;
}

// Get attributes from a proc status file
map<string, string> get_attributes(int pid) {
    string path = "/proc/" + to_string(pid) + "/status";
    string contents = file_to_string(path);
    vector<string> content_vec = split_str(contents, '\n');
    map<string, string> return_map;
    
    vector<string> res;
    for (auto i:content_vec) {
        vector<string> split_res = split_str(i, ':');
        string key = split_res[0];
        if (key == "") {
            continue;
        }
        string value = trim_str(split_res[1]);
        return_map[key] = value;
    }
    return return_map;
}

//================================
// menu functions
//================================

// Show options
void display_options() {
    cout << "a) Show processes\n"
        "b) Get name\n"
        "c) Get Virtual Memory Size\n"
        "d) Get State\n"
        "e) Get Parent Process ID\n"
        "f) Exit Program\n";
}

// Main menu driver program
void menu() {
    cout << "=================================" << endl;
    cout << "Linux process info program" << endl;
    cout << "=================================" << endl;
    cout << "\n\n";

    string res;
    vector<int> processes;
    string pid;
    map<string, string> process_attributes;
    while (true) {
        display_options();
        cout << "Select an option: " << endl;
        cin >> res;
        if (res == "a") {
            processes = get_pids();
            for (auto p:processes) {
                cout << p << endl;
            }
        } else if (res == "b") {
            cout << "Enter a process id: ";
            cin >> pid;
            if (!is_number(pid)) {
                cout << "Please enter a number for pid." << endl;
                continue;
            }
            string res = get_attributes(stoi(pid))["Name"];
            cout << "Name: " << res << endl;
        } else if (res == "c") {
            cout << "Enter a process id: ";
            cin >> pid;
            if (!is_number(pid)) {
                cout << "Please enter a number for pid." << endl;
                continue;
            }
            string res = get_attributes(stoi(pid))["VmSize"];
            cout << "Virtual Memory size: " << res << endl;
        } else if (res == "d") {
            cout << "Enter a process id: ";
            cin >> pid;
            if (!is_number(pid)) {
                cout << "Please enter a number for pid." << endl;
                continue;
            }
            string res = get_attributes(stoi(pid))["State"];
            cout << "State: " << res << endl;
        } else if (res == "e") {
            cout << "Enter a process id: ";
            cin >> pid;
            if (!is_number(pid)) {
                cout << "Please enter a number for pid." << endl;
                continue;
            }
            string res = get_attributes(stoi(pid))["PPid"];
            cout << "Parent Process ID: " << res << endl;
        } else if (res == "f") {
            break;
        } else {
            cout << "Please enter a valid option" << endl;
        }
    }
}

//================================
// main
//================================
int main()
{
    menu();
}
