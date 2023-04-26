/****************************************************************************************************************************
* @function:校友管理系统问卷功能子函数
* @version:v1.0.1
* @author:chenjunlong
* @description:Implement the system's questionnaire editing, saving, and publishing functions, as well as answer collection.
* @github:https://github.com/Kayll2000/Alumni-login-system.git
* @date:2023.04.06
* @lmodauthor:chenjunlong
* @lmoddate:2023.04.26
*           FUCTION:
                    1、添加问卷
                    2、删除问卷
                    3、修改问卷
                    4、显示所有问卷
                    5、显示已发布问卷
                    6、发布问卷
                    7、清空已发布问卷
                    8、清空所有问卷
                    9、收集用户答案
                    10、问卷保存到指定文件夹，输出文本文件
            BUGFIX:
                    1、[2023.04.11]修复问卷信息保存的文件夹创建错误的bug。
                    2、[2023.04.24]修复查询1号问卷时内容为空，当有2个及以上问卷时，查询1号问卷显示的是后一个问卷内容的bug。
                    3、[2023.04.24]修复当使用新闻后再使用问卷功能时，即创建了Debug文件夹后，新闻功能将不会创建对应的文件夹QuestionData的bug。
                    4、[2023.04.26]修复读取问卷数据报错的bug。
            MODIFY: 1、[2023.04.06]添加查询指定id问卷功能
                    2、[2023.04.10]修改菜单界面函数
                    3、[2023.04.24]优化UI。
                    4、[2023.04.25]增加问卷信息统计（问卷总数以及每个问卷的选项数），将文件保存发送改为追加写入（ios::app）。
                    5、[2023.04.25]增加读取问卷信息的API。
                    6、[2023.04.26]完善问卷数据的读取的API并增加问卷数据初始化功能。

****************************************************************************************************************************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <io.h>
#include <ctype.h>
#include <typeinfo>
#include <direct.h>
#include "question.h"

using namespace std;

void showquestionmenu()
{
    cout << "********************************************************" << endl;
    cout << "******************《问卷发布子系统》*********************" << endl;
    cout << "******************[1] 增加问卷***************************" << endl;//ok
    cout << "******************[2] 删除问卷***************************" << endl;//ok
    cout << "******************[3] 修改问卷***************************" << endl;//ok
     cout << "******************[4] 查询问卷***************************" << endl;//ok
    cout << "******************[5] 显示所有问卷***********************" << endl;//ok
    cout << "******************[6] 显示已经发布的问卷*****************" << endl;//ok
    cout << "******************[7] 发布问卷***************************" << endl;//ok
    cout << "******************[8] 收集问卷答案***********************" << endl;//ok
    cout << "******************[9] 填写问卷***************************" << endl;//ok
    cout << "******************[10] 清空已经发布的问卷****************" << endl;//ok
    cout << "******************[11] 清空所有问卷**********************" << endl;//ok
    cout << "******************[12] 清屏******************************" << endl;//ok
    cout << "******************[13] 退出当前问卷菜单******************" << endl;//ok
    cout << "******************[14] 初始化系统问卷数据*****************" << endl;//ok
    cout << "********************************************************" << endl;
}

void readdata()//读取问卷信息——>>> 问卷总数 +  每条问卷对应的选项个数
{
    ifstream infile(QALLDATA);//读取问卷个数以及每个问卷对应的选项个数
    if (infile.good())
    {
        cout << "文件存在" << endl;
        if (!infile.is_open()) {
       cout << "Error opening file" << endl;
       return;
       }
       if (infile.is_open()) {
        int tnum;
        int questid = 1;//debug 参数
        string line; //保存读入的每一行
        getline(infile,line);//line 是 问卷总数
        qdatanum = stoi(line);//问卷总数，将string 转为 int
        //cout << "是否为数字："  << isdigit(qdatanum)  << endl;
        cout << "问卷总数："<< qdatanum << "条" << endl;
        while (infile >> tnum) {
           cout << "问卷[" << questid << "]" <<"的选项个数为" << tnum << endl; //debug
           itemnum.push_back(tnum);
           questid++;
       }
        infile.close();
        } else {
        cout << "Failed to open file for reading." << endl;
        return;
        }
    }
    else
    {
        cout << "文件不存在" << endl;
    }
}
void questioninit(QArray *var)
{
    readdata();
    ifstream infile(QUEFILETOREAD);
    if (infile.good())
    {
        cout << "文件存在" << endl;
        num = qdatanum;//init 问卷总数
        QDATA qdataarr[20];
        if (infile.is_open()) {
            string line;
            int i = 0;
        while (getline(infile, line)) {
        if (i >= qdatanum) {
            break; // 结构体数组已满，退出循环
        }
            //当问卷总数超过10时需要再加处理
        for(i;i<qdatanum;i++)//标题和id
            {
                int tt = stoi(line);
                /*debug*/
        #if DEBUG
            if (typeid(tt) == typeid(int)) {
                cout << "tt is an integer." << endl;
            } else {
                cout << "tt is not an integer." << endl;
            }
        #endif
                qdataarr[i].Qid = tt;
                getline(infile, line); // 读取下一行
                qdataarr[i].Qtitle = line;//line.substr();
                getline(infile, line); // 读取下一行
                for(int j = 0;j<itemnum[i];j++)//选项
                {
                    qdataarr[i].reitem.push_back(line); //= line;
                    getline(infile, line); // 读取下一行
                }
            }
        //Init
        for(int k = 0;k < qdatanum;k++)
        {
            cout << "qid :" << qdataarr[k].Qid << endl;
            cout << "qtitle:" << qdataarr[k].Qtitle << endl;
            var ->qarray[k].id = qdataarr[k].Qid;
            var->qarray[k].title = qdataarr[k].Qtitle;
            for(int w = 0;w<itemnum[k];w++)//选项
            {
                cout << "选项" <<  w+1 << "为：" << qdataarr[k].reitem[w] << endl;
                var->qarray[k].items.push_back(qdataarr[k].reitem[w]);// =  qdataarr[k].reitem[w];
            } 
        }
        cout << "数据初始化成功！" << endl;

    }
        infile.close();
        } else {
        cout << "Failed to open file for reading." << endl;
        return;
        }

    }else{
        cout << "文件不存在！" << endl;
    }
}
void showquestion(QArray *var)//显示所有问卷及选项
{
    //cout <<"qsize = " <<var->qsize << endl;//debug
    cout << endl;
    cout << "<<<所有问卷>>>" << endl;
    cout << "总问卷条数为：" << num << endl;
    if(num > 0)
    {
        // for(int i = 0;i<var->qsize;i++)
        for(int i = 0;i<num;i++)
        {
            cout << "问卷编号：" << var->qarray[i].id << endl;
            cout << "问卷标题：" << var->qarray[i].title << endl;
            for(int j=0;j<var->qarray[i].items.size();j++)
            {
                cout << "选项"<<j+1<<"："  << var->qarray[i].items[j] << endl;
            }
                cout << endl;
        }
    }else{
        cout << "问卷为空！" << endl;
    }
    system("pause");
    system("cls");
}
int IsidExit(QArray *var,int id)//问卷id是否存在  存在返回id  不存在返回-1
{
    for(int i=0;i<num;i++)
    {
        if(var->qarray[i].id == id)
        {
            //cout << "此问卷编号存在！" << endl;//debug
            return id;
        }else{
            //cout << "此问卷编号不存在！" << endl;
        }
    }
    return -1;
}

int Ispublish(QArray *var,int id)//问卷id是否已经发布  未发布返回id  已经发布返回-1
{
    if(IsidExit(var,id) != -1)//问卷id存在
    {
        for(int i=0;i<num;i++)
        {
            if(var->parray[i].id == id)
            {
                //cout << "问卷编号为"<< id <<"的问卷已经发布！" << endl;//debug
                return -1;
            }else{
                cout << "编号为"<<id<<"的问卷还未发布！"<< endl;
                return id;
            }
        }
    }else{
        cout << "该问卷编号不存在，请先创建！或者" << endl;
    }
    return -1;
}

void saveanswerinfo(Answer *vat ,QArray *var)
{
    cout << "正在保存答案信息···" << endl;
    if(_access("AnswerData", 0) == -1)
    {
        _mkdir("AnswerData");//创建文件夹
    }
    ofstream fo;
    fo.open(ANSWERFILE,ios::app);
    for(int i=0;i<answerflag;i++)
    {
        fo << "问卷ID[" << i+1 << "]" << endl
        << "问卷标题{" << var->parray[i].title << "}" << endl;
        for(int j=0;j<var->parray[i].items.size() ;j++)
        {
            fo << "选项[" << j+1 <<"]: " << var->parray[i].items[j] << endl;
        }

        fo << "问卷答案：" << vat->results[i] << endl;
        fo << endl;
    }
    fo.close();
    cout << "保存成功！" << endl;
}
void savequalldata(QArray *var)
{
    if(_access("Debug/QuestionALLNUMData", 0) == -1)
    {
        _mkdir("Debug/QuestionALLNUMData");//创建QuestionALLNUMData文件夹,保存问卷个数以及每个问卷的选项个数
    }
    ofstream qfo;
    qfo.open(QALLDATA,ios::out);//这里需要覆盖写入
    qfo << num << endl;//所有问卷数量
    for(int j = 0;j < num; ++j)
    {
        qfo << var->qarray[j].qunum << " ";
    }
    qfo.close();
    cout << "数据存储成功！" << endl;
}

void savetoread(QArray *var)
{
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/QuestionData", 0) == -1)
    {
        _mkdir("Debug/QuestionData");//创建AlumniData文件夹
    }
    ofstream _fo;
    _fo.open(QUEFILETOREAD,ios::app);
    for(int j = 0;j < num; ++j)
    {
        _fo << var ->qarray[j].id << endl
        <<var->qarray[j].title << endl;
            for(int k=0;k<var->qarray[j].items.size();k++)
            {
                _fo <<var->qarray[j].items[k] << endl;
            }
    }
    _fo.close();
    cout << "保存到读的信息保存成功！" << endl;
}

void saveinfo(QArray *var)
{
    cout <<"正在保存信息···"<< endl;
    if(_access("Debug", 0) == -1)
    {
        _mkdir("Debug");//创建Debug文件夹
    }
    if(_access("Debug/QuestionData", 0) == -1)
    {
        _mkdir("Debug/QuestionData");//创建AlumniData文件夹
    }
    ofstream fo;
    fo.open(QUEFILENAME,ios::app);//允许输出(写入操作)到流。
    for(int i = 0;i < num; ++i)
    {
        fo << "问卷ID[" << var ->qarray[i].id  << "]" << endl
        << "问卷标题{" << var->qarray[i].title << "}" << endl;
            for(int j=0;j<var->qarray[i].items.size();j++)
            {
                fo << "选项[" << j+1 <<"]: " << var->qarray[i].items[j] << endl;
            }
            fo << endl;
    }
    fo.close();
    savequalldata(var);
    savetoread(var);
    cout << "保存成功！" << endl;
}

void clearallquestion(QArray *var)//清空所有问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    num = 0;
    saveinfo(var);
}
void clearpublished(QArray *var)//清空已经发布的问卷
{
    for(int i = 0 ;i<var->qsize;i++)
    {
        var->parray[i] = var->parray[i+1];//把数组所有元素往前移动
    }
    var->qsize = 0;
    pnum = 0;
}

void publish(QArray *var)//发布问卷
{
    vector<string> batarr;
    string flag;
    int index;//发布的索引
    cout << "是否重新发布修改的问卷[Y/N]" << endl;
    while(true){
        cin >> flag;
        if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
        {
            break;
        }else{
            cout << "输入指令不存在！" << endl;
            cout << "请重新输入！" << endl;
        }
    }
    if(flag == "Y" ||flag == "y")
    {
        index = 0;//全部重新发布
        clearpublished(var);
    }else{
        index = pnum;//从全部问卷中发布未发布的问卷
    }
    for(int i = index;i<num;i++)
    {
    batarr =  var->qarray[i].items;
    var->parray[pnum].id = var->qarray[i].id;
    var->parray[pnum].title = var-> qarray[i].title;
    var->parray[pnum].items.swap(batarr);
    cout << "id:" << var->parray[pnum].id << endl;
    cout << "title: " << var-> parray[pnum].title << endl;
    pnum++;
    }
    cout << "问卷发布成功！" << endl;
    system("pause");
    system("cls");
}

void addquestion(QArray *var)
{
    string _Title,flag;
    string _items[MAXITEM];//最多容纳的选项 ——> MAXITEM 个  10个
    int _nums;//_id;
    char ch;
    while(true)
    {
        cin.get(ch);//吃掉回车\n
        var ->qarray[num].id = num+1;//编号从1开始
        cout << "输入问卷标题：" << endl;
        getline(cin,_Title);
        //cin >> _Title;                                            //修复当输入的字符串包含空格时，只接收到第一个空格前的字符的bug
        var->qarray[num].title = _Title;
        cout << "你想要输入几个选项：" << endl;
        cin >> _nums;
        while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
        {
        cin.clear();//清除cin的错误信息
        cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
        cout<<"请输入整数:";
        cin.ignore();//EOF位置，接收下一个cin函数
        cin>>_nums;
        }
        var->qarray[num].qunum = _nums;
        for(int i=0;i<_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> _items[i];
        var->qarray[num].items.push_back(_items[i]);
        }
        num++;
        var->qsize++;
        cout << "是否继续添加？[Y/N]" << endl;
        for(;;){
            cin >> flag;
            if(flag == "Y" ||flag == "y" || flag == "N" ||flag == "n")
            {
                break;
            }else{
                cout << "输入指令不存在！" << endl;
                cout << "请重新输入！" << endl;
            }
        }
        if(flag == "Y" ||flag == "y")
        {
            cout << "继续添加第[" << num + 1 << "]张问卷" << endl;
        }else{
            break;
        }
    }
    saveinfo(var);
    system("pause");
    system("cls");
}

void delquestion(QArray *var)//删除指定问卷
{
    //通过问卷编号删除，此时已经发布或者未发布的问卷都将被删除
    //cout << "删除test！" << endl;
    int del_id;
    cout << "输入你想要删除的问卷编号：" << endl;
    cin >> del_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号:";
    cin.ignore();//EOF位置，接收下一个cin函数
    cin>>del_id;
    }
    if(IsidExit(var,del_id) != -1)//id is exit（存在）
    {
        for(int i = del_id - 1;i<var->qsize;i++)
        {
            var->qarray[i] = var->qarray[i+1];//把数组所有元素往前移动
        }
        var->qsize--;
    }
    num = num - 1;
    cout << "问卷ID为[" << del_id << "]的问卷删除成功！" << endl;
    saveinfo(var);
    system("pause");
    system("cls");
}

void modquestion(QArray *var)
{
    //通过问卷id修改问卷，此时无论发布的还是未发布的问卷都将被修改

    string mod_Title;
    string mod_items[10];//最多容纳的选项 ——> 10个
    int mod_nums,mod_id;
    cout << "输入需要修改的问卷编号：" << endl;
    cin >> mod_id;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号: " << endl;;
    cin.ignore();//EOF位置，接收下一个cin函数
    cin >> mod_id;
    }

    if(IsidExit(var,mod_id) != -1)//问卷id存在
    {
        cout << "输入修改后的标题：" << endl;
        cin >> mod_Title;
        var->qarray[mod_id-1].title = mod_Title;
        cout << "输入修改后的选项个数：" << endl;
        cin >> mod_nums;
        var->qarray[mod_id-1].items.clear();//清空原有的，不会回收空间，但size变成0，后续可能有bug
        for(int i=0;i<mod_nums;i++)
        {
        cout << "输入选项"<<i+1<<"：" << endl;
        cin >> mod_items[i];
        var->qarray[mod_id-1].items.push_back(mod_items[i]);
        //var->parray[]
        }
        cout << "修改成功！" << endl;
    }else{
        cout << "问卷id不存在！修改失败！" << endl;
    }
    saveinfo(var);
    system("pause");
    system("cls");
}

void showpublish(QArray *var)
{
    cout << endl;
    if(pnum != 0)
    {
    cout << "《已经发布的问卷》" << endl;
    for(int i = 0;i<pnum;i++)
    {
        cout << "问卷编号[" << var->parray[i].id << "]" << endl;
        cout << "问卷标题[" << var->parray[i].title << "]" << endl;
        for(int j=0;j<var->parray[i].items.size();j++)
        {
            cout << "选项["<<j+1<<"]："  << var->parray[i].items[j] << endl;
        }
        cout << endl;
    }
    }else{
        cout << "还没有发布问卷！" << endl;
    }
    system("pause");
    system("cls");
}
void useranswer(QArray *var,Answer *vat)//用户回答问卷
{
    int myselect,itemsize;
    bool writeflag = false;

    for(int i = answerflag;i<pnum;i++)
    {
        cout << "问卷编号[" << var->parray[i].id << "]" << endl;
        cout << "问卷标题：" << var->parray[i].title << endl;
        for(int j=0;j<var->parray[i].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->parray[i].items[j] << endl;
            itemsize = var->parray[i].items.size();
        }
        cout << "请选择你的答案 >>> " << endl;
        while(true)
        {
            cin >> myselect;
            if(myselect>0 && myselect <= itemsize)
            {
                break;
            }else{
                cout << "选项不存在！" << endl;
            }
        }
        // vat->answerarr[i].results.push_back(myselect);
        vat->results.push_back(myselect);
        vat->asize++;
        answerflag++;
        writeflag = true;
        cout << "写入成功！" << endl;
    }
    if(writeflag != true)
    {
        cout << "问卷已经全部填写完毕！或者 问卷未发布！" << endl;
    }
    saveanswerinfo(vat,var);//保存用户答案
        system("pause");
        system("cls");

}
void collectanswer(Answer *vat)
{
    //cout << "收集问卷答案test!" << endl;
    cout << "问卷填写数量：" << vat->asize << endl;
    for(int i = 0;i < answerflag;i++)
    {
        cout <<"id["<< i+1 <<"] 的问卷答案为：" << vat->results[i] << endl;
    }
    system("pause");
    system("cls");
}

void searchquestion(QArray *var)//需要测试
{
    int fid;
    cout << "输入您想查询的问卷id：" << endl;
    cin >> fid;
    while(cin.fail())//解决 当输入的id非数字时导致程序奔溃
    {
    cin.clear();//清除cin的错误信息
    cin.ignore();//忽略掉缓冲区的内容,置于EOF位置
    cout<<"请输入正确的问卷编号: " << endl;;
    cin.ignore();//EOF位置，接收下一个cin函数
    cin >> fid;
    }
    if(IsidExit(var,fid) != -1)//问卷id存在
    {
        cout << "问卷id[" << fid << "]的问卷信息如下：" << endl;
        cout << "问卷编号：[" << fid << "]" << endl;
        cout << "问卷标题：" << var->qarray[fid-1].title << endl;
        for(int j=0;j<var->qarray[fid-1].items.size();j++)
        {
            cout << "选项"<<j+1<<"："  << var->qarray[fid-1].items[j] << endl;
        }
        cout << endl;
    }else{
        cout << "问卷不存在！" << endl;
    }
    system("pause");
    system("cls");
}
void test()//测试API
{
    cout << "功能未开发！" << endl;
    cout << "详情联系QQ2825363541" << endl;
    system("pause");
    system("cls");
}
