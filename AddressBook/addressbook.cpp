#include "addressbook.h"
#include<QLabel>
#include<QTextEdit>

AddressBook::AddressBook(QWidget *parent)
    : QWidget(parent)
{
    QLabel *nameLabel = new QLabel(tr("Name:"));
    nameLine = new QLineEdit;

    QLabel *addressLabel = new QLabel(tr("Address:"));
};
    addressText = new QTextEdit;
