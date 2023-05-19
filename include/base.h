#ifndef CLOUDRARY_BASE_H
#define CLOUDRARY_BASE_H

#include <algorithm>
#include <initializer_list>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

typedef int64_t INT;

using nlohmann::json;
using std::iterator_traits;
using std::string;
using std::vector;

class Bookmark {};

class BookmarkGroup {};

class Book {
 public:
  Book() = default;
  Book(const string &j);
  Book(const Book &b) = default;      // 复制构造
  Book(Book &&b) noexcept = default;  // 移动构造
  ~Book() = default;

  Book &operator=(const Book &b) = default;
  Book &operator=(Book &&b) = default;

  [[nodiscard]] string getName() const { return _name; }
  [[nodiscard]] string getTitle() const { return _title; }  // 标题和名字区分
  [[nodiscard]] string getTextPath() const { return _textPath; }
  [[nodiscard]] string getCoverPath() const { return _coverPath; }  // 封面
  [[nodiscard]] string getAuthor() const { return _author; }
  [[nodiscard]] string getDescription() const { return _description; }

  void setName(string name) { name = _name; }
  void setTitle(string title) { title = _title; }  // 标题和名字区分
  void setTextPath(string textPath) { textPath = _textPath; }
  void setCoverPath(string coverPath) { coverPath = _coverPath; }  // 封面
  void setAuthor(string author) { author = _author; }
  void setDescription(string description) { description = _description; }

  BookmarkGroup &bookmarks();

  friend void from_json(const json &j, Book &b);//大半夜尝试半天，这函数不能用static，得friend
  friend void to_json(json &j, const Book &b);

 private:
  string _name;
  string _title;
  string _textPath;
  string _coverPath;
  string _author;
  string _description;
  BookmarkGroup _bookmarks;
};

bool operator==(const Book &a, const Book &b) {
  return a.getTextPath() == b.getTextPath();
}

// 暂时认为路径相同即相同
bool operator!=(const Book &a, const Book &b) { return !(a == b); }

bool operator<(const Book &a, const Book &b) {
  return a.getName() < b.getName();
}

bool operator>(const Book &a, const Book &b) { return b < a; }

class BookList {  // 无名的书单，用于临时对象（如筛选结果）

 public:
  BookList() = default;

  BookList(std::initializer_list<Book> args) : _books(args){};  // 可变参数
  BookList(Book *arr, INT len) : _books(arr, arr + len){};
  BookList(const string &j);

  BookList(const BookList &lib) = default;  // 复制构造
  BookList(BookList &&lib) = default;       // 移动构造
  ~BookList() = default;

  Book &operator[](INT index) { return this->at(index); }
  BookList &operator=(const BookList &bl) = default;
  BookList &operator=(BookList &&bl) = default;

  typedef vector<Book>::iterator iterator;

  iterator begin() { return _books.begin(); }
  iterator end() { return _books.end(); }

  [[nodiscard]] INT size() const { return static_cast<INT>(_books.size()); }

  void add(Book &book) { _books.push_back(book); }
  void remove(Book &book) { _books.erase(_books.begin() + find(book)); }

  Book &at(INT index) { return _books[index]; }

  INT find(string name);  // 以名字做主键
  INT find(Book book);

  Book &search(string info);  // 模糊查找

  //    Deprecated
  //    static string serialize(BookList &b);
  //    static BookList deserialize(string j);
  friend void to_json(json& j, const BookList& b);
  friend void from_json(const json& j, BookList& b);
 private:
  vector<Book> _books;
};

bool operator==(BookList &a, BookList &b) {  // 顺序相同
  if (a.size() != b.size()) return false;

  for (int i = 0; i < a.size(); i++) {
    if ((a.at(i)) != (b.at(i))) return false;
  }
  return true;
}

class Library : BookList {  // tbc

 public:
  string getName() { return _name; };
  void setName(const string &name) { _name = name; };

  friend void from_json(const json& j, Library& l);
  friend void to_json(json& j, const Library& l);

 private:
  string _name;
};

class Base {
 public:
  Base() = default;
  Base(const string &j);

  typedef vector<Library>::iterator iterator;

  iterator begin() { return _libs.begin(); }
  iterator end() { return _libs.end(); }

  void add(Library &lib) { _libs.push_back(lib); }  // 我错了 是引用
  void remove(int index) { _libs.erase(_libs.begin() + index); }

  void swap(INT a, INT b) {
    std::swap(_libs[a], _libs[b]);
  }  // 交换两个Library的位置

  static string serialize(Base b);
  static Base &deserialize(string j);

 private:
  vector<Library> _libs;
};

class Process {
 public:
  void addBook();
  void deleteBook();
  void searchBook();
  void downloadBook();
  void deepDeleteBook();
  void sortBook();
  void editBook();
  void showBook();

};

#endif
