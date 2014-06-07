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
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void afficheRC4();
    void afficheRSA();
    void afficheDecipher();
    void afficheCipher();
    void afficheImage();

    void clearTextEdit();
    void hideRC4();
    void hideRSA();
    QString textCleaner(QString const TextToClean);
    void rc4_cipher(const std::string plaintext, const std::string key);
    void rc4_decipher(const std::string ciphered, const std::string key);
    QString removeAccents(QString const s);
    void keystream_generation(int * const stream, int *keystream);
    void stream_generation(const std::string key, int* Stream);
    std::string hex_to_string(const std::string& input);
    std::string string_to_hex(const std::string& input);
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
