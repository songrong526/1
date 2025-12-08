#ifndef STACK_AND_LIST_H
#define STACK_AND_LIST_H

#include "easyx.h"
#include <iostream>
#include <fstream>
#include <graphics.h>
#include <cmath>
#include <windows.h>
#include <conio.h>
#include <locale>
#include <cstdlib>
#include <codecvt>
#include <string> 
#include <sstream>

using namespace std;
struct complex_number
{
    float real=0;
    float imag=0;
};
class binary_tree
{
private:
    struct node
    {
        float data = 0;
        float complex_data = 0;
        node* lchild = NULL;
        node* rchild = NULL;
        node* parent = NULL;
    };
    node* root;

public:
    binary_tree();
    ~binary_tree();
    void create_tree(string s);
    complex_number* calculate();
    node* get_root() { return root; }
    float return_complex_data();
    float return_data();
};

binary_tree::binary_tree()
{
    root = NULL;
}

binary_tree::~binary_tree()
{
}

void binary_tree::create_tree(string s)
{
    root = new node;
    node* p = root;
    int l = s.length();
    for (int i = 0; i < l; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            p->data = (s[i] - '0') + p->data * 10;
        }
        else if (s[i] == 'i')
        {
            p->complex_data = p->data;
			p->data = 0;
        }
        else if (s[i] == '(')
        {
            p->lchild = new node;
            p->lchild->parent = p;
            p = p->lchild;
        }
        else if (s[i] == ')')
        {
            if (p->parent != NULL)
                p = p->parent; 
        }
        else
        {
            switch (s[i])
            {
            case '+':
                if (p->parent != NULL && p->parent->data == 0)
                    p = p->parent;
                else if (p->parent != NULL)
                {
                    while (p->parent != NULL && p->parent->data != 0)
                    {
                        p = p->parent;
                    }
                }
                else
                {
                    node* newroot = new node;
                    newroot->lchild = root;
                    root->parent = newroot;
                    root = newroot;
					p = root;
                }
                p->data = -1;
                p->rchild = new node;
                p->rchild->parent = p;
                p = p->rchild;
                break;
            case '-':
                if (p->parent != NULL&&p->parent->data==0)
                    p = p->parent;
                else if (p->parent != NULL)
                {
                    while (p->parent != NULL && p->parent->data != 0)
                    {
                        p = p->parent;
                    }
                }
                else
                {
                    node* newroot = new node;
                    newroot->lchild = root;
                    root->parent = newroot;
                    root = newroot;
                    p = root;
                }
                p->data = -2;
                p->rchild = new node;
                p->rchild->parent = p;
                p = p->rchild;
                break;
            case '*':
                if (p->parent != NULL)
                {
                    node* newroot = new node;
					newroot->parent = p->parent;
					newroot->lchild = p;
					p->parent->rchild = newroot;
					p->parent = newroot;
					p = newroot;
                }
                else
                {
                    node* newroot = new node;
                    newroot->lchild = root;
                    root->parent = newroot;
                    root = newroot;
                    p = root;
                }
                p->data = -3;
                p->rchild = new node;
                p->rchild->parent = p;
                p = p->rchild;
                break;
            case '/':
                if (p->parent != NULL)
                {
                    if (p->parent != NULL)
                    {
                        node* newroot = new node;
                        newroot->parent = p->parent;
                        newroot->lchild = p;
                        p->parent->rchild = newroot;
                        p->parent = newroot;
                        p = newroot;
                    }
                }
                else
                {
                    node* newroot = new node;
                    newroot->lchild = root;
                    root->parent = newroot;
                    root = newroot;
                    p = root;
                }
                p->data = -4;
                p->rchild = new node;
                p->rchild->parent = p;
                p = p->rchild;
                break;
            default:
                break;
            }
        }
    }
}

complex_number* binary_tree::calculate()
{
    float a=0, b=0;
	complex_number* lresult = new complex_number();
    complex_number* rresult = new complex_number();
    complex_number* result = new complex_number();
    if (root->lchild == NULL && root->rchild == NULL && root->complex_data == 0)
    {
		result->real = root->data;
        result->imag = 0;
		return result;
    }
    else if (root->lchild == NULL && root->rchild == NULL && root->data == 0)
    {
		result->real = 0;
		result->imag = root->complex_data;
		return result;
    }
    else
    {
        float a = 0, b = 0,ca=0,cb=0;
		if (root->lchild != NULL)
        {
            binary_tree lt;
            lt.root = root->lchild;
            lresult= lt.calculate();
		}
        if (root->rchild != NULL)
        {
            binary_tree rt;
            rt.root = root->rchild;
            rresult= rt.calculate();
        }
        switch ((int)root->data)
        {
        case -1:
			a = lresult->real;
			ca = lresult->imag;
			b = rresult->real;
			cb = rresult->imag;
			result->real = a + b;
			result->imag = ca + cb;
            return result;
            break;
        case -2:
            a = lresult->real;
            ca = lresult->imag;
            b = rresult->real;
            cb = rresult->imag;
			result->imag = ca - cb;
			result->real = a - b;
            return result;
            break;
        case -3:
            a = lresult->real;
            ca = lresult->imag;
            b = rresult->real;
            cb = rresult->imag;
			result->imag = a * cb + b * ca;
			result->real = a * b - cb * ca;
            return result;
            break;
        case -4:
            {
                a = lresult->real;
                ca = lresult->imag;
                b = rresult->real;
                cb = rresult->imag;
                float denominator = b * b + cb * cb;
				result->real = (a * b + ca * cb) / denominator;
				result->imag = (ca * b - a * cb) / denominator;
                return result;
            }
            break;
        default:
            return 0;
            break;
		}
	}
    
}
float binary_tree::return_data()
{
	return root->data;
}
float binary_tree::return_complex_data()
{
    return root->complex_data;
}
string random_expression()
{
    string expr;
    int a, b;
    int n;
    char op;

    srand(time(NULL));  // 添加随机种子

    n = -(rand() % 4 + 1);
    a = rand() % 10 + 1;
    b = rand() % 10 + 1;

    switch (n)
    {
    case -1:
        op = '+';
        break;
    case -2:
        op = '-';
        break;
    case -3:
        op = '*';
        break;
    case -4:
        op = '/';
        break;
    default:
        op = '+';
        break;
    }

    expr = to_string(a) + op + to_string(b);
    return expr;
}
string file_expression()
{
    ifstream n("expression.txt", ios::in);
    if (!n.is_open())
    {
        cout << "无法打开文件" << endl;
        return "";
    }

    string expr;
    if (getline(n, expr))  // 只读取第一行
    {
        n.close();
        return expr;
    }
    else
    {
        cout << "文件为空或读取失败" << endl;
        n.close();
        return "";
    }
}
string TCHARToString(const TCHAR* tstr)//改变编码
{
    string result;

#ifdef _UNICODE
    // Unicode 版本
    int len = WideCharToMultiByte(CP_ACP, 0, tstr, -1, NULL, 0, NULL, NULL);
    if (len > 0)
    {
        char* buffer = new char[len];
        WideCharToMultiByte(CP_ACP, 0, tstr, -1, buffer, len, NULL, NULL);
        result = buffer;
        delete[] buffer;
    }
#else
    // 多字节版本
    result = tstr;
#endif

    return result;
}
// 修改现有的字符串转换函数或创建新的转换函数
wstring StringToWString(const string& str)
{
#ifdef _UNICODE
    // 如果使用Unicode
    int len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
    wchar_t* wstr = new wchar_t[len];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, wstr, len);
    wstring result(wstr);
    delete[] wstr;
    return result;
#else
    // 如果使用多字节
    return wstring(str.begin(), str.end());
#endif
}
void draw_meun()
{
    binary_tree t;

    // 初始化图形窗口
    initgraph(600, 400);
    setbkcolor(WHITE);
    cleardevice();
    settextcolor(BLACK);
    setlinecolor(BLACK);

    // 设置字体（重要！）
    LOGFONT f;
    gettextstyle(&f);
    _tcscpy_s(f.lfFaceName, _T("宋体"));  // 设置中文字体
    f.lfHeight = 15;                      // 设置字体高度
    f.lfCharSet = DEFAULT_CHARSET;        // 使用默认字符集
    settextstyle(&f);

    // 绘制初始界面
    outtextxy(10, 10, _T("计算表达式: "));
    rectangle(100, 200, 500, 300);
    outtextxy(220, 220, _T("点击这里输入表达式"));
    outtextxy(100, 100, _T("答案:"));
    outtextxy(10, 350, _T("点击左上角关闭窗口"));
    rectangle(0, 0, 50, 50);
    rectangle(550, 0, 600, 50);
    outtextxy(10, 10, _T("退出"));
    outtextxy(560, 10, _T("随机"));
    rectangle(100, 320, 500, 380);
    outtextxy(220, 340, _T("从文件读取表达式"));

    // 进入消息循环
    ExMessage msg;
    while (true)
    {
        // 获取消息
        if (peekmessage(&msg, EX_MOUSE))
        {
            if (msg.message == WM_LBUTTONDOWN)
            {
                if (msg.x > 100 && msg.x < 500 && msg.y > 200 && msg.y < 300)
                {
                    // 输入框
                    TCHAR str[100] = { 0 };
                    if (InputBox(str, 100, _T("输入表达式"), _T("请输入数学表达式"), _T("(21+1)*3"), 300, 200, false))
                    {
                        // 转换字符串
                        string s = TCHARToString(str);

                        // 创建树并计算
                        t.create_tree(s);
                        complex_number* result = t.calculate();

                        // 清屏并重绘
                        cleardevice();

                        // 重新设置字体（每次清屏后需要重置）
                        settextstyle(&f);

                        outtextxy(10, 10, _T("计算表达式: "));
                        rectangle(100, 200, 500, 300);
                        outtextxy(220, 220, _T("点击这里输入表达式"));
                        outtextxy(100, 100, _T("答案:"));
                        outtextxy(10, 350, _T("点击左上角关闭窗口"));
                        rectangle(0, 0, 50, 50);
                        rectangle(550, 0, 600, 50);
                        outtextxy(10, 10, _T("退出"));
                        outtextxy(560, 10, _T("随机"));
                        rectangle(100, 320, 500, 380);
                        outtextxy(220, 340, _T("从文件读取表达式"));

                        // 显示表达式（直接使用转换后的TCHAR字符串）
                        outtextxy(10, 50, str);

                        // 显示结果
                        TCHAR resultStr[100];
                        if (fabs(result->imag) < 1e-6)  // 虚部为0
                        {
                            _stprintf_s(resultStr, _T("%.2f"), result->real);
                        }
                        else if (result->imag > 0)
                        {
                            _stprintf_s(resultStr, _T("%.2f+%.2fi"), result->real, result->imag);
                        }
                        else  // result->imag < 0
                        {
                            _stprintf_s(resultStr, _T("%.2f%.2fi"), result->real, result->imag);
                        }
                        outtextxy(500, 100, resultStr);
                        delete result;
                    }
                }
                else if (msg.x > 550 && msg.x < 600 && msg.y > 0 && msg.y < 50)
                {
                    // 随机表达式
                    string s = random_expression();
                    t.create_tree(s);
                    complex_number* result = t.calculate();

                    // 清屏并重绘
                    cleardevice();
                    settextstyle(&f);

                    outtextxy(10, 10, _T("计算表达式: "));
                    rectangle(100, 200, 500, 300);
                    outtextxy(220, 220, _T("点击这里输入表达式"));
                    outtextxy(100, 100, _T("答案:"));
                    outtextxy(10, 350, _T("点击左上角关闭窗口"));
                    rectangle(0, 0, 50, 50);
                    rectangle(550, 0, 600, 50);
                    outtextxy(10, 10, _T("退出"));
                    outtextxy(560, 10, _T("随机"));
                    rectangle(100, 320, 500, 380);
                    outtextxy(220, 340, _T("从文件读取表达式"));

                    TCHAR str[100];
                    // 正确转换string到TCHAR
#ifdef _UNICODE
                    MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, str, 100);
#else
                    strcpy_s(str, s.c_str());
#endif
                    outtextxy(10, 50, str);

                    // 显示结果
                    TCHAR resultStr[100];
                    if (fabs(result->imag) < 1e-6)  // 虚部为0
                    {
                        _stprintf_s(resultStr, _T("%.2f"), result->real);
                    }
                    else if (result->imag > 0)
                    {
                        _stprintf_s(resultStr, _T("%.2f+%.2fi"), result->real, result->imag);
                    }
                    else  // result->imag < 0
                    {
                        _stprintf_s(resultStr, _T("%.2f%.2fi"), result->real, result->imag);
                    }
                    outtextxy(500, 100, resultStr);
                    delete result;
                }
                else if (msg.x > 100 && msg.x < 500 && msg.y > 320 && msg.y < 380)
                {
                    // 从文件读取表达式
                    string s = file_expression();
                    if (s.empty())  // 检查是否成功读取
                    {
                        continue;
                    }

                    t.create_tree(s);
                    complex_number* result = t.calculate();

                    // 清屏并重绘
                    cleardevice();
                    settextstyle(&f);

                    outtextxy(10, 10, _T("计算表达式: "));
                    rectangle(100, 200, 500, 300);
                    outtextxy(220, 220, _T("点击这里输入表达式"));
                    outtextxy(100, 100, _T("答案:"));
                    outtextxy(10, 350, _T("点击左上角关闭窗口"));
                    rectangle(0, 0, 50, 50);
                    rectangle(550, 0, 600, 50);
                    outtextxy(10, 10, _T("退出"));
                    outtextxy(560, 10, _T("随机"));
                    rectangle(100, 320, 500, 380);
                    outtextxy(220, 340, _T("从文件读取表达式"));

                    TCHAR str[100];
                    // 正确转换string到TCHAR
#ifdef _UNICODE
                    MultiByteToWideChar(CP_ACP, 0, s.c_str(), -1, str, 100);
#else
                    strcpy_s(str, s.c_str());
#endif
                    outtextxy(10, 50, str);

                    // 显示结果
                    TCHAR resultStr[100];
                    if (fabs(result->imag) < 1e-6)  // 虚部为0
                    {
                        _stprintf_s(resultStr, _T("%.2f"), result->real);
                    }
                    else if (result->imag > 0)
                    {
                        _stprintf_s(resultStr, _T("%.2f+%.2fi"), result->real, result->imag);
                    }
                    else  // result->imag < 0
                    {
                        _stprintf_s(resultStr, _T("%.2f%.2fi"), result->real, result->imag);
                    }
                    outtextxy(500, 100, resultStr);
                    delete result;
                }
                else if (msg.x < 50 && msg.y < 50)
                {
                    break; // 退出循环
                }
            }
        }

        // 短暂延迟，减少CPU占用
        Sleep(10);
    }

    // 关闭图形窗口
    closegraph();
}

#endif