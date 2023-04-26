#ifndef QUESTION_H
#define QUESTION_H
// "news.h"
#include <string>
#include <vector>
#define MAX 100 //最多的问卷数
#define MAXITEM 10//最多的选项个数
#define DEBUG false//true
#define QUEFILENAME "./Debug/QuestionData/QuestionFILE.txt"//保存问卷信息的路径
#define QUEFILETOREAD "./Debug/QuestionData/QuestionToRead.txt"//保存问卷信息(读的文件)的路径
#define ANSWERFILE "./Debug/AnswerData/AnswerFILE.txt"//保存问卷答案路径
#define QALLDATA "./Debug/ALLNUMData/Qalldata.txt"//保存问卷个数以及选项个数路径

using namespace std;
//全局变量
static int num = 0;// 记录所有问卷的数量
static int pnum = 0;//记录已经发布问卷的数量
static int answerflag = 0;//记录已经填写的问卷个数
static int qdatanum = 0;//记录问卷总数，读取问卷时的总数
static vector<int> itemnum{};//记录每个问卷的选项数

struct Questionnaire
{
    int id;
    int qunum;//问卷选项数
    string title;         // 问卷标题
    vector<string> items; // 问卷选项
    //vector<int> results;  // 选项结果
};

struct QArray
{
    Questionnaire qarray[MAX];//所有问卷
    Questionnaire parray[MAX];//已发布问卷
    int qsize;
};

struct Answer
{
    Questionnaire answerarr[MAX];//答案
    vector<int> results;  // 选项结果
    int asize;
    // string content;//填写问卷答案内容
};

struct QDATA {//read
    int Qid;
    string Qtitle;
    vector<string> reitem;
};

extern void showquestionmenu();
extern void showquestion(QArray *var);
extern int IsidExit(QArray *var,int id);
extern int Ispublish(QArray *var,int id);
extern void saveanswerinfo(Answer *vat ,QArray *var);
extern void saveinfo(QArray *var);
extern void clearallquestion(QArray *var);
extern void clearpublished(QArray *var);
extern void publish(QArray *var);
extern void addquestion(QArray *var);
extern void delquestion(QArray *var);
extern void modquestion(QArray *var);
extern void showpublish(QArray *var);
extern void useranswer(QArray *var,Answer *vat);
extern void collectanswer(Answer *vat);
extern void searchquestion(QArray *var);
extern  void readdata();
extern void questioninit(QArray *var);
extern void test();

#endif