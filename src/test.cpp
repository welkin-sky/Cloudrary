#include <algorithm>
#include <fstream>
#include <iostream>
#include <utility>
#include "./include/base.h"

using std::cout, std::endl;

int test() {
    // 测试用例
    // Book类测试
    cout << "Book test case:\n\n";

    auto showBook = [](const Book & a, const char name[])
    { cout << name << ": " << a.getName() << '\t' << a.getTitle() << '\t' << a.getTextPath() << '\t'
           << a.getCoverPath() << '\t' << a.getAuthor() << '\t' << a.getDescription() << endl; }; // getter测试

    Book b1; //默认初始化
    Book b2 = {"b2", "Book 2", "C:\\text_path2",
               "C:\\cover_path2", "Author 2", "List init"};  // 列表初始化
    Book b3 = b2; // 复制赋值，为深拷贝
    Book b4;
    Book b5("{\"description\":\"Default initialization.\",\"author\":\"Author 5\",\"coverPath\":\"C:\\\\"
            "coverPath5\",\"name\":\"b5\",\"textPath\":\"C:\\\\textPath5\",\"title\":\"Book 5\"}"); //从JSON初始化

    showBook(b1, "b1"); // 默认赋值测试
    showBook(b2, "b2");
    showBook(b3, "b3");

    b4 = std::move(b3); // 移动赋值测试
    showBook(b4, "b4");
    b3 = std::move(b4); // 将b4的内存空间归还b3
    showBook(b5, "b5");
    endl(cout);

    b1.setName("b1").setTitle("Book 1").setTextPath("C:\\somepath")
            .setCoverPath("C:\\another").setAuthor("Author 1").setDescription("Default init"); //setter测试
    showBook(b1, "b1");

    b3.setName("b3").setTitle("Book 3"); // 检测深拷贝
    showBook(b2, "b2");
    showBook(b3, "b3"); // b1的值与b3不同

    cout << Book::serialize(b3) << endl; // 序列化测试
    string json1 = "{\"description\":\"Default initialization.\",\"author\":\"Author 4\",\"coverPath\":\"C:\\\\"
                   "coverPath4\",\"name\":\"b4\",\"textPath\":\"C:\\\\textPath4\",\"title\":\"Book 4\"}";
    b4 = Book::deserialize(json1); // 反序列化
    showBook(b4,"b4");


    // BookList测试
    // 目标是能够应用<algorithm>中的常用算法

    cout << "\nBookList test case: \n\n";
    BookList l1; // 默认初始化
    BookList l2 = {b1, b3}; // 列表初始化，可有任意多个
    Book arr1[2] = {b2, b3};
    BookList l3(arr1, 2); // 使用数组的初始化
    BookList l4 = l3; // 复制赋值
    BookList l5; // 移动赋值

    auto showBL = [](const BookList & bl, const char * name){
        cout << name << ": ";
        for (const auto& b : bl)
            cout << b.getName() << '\t';
        cout << endl; }; // BookList可以使用基于范围的for语法

    showBL(l1, "l1");
    showBL(l2, "l2");
    showBL(l3, "l3");
    showBL(l4, "l4");

    l5 = std::move(l4); // 移动赋值
    showBL(l5, "l5");
    l4 = std::move(l5); // 归还内存
    endl(cout);

    l1.add(b1).add(b2).add(b3).add(b4).add(b5); // 添加Book，参数为Book的引用
    l3.remove(b2); // 删除Book，参数为Book的引用
    showBL(l1, "l1");
    showBL(l3, "l3"); // 检测深拷贝是否有效
    showBL(l4, "l4");

    cout << "l2[0] :"<< l2[0].getName() << ", l2[1]: " << l2.at(1).getName() << endl; // 按索引访问

    cout << "Index of b1 in l2:" << l2.find(b1) << endl; // 按Book引用查找对应索引

    // 破坏性操作，建议不要直接对Library使用
    // 可以先复制到一个临时的Booklist再对临时变量操作
    l1.reverse(); //反转顺序
    cout << "Reverse l1:\n";
    showBL(l1, "l1");
    l1.sortBy(Book::CompareName); //按名字排序，同时也是默认的行为
    cout << "Sort by name:\n";
    showBL(l1, "l1");
    l1.sortBy(Book::CompareDescription); // 按描述排序
    cout << "Sort by description:\n";
    showBL(l1, "l1");
    // 当然，l1.add(b1).remove(b1).sortBy().reverse()都是可行的，这些方法都会返回*this

    cout << BookList::serialize(l1) << endl; // 序列化
    string json2 = "[{\"author\":\"Author 2\",\"coverPath\":\"C:\\\\cover_path2\",\"description\":\"List init\","
                   "\"name\":\"b2\",\"textPath\":\"C:\\\\text_path2\",\"title\":\"Book 2\"},{\"author\":\"Author 2\","
                   "\"coverPath\":\"C:\\\\cover_path2\",\"description\":\"List init\",\"name\":\"b3\","
                   "\"textPath\":\"C:\\\\text_path2\",\"title\":\"Book 3\"}]";
    l5 = BookList::deserialize(json2);
    showBL(l5, "l5");
    return 0;
}
