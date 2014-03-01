#include <string>
#include <iterator>
#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <sstream>
#include <vector>

using namespace std;

void StreamGen(string& Key, int* StreamGenerated);
void KeystreamGen(int* StreamGenerated, int* KeystreamGenerated);
string Cipher(const string& Keystream, const string& Plaintext);
string Decipher(const string& Keystream, const string& EncryptedMessage);

int main(int argc, char** argv) {
    
    //Key chosen by the user to crypt his text
    string Key("Key");
    string Plaintext("Plaintext");
    string stKeystream("");
    string sKeystream[255];
    int Stream[255];
    int Keystream[255];
    
    //Generation of the Stream for the RC4 method => KSA
    StreamGen(Key,Stream);
    
    //Generation of the Keystream for the RC method => PRGA
    KeystreamGen(Stream,Keystream);
    
    //Conversion of the int[] Keystream into a string
    for(int i=0;i<255;i++)
    {
        sKeystream[i]=to_string(Keystream[i]);
        stKeystream+=sKeystream[i];
    }
    
    string EncryptedMessage(Cipher(stKeystream,Plaintext));
    string DecryptedMessage(Decipher(stKeystream,EncryptedMessage));
    
    cout << "Plaintext: " << Plaintext << endl << "Key: " << Key << endl;
    cout << "Keystream: " << stKeystream << endl;
    cout << "Encoded Message: " << EncryptedMessage << endl;
    cout << "Decoded Message: " << DecryptedMessage << endl;
    
    return 0;
}

void StreamGen(string& Key, int *StreamGenerated)
{
    //Local variable for the swapping
    int Swapper = 0;
    
    //Initialisation of the stream
    for(int i=0;i<255;i++)
        StreamGenerated[i] = i;
    
    //Switching the bytes of the table to create the stream
    int j = 0;
    for(int i=0;i<255;i++)
    {
        //Calculate the index with which we're going to swap
        j = (j + StreamGenerated[i] + (Key[i % Key.length()]-'0')) % 255;
        //Swap the cases
        Swapper = StreamGenerated[i];
        StreamGenerated[i]=StreamGenerated[j];
        StreamGenerated[j]=Swapper;
    }
}

void KeystreamGen(int* StreamGenerated, int* KeystreamGenerated)
{
    int i = 0;
    int j = 0;
    int Swapper = 0;
    
    for(int k=0;k<255;k++)
    {
        i = (i + 1) % 255;
        j = (j + StreamGenerated[i]) % 255;
        Swapper = StreamGenerated[i];
        StreamGenerated[i] = StreamGenerated[j];
        StreamGenerated[j] = Swapper;
        KeystreamGenerated[i] = StreamGenerated[(StreamGenerated[i] + StreamGenerated[j]) % 255];
    }
}

string Cipher(const string& Keystream, const string& Plaintext)
{
    string EncryptedMessage(Plaintext);
    for(int i=0;i<Plaintext.length();i++)
    {
        EncryptedMessage[i] = Plaintext[i] ^ Keystream[i];
    }
    return EncryptedMessage;
}

string Decipher(const string& Keystream, const string& EncryptedMessage)
{
    string DecryptedMessage(EncryptedMessage);
    for(int i=0;i<EncryptedMessage.length();i++)
    {
        DecryptedMessage[i] = EncryptedMessage[i] ^ Keystream[i];
    }
    return DecryptedMessage;
}