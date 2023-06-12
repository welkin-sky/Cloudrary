#include <fstream>
#include <iostream>
#include <filesystem>
#include "base.h"

const char *FILEPATH = "data.json";

using std::cout, std::cerr, std::cin;

void cli(Base &base);

class Process {
public:
    Base &base;
    Library & now;
    Process() = default;
    explicit Process(Base &b) : base(b), now(b.at(0)) {}
    void ls() {
            cout << "In " << now.getName() << ":\n";
            for (const auto & i: now) {
                cout << i.getTitle() << i.getAuthor() << i.getTextPath() << i.getDescription() << std::endl;
        }
    }
    void cd(const string & name) {
        for (const auto & i : base) {
            if (i.getName() == name) {
                now = i;
            }
        }
    }
    void search(const string & info) {
        auto bl = now.search(info);
        cout << "Search results:\n";
        for (const auto & i : bl) {
            cout << i.getTitle() << i.getAuthor() << i.getTextPath() << i.getDescription() << std::endl;
        }
    }
    void addbook() {
        Book b;
        string temp;
        cout << "Title:";
        getline(cin, temp);
        b.setTitle(temp);
        cout << "Path:";
        getline(cin, temp);
        b.setTextPath(temp);
        std::filesystem::path pt(temp);
        b.setName(pt.filename().string());
        cout << "Author:";
        getline(cin, temp);
        b.setAuthor(temp);
        cout << "Description:";
        getline(cin, temp);
        b.setDescription(temp);
        now.add(b);
        cout << "Add suscessfully.";
    }
    void addlib() {

    }
    void remove();
    void sortby();
};

int main() {
//  test();
    Base base;
    std::ifstream in(FILEPATH);
    if (!in) {
        std::ofstream out(FILEPATH);
        Library l;
        l.setName("Untitled 1");
        base.add(l);
        out << Base::serialize(base);
        in.open(FILEPATH);
    }
    string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    try {
        base = Base::deserialize(data);
    } catch (std::exception &ex) {
        cerr << "JSON Parsing is wrong. data.json might be broken.\nDetail: \n" << ex.what();
    }
    cli(base);
    return 0;
}

void cli(Base &base) {
    static const string usage = "Usage: ls / cd [lib] / search [info] / addbook "
                                "/ addlib / remove [name] / sortby [lib] [method] / exit\n";
    Process p(base);
    cout << "Welcome to Cloudrary, an ebook manager.\n"
         << usage << "(name should not include spaces and tabs)\n";
    cout << p.now.getName() << ":";
    string cliInput;
    while (cin >> cliInput) {
        if (cliInput == "ls") {
            p.ls();
        } else if (cliInput == "search") {
            string info ;
            cin >> info;
            p.search(info);
        } else if (cliInput == "cd") {
            string name;
            cin >> name;
            p.cd(name);
        } else if (cliInput == "addbook") {
            cin.sync();
            p.addbook();
        } else if (cliInput == "remove") {

        } else if (cliInput == "sortby") {

        } else if (cliInput == "exit"){
            break;
        } else {
            cout << "Invalid arugment.\n" << usage;
        }
        cin.clear();
        cin.sync();
        cout << p.now.getName() << ":";
    }
}

