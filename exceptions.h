#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>
#include <QMessageBox>
#include <QIcon>

class CryptExceptions : public std::exception
{
    QString info;
public:
    CryptExceptions(const QString s)throw():info(s){}
    ~CryptExceptions()throw(){}
    const QString GetInfo() const{return info;}
    void alert()
    {
        QMessageBox msgBox(0);
        msgBox.setWindowTitle("Error");
        msgBox.setText(GetInfo());
        msgBox.setIcon(QMessageBox::Critical);
        msgBox.setStandardButtons(QMessageBox::Ok);
        msgBox.setDefaultButton(QMessageBox::Ok);
        msgBox.exec();
    }
};

#endif // EXCEPTIONS_H
