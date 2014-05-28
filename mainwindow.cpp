#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rc4.h"


/*****************************************************************/
/*                               TODO                            */
/*****************************************************************/
/* - aes                                                         */
/* - rsa                                                         */
/* - rc4 : demonstration construction keystream                  */
/* => intégration shéma dans nouvelle fenêtre avec remplissage   */
/* de labels                                                     */
/* - DOXYGEN                                                     */
/*****************************************************************/

rc4 rc4_obj("","","");
int compt_disp=0;
bool CipherMode=true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //default mode : RC4 & Cipher
    ui->setupUi(this);
    this->afficheRC4();

    //connection of the menus and buttons
    QObject::connect(ui->actionCipher,SIGNAL(triggered()),this,SLOT(cipherClicked()));
    QObject::connect(ui->actionDecipher,SIGNAL(triggered()),this,SLOT(decipherClicked()));
    QObject::connect(ui->actionAbout,SIGNAL(triggered()),this,SLOT(aboutClicked()));
    QObject::connect(ui->pushButton_cipher,SIGNAL(clicked()),this,SLOT(cipherButtonClicked()));
    QObject::connect(ui->pushButton_decipher,SIGNAL(clicked()),this,SLOT(decipherButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        QString k = QString::fromStdString(rc4_obj.getKeystream());
        QString in;
        if(!ui->radioButton_hexa->isChecked())
            in = QString::fromStdString(rc4_obj.string_to_hex(textCleaner(ui->textEdit_inputText->toPlainText()).toStdString()));
        else
            in =QString::fromStdString(textCleaner(ui->textEdit_inputText->toPlainText()).toStdString());
        QString de = QString::fromStdString(rc4_obj.string_to_hex(rc4_obj.getDecoded()));
        QString en = QString::fromStdString(rc4_obj.string_to_hex(rc4_obj.getEncoded()));
        QString de_plain = QString::fromStdString(rc4_obj.getDecoded());

        QString affK;
        QString affIn;
        QString affDe;
        QString affEn;

        if(CipherMode)
        {
            switch(compt_disp)
            {
            case 0:
                ui->textBrowser_input0->setText("");
                ui->textBrowser_keystream0->setText("");
                ui->textBrowser_result0->setText("");
                ui->textBrowser_input1->setText("");
                ui->textBrowser_keystream1->setText("");
                ui->textBrowser_result1->setText("");
                ui->textBrowser_input2->setText("");
                ui->textBrowser_keystream2->setText("");
                ui->textBrowser_result2->setText("");
                ui->textBrowser_input3->setText("");
                ui->textBrowser_keystream3->setText("");
                ui->textBrowser_result3->setText("");
                ui->textBrowser_input4->setText("");
                ui->textBrowser_keystream4->setText("");
                ui->textBrowser_result4->setText("");

                ui->label_equal4->hide();
                ui->label_xor4->hide();
                ui->label_equal->show();
                ui->label_xor->show();

                affK = k[0];
                affK.append(k[1]);
                affIn = in[0];
                affIn.append(in[1]);
                affEn = en[0];
                affEn.append(en[1]);
                ui->textBrowser_input0->setText(affIn);
                ui->textBrowser_keystream0->setText(affK);
                ui->textBrowser_result0->setText(affEn);
                ui->textBrowser_ciphered->setText(affEn);
                break;
            case 1:
                ui->label_equal->hide();
                ui->label_xor->hide();
                ui->label_equal1->show();
                ui->label_xor1->show();

                affK = k[2];
                affK.append(k[3]);
                affIn = in[2];
                affIn.append(in[3]);
                affEn = en[2];
                affEn.append(en[3]);
                ui->textBrowser_input1->setText(affIn);
                ui->textBrowser_keystream1->setText(affK);
                ui->textBrowser_result1->setText(affEn);
                ui->textBrowser_ciphered->setText(en.mid(0,4));
                break;
            case 2:
                ui->label_equal1->hide();
                ui->label_xor1->hide();
                ui->label_equal2->show();
                ui->label_xor2->show();

                affK = k[4];
                affK.append(k[5]);
                affIn = in[4];
                affIn.append(in[5]);
                affEn = en[4];
                affEn.append(en[5]);
                ui->textBrowser_input2->setText(affIn);
                ui->textBrowser_keystream2->setText(affK);
                ui->textBrowser_result2->setText(affEn);
                ui->textBrowser_ciphered->setText(en.mid(0,6));
                break;
            case 3:
                ui->label_equal2->hide();
                ui->label_xor2->hide();
                ui->label_equal3->show();
                ui->label_xor3->show();

                affK = k[6];
                affK.append(k[7]);
                affIn = in[6];
                affIn.append(in[7]);
                affEn = en[6];
                affEn.append(en[7]);
                ui->textBrowser_input3->setText(affIn);
                ui->textBrowser_keystream3->setText(affK);
                ui->textBrowser_result3->setText(affEn);
                ui->textBrowser_ciphered->setText(en.mid(0,8));
                break;
            case 4:
                ui->label_equal3->hide();
                ui->label_xor3->hide();
                ui->label_equal4->show();
                ui->label_xor4->show();

                affK = k[8];
                affK.append(k[9]);
                affIn = in[8];
                affIn.append(in[9]);
                affEn = en[8];
                affEn.append(en[9]);
                ui->textBrowser_input4->setText(affIn);
                ui->textBrowser_keystream4->setText(affK);
                ui->textBrowser_result4->setText(affEn);
                ui->textBrowser_ciphered->setText(en.mid(0,10));
                break;
            case 5:
                ui->textBrowser_ciphered->setText(en);
                break;
            default:
                break;
            }
            compt_disp=(compt_disp+1)%6;
        }
        else//Mode Decipher
        {
            switch(compt_disp)
            {
            case 0:
                ui->textBrowser_input0->setText("");
                ui->textBrowser_keystream0->setText("");
                ui->textBrowser_result0->setText("");
                ui->textBrowser_input1->setText("");
                ui->textBrowser_keystream1->setText("");
                ui->textBrowser_result1->setText("");
                ui->textBrowser_input2->setText("");
                ui->textBrowser_keystream2->setText("");
                ui->textBrowser_result2->setText("");
                ui->textBrowser_input3->setText("");
                ui->textBrowser_keystream3->setText("");
                ui->textBrowser_result3->setText("");
                ui->textBrowser_input4->setText("");
                ui->textBrowser_keystream4->setText("");
                ui->textBrowser_result4->setText("");

                ui->label_equal4->hide();
                ui->label_xor4->hide();
                ui->label_equal->show();
                ui->label_xor->show();

                affK = k[0];
                affK.append(k[1]);
                affIn = in[0];
                affIn.append(in[1]);
                affDe = de[0];
                affDe.append(de[1]);
                ui->textBrowser_input0->setText(affIn);
                ui->textBrowser_keystream0->setText(affK);
                ui->textBrowser_result0->setText(affDe);
                ui->textBrowser_ciphered->setText(affDe);
                ui->textBrowser_cipheredPlain->setText(de_plain.at(0));
                break;
            case 1:
                ui->label_equal->hide();
                ui->label_xor->hide();
                ui->label_equal1->show();
                ui->label_xor1->show();

                affK = k[2];
                affK.append(k[3]);
                affIn = in[2];
                affIn.append(in[3]);
                affDe = de[2];
                affDe.append(de[3]);
                ui->textBrowser_input1->setText(affIn);
                ui->textBrowser_keystream1->setText(affK);
                ui->textBrowser_result1->setText(affDe);
                ui->textBrowser_ciphered->setText(de.mid(0,4));
                ui->textBrowser_cipheredPlain->setText(de_plain.mid(0,2));
                break;
            case 2:
                ui->label_equal1->hide();
                ui->label_xor1->hide();
                ui->label_equal2->show();
                ui->label_xor2->show();

                affK = k[4];
                affK.append(k[5]);
                affIn = in[4];
                affIn.append(in[5]);
                affDe = de[4];
                affDe.append(de[5]);
                ui->textBrowser_input2->setText(affIn);
                ui->textBrowser_keystream2->setText(affK);
                ui->textBrowser_result2->setText(affDe);
                ui->textBrowser_ciphered->setText(de.mid(0,6));
                ui->textBrowser_cipheredPlain->setText(de_plain.mid(0,3));
                break;
            case 3:
                ui->label_equal2->hide();
                ui->label_xor2->hide();
                ui->label_equal3->show();
                ui->label_xor3->show();

                affK = k[6];
                affK.append(k[7]);
                affIn = in[6];
                affIn.append(in[7]);
                affDe = de[6];
                affDe.append(en[7]);
                ui->textBrowser_input3->setText(affIn);
                ui->textBrowser_keystream3->setText(affK);
                ui->textBrowser_result3->setText(affDe);
                ui->textBrowser_ciphered->setText(de.mid(0,8));
                ui->textBrowser_cipheredPlain->setText(de_plain.mid(0,4));
                break;
            case 4:
                ui->label_equal3->hide();
                ui->label_xor3->hide();
                ui->label_equal4->show();
                ui->label_xor4->show();

                affK = k[8];
                affK.append(k[9]);
                affIn = in[8];
                affIn.append(in[9]);
                affDe = de[8];
                affDe.append(de[9]);
                ui->textBrowser_input4->setText(affIn);
                ui->textBrowser_keystream4->setText(affK);
                ui->textBrowser_result4->setText(affDe);
                ui->textBrowser_ciphered->setText(de.mid(0,10));
                ui->textBrowser_cipheredPlain->setText(de_plain.mid(0,5));
                break;
            case 5:
                ui->textBrowser_ciphered->setText(de);
                ui->textBrowser_cipheredPlain->setText(de_plain);
                break;
            default:
                break;
            }
            compt_disp=(compt_disp+1)%6;
        }
    }
}

void MainWindow::afficheRC4()
{
    afficheCipher();
    ui->textBrowser_input0->show();
    ui->textBrowser_input1->show();
    ui->textBrowser_input2->show();
    ui->textBrowser_input3->show();
    ui->textBrowser_input4->show();
    ui->textBrowser_keystream0->show();
    ui->textBrowser_keystream1->show();
    ui->textBrowser_keystream2->show();
    ui->textBrowser_keystream3->show();
    ui->textBrowser_keystream4->show();
    ui->label_equal->show();
    ui->label_xor->show();
    ui->label_key->show();
    ui->label_final->show();
    ui->label_keystreambox->show();
    ui->label_textbox->show();
    ui->label_res->show();
    ui->radioButton_hexa->show();
    ui->radioButton_string->show();
    ui->radioButton_string->setChecked(true);
    ui->label_inputmode->show();
    this->setWindowTitle("RC4");
    ui->label_equal->show();
    ui->label_xor->show();
    ui->label_equal1->hide();
    ui->label_xor1->hide();
    ui->label_equal2->hide();
    ui->label_xor2->hide();
    ui->label_equal3->hide();
    ui->label_xor3->hide();
    ui->label_equal4->hide();
    ui->label_xor4->hide();
}

void MainWindow::afficheAES()
{
    this->setWindowTitle("AES");
}

void MainWindow::afficheRSA()
{
    this->setWindowTitle("RSA");
}

void MainWindow::afficheCipher()
{
    clearTextEdit();
    ui->pushButton_cipher->setEnabled(true);
    ui->pushButton_decipher->setEnabled(false);
    ui->label_cipher->show();
    ui->label_decipher->hide();
    ui->radioButton_hexa->setChecked(true);
    ui->radioButton_string->setCheckable(true);
    ui->label_inputHex->show();
    ui->textEdit_inputTextHex->show();
    ui->textBrowser_cipheredPlain->hide();
    ui->label_finalPlain->hide();
    ui->textEdit_inputTextHex->setReadOnly(true);
    ui->label_equal->show();
    ui->label_xor->show();
    ui->label_equal4->hide();
    ui->label_xor4->hide();
}

void MainWindow::afficheDecipher()
{
    clearTextEdit();
    ui->pushButton_decipher->setEnabled(true);
    ui->pushButton_cipher->setEnabled(false);
    ui->label_cipher->hide();
    ui->label_decipher->show();
    ui->radioButton_hexa->setChecked(true);
    ui->radioButton_string->setCheckable(false);
    ui->label_inputHex->hide();
    ui->textEdit_inputTextHex->hide();
    ui->textBrowser_cipheredPlain->show();
    ui->label_finalPlain->show();
    ui->label_equal->show();
    ui->label_xor->show();
    ui->label_equal4->hide();
    ui->label_xor4->hide();
}

void MainWindow::cipherClicked()
{
    afficheCipher();
    CipherMode=true;
}

void MainWindow::decipherClicked()
{
    afficheDecipher();
    CipherMode=false;
}

void MainWindow::aboutClicked()
{
    QMessageBox About;
    About.setText("Cryptographic project : realization of educational demonstrators for RSA, AES and RC4 ciphers");
    About.exec();
}

void MainWindow::clearTextEdit()
{
    ui->textBrowser_ciphered->setText("");
    ui->textBrowser_cipheredPlain->setText("");
    ui->textBrowser_input0->setText("");
    ui->textBrowser_input1->setText("");
    ui->textBrowser_input2->setText("");
    ui->textBrowser_input3->setText("");
    ui->textBrowser_input4->setText("");
    ui->textBrowser_keystream0->setText("");
    ui->textBrowser_keystream1->setText("");
    ui->textBrowser_keystream2->setText("");
    ui->textBrowser_keystream3->setText("");
    ui->textBrowser_keystream4->setText("");
    ui->textBrowser_result0->setText("");
    ui->textBrowser_result1->setText("");
    ui->textBrowser_result2->setText("");
    ui->textBrowser_result3->setText("");
    ui->textBrowser_result4->setText("");
}

void MainWindow::rc4Clicked()
{
    afficheRC4();
}

void MainWindow::rsaClicked()
{
    afficheRSA();
}

void MainWindow::aesClicked()
{
    afficheAES();
}

void MainWindow::cipherButtonClicked()
{
    QString input = ui->textEdit_inputText->toPlainText();
    QString key = ui->textEdit_key->toPlainText();
    QString input_qhex;

    input = textCleaner(input);

    std::string input_str = input.toStdString();

    std::string key_str = key.toStdString();
    std::string input_hex = rc4_obj.string_to_hex(input_str);

    if(ui->radioButton_string->isChecked())
        input_qhex = QString::fromStdString(input_hex);
    else //ui->radioButton_hex->isChecked()
        input_qhex = input;

    ui->textEdit_inputTextHex->setText(input_qhex);

    if(ui->radioButton_hexa->isChecked())
        rc4_obj.cipher(input_str,key_str,true);
    else
        rc4_obj.cipher(input_str,key_str,false);
}

void MainWindow::decipherButtonClicked()
{
    QString input = ui->textEdit_inputText->toPlainText();
    QString key = ui->textEdit_key->toPlainText();

    input = textCleaner(input);

    std::string input_str = input.toStdString();
    std::string key_str = key.toStdString();

    input = QString::fromStdString(input_str);

    rc4_obj.decipher(input_str,key_str);
}

QString MainWindow::textCleaner(const QString TextToClean)
{
    QString CleanedText(TextToClean);
    //delete spaces at the beginning and at the end
    CleanedText=TextToClean.trimmed();

    //remove accents
    CleanedText=removeAccents(CleanedText);

    //remove spaces
    CleanedText.replace(" ","");

    //to upper case
    CleanedText=CleanedText.toUpper();

    return CleanedText;
}

QString MainWindow::removeAccents(const QString s)
{
    QString diacriticLetters;
    QStringList noDiacriticLetters;
    if (diacriticLetters.isEmpty()) {
            diacriticLetters = QString::fromUtf8("ŠŒŽšœžŸ¥µÀÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖØÙÚÛÜÝßàáâãäåæçèéêëìíîïðñòóôõöøùúûüýÿẑẐŶŷŜŝĜĝĤĥĴĵŴŵĈĉ");
            noDiacriticLetters << "S"<<"OE"<<"Z"<<"s"<<"oe"<<"z"<<"Y"<<"Y"<<"u"<<"A"<<"A"<<"A"<<"A"<<"A"<<"A"<<"AE"<<"C"<<"E"<<"E"<<"E"<<"E"<<"I"<<"I"<<"I"<<"I"<<"D"<<"N"<<"O"<<"O"<<"O"<<"O"<<"O"<<"O"<<"U"<<"U"<<"U"<<"U"<<"Y"<<"s"<<"a"<<"a"<<"a"<<"a"<<"a"<<"a"<<"ae"<<"c"<<"e"<<"e"<<"e"<<"e"<<"i"<<"i"<<"i"<<"i"<<"o"<<"n"<<"o"<<"o"<<"o"<<"o"<<"o"<<"o"<<"u"<<"u"<<"u"<<"u"<<"y"<<"y"<<"z"<<"Z"<<"Y"<<"y"<<"S"<<"s"<<"G"<<"g"<<"H"<<"h"<<"J"<<"j"<<"W"<<"w"<<"C"<<"c";
        }

        QString output = "";
        for (int i = 0; i < s.length(); i++)
        {
            QChar c = s[i];
            int dIndex = diacriticLetters.indexOf(c);
            if (dIndex < 0)
            {
                output.append(c);
            }
            else
            {
                QString replacement = noDiacriticLetters[dIndex];
                output.append(replacement);
            }
        }
        return output;
 }
