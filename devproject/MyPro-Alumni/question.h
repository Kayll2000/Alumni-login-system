#ifndef QUESTION_H
#define QUESTION_H
// "news.h"
#include <string>
#include <vector>
#include "global.h"

using namespace std;

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