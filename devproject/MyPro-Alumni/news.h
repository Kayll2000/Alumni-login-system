#ifndef NEWS_H
#define NEWS_H
// "news.h"
#include <string>
#include <vector>
using namespace std;
#define FILENAME "./Debug/NewsData/NewsFILE.txt"    //保存为TXT文本格式
#define NEWSFILETOREAD "./Debug/NewsData/NewsToRead.txt"//保存新闻信息(读的文件)的路径
#define NALLDATA "./Debug/ALLNUMData/Nalldata.txt"//保存新闻总个数
static int newsnum;//记录新闻总条数  static  
static int readallnum = 0;//读的新闻总数

struct NDATA {//read
    int nid;//read新闻编号
    string ntitle;//read新闻标题
    string ncontent;//read新闻内容
    string nauthor;//read新闻作者
    string ndate;//read新闻日期
};

class News {//新闻类
public:
    News(int _id,string _title,string _content,string _date,string _author);
    int id;//新闻编号
    string title;//新闻标题
    string content;//新闻内容
    string author;//新闻作者
    string date;//新闻日期
    void News_display();//发布
};

class GM//admin
{
public:
    GM();
    int IDIsExist(int id);
    void Show_menu();       //显示新闻菜单
    void News_add();       //增加新闻信息
    void News_del();        //删除新闻信息
    void News_mod();        //修改新闻信息
    void News_find();       //查询指定编号的新闻信息
    void News_show();       //显示新闻内容
    void Save_Info();       //输出新闻信息到文件
    void Read_Data();       //读取新闻总数
    void Read_NumData();   //读取新闻总数
    void Save_Nalldata();   //保存新闻总数
    void Save_ToRead();     //保存新闻信息，方便读的格式保存
    void Init_NewsDate();   //初始化新闻数据
    vector<News*> *News_Array;
    ~GM();
};

#endif