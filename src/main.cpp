#include <fstream>
#include <iostream>
#include <filesystem>
#include "base.h"

const char *FILEPATH = "data.json";

using std::cout, std::cerr, std::cin;

void cli(Base &base, std::ofstream & out);

class Process {
public:
    Base &base;
    INT now = 0;
    Process() = default;
    explicit Process(Base &b) : base(b), now(0) {}
    void ls() {
            cout << "In " << base.at(now).getName() << ":\n";
            for (const auto & i: base.at(now)) {
                cout << i.getName() << '\t' << i.getTitle()  << '\t' << i.getAuthor() << '\t'
                << i.getTextPath() << '\t' << i.getDescription() << std::endl;
        }
    }
    void cd(const string & name) {
        bool status = false;
        for (int i = 0; i < base.size(); i++) {
            if (base.at(i).getName() == name) {
                now = i;
                status = true;
            }
        }
        if (!status) cout << "No matching\n";
    }
    void search(const string & info) {
        auto bl = base.at(now).search(info);
        cout << "Search results:\n";
        for (const auto & i : bl) {
            cout << i.getName() << '\t' << i.getTitle()  << '\t' << i.getAuthor() << '\t'
                 << i.getTextPath() << '\t' << i.getDescription() << std::endl;
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
        base.at(now).add(b);
        cout << "Add suscessfully.\n";
    }
    void addlib() {
        Library l;
        string name;
        cout << "Name:";
        cin >> name;
        l.setName(name);
        base.add(l);
        cout << "Add sucessfully.\n";
    }
    void removebook() {
        string name;
        cout << "Name:";
        cin >> name;
        for (const auto i : base.at(now)) {
            if (i.getName() == name) {
                base.at(now).remove(i);
                break;
            }
        }
        cout << "Remove successfully.\n";
    }
    void removelib() {
        string name;
        cout << "Name:";
        cin >> name;
        for (int i = 0; i < base.size(); i++) {
            if (base.at(i).getName() == name) {
                base.remove(i);
                now = i - 1;
                break;
            }
        }

        cout << "Remove succesfully.\n";
    }
    void sortby(const string & str) {
        BookList b;
        static const char * method [5]  =
                {"name", "title", "path", "author", "description"};
        int i = 0;
        for (; i < 5 ; i++) {
            if (str == method[i]) {
                switch (i) {
                    case 0:
                        base.at(now).sortBy(Book::CompareName);
                        break;
                    case 1:
                        base.at(now).sortBy(Book::CompareTitle);
                        break;
                    case 2:
                        base.at(now).sortBy(Book::CompareTextPath);
                        break;
                    case 3:
                        base.at(now).sortBy(Book::CompareAuthor);
                        break;
                    case 4:
                        base.at(now).sortBy(Book::CompareDescription);
                        break;
                }
                break;
            }
        }
        if (i == 5) cout << "Wrong method! Available method: name, title, path, author, description.\n";
        else ls();
    }
};

int main() {
//  test();
    Base base;
    std::ifstream in(FILEPATH);
    string data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
    std::ofstream out(FILEPATH);
    if (!in) {
        Library l;
        l.setName("Untitled-1");
        base.add(l);
        data = Base::serialize(base);
        out << data;
        out.flush();
        in.open(FILEPATH);
    }
    try {
        base = Base::deserialize(data);
    } catch (std::exception &ex) {
        cerr << "JSON Parsing is wrong. data.json might be broken.\nDetail: \n" << ex.what();
    }
    cli(base, out);

    return 0;
}

void cli(Base &base, std::ofstream & out) {
    static const string usage = "Usage: ls / cd [lib] / search [info] / addbook "
                                "/ addlib / removebook / removelib / sortby [method] / exit\n";
    Process p(base);
    cout << "Welcome to Cloudrary, an ebook manager.\n"
         << usage << "(name should not include spaces and tabs)\n";
    cout << p.base.at(p.now).getName() << ":";
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
        } else if (cliInput == "addlib") {
            cin.sync();
            p.addlib();
        } else if (cliInput == "removebook") {
            cin.sync();
            p.removebook();
        } else if (cliInput == "removelib") {
            cin.sync();
            p.removelib();
        } else if (cliInput == "sortby") {
            string method;
            cin >> method;
            p.sortby(method);
        } else if (cliInput == "exit"){
            break;
        } else {
            cout << "Invalid arugment.\n" << usage;
        }
        cin.clear();
        cin.sync();
        out.close();
        out.open(FILEPATH);
        out << Base::serialize(base);
        out.flush();
        cout << p.base.at(p.now).getName() << ":";
    }
}

