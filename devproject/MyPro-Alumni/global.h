#ifndef GLOBAL_H
#define GLOBAL_H
using namespace std;
#include <vector>

#define ALUMNIFILE "./Debug/AlumniData/AlumniFILE.txt"    //保存为TXT文本格式
#define ALUMNISAVETOREAD "./Debug/AlumniData/AlumniSaveToreadFILE.txt"    //保存以便读取的文件
#define AALLDATA "./Debug/ALLNUMData/Aalldata.txt"//保存校友总个数
#define FILENAME "./Debug/NewsData/NewsFILE.txt"    //保存为TXT文本格式
#define NEWS_PUBLISHFILENAME "./Debug/NewsData/NewsPublishFILE.txt"    //已经发布的新闻
#define NEWSFILETOREAD "./Debug/NewsData/NewsToRead.txt"//保存新闻信息(读的文件)的路径
#define NALLDATA "./Debug/ALLNUMData/Nalldata.txt"//保存新闻总个数
#define MAX 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define DEBUG false//true
#define QUEFILENAME "./Debug/QuestionData/QuestionFILE.txt"//保存问卷信息的路径
#define QUEFILETOREAD "./Debug/QuestionData/QuestionToRead.txt"//保存问卷信息(读的文件)的路径
#define ANSWERFILE "./Debug/AnswerData/AnswerFILE.txt"//保存问卷答案路径
#define QALLDATA "./Debug/ALLNUMData/Qalldata.txt"//保存问卷个数以及选项个数路径

extern int alumninum;//校友总数 extern全局，因为main需要使用。
extern int alumninumread;//记录读取校友总条数  static 
extern bool InitFlag;//校友初始化flag
extern bool QuestionInitFlag;//问卷初始化flag
extern int newsnum;//记录新闻总条数  static  
extern int readallnum;//读的新闻总数
extern int publishnum;//以及发布的新闻条数
extern int num;// 记录所有问卷的数量
extern int pnum;//记录已经发布问卷的数量
extern int answerflag;//记录已经填写的问卷个数
extern int qdatanum;//记录问卷总数，读取问卷时的总数
extern vector<int> itemnum;//记录每个问卷的选项数

#endif
