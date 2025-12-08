#ifndef STACK_AND_LIST_H
#define STACK_AND_LIST_H

#include "easyx.h"
#include <iostream>
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

class binary_tree
{
private:
    struct node
    {
        int data = 0;
        node* lchild = NULL;
        node* rchild = NULL;
        node* parent = NULL;
    };
    node* root;

public:
    binary_tree();
    ~binary_tree();
    void create_tree(string s);
    float calculate();
    node* get_root() { return root; }
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
                if (p->parent != NULL)
                   p = p->parent;
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
                if (p->parent != NULL)
                    p = p->parent;
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
                    p = p->parent;
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
                    p = p->parent;
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

float binary_tree::calculate()
{
    float a, b;
    if (root->lchild != NULL && root->rchild != NULL)
    {
        binary_tree t1, t2;
        t1.root = root->lchild;
        t2.root = root->rchild;
        a = t1.calculate();
        b = t2.calculate();
        switch (root->data)
        {
        case -1:
            return a + b;
        case -2:
            return a - b;
        case -3:
            return a * b;
        case -4:
            if (b != 0) return a / b;
            else return 0;
        default:
            return 0;
        }
    }
    else
        return root->data;
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

    // 绘制初始界面
    outtextxy(10, 10, _T("计算表达式: "));
    rectangle(100, 200, 500, 300);
    outtextxy(220, 220, _T("点击这里输入表达式"));
    outtextxy(100, 100, _T("答案:"));
    outtextxy(10, 350, _T("点击左上角关闭窗口"));

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
                        wstring_convert<codecvt_utf8<wchar_t>> converter;
                        string s = converter.to_bytes(str);

                        // 创建树并计算
                        t.create_tree(s);
                        float result = t.calculate();

                        // 清屏并重绘
                        cleardevice();
                        outtextxy(10, 10, _T("计算表达式: "));
                        rectangle(100, 200, 500, 300);
                        outtextxy(220, 220, _T("点击这里输入表达式"));
                        outtextxy(100, 100, _T("答案:"));
                        outtextxy(10, 350, _T("点击左上角关闭窗口"));

                        // 显示表达式和结果
                        outtextxy(10, 50, str);

                        TCHAR resultStr[50];
                        _stprintf_s(resultStr, _T("%.2f"), result);
                        outtextxy(550, 100, resultStr);
                    }
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