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
    const QString getInfo() const{return info;}
    void alert()
    {
        QMessageBox mBox;
        mBox.setText(getInfo());
        mBox.exec();
    }
};

#endif // EXCEPTIONS_H
