#ifndef STRINGMANIPULATION_H
#define	STRINGMANIPULATION_H
#include <string>

using namespace std;

void StreamGen(const string& Key, int* StreamGenerated);
void KeystreamGen(int* StreamGenerated, int* KeystreamGenerated);
string Cipher(const string& Keystream, const string& Plaintext);
string Decipher(const string& Keystream, const string& EncryptedMessage);
string TextCleaner(const string& TextToClean);
string removeSpaces(const string& StringToUnspace);

string TextCleaner(const string& TextToClean)
{
    //initialization of the new text with the ancient one
    string CleanedText(TextToClean);
    
    for(int i=0;i<TextToClean.length();i++)
    {
        //lower case to upper case
        if(TextToClean[i]<=122 && TextToClean[i]>=97)
            CleanedText[i]=TextToClean[i]-32;
        
        //é è ê and upper case equivalents
        if(TextToClean[i]==130 || TextToClean[i]>=136 && TextToClean[i]<=138 || TextToClean[i]==144)
            CleanedText[i]=69;
        
        //à â ä and upper case equivalents
        if(TextToClean[i]==160 || TextToClean[i]>=131 && TextToClean[i]<=134 || TextToClean[i]==142 || TextToClean[i]==143)
            CleanedText[i]=65;
        
        //ç and Ç
        if(TextToClean[i]==128 || TextToClean[i]==135)
            CleanedText[i]=67;
        
        //ù û and upper case equivalents
        if(TextToClean[i]==150 || TextToClean[i]==151 || TextToClean[i]==154 || TextToClean[i]=='Û' || TextToClean[i]=='Ù')
            CleanedText[i]=85;
        
        //ô ö and upper case equivalents
        if(TextToClean[i]=='ô' || TextToClean[i]=='ö' || TextToClean[i]=='Ô' || TextToClean[i]=='Ö')
            CleanedText[i]='O';
        
        //î ï and upper case equivalents
        if(TextToClean[i]=='î' || TextToClean[i]=='ï' || TextToClean[i]=='Î' || TextToClean[i]=='Ï')
            CleanedText[i]='I';
    }
    
    //delete spaces
    CleanedText = removeSpaces(CleanedText);
    
    return CleanedText;
}

string removeSpaces(const string& StringToUnspace)
{
    string StringUnspaced(StringToUnspace);
    for(int i=0;i<StringUnspaced.length();i++)
        if(StringUnspaced[i]==' ')
                StringUnspaced.erase(i,1);
    return StringUnspaced;
}

#endif	/* STRINGMANIPULATION_H */

