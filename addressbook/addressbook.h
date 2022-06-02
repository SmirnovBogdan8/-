#ifndef ADDRESSBOOK_H
#define ADDRESSBOOK_H
#include <QLineEdit>
#include<QTextEdit>
#include <QWidget>
#include<QPushButton>

class AddressBook : public QWidget //Реализация класса AddressBook
{
    Q_OBJECT

enum Mode { NavigationMode, AddingMode, EditingMode };

public:
   AddressBook(QWidget *parent = 0);

//Мы имеем установленные метки и поля ввода, добавим кнопки для завершения процесса добавления контакта.
//Это означает, что наш файл addressbook.h теперь содержит три объявленных объекта QPushButton и 8 соответствующих открытых слотов.
public slots:
    void addContact();
    void submitContact();
    void cancel();
    void next();
    void previous();
    void editContact();
    void removeContact();
    void updateInterface(Mode mode);

//Три объекта QPushButton - addButton, submitButton и cancelButton - теперь включены в объявления закрытых переменных
//бъект класса QMap, contacts, используется в этих целях поскольку он содержит пару ключ-значение:
//имя контакта выступает в качестве ключа, а адрес контакта - в качестве значения.
private:
     QPushButton *addButton;
     QPushButton *submitButton;
     QPushButton *cancelButton;
     QLineEdit *nameLine;
     QTextEdit *addressText;
     QMap<QString, QString> contacts;
     QString oldName;
     QString oldAddress;
     QPushButton *nextButton;
     QPushButton *previousButton;

};

#endif // ADDRESSBOOK_H
