#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H
#include <QLineEdit>
#include<QTextEdit>
#include <QWidget>

class AddressBook : public QWidget
{
    Q_OBJECT

public:
   AddressBook(QWidget *parent = 0);

private:
   QLineEdit *nameLine;
   QTextEdit *addressText;
};

#endif // ADDRESSBOOK_H
