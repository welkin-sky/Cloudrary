#ifndef CLOUDRARY_BASE_H
#define CLOUDRARY_BASE_H

#include <algorithm>
#include <initializer_list>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

typedef int64_t INT;

using nlohmann::json;
using std::string;
using std::vector;

class Bookmark {};

class BookmarkGroup {};

class Book {
 public:
  // Constructors and destructors

  Book() = default;
  explicit Book(const string &j);
  Book(const Book &b) = default;      // 复制构造
  Book(Book &&b) noexcept = default;  // 移动构造
  ~Book() = default;

  // Assignment operator overload

  Book &operator=(const Book &b) = default;
  Book &operator=(Book &&b) = default;

  // Getters
  [[nodiscard]] string getName() const { return _name; }
  [[nodiscard]] string getTitle() const { return _title; }  // 标题和名字区分
  [[nodiscard]] string getTextPath() const { return _textPath; }
  [[nodiscard]] string getCoverPath() const { return _coverPath; }  // 封面
  [[nodiscard]] string getAuthor() const { return _author; }
  [[nodiscard]] string getDescription() const { return _description; }

  // Setters

  void setName(string name) { _name = std::move(name); }
  void setTitle(string title) { _title = std::move(title); }  // 标题和名字区分
  void setTextPath(string textPath) { _textPath = std::move(textPath); }
  void setCoverPath(string coverPath) {
    _coverPath = std::move(coverPath);
  }  // 封面
  void setAuthor(string author) { _author = std::move(author); }
  void setDescription(string description) {
    _description = std::move(description);
  }

  BookmarkGroup &bookmarks();

  // To JSON format string
  static string serialize(const Book &b);
  static Book deserialize(const string &j);

 private:
  string _name;
  string _title;
  string _textPath;
  string _coverPath;
  string _author;
  string _description;
  BookmarkGroup _bookmarks;
};

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
  typedef vector<Book>::const_iterator const_iterator;
  typedef vector<Book>::reverse_iterator reverse_iterator;
  typedef vector<Book>::const_reverse_iterator const_reverse_iterator;

  iterator begin() { return _books.begin(); }
  iterator end() { return _books.end(); }
  reverse_iterator rbegin() { return _books.rbegin(); }
  reverse_iterator rend() { return _books.rend(); }

  [[nodiscard]] const_iterator begin() const { return cbegin(); }
  [[nodiscard]] const_iterator end() const { return cend(); }
  [[nodiscard]] const_reverse_iterator rbegin() const { return crbegin(); }
  [[nodiscard]] const_reverse_iterator rend() const { return crend(); }

  [[nodiscard]] const_iterator cbegin() const { return _books.cbegin(); }
  [[nodiscard]] const_iterator cend() const { return _books.cend(); }
  [[nodiscard]] const_reverse_iterator crbegin() const {
    return _books.crbegin();
  }
  [[nodiscard]] const_reverse_iterator crend() const { return _books.crend(); }

  [[nodiscard]] INT size() const { return static_cast<INT>(_books.size()); }

  void add(Book &book) { _books.push_back(book); }
  void remove(Book &book) { _books.erase(_books.begin() + find(book)); }
  vector<Book> &data() { return _books; }
  [[nodiscard]] vector<Book> data() const { return _books; }

  Book &at(INT index) { return _books[index]; }

  INT find(string name);  // 以名字做主键
  INT find(Book book);

  Book &search(string info);  // 模糊查找

  BookList subList(INT first, INT last);

  static string serialize(const BookList &b);
  static BookList deserialize(const string &j);

 private:
  vector<Book> _books;
};

class Library : BookList {  // tbc

 public:
  [[nodiscard]] string getName() const { return _name; };
  void setName(const string &name) { _name = name; };

  friend void from_json(const json &j, Library &l);
  friend void to_json(json &j, const Library &l);

 private:
  string _name;
};

class Base {
 public:
  Base() = default;
  Base(const string &j);

  typedef vector<Library>::iterator iterator;
  typedef vector<Library>::const_iterator const_iterator;
  typedef vector<Library>::reverse_iterator reverse_iterator;
  typedef vector<Library>::const_reverse_iterator const_reverse_iterator;

  iterator begin() { return _libs.begin(); }
  iterator end() { return _libs.end(); }
  reverse_iterator rbegin() { return _libs.rbegin(); }
  reverse_iterator rend() { return _libs.rend(); }

  [[nodiscard]] const_iterator begin() const { return cbegin(); }
  [[nodiscard]] const_iterator end() const { return cend(); }
  [[nodiscard]] const_reverse_iterator rbegin() const { return crbegin(); }
  [[nodiscard]] const_reverse_iterator rend() const { return crend(); }

  [[nodiscard]] const_iterator cbegin() const { return _libs.cbegin(); }
  [[nodiscard]] const_iterator cend() const { return _libs.cend(); }
  [[nodiscard]] const_reverse_iterator crbegin() const {
    return _libs.crbegin();
  }
  [[nodiscard]] const_reverse_iterator crend() const { return _libs.crend(); }

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

// Declarations

bool operator==(const Book &a, const Book &b);
bool operator!=(const Book &a, const Book &b);
bool operator<(const Book &a, const Book &b);
bool operator>(const Book &a, const Book &b);
bool operator==(BookList &a, BookList &b);
bool operator==(Library &a, Library &b);

void to_json(json &j, const Book &b);
void from_json(const json &j, Book &b);
void to_json(json &j, const BookList &b);
void from_json(const json &j, BookList &b);
void to_json(json &j, const Library &l);
void from_json(const json &j, Library &l);

#endif
