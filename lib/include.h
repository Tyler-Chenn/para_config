#include <iostream>
#include <map>

// #include <string>
using namespace std;

class Para_config
{
public:
    void read_config(const string config_path);
    string find_para(const string key);
    string find_para(const string section, const string key);

private:
    map<string, map<string, string>> parameters;
};