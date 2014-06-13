#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QString>
#include <QtDebug>
#include <QByteArray>
#include <string>
#include <sstream>
#include <algorithm>
#include <stdexcept>
#include <iostream>

namespace Ui {
class MainWindow;
}

/*! \class MainWindow
 *  \brief The main window of the application.
 *  This class defines the main interface of the application and the different functions to be
 *  called when an action is realized by the user.*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /*! \fn MainWindow
     *  Constructor of the MainWindow class*/
    explicit MainWindow(QWidget *parent = 0);
    /*! \fn ~MainWindow
     *  Destructor of the MainWindow class*/
    ~MainWindow();
    /*! \fn afficheRC4
     *  Function displaying the zones for the RC4 graphic interface*/
    void afficheRC4();
    /*! \fn afficheRSA
     *  Function displaying the zones for the RSA graphic interface*/
    void afficheRSA();
    /*! \fn afficheDecipher
     *  Function displaying the zones regarding the decipher process*/
    void afficheDecipher();
    /*! \fn afficheCipher
     *  Function displaying the zones regarding the cipher process*/
    void afficheCipher();
    /*! \fn afficheImage
     *  Function displaying the schema for keystream generation (RC4 cipher)*/
    void afficheImage();

    /*! \fn clearTextEdit
     *  Function cleaning the text box in the GUI*/
    void clearTextEdit();
    /*! \fn hideRC4
     *  Function hiding the zones for the RC4 algorithm*/
    void hideRC4();
    /*! \fn hideRSA
     *  Function hiding the zones for the RSA algorithm*/
    void hideRSA();
    /*! \fn textCleaner
     *  Function deleting spaces, accents and special characters (quotes, parenthesis) from an input text
     *  \param[in] QString TextToClean: the input text to clean
     *  \param[out] QString cleanedText: the text without spaces, accents, ...*/
    QString textCleaner(QString const TextToClean);
    /*! \fn rc4_cipher
     *  Realizes the RC4 cipher
     *  \param[in] std::string plaintext: the text to cipher
     *  \param[in] std::string key: the key to cipher the text*/
    void rc4_cipher(const std::string plaintext, const std::string key);
    /*! \fn rc4_decipher
     *  Realizes the RC4 decipher
     *  \param[in] std::string ciphered: the ciphered text to decipher
     *  \param[in] std::string key: the key to decipher the text*/
    void rc4_decipher(const std::string ciphered, const std::string key);
    /*! \fn removeAccents
     *  Function which removes the accents from a text
     *  \param[in] Qstring s: the string to clean*/
    QString removeAccents(QString const s);
    /*! \fn keystream_generation
     *  Function calling the rc4 method for the keystream generation, thus displaying the different areas of the GUI
     *  \param[in] Qstring s: the string to clean*/
    void keystream_generation(int * const stream, int *keystream);
    /*! \fn stream_generation
     *  Function calling the rc4 method for the stream generation, thus displaying the different areas of the GUI
     *  \param[in] Qstring s: the string to clean*/
    void stream_generation(const std::string key, int* Stream);
    /*! \fn string_to_hex
     *   get the hexadecimal conversion of a string
     *  \param[in] std::string input: the string to convert
     *  \param[out] std::string: the hexadecimal conversion of the input string*/
    std::string hex_to_string(const std::string& input);
    /*! \fn hex_to_string
     *   Get the string represented by an hexadecimal value
     *  \param[in] std::string input: the hexadecimal string to convert
     *  \param[out] std::string: the string corresponding to the hexadecimal value input*/
    std::string string_to_hex(const std::string& input);
    /*! \fn mousePressEvent
     *   Mouse handler for the RC4 GUI demonstration (when clicking on the right button of the mouse
     *  \param[in] QMouseEvent* e: the event realized by the mouse*/
    void mousePressEvent(QMouseEvent* e);

private:
    Ui::MainWindow *ui;

private slots:
    void cipherClicked();
    void decipherClicked();
    void aboutClicked();
    void rc4Clicked();
    void rsaClicked();
    void cipherButtonClicked();
    void decipherButtonClicked();
    void imageButtonClicked();
    void backButtonClicked();
    void remplissageImage();

};
#endif // MAINWINDOW_H
