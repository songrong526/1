#include "3-1.h"

int main()
{
    // 测试二叉树计算
    binary_tree t;
    t.create_tree("((21+1)*3)");
    cout << "计算结果: " << t.calculate() << endl;

    // 显示图形界面
    draw_meun();

    return 0;
}