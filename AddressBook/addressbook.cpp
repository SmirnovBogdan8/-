#include "addressbook.h"
#include<QLabel>
#include<QTextEdit>
#include<QGridLayout>
#include<QVBoxLayout>
#include<QMessageBox>

QPushButton *editButton;
QPushButton *removeButton;

void AddressBook::addContact()
{
    oldName = nameLine->text();
    oldAddress = addressText->toPlainText();

    nameLine->clear();
    addressText->clear();

    nameLine->setReadOnly(false);
    nameLine->setFocus(Qt::OtherFocusReason);
    addressText->setReadOnly(false);

    addButton->setEnabled(false);
    submitButton->show();
    cancelButton->show();
}

void AddressBook::submitContact()
{
    QString name = nameLine->text();
    QString address = addressText->toPlainText();

    if (name == "" || address == "")
    {
        QMessageBox::information(this, tr("Empty Field"),
            tr("Please enter a name and address."));
        return;
    }
    if (!contacts.contains(name)) {
             contacts.insert(name, address);
             QMessageBox::information(this, tr("Add Successful"),
                 tr("\"%1\" has been added to your address book.").arg(name));
         } else {
             QMessageBox::information(this, tr("Add Unsuccessful"),
                 tr("Sorry, \"%1\" is already in your address book.").arg(name));
             return;
         }
    if (contacts.isEmpty()) {
        nameLine->clear();
        addressText->clear();
    }

    Mode currentMode;

    nameLine->setReadOnly(true);
    addressText->setReadOnly(true);
    addButton->setEnabled(true);
    submitButton->hide();
    cancelButton->hide();
    if (currentMode == AddingMode) {

        if (!contacts.contains(name)) {
            contacts.insert(name, address);
            QMessageBox::information(this, tr("Add Successful"),
                tr("\"%1\" has been added to your address book.").arg(name));
        } else {
            QMessageBox::information(this, tr("Add Unsuccessful"),
                tr("Sorry, \"%1\" is already in your address book.").arg(name));
            return;
        }
    } else if (currentMode == EditingMode) {

             if (oldName != name) {
                 if (!contacts.contains(name)) {
                     QMessageBox::information(this, tr("Edit Successful"),
                         tr("\"%1\" has been edited in your address book.").arg(oldName));
                     contacts.remove(oldName);
                     contacts.insert(name, address);
                 } else {
                     QMessageBox::information(this, tr("Edit Unsuccessful"),
                         tr("Sorry, \"%1\" is already in your address book.").arg(name));
                     return;
                 }
             } else if (oldAddress != address) {
                 QMessageBox::information(this, tr("Edit Successful"),
                     tr("\"%1\" has been edited in your address book.").arg(name));
                 contacts[name] = address;
             }
         }

         updateInterface(NavigationMode);
}

void AddressBook::cancel()
 {
     nameLine->setText(oldName);
     nameLine->setReadOnly(true);

     addressText->setText(oldAddress);
     addressText->setReadOnly(true);

     addButton->setEnabled(true);
     submitButton->hide();
     cancelButton->hide();
 }

void AddressBook::next()
 {
     QString name = nameLine->text();
     QMap<QString, QString>::iterator i = contacts.find(name);

     if (i != contacts.end())
         i++;

     if (i == contacts.end())
         i = contacts.begin();

     nameLine->setText(i.key());
     addressText->setText(i.value());
 }

void AddressBook::previous()
 {
     QString name = nameLine->text();
     QMap<QString, QString>::iterator i = contacts.find(name);

     if (i == contacts.end()){
         nameLine->clear();
         addressText->clear();
         return;
     }

     if (i == contacts.begin())
         i = contacts.end();

     i--;
     nameLine->setText(i.key());
     addressText->setText(i.value());
 }

void AddressBook::editContact()
 {
     oldName = nameLine->text();
     oldAddress = addressText->toPlainText();

     updateInterface(EditingMode);
 }

void AddressBook::removeContact()
 {
     QString name = nameLine->text();
     QString address = addressText->toPlainText();

     if (contacts.contains(name)) {

         int button = QMessageBox::question(this,
             tr("Confirm Remove"),
             tr("Are you sure you want to remove \"%1\"?").arg(name),
             QMessageBox::Yes | QMessageBox::No);

         if (button == QMessageBox::Yes) {

             previous();
             contacts.remove(name);

             QMessageBox::information(this, tr("Remove Successful"),
                 tr("\"%1\" has been removed from your address book.").arg(name));
         }
     }

     updateInterface(NavigationMode);
 }

void AddressBook::updateInterface(Mode mode)
{
    Mode currentMode;
    currentMode = mode;

    switch (currentMode) {

    case AddingMode:
    case EditingMode:

        nameLine->setReadOnly(false);
        nameLine->setFocus(Qt::OtherFocusReason);
        addressText->setReadOnly(false);

        addButton->setEnabled(false);
        editButton->setEnabled(false);
        removeButton->setEnabled(false);

        nextButton->setEnabled(false);
        previousButton->setEnabled(false);

        submitButton->show();
        cancelButton->show();
        break;

    case NavigationMode:

        if (contacts.isEmpty()) {
            nameLine->clear();
            addressText->clear();
        }

        nameLine->setReadOnly(true);
        addressText->setReadOnly(true);
        addButton->setEnabled(true);

        int number = contacts.size();
        editButton->setEnabled(number >= 1);
        removeButton->setEnabled(number >= 1);
        nextButton->setEnabled(number > 1);
        previousButton->setEnabled(number >1 );

        submitButton->hide();
        cancelButton->hide();
        break;
    }
}

AddressBook::AddressBook(QWidget *parent) //Класс содержит объявления nameLine и addressText, закрытых экземпляров класса QLineEdit и QTextEdit
     : QWidget(parent)
 {
    //Внутри конструктора AddressBook мы устанавливаем nameLine и addressText только для чтения, так что мы можем только отображать, но не редактировать детали имеющихся контактов.
     QLabel *nameLabel = new QLabel(tr("Name:"));
     nameLine = new QLineEdit;

     QLabel *addressLabel = new QLabel(tr("Address:"));
     addressText = new QTextEdit;

     QGridLayout *mainLayout = new QGridLayout; //Мы используем QGridLayout чтобы структурировано расположить метки и поля ввода.
          mainLayout->addWidget(nameLabel, 0, 0);
          mainLayout->addWidget(nameLine, 0, 1);
          mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
          mainLayout->addWidget(addressText, 1, 1);
          nameLine->setReadOnly(true);
          addressText->setReadOnly(true);

     addButton = new QPushButton(tr("&Add"));
          addButton->show();

     submitButton = new QPushButton(tr("&Submit"));
          submitButton->hide();

     cancelButton = new QPushButton(tr("&Cancel"));
          cancelButton->hide();

     connect(addButton, SIGNAL(clicked()), this, SLOT(addContact()));
     connect(submitButton, SIGNAL(clicked()), this, SLOT(submitContact()));
     connect(cancelButton, SIGNAL(clicked()), this, SLOT(cancel()));

     QVBoxLayout *buttonLayout1 = new QVBoxLayout;
         buttonLayout1->addWidget(addButton, Qt::AlignTop);
         buttonLayout1->addWidget(submitButton);
         buttonLayout1->addWidget(cancelButton);
         buttonLayout1->addStretch();

     setLayout(mainLayout);//Для того, чтобы вставить объект компоновки в виджет мы вызываем функцию виджета setLayout():
     QGridLayout *mainLayout1 = new QGridLayout;
        mainLayout->addWidget(nameLabel, 0, 0);
        mainLayout->addWidget(nameLine, 0, 1);
        mainLayout->addWidget(addressLabel, 1, 0, Qt::AlignTop);
        mainLayout->addWidget(addressText, 1, 1);
        mainLayout->addLayout(buttonLayout1, 1, 2);

    nextButton = new QPushButton(tr("&Next"));
        nextButton->setEnabled(false);

    previousButton = new QPushButton(tr("&Previous"));
        previousButton->setEnabled(false);

    connect(nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(previousButton, SIGNAL(clicked()), this, SLOT(previous()));

    QHBoxLayout *buttonLayout2 = new QHBoxLayout;
         buttonLayout2->addWidget(previousButton);
         buttonLayout2->addWidget(nextButton);
         mainLayout->addLayout(buttonLayout2, 3, 1);
         nextButton->setEnabled(false);
         previousButton->setEnabled(false);

     int number = contacts.size();
      nextButton->setEnabled(number > 1);
      previousButton->setEnabled(number > 1);



    editButton = new QPushButton(tr("&Edit"));
         editButton->setEnabled(false);
    removeButton = new QPushButton(tr("&Remove"));
         removeButton->setEnabled(false);

         connect(editButton, SIGNAL(clicked()), this, SLOT(editContact()));
              connect(removeButton, SIGNAL(clicked()), this, SLOT(removeContact()));
              buttonLayout1->addWidget(editButton);
              buttonLayout1->addWidget(removeButton);

    setWindowTitle(tr("Simple Address Book"));

}
