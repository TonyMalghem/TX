#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "rc4.h"
#include "RSA.h"


/*****************************************************************/
/*                               TODO                            */
/*****************************************************************/
/* - aes                                                         */
/* - rsa : ui                                                    */
/* - rc4 : demonstration construction keystream                  */
/* => intégration shéma dans nouvelle fenêtre avec remplissage   */
/* de labels                                                     */
/* - DOXYGEN                                                     */
/* - exceptions                                                  */
/*****************************************************************/

rc4 rc4_obj("","","");
rsa rsa_obj(0,"",0,0,0,0);

int compt_disp=0;
bool CipherMode=true;
/*1=>rc4 2=>rsa 3=>aes*/
int mode=1;

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
    QObject::connect(ui->actionAES,SIGNAL(triggered()),this,SLOT(aesClicked()));
    QObject::connect(ui->actionRSA,SIGNAL(triggered()),this,SLOT(rsaClicked()));
    QObject::connect(ui->actionRC4,SIGNAL(triggered()),this,SLOT(rc4Clicked()));
    QObject::connect(ui->pushButton_image,SIGNAL(clicked()),this,SLOT(imageButtonClicked()));
    QObject::connect(ui->pushButton_back,SIGNAL(clicked()),this,SLOT(backButtonClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::RightButton)
    {
        if(mode==1)
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
}

void MainWindow::afficheRC4()
{
    afficheCipher();
    hideRSA();
    ui->textEdit_inputText->show();
    ui->textEdit_key->show();
    ui->textBrowser_result0->show();
    ui->textBrowser_result1->show();
    ui->textBrowser_result2->show();
    ui->textBrowser_result3->show();
    ui->textBrowser_result4->show();
    ui->textBrowser_ciphered->show();
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
    ui->label_image->hide();
    ui->pushButton_back->hide();
    ui->textBrowser_img0->hide();
    ui->textBrowser_img1->hide();
    ui->textBrowser_img2->hide();
    ui->textBrowser_img3->hide();
    ui->textBrowser_img4->hide();
    ui->textBrowser_img5->hide();
    ui->textBrowser_img6->hide();
    ui->textBrowser_img7->hide();
    ui->textBrowser_img8->hide();
    ui->textBrowser_img91->hide();
    ui->textBrowser_img99->hide();
}

void MainWindow::hideRSA()
{
    ui->textEdit_RSA_M->hide();
    ui->textEdit_RSA_p->hide();
    ui->textEdit_RSA_q->hide();
    ui->label_RSA_M->hide();
    ui->label_RSA_p->hide();
    ui->label_RSA_q->hide();
    ui->label_RSA_m->hide();
    ui->textBrowser_RSA_m->hide();
}

void MainWindow::hideRC4()
{
    ui->textEdit_inputText->hide();
    ui->textEdit_key->hide();
    ui->textBrowser_result0->hide();
    ui->textBrowser_result1->hide();
    ui->textBrowser_result2->hide();
    ui->textBrowser_result3->hide();
    ui->textBrowser_result4->hide();
    ui->textBrowser_ciphered->hide();
    ui->pushButton_cipher->hide();
    ui->pushButton_decipher->hide();
    ui->label_cipher->hide();
    ui->label_decipher->hide();
    ui->radioButton_hexa->hide();
    ui->radioButton_string->hide();
    ui->label_inputHex->hide();
    ui->textEdit_inputTextHex->hide();
    ui->textBrowser_cipheredPlain->hide();
    ui->label_finalPlain->hide();
    ui->textEdit_inputTextHex->hide();
    ui->textBrowser_input0->hide();
    ui->textBrowser_input1->hide();
    ui->textBrowser_input2->hide();
    ui->textBrowser_input3->hide();
    ui->textBrowser_input4->hide();
    ui->textBrowser_keystream0->hide();
    ui->textBrowser_keystream1->hide();
    ui->textBrowser_keystream2->hide();
    ui->textBrowser_keystream3->hide();
    ui->textBrowser_keystream4->hide();
    ui->label_equal->hide();
    ui->label_xor->hide();
    ui->label_key->hide();
    ui->label_final->hide();
    ui->label_keystreambox->hide();
    ui->label_textbox->hide();
    ui->label_res->hide();
    ui->radioButton_hexa->hide();
    ui->radioButton_string->hide();
    ui->radioButton_string->hide();
    ui->label_inputmode->hide();
    ui->label_equal->hide();
    ui->label_xor->hide();
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
    clearTextEdit();
    hideRC4();
    this->setWindowTitle("RSA");
    ui->textEdit_RSA_M->show();
    ui->textEdit_RSA_p->show();
    ui->textEdit_RSA_q->show();
    ui->label_RSA_M->show();
    ui->label_RSA_p->show();
    ui->label_RSA_q->show();
    ui->pushButton_cipher->show();
    ui->pushButton_decipher->show();
    ui->label_RSA_m->show();
    ui->textBrowser_RSA_m->show();
}

void MainWindow::afficheCipher()
{
    clearTextEdit();
    if(mode==1)
    {
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
}

void MainWindow::afficheDecipher()
{
    clearTextEdit();
    if(mode==1)
    {
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
}

void MainWindow::afficheImage()
{
	ui->label_cipher->hide();
	ui->label_decipher->hide();
	ui->label_equal->hide();
	ui->label_equal1->hide();
	ui->label_equal2->hide();
	ui->label_equal3->hide();
	ui->label_equal4->hide();
	ui->label_final->hide();
	ui->label_finalPlain->hide();
	ui->label_inputHex->hide();
	ui->label_inputmode->hide();
	ui->label_key->hide();
	ui->label_keystreambox->hide();
	ui->label_res->hide();
	ui->label_textbox->hide();
	ui->label_xor->hide();
	ui->label_xor1->hide();
	ui->label_xor2->hide();
	ui->label_xor3->hide();
	ui->label_xor4->hide();
	ui->pushButton_cipher->hide();
	ui->pushButton_decipher->hide();
	ui->pushButton_image->hide();
	ui->radioButton_hexa->hide();
	ui->radioButton_string->hide();
	ui->textBrowser_ciphered->hide();
	ui->textBrowser_cipheredPlain->hide();
	ui->textBrowser_input0->hide();
	ui->textBrowser_input1->hide();
	ui->textBrowser_input2->hide();
	ui->textBrowser_input3->hide();
	ui->textBrowser_input4->hide();
	ui->textBrowser_keystream0->hide();
	ui->textBrowser_keystream1->hide();
	ui->textBrowser_keystream2->hide();
	ui->textBrowser_keystream3->hide();
	ui->textBrowser_keystream4->hide();
	ui->textBrowser_result0->hide();
	ui->textBrowser_result1->hide();
	ui->textBrowser_result2->hide();
	ui->textBrowser_result3->hide();
	ui->textBrowser_result4->hide();
	ui->textEdit_inputText->hide();
	ui->textEdit_inputTextHex->hide();
	ui->textEdit_key->hide();
	
	ui->label_image->show();
	ui->pushButton_back->show();
    ui->textBrowser_img0->show();
    ui->textBrowser_img1->show();
    ui->textBrowser_img2->show();
    ui->textBrowser_img3->show();
    ui->textBrowser_img4->show();
    ui->textBrowser_img5->show();
    ui->textBrowser_img6->show();
    ui->textBrowser_img7->show();
    ui->textBrowser_img8->show();
    ui->textBrowser_img91->show();
    ui->textBrowser_img99->show();
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
    mode=1;
}

void MainWindow::rsaClicked()
{
    afficheRSA();
    mode=2;
}

void MainWindow::aesClicked()
{
    afficheAES();
    mode=3;
}

void MainWindow::cipherButtonClicked()
{
    if(mode==1)/*if we're working in RC4*/
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
    else if(mode==2)/*RSA*/
    {
        int input_p = ui->textEdit_RSA_p->toPlainText().toInt();
        int input_q = ui->textEdit_RSA_q->toPlainText().toInt();
        std::string input_message = ui->textEdit_RSA_M->toPlainText().toStdString();

        if(rsa_obj.isPrime(input_p) && rsa_obj.isPrime(input_q))
        {
            int n = rsa_obj.calc_n(input_p,input_q);
            int phi_n = rsa_obj.calc_phi_n(input_p,input_q);
            int e = rsa_obj.calc_e(phi_n);
            int d = rsa_obj.calc_d(phi_n,e);
            int in_input_message = input_message.length()+(n/3);
            rsa_obj.set_d(d);
            rsa_obj.set_n(n);
            rsa_obj.set_e(e);
            int encoded = rsa_obj.cipher(in_input_message,n,e);
            int decoded = rsa_obj.cipher(encoded,n,d);
            qDebug()<<"m: "<<in_input_message<<endl<<"encoded: "<<encoded<<endl<<"decoded: "<<decoded;
            rsa_obj.setEncoded(encoded);
        }
    }
    else/*AES*/
    {
    }
}

void MainWindow::decipherButtonClicked()
{
    if(mode==1)
    {
        QString input = ui->textEdit_inputText->toPlainText();
        QString key = ui->textEdit_key->toPlainText();

        input = textCleaner(input);

        std::string input_str = input.toStdString();
        std::string key_str = key.toStdString();

        input = QString::fromStdString(input_str);

        rc4_obj.decipher(input_str,key_str);
    }
    else if(mode==2)
    {
    }
    else
    {
    }
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
 
 void MainWindow::remplissageImage()
{
    QString key = ui->textEdit_key->toPlainText();
    std::string key_str = key.toStdString();
    int stream_generated[255] = {};
    int i = 0;
    int j = 0;
    int a0,a1,a2,a3,a4,a5,a6,a8,a99;

    if (key_str.length() <2)
    {
        return;
    }
    else
    {
    rc4_obj.stream_generation(key_str, stream_generated);

    i = (i + 1) % 255;
    j = (j + stream_generated[i]) % 255;

        a0 = stream_generated[i];
        a1 = stream_generated[j];
        a2 = stream_generated[j];
        a3 = stream_generated[i];
        a4 = stream_generated[j];
        a5 = stream_generated[i];
        a6 = stream_generated[(stream_generated[i] + stream_generated[j]) % 255];
        a8 = i;
        a99 = j;

        ui->textBrowser_img0->setText(QString::number(a0));
        ui->textBrowser_img1->setText(QString::number(a1));
        ui->textBrowser_img2->setText(QString::number(a2));
        ui->textBrowser_img3->setText(QString::number(a3));
        ui->textBrowser_img4->setText(QString::number(a4));
        ui->textBrowser_img5->setText(QString::number(a5));
        ui->textBrowser_img6->setText(QString::number(a6));
        ui->textBrowser_img8->setText(QString::number(a8));
        ui->textBrowser_img99->setText(QString::number(a99));
    }
}

void MainWindow::imageButtonClicked()
{
    afficheImage();
    remplissageImage();

    ui->textBrowser_img0->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img0->setGeometry(QRect(531, 123, 40, 30));

    ui->textBrowser_img1->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img1->setGeometry(QRect(713, 123, 40, 30));

    ui->textBrowser_img2->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img2->setGeometry(QRect(531, 203, 40, 30));

    ui->textBrowser_img3->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img3->setGeometry(QRect(713, 203, 40, 30));

    ui->textBrowser_img4->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img4->setGeometry(QRect(531, 282, 40, 30));

    ui->textBrowser_img5->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img5->setGeometry(QRect(713, 282, 40, 30));

    ui->textBrowser_img6->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img6->setGeometry(QRect(402, 282, 40, 30));

    ui->textBrowser_img7->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img7->setGeometry(QRect(800, 400, 120, 30));

    ui->textBrowser_img8->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img8->setGeometry(QRect(900, 400, 40, 30));

    ui->textBrowser_img91->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img91->setGeometry(QRect(800, 500, 120, 30));

    ui->textBrowser_img99->setStyleSheet("background-color: #6699FF");
    ui->textBrowser_img99->setGeometry(QRect(900, 500, 40, 30));

    QPixmap *p=new QPixmap("C:/Users/Julien/Desktop/TX/Application/rc4_keystream.jpg");
    QPixmap p1(p->scaled ( ui->label_image->width(),ui->label_image->height(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation ));
    ui->label_image->setPixmap(p1);
    ui->label_image->show();
    ui->label_image->adjustSize();

    ui->pushButton_back->setGeometry(QRect(1100, 500, 60, 30));
}

void MainWindow::backButtonClicked()
{
    ui->label_image->hide();
    ui->pushButton_back->hide();
    ui->textBrowser_img0->hide();
    ui->textBrowser_img1->hide();
    ui->textBrowser_img2->hide();
    ui->textBrowser_img3->hide();
    ui->textBrowser_img4->hide();
    ui->textBrowser_img5->hide();
    ui->textBrowser_img6->hide();
    ui->textBrowser_img7->hide();
    ui->textBrowser_img8->hide();
    ui->textBrowser_img91->hide();
    ui->textBrowser_img99->hide();

    ui->label_cipher->show();
    ui->label_decipher->show();
    ui->label_equal->show();
    ui->label_equal1->show();
    ui->label_equal2->show();
    ui->label_equal3->show();
    ui->label_equal4->show();
    ui->label_final->show();
    ui->label_finalPlain->show();
    ui->label_inputHex->show();
    ui->label_inputmode->show();
    ui->label_key->show();
    ui->label_keystreambox->show();
    ui->label_res->show();
    ui->label_textbox->show();
    ui->label_xor->show();
    ui->label_xor1->show();
    ui->label_xor2->show();
    ui->label_xor3->show();
    ui->label_xor4->show();
    ui->pushButton_cipher->show();
    ui->pushButton_decipher->show();
    ui->pushButton_image->show();
    ui->radioButton_hexa->show();
    ui->radioButton_string->show();
    ui->textBrowser_ciphered->show();
    ui->textBrowser_cipheredPlain->show();
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
    ui->textBrowser_result0->show();
    ui->textBrowser_result1->show();
    ui->textBrowser_result2->show();
    ui->textBrowser_result3->show();
    ui->textBrowser_result4->show();
    ui->textEdit_inputText->show();
    ui->textEdit_inputTextHex->show();
    ui->textEdit_key->show();
}
