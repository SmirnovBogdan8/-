#include<QApplication>
#include<addressbook.h>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //char s[100];
    //wchar_t w[100];
    //MULTIBYTETOWIDCHAR
    AddressBook *addressBook = new AddressBook;
    addressBook->show();

    return app.exec();
}
