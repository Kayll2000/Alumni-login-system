/****************************************************************************************************************************
* @function:封装核心函数
* @version:v1.0.1
* @author:chenjunlong
* @description:Encapsulated core function.
* @github:https://github.com/Kayll2000/Alumni-login-system.git
* @date:2023.05.08
* @lmodauthor:chenjunlong
* @lmoddate:2023.05.15
*           FUCTION:
                    1、存放程序的核心代码、函数。
            BUGFIX:
            MODIFY:
                    1、[2023.05.11]增加退出系统选项功能。
                    2、[2023.05.11]增加校友查看他人信息时，信息不存在的提示信息。
                    3、[2023.05.15]增加逐字输出问候功能。

****************************************************************************************************************************/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <io.h>
#include<direct.h> 
#include <list>
#include <cstdlib>
#include <chrono>
#include <thread>
#include "login.h"
#include "core.h"

using namespace std;

void core()
{
    
    AlumniManager alumni_manager;
    AdminManager admin_manager;

    Admin admin("admin", "1024");//管理员登录账号及密码
    admin_manager.addAdmin(admin);

    while (true) {
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        cout << ">>> 请选择登录身份 >>>" << endl;
        cout << ">>> 1. 校友 >>>"  << endl;
        cout << ">>> 2. 管理员 >>>" << endl;
        cout << ">>> 3. 退出系统 >>>" << endl;
        cout << ">>>>>>>>>>>>>>>>>>>>>>>>" << endl;
        int choice;
        cin >> choice;
        while(cin.fail())//解决 当输入的choice非数字时导致程序奔溃
        {
            cin.clear();//清除cin的错误信息
            cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
            cout << "请输入整数: \t";
            cin.ignore();//EOF位置，接收下一个cin函数
            cin >> choice;
        }
        if (choice == 1) {
            cout << "请输入学号和密码：" << endl;
            string student_id, password;
            cin >> student_id >> password;
            if (alumni_manager.login(student_id, password)) {
                system("cls");
                while (true) {
                    Alumni* alumni = alumni_manager.getAlumni(student_id);
                    cout << "欢迎您，" << alumni->getName() << "！" << endl;
                    cout << "请选择操作：" << endl;
                    cout << "[1] 修改个人信息" << endl;
                    cout << "[2] 查看其他校友信息" << endl;
                    cout << "[3] 填写问卷" << endl;
                    cout << "[4] 查看新闻" << endl;
                    cout << "[5] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        cout << "请输入新密码、联系电话和电子邮件：" << endl;
                        string new_password, phone, email;
                        cin >> new_password >> phone >> email;
                        alumni->setPassword(new_password);
                        alumni->setPhone(phone);
                        alumni->setEmail(email);
                        alumni_manager.modifyAlumni(*alumni);
                        cout << "修改成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        vector<Alumni> alumni_list = alumni_manager.getAlumniList();
                        cout << "<<校友总数>> " << alumninum << endl;
                        if(alumni_list.size() == 1)
                        {
                            cout << "暂无信息！" << endl;
                        }
                        for (int i = 0; i < alumni_list.size(); i++) {
                            if (alumni_list[i].getStudentId() != student_id) {
                                cout << "姓名：" << alumni_list[i].getName() << endl;
                                cout << "学号：" << alumni_list[i].getStudentId() << endl;
                                cout << "性别：" << alumni_list[i].getGender() << endl;
                                cout << "出生日期：" << alumni_list[i].getBirthdate() << endl;
                                cout << "联系电话：" << alumni_list[i].getPhone() << endl;
                                cout << "电子邮件：" << alumni_list[i].getEmail() << endl;
                                cout << endl;
                            }
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3){
                        int temp = alumni->getFlagid();
                        string tname = alumni->getName();
                        admin_manager.alumni_answerquestion(temp,tname);
                    }
                    else if (choice == 4){
                        admin_manager.alumni_viewnews();
                    }
                    else if (choice == 5) {
                        system("pause");
                        system("cls");
                        break;
                    }
                    else {
                        cout << "输入有误，请重新输入！" << endl;
                        // system("pause");
                        // system("cls");
                    }
                }
            }
            else {
                cout << "学号或密码错误，请重新输入！" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (choice == 2) {
            cout << "请输入管理员账号和密码：" << endl;
            string username, password;
            cin >> username >> password;
            
            if (admin_manager.login(username, password)) {
                system("cls");
                while (true) {
                    cout << "\t\t\t\t请选择操作>>>" << endl;
                    cout << "\t\t\t\t[1] 查看校友列表" << endl;
                    cout << "\t\t\t\t[2] 添加校友信息" << endl;
                    cout << "\t\t\t\t[3] 修改校友信息" << endl;
                    cout << "\t\t\t\t[4] 删除校友信息" << endl;
                    cout << "\t\t\t\t[5] 新闻功能" << endl;
                    cout << "\t\t\t\t[6] 问卷功能" << endl;
                    cout << "\t\t\t\t[7] 初始化系统校友数据" << endl;
                    cout << "\t\t\t\t[8] 退出登录" << endl;
                    cin >> choice;
                    if (choice == 1) {
                        vector<Alumni> alumni_list = alumni_manager.getAlumniList();
                        cout << "<<校友总数>> " << alumninum << endl;
                        for (int i = 0; i < alumni_list.size(); i++) {
                            cout << "姓名：" << alumni_list[i].getName() << endl;
                            cout << "学号：" << alumni_list[i].getStudentId() << endl;
                            cout << "性别：" << alumni_list[i].getGender() << endl;
                            cout << "出生日期：" << alumni_list[i].getBirthdate() << endl;
                            cout << "联系电话：" << alumni_list[i].getPhone() << endl;
                            cout << "电子邮件：" << alumni_list[i].getEmail() << endl;
                            cout << endl;
                        }
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 2) {
                        cout << "请输入新增校友的姓名、学号、密码、性别、出生日期、联系电话和电子邮件：" << endl;
                        string name, student_id, password, gender, birthdate, phone, email;
                        cin >> name >> student_id >> password >> gender >> birthdate >> phone >> email;
                        //Alumni alumni(name, student_id, password, gender, birthdate, phone, email);
                        Alumni alumni(name, student_id, password, gender, birthdate, phone, email,stuid);
                        alumni_manager.addAlumni(alumni);
                        stuid++;
                        // alumninum++;
                        cout << "添加成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if (choice == 3) {
                        cout << "请输入要修改的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        Alumni* alumni = alumni_manager.getAlumni(student_id);
                        if (alumni == NULL) {
                            cout << "校友不存在，请重新输入！" << endl;
                            system("pause");
                            system("cls");
                        }
                        else {
                            cout << "请输入新密码、联系电话和电子邮件：" << endl;
                            string new_password, phone, email;
                            cin >> new_password >> phone >> email;
                            alumni->setPassword(new_password);
                            alumni->setPhone(phone);
                            alumni->setEmail(email);
                            alumni_manager.modifyAlumni(*alumni);
                            cout << "修改成功！" << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else if (choice == 4) {
                        cout << "请输入要删除的校友学号：" << endl;
                        string student_id;
                        cin >> student_id;
                        alumni_manager.deleteAlumni(student_id);
                        stuid--;
                        //alumninum--;
                        cout << "校友信息删除成功！" << endl;
                        system("pause");
                        system("cls");
                    }
                    else if(choice == 5){
                        //if(admin_manager.Newsfun() == -1){
                        // system("pause");
                        // system("cls");
                        //goto here;
                           // cout << "test " << endl;
                       // }
                       system("cls");
                        admin_manager.Newsfun();//新闻功能
                    }
                    else if(choice == 6){
                    	system("cls");
                        admin_manager.questionfun();//问卷功能
                    }
                    else if(choice == 7){
                        system("cls");
                        if(InitFlag)
                        {
                            alumni_manager.Init_AlumniDate();//init
                            InitFlag = false;//只初始化一次
                        }else{
                            cout << "数据已初始化！" << endl;
                            system("pause");
                            system("cls");
                        }
                    }
                    else if (choice == 8) {
                        system("pause");
                        system("cls");
                        break;
                    }        
                    else {
                        cout << "输入有误，请重新输入！" << endl;
                        system("pause");
                        system("cls");
                    }
                }
            }
            else {
                cout << "管理员账号或密码错误，请重新输入！" << endl;
                system("pause");
                system("cls");
            }
        }
        else if (choice =3) {
            cout << "欢迎您的使用！" << endl;
            exit(0);
        }
        else {
            cout << "输入有误，请重新输入！" << endl;
            system("pause");
            system("cls");
        }
    }
}

// 逐字输出文字
void PrintCharByChar(string s, int delay) {
    for (int i = 0; i < s.size(); i++) {
        cout << s[i];
        cout.flush();
        this_thread::sleep_for(chrono::milliseconds(delay)); // 延时
    }
}

//初始化
void Init(void)
{
    string s = "欢迎使用GCU校友管理系统!";
    int delay = 100; // 每个字符输出后延时的时间（单位为毫秒）
    PrintCharByChar(s, delay);
    cout << endl;
}