/****************************************************************************************************************************
* @function:保存全局变量及函数
* @version:v1.0.1
* @author:chenjunlong
* @description:Save global variables and functions for the project.
* @github:https://github.com/Kayll2000/Alumni-login-system.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.06
*           FUCTION:
                    1、后续将进行优化，这个文件主要存放全局变量以及函数。
            BUGFIX:
            MODIFY:

****************************************************************************************************************************/
#include <iostream>
#include <vector>
#include "global.h"

int alumninum = 0;//校友总数 extern全局，因为main需要使用。
int alumninumread = 0;//记录读取校友总条数   
bool InitFlag = true;
bool QuestionInitFlag = true;
int newsnum = 0;//记录新闻总条数    
int readallnum = 0;//读的新闻总数
int publishnum = 0;//以及发布的新闻条数
int num = 0;// 记录所有问卷的数量
int pnum = 0;//记录已经发布问卷的数量
//int answerflag = 0;//记录已经填写的问卷个数
int qdatanum = 0;//记录问卷总数，读取问卷时的总数
int answerflag[MAX] = {0};//记录已经填写的问卷个数，初始化为0
int answersave[MAX] = {0};
int stuid = 0;//记录校友初始编号
vector<int> itemnum = {};//记录每个问卷的选项数 ——————》看怎么赋初值
