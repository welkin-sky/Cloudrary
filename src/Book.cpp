//
// Created by Welkinsky on 5/18.
//

#include <string>

#include "../include/base.h"
#include "base.h"

void to_json(json& j, const Book& b) {
  j = json{
      {"name", b.getName()},         {"title", b.getTitle()},
      {"textPath", b.getTextPath()}, {"coverPath", b.getCoverPath()},
      {"author", b.getAuthor()},     {"Description", b.getDescription()},
  };
}

void from_json(const json& j, Book& b) {
  b.setName(j.at("name").get<string>());
  b.setTitle(j.at("title").get<string>());
  b.setTextPath(j.at("textPath").get<string>());
  b.setCoverPath(j.at("coverPath").get<string>());
  b.setAuthor(j.at("author").get<string>());
  b.setDescription(j.at("description").get<string>());
}

Book::Book(const string& j) : Book() {
  auto tempJson = json::parse(j);
  auto tempBook = tempJson.get<Book>();
  *this = std::move(tempBook);  // 不知道对不对
}

void to_json(json& j, const BookList& b) {
  for (const auto& item : b._books) {
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
  json name = {"name", l._name};
  j = l;
  j.push_back(name);
}

void from_json(const json& j, Library& l) {
  for (const auto& item : j) {
    if (item.contains("name"))
      l._name = item.at("name").get<string>();
    else {
      Book temp;
      temp = item;
      l.add(temp);
    }
  }
}