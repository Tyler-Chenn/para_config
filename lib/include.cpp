#include "include.h"
#include <fstream>
#include <vector>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

/*读取文本文件参数*/
void Para_config::read_config(const string config_path)
{
    ifstream fin(config_path);
    if (!fin.is_open())
    {
        cout << "文件打开失败！" << endl;
        return;
    }
    // for (string line;getline(fin,line); )
    string line;
    string section;
    while (getline(fin, line))
    {
        //避开注释
        if (line.find_first_of("#") != string::npos)
        {
            line.erase(line.find_first_of("#"));
        }
        //跳过空行
        if (line.empty())
            continue;
        //进入字段
        //剔除空格符
        line.erase(remove(line.begin(), line.end(), ' '), line.end());
        if (line[0] == '[')
        {
            if (line[line.size() - 1] != ']')
            {
                cout << "文件字段错误，无法解析" << endl;
                return;
            }
            map<string, string> k_v;
            section = string(line, 1, line.size() - 2);
            parameters.insert(make_pair(section, k_v));
        }
        else
        {
            vector<string> V;
            boost::split(V, line, boost::is_any_of("="), boost::token_compress_on);
            if (V.size() != 2)
            {
                cout << "配置文件此处参数输入有误" << endl;
                cout << "---->" << line << "<----" << endl;
                return;
            }
            else
            {
                auto it = parameters.find(section);
                it->second.insert(make_pair(V[0], V[1]));
            }
        }
    }
}
/*键检索*/
string Para_config::find_para(const string key)
{
    vector<string> value;
    for (auto i : parameters)
    {
        for (auto j : i.second)
        {
            if (j.first == key)
            {
                value.push_back(j.second);
            }
        }
    }
    if (value.size() > 1)
    {
        cout << "检索到 “" << key << "”的值有" << value.size()
             << "个，已返回第1个检索结果。如需精确查询，请使用 字段+键 方法检索" << endl;
    }
    else if (value.size() == 0)
    {
        cout << "未检索到“" << key << "”的值，请检查参数文件或键的输入" << endl;
        return "";
    }
    return value[0];
}
/*字段+键检索*/
string Para_config::find_para(const string section, const string key)
{
    string value;
    for (auto i : parameters)
    {
        if (i.first == section)
        {
            for (auto j : i.second)
            {
                if (j.first == key)
                {
                    return j.second;
                }
            }
        }
    }
    cout << "未检索到“" << key << "”的值，请检查参数文件或键的输入是否正确" << endl;
    return "";
}