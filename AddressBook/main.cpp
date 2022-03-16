#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AddressBook addressBook;
    addressBook.show();
    return a.exec();
}
