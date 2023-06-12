#include "base.h"

BookList::BookList(const string& j) {
  auto tempJson = json::parse(j);
  auto tempBookList = tempJson.get<BookList>();
  *this = std::move(tempBookList);  // 不知道对不对
}

string BookList::serialize(const BookList& b) {
  json j = b;
  return j.dump();
}

BookList BookList::deserialize(const string& j) {
  auto tempJson = json::parse(j);
  return tempJson.get<BookList>();
}

void to_json(json& j, const BookList& b) {
  for (const auto& item : b) {
    j.push_back(item);
  }
}

void from_json(const json& j, BookList& b) {
  for (const auto& item : j) {
    Book temp;
    temp = item;
    b.add(temp);
  }
}

void to_json(json& j, const Library& l) {
  j = {{"name", l.getName()}, {"data", static_cast<BookList>(l)}};
}

void from_json(const json& j, Library& l) {
    l.setName(j["name"]);
  for (const auto& item : j["data"]) {
    Book temp;
    temp = item;
    l.add(temp);
  }
}

bool operator==(BookList& a, BookList& b) {  // 顺序相同
  if (a.size() != b.size()) return false;

  for (int i = 0; i < a.size(); i++) {
    if ((a.at(i)) != (b.at(i))) return false;
  }
  return true;
}

bool operator==(Library& a, Library& b) { return a.getName() == b.getName(); }