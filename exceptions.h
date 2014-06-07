#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <string>
#include <exception>
#include <QMessageBox>

/*! \class CryptExceptions
 *  \brief Exceptions handling class
 *
 *  An homemade class to handle the exceptions thrown by the program
 */

class CryptExceptions : public std::exception
{
private:
    /*! Contains the error message displayed to the user*/
    QString info;
public:
    /*! \fn CryptExceptions()
     *  Constructor of the CryptExceptions class
     *  \param[in] QString s : The reason why the exception was thrown*/
    CryptExceptions(const QString s)throw():info(s){}
    /*! \fn ~CryptExceptions()
     *  Destructor of the CryptExceptions class*/
    ~CryptExceptions()throw(){}
    /*! \fn QString getInfo()
     *  Getter for info attribute
     *  \param[out] QString info : The reason why the exception was thrown*/
    const QString getInfo() const{return info;}
    /*! \fn void alert()
     *  Action realized when an exception is caught*/
    void alert()
    {
        QMessageBox mBox;
        mBox.setText(getInfo());
        mBox.exec();
    }
};

#endif // EXCEPTIONS_H
