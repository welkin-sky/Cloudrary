#include "base.h"

Book::Book(const string &j) : Book() {
  auto tempJson = json::parse(j);
  auto tempBook = tempJson.get<Book>();
  *this = std::move(tempBook);  // 不知道对不对
}

string Book::serialize(const Book &b) {
  json j = b;
  return j.dump();
}

Book Book::deserialize(const string &j) {
  auto tempJson = json::parse(j);
  return tempJson.get<Book>();
}

// JSON converters
// Book用键值对方式存储

void to_json(json &j, const Book &b) {
  j = json{
      {"name", b.getName()},         {"title", b.getTitle()},
      {"textPath", b.getTextPath()}, {"coverPath", b.getCoverPath()},
      {"author", b.getAuthor()},     {"Description", b.getDescription()},
  };
}

void from_json(const json &j, Book &b) {
  b.setName(j.at("name").get<string>());
  b.setTitle(j.at("title").get<string>());
  b.setTextPath(j.at("textPath").get<string>());
  b.setCoverPath(j.at("coverPath").get<string>());
  b.setAuthor(j.at("author").get<string>());
  b.setDescription(j.at("description").get<string>());
}

// Operator overloads
bool operator==(const Book &a, const Book &b) {
  return a.getTextPath() == b.getTextPath();
}

// 暂时认为路径相同即相同
bool operator!=(const Book &a, const Book &b) { return !(a == b); }

bool operator<(const Book &a, const Book &b) {
  return a.getName() < b.getName();
}

bool operator>(const Book &a, const Book &b) { return b < a; }
