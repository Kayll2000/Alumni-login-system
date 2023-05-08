#ifndef LOGIN_H
#define LOGIN_H

#include "news.h"
#include "question.h"
#include "global.h"
#include <string>
#include <vector>
using namespace std;

//"login.h"
//存放读取的数据
struct ADATA {//read 用来读取校友数据
    string _name;        //姓名
    string _student_id;  //学号
    string _password;    //密码
    string _gender;      //性别
    string _birthdate;   //出生日期
    string _phone;       //联系电话
    string _email;       //电子邮件
};
//校友信息
class Alumni {
private:
	int flagid;//id标识
    string name;        //姓名
    string student_id;  //学号
    string password;    //密码
    string gender;      //性别
    string birthdate;   //出生日期
    string phone;       //联系电话
    string email;       //电子邮件
public:
Alumni(string name, string student_id, string password, string gender, string birthdate, string phone, string email,int flagid);
    string getName();
    string getStudentId();
    string getPassword();
    string getGender();
    string getBirthdate();
    string getPhone();
    string getEmail();
    int getFlagid();

    void setPassword(string password);
    void setPhone(string phone);
    void setEmail(string email);
};

//管理员对校友信息的操作
class AlumniManager {
private:
    vector<Alumni> alumni_list;  //校友列表
public:
    AlumniManager(){};
    bool login(string student_id, string password);
    Alumni* getAlumni(string student_id);
    vector<Alumni> getAlumniList();
    void addAlumni(Alumni alumni);
    void modifyAlumni(Alumni alumni);
    void deleteAlumni(string student_id);
    void savealumniinfo();
    void SaveAlumni_ToRead();
    void Save_Nalldata();
    void Read_AlummiNumData();
    void Init_AlumniDate();
};

class Admin {
private:
    string username;  //管理员账号
    string password;  //管理员密码
public:
    Admin(string username, string password);
    string getUsername();
    bool login(string username, string password);
};

class AdminManager {
private:
    vector<Admin> admin_list;  //管理员列表
public:
    //AdminManager() {}
    GM gm;
    QArray var;//实例化问卷对象
    Answer vat;//实例化答案对象
    AdminManager():gm() {}
    void addAdmin(Admin admin);
    bool login(string username, string password);
    void Newsfun();
    void questionfun();
    void alumni_answerquestion(int temp,string name);
    void alumni_viewnews();
};

#endif