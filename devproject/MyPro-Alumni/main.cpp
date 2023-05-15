/****************************************************************************************************************************
* @function:校友管理系统主函数
* @version:v1.0.1
* @author:chenjunlong
* @description:By calling other modules, the main functions are achieved.
* @github:https://github.com/Kayll2000/Alumni-login-system.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.05.15
* @compile:Compile the environment is Dev-C++(Embarcadero Dev-C++)
*           FUCTION:
                    1、校友登录
                        	1.1 修改个人信息
	                        1.2 查看其他校友信息
	                        1.3 填写问卷
	                        1.4 查看新闻
	                        1.5 退出登录
                    2、管理员登录
                    	    2.1 查看校友列表
	                        2.2 添加校友信息
	                        2.3 修改校友信息
	                        2.4 删除校友信息
	                        2.5 新闻功能
	                        2.6 问卷功能
	                        2.7 退出登录
            BUGFIX:[2023.04.27]解决显示校友总数一直为0的bug。
            MODIFY:[2023.04.24]增加主函数登录界面输入的容错性，优化主界面，优化UI。
                   [2023.04.27]优化登录界面。
                   [2023.04.27]优化校友查看新闻信息功能。
				   [2023.05.15]增加逐字输出问候功能。

*
****************************************************************************************************************************/
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <io.h>
#include<direct.h> 
#include <list>
#include "login.h"
#include "core.h"

using namespace std;
//int main(int argc, char** argv)
int main() 
{
	Init();
    core();
    return 0;
}