#ifndef CLOUDRARY_BASE_H
#define CLOUDRARY_BASE_H

#include <algorithm>
#include <functional>
#include <initializer_list>
#include <string>
#include <vector>

#include "nlohmann/json.hpp"

typedef int64_t INT;

using nlohmann::json;
using std::string;
using std::vector;
using std::function;

class Book;

class BookList;

class Library;

class Base;

// Operator overloads

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


class BookmarkGroup {
};

class Book {
public:
    // Constructors and destructors

    Book() = default;
    explicit Book(const string &j);
    Book(string name, string title, string textPath, string coverPath,
         string author, string description)
            : _name(std::move(name)), _title(std::move(title)), _textPath(std::move(textPath)),
              _coverPath(std::move(coverPath)), _author(std::move(author)), _description(std::move(description)) {}
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

    Book &setName(string name) {
        _name = std::move(name);
        return *this;
    }
    Book &setTitle(string title) {
        _title = std::move(title);
        return *this;
    }  // 标题和名字区分
    Book &setTextPath(string textPath) {
        _textPath = std::move(textPath);
        return *this;
    }
    Book &setCoverPath(string coverPath) {
        _coverPath = std::move(coverPath);
        return *this;
    }  // 封面
    Book &setAuthor(string author) {
        _author = std::move(author);
        return *this;
    }
    Book &setDescription(string description) {
        _description = std::move(description);
        return *this;
    }

    // Predicates
    typedef const function<bool(const Book &, const Book &)> predicate;
    static predicate CompareName;
    static predicate CompareTitle;
    static predicate CompareTextPath;
    static predicate CompareCoverPath;
    static predicate CompareAuthor;
    static predicate CompareDescription;

    // To JSON format string
    static string serialize(const Book &b);
    static Book deserialize(const string &j);

    [[nodiscard]] bool contains(const string & info) const {
        return (_name.find(info) != string::npos) ||
               (_title.find(info) != string::npos) ||
               (_textPath.find(info) != string::npos) ||
               (_coverPath.find(info) != string::npos) ||
               (_author.find(info) != string::npos) ||
               (_description.find(info) != string::npos) ;
    }

private:
    string _name = "null";
    string _title = "null";
    string _textPath = "null";
    string _coverPath = "null";
    string _author = "null";
    string _description = "null";
};


class BookList {  // 无名的书单，用于临时对象（如筛选结果）

public:
    BookList() = default;

    BookList(std::initializer_list<Book> args) : _books(args) {}  // 可变参数
    BookList(Book *arr, INT len) : _books(arr, arr + len) {}
    BookList(vector<Book> v) : _books(std::move(v)) {}
    explicit BookList(const string &j);
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
    [[nodiscard]] const_reverse_iterator crbegin() const { return _books.crbegin(); }
    [[nodiscard]] const_reverse_iterator crend() const { return _books.crend(); }

    [[nodiscard]] INT size() const { return static_cast<INT>(_books.size()); }

    BookList &add(const Book & book) {
        _books.push_back(book);
        return *this;
    }
    BookList &remove(const Book &book) {
        _books.erase(_books.begin() + find(book));
        return *this;
    }
    BookList &reverse() {
        std::reverse(begin(), end());
        return *this;
    }
    vector<Book> &data() { return _books; }
    [[nodiscard]] vector<Book> data() const { return _books; }

    Book &at(INT index) { return _books.at(index); }

    [[nodiscard]] INT find(const Book &book) const {
        return std::distance(begin(),
                             std::find(cbegin(), cend(), book));
    }

    BookList &sortBy(const function<bool(const Book &, const Book &)> &comp = Book::CompareName) {
        std::sort(begin(), end(), comp);
        return *this;
    }

    BookList search(const string & info) {
        BookList bl;
        for (auto i : *this) {
            if (i.contains(info)) {
                bl.add(i);
            }
        }
        return bl;
    }  // 模糊查找

    BookList sublist(INT first, INT last) {
        return {
                vector<Book>(_books.begin() + first, _books.begin() + last)};
    }

    static string serialize(const BookList &b);
    static BookList deserialize(const string &j);

private:
    vector<Book> _books;
};

class Library : public BookList {  // tbc

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

    void add(const Library & lib) { _libs.push_back(lib); }  // 我错了 是引用
    void remove(int index) { _libs.erase(_libs.begin() + index); }
    INT size() const {return _libs.size();}
    Library & at(INT index) { return _libs.at(index); }
    void swap(INT a, INT b) {
        std::swap(_libs[a], _libs[b]);
    }  // 交换两个Library的位置

    static string serialize(const Base &b);
    static Base deserialize(const string &j);

private:
    vector<Library> _libs;
};




#endif
