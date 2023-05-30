#include "En.h"

En::En(QObject *parent)
    : Lang{parent}
{
    setObjectName("En");
    search("Search");
    dark_mode("Dark Mode");
    settings("Setting");
    book_already_input("Book Input");
    home("Home");
}
