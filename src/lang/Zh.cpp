#include "Zh.h"

Zh::Zh(QObject *parent)
    : Lang{parent}
{
    setObjectName("Zh");
    search("搜索");
    dark_mode("夜间模式");
    settings("设置");
    book_already_input("已导入书籍");
    home("主页");
}
