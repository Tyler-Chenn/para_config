#include "./lib/include.h"

int main()
{
    Para_config p;                                   //实例化一个参数解析器
    p.read_config("/home/tyler/parameter/conf.ini"); //传入参数文本文件

    cout << "----------------------" << endl;
    cout << p.find_para("ii") << endl;              //使用 键 检索
    cout << p.find_para("default_1", "ii") << endl; //使用 字段+键 检索
}
