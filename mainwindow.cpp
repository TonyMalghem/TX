#include "mainwindow.h"
#include "ui_mainwindow.h"


/*****************************************************************/
/*                               TODO                            */
/*****************************************************************/
/* - ajout mode saisie hexa/string                               */
/* - aes                                                         */
/* - rsa                                                         */
/* - clean code                                                  */
/*****************************************************************/


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
    ui->pushButton_cipher->setEnabled(true);
    ui->pushButton_decipher->setEnabled(false);
    ui->label_cipher->show();
    ui->label_decipher->hide();
    ui->radioButton_hexa->setChecked(true);
    ui->radioButton_string->setCheckable(true);
}

void MainWindow::afficheDecipher()
{
    ui->pushButton_decipher->setEnabled(true);
    ui->pushButton_cipher->setEnabled(false);
    ui->label_cipher->hide();
    ui->label_decipher->show();
    ui->radioButton_hexa->setChecked(true);
    ui->radioButton_string->setCheckable(false);
}

void MainWindow::cipherClicked()
{
    afficheCipher();
}

void MainWindow::decipherClicked()
{
    afficheDecipher();
}

void MainWindow::aboutClicked()
{
    QMessageBox About;
    About.setText("Cryptographic project : realization of educational demonstrators for RSA, AES and RC4 ciphers");
    About.exec();
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
    std::string input_hex = string_to_hex(input_str);

    if(ui->radioButton_string->isChecked())
        input_qhex = QString::fromStdString(input_hex);
    else //ui->radioButton_hex->isChecked()
        input_qhex = input;

    QString inp0 = input_qhex[0] + '\0';
    inp0.append(input_qhex[1]);
    QString inp1 = input_qhex[2] + '\0';
    inp1.append(input_qhex[3]);
    QString inp2 = input_qhex[4] + '\0';
    inp2.append(input_qhex[5]);
    QString inp3 = input_qhex[6] + '\0';
    inp3.append(input_qhex[7]);
    QString inp4 = input_qhex[8] + '\0';
    inp4.append(input_qhex[9]);

    //display of the 5 first char of the input text
    ui->textBrowser_input0->setText(inp0);
    ui->textBrowser_input1->setText(inp1);
    ui->textBrowser_input2->setText(inp2);
    ui->textBrowser_input3->setText(inp3);
    ui->textBrowser_input4->setText(inp4);

    rc4_cipher(input_str,key_str);
}

void MainWindow::decipherButtonClicked()
{
    QString input = ui->textEdit_inputText->toPlainText();
    QString key = ui->textEdit_key->toPlainText();
    QString input_qhex;

    input = textCleaner(input);

    std::string input_str = input.toStdString();
    std::string key_str = key.toStdString();
    std::string input_hex = string_to_hex(input_str);

    input = QString::fromStdString(input_str);

    if(ui->radioButton_string->isChecked())
        input_qhex = QString::fromStdString(input_hex);
    else //ui->radioButton_hex->isChecked()
        input_qhex = input;

    QString inp0 = input_qhex[0] + '\0';
    inp0.append(input_qhex[1]);
    QString inp1 = input_qhex[2] + '\0';
    inp1.append(input_qhex[3]);
    QString inp2 = input_qhex[4] + '\0';
    inp2.append(input_qhex[5]);
    QString inp3 = input_qhex[6] + '\0';
    inp3.append(input_qhex[7]);
    QString inp4 = input_qhex[8] + '\0';
    inp4.append(input_qhex[9]);

    //display of the 5 first char of the input text
    ui->textBrowser_input0->setText(inp0);
    ui->textBrowser_input1->setText(inp1);
    ui->textBrowser_input2->setText(inp2);
    ui->textBrowser_input3->setText(inp3);
    ui->textBrowser_input4->setText(inp4);

    rc4_decipher(input_str,key_str);
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

void MainWindow::rc4_cipher(const std::string plaintext, const std::string key)
{
    int stream_generated[255]={};
    int keystream[255]={};
    std::string keystream_str;
    std::string keystream_hex;
    std::string encoded_message;
    std::string encoded_message_hex;

    //stream and keystream generation
    stream_generation(key, stream_generated);
    keystream_generation(stream_generated, keystream);

    //int[] to std::string for the keystream

    for(int i=0;i<255;i++)
    {
        keystream_str+=keystream[i];
    }
    keystream_hex = string_to_hex(keystream_str);

    for(unsigned int i=0;i<plaintext.length();i++)
    {
        encoded_message += plaintext[i] ^  keystream[i];
    }
    encoded_message_hex = string_to_hex(encoded_message);

    //setup for displaying the results
    QString aff = QString::fromStdString(keystream_hex);

    QString key0 = aff[0] + '\0';
    key0.append(aff[1]);
    QString key1 = aff[2] + '\0';
    key1.append(aff[3]);
    QString key2 = aff[4] + '\0';
    key2.append(aff[5]);
    QString key3 = aff[6] + '\0';
    key3.append(aff[7]);
    QString key4 = aff[8] + '\0';
    key4.append(aff[9]);

    aff.clear();
    aff = QString::fromStdString(encoded_message_hex);

    QString enc0 = aff[0] + '\0';
    enc0.append(aff[1]);
    QString enc1 = aff[2] + '\0';
    enc1.append(aff[3]);
    QString enc2 = aff[4] + '\0';
    enc2.append(aff[5]);
    QString enc3 = aff[6] + '\0';
    enc3.append(aff[7]);
    QString enc4 = aff[8] + '\0';
    enc4.append(aff[9]);

    ui->textBrowser_keystream0->setText(key0);
    ui->textBrowser_keystream1->setText(key1);
    ui->textBrowser_keystream2->setText(key2);
    ui->textBrowser_keystream3->setText(key3);
    ui->textBrowser_keystream4->setText(key4);

    ui->textBrowser_result0->setText(enc0);
    ui->textBrowser_result1->setText(enc1);
    ui->textBrowser_result2->setText(enc2);
    ui->textBrowser_result3->setText(enc3);
    ui->textBrowser_result4->setText(enc4);

    ui->textBrowser_ciphered->setText(aff);
}

void MainWindow::rc4_decipher(const std::string ciphered, const std::string key)
{
    int stream_generated[255]={};
    int keystream[255]={};
    std::string keystream_str;
    std::string keystream_hex;
    std::string decoded_message;
    std::string decoded_message_hex;
    std::string ciphered_str = hex_to_string(ciphered);

    //stream and keystream generation
    stream_generation(key, stream_generated);
    keystream_generation(stream_generated, keystream);

    //int[] to std::string for the keystream

    for(int i=0;i<255;i++)
    {
        keystream_str+=keystream[i];
    }
    keystream_hex = string_to_hex(keystream_str);

    for(unsigned int i=0;i<ciphered_str.length();i++)
    {
        decoded_message += ciphered_str[i] ^ keystream[i];
    }
    decoded_message_hex = string_to_hex(decoded_message);

    //setup for displaying the results
    QString aff = QString::fromStdString(keystream_hex);

    QString key0 = aff[0] + '\0';
    key0.append(aff[1]);
    QString key1 = aff[2] + '\0';
    key1.append(aff[3]);
    QString key2 = aff[4] + '\0';
    key2.append(aff[5]);
    QString key3 = aff[6] + '\0';
    key3.append(aff[7]);
    QString key4 = aff[8] + '\0';
    key4.append(aff[9]);

    aff.clear();
    aff = QString::fromStdString(decoded_message_hex);

    QString enc0 = aff[0] + '\0';
    enc0.append(aff[1]);
    QString enc1 = aff[2] + '\0';
    enc1.append(aff[3]);
    QString enc2 = aff[4] + '\0';
    enc2.append(aff[5]);
    QString enc3 = aff[6] + '\0';
    enc3.append(aff[7]);
    QString enc4 = aff[8] + '\0';
    enc4.append(aff[9]);

    ui->textBrowser_keystream0->setText(key0);
    ui->textBrowser_keystream1->setText(key1);
    ui->textBrowser_keystream2->setText(key2);
    ui->textBrowser_keystream3->setText(key3);
    ui->textBrowser_keystream4->setText(key4);

    ui->textBrowser_result0->setText(enc0);
    ui->textBrowser_result1->setText(enc1);
    ui->textBrowser_result2->setText(enc2);
    ui->textBrowser_result3->setText(enc3);
    ui->textBrowser_result4->setText(enc4);

    ui->textBrowser_ciphered->setText(aff);
}

void MainWindow::stream_generation(const std::string key, int* Stream)
{
    int Swapper=0;
    int j=0;

    //Initialization of the Stream array
    for(int i=0;i<=254;i++)
    {
        Stream[i]=i;
    }

    for(int i=0;i<=254;i++)
    {
        j = (j + Stream[i] + (key[i%key.length()])) % 255;
        Swapper = Stream[i];
        Stream[i] = Stream[j];
        Stream[j] = Swapper;
    }
}

void MainWindow::keystream_generation(int* const stream, int* keystream)
{
    int i=0;
    int j=0;
    int Swapper=0;

    for(int k=0;k<255;k++)
    {
        i=(i+1)%255;
        j=(j+stream[i])%255;
        Swapper=stream[i];
        stream[i]=stream[j];
        stream[j]=Swapper;
        keystream[i]=stream[(stream[i]+stream[j])%255];
    }
}

std::string MainWindow::string_to_hex(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();

    std::string output;
    output.reserve(2 * len);
    for (size_t i = 0; i < len; ++i)
    {
        const unsigned char c = input[i];
        output.push_back(lut[c >> 4]);
        output.push_back(lut[c & 15]);
    }
    return output;
}

std::string MainWindow::hex_to_string(const std::string& input)
{
    static const char* const lut = "0123456789ABCDEF";
    size_t len = input.length();
    if (len & 1) throw std::invalid_argument("odd length");

    std::string output;
    output.reserve(len / 2);
    for (size_t i = 0; i < len; i += 2)
    {
        char a = input[i];
        const char* p = std::lower_bound(lut, lut + 16, a);
        if (*p != a) throw std::invalid_argument("not a hex digit");

        char b = input[i + 1];
        const char* q = std::lower_bound(lut, lut + 16, b);
        if (*q != b) throw std::invalid_argument("not a hex digit");

        output.push_back(((p - lut) << 4) | (q - lut));
    }
    return output;
}
