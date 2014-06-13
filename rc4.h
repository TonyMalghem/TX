#include <string>
#include <QMouseEvent>

#ifndef RC4_H
#define RC4_H

/*! \class rc4
 *  \brief Class implementing the functions for the RC4 cryptographic algorithm.
 *  This class contains the definition of the different functions allowing the user to realize the
 *  demonstration of the RC4 cipher.*/

class rc4 {
public:
    /*! \fn rc4
     *  Constructor of the rc4 class
     *  \param[in] std::string e: the encoded message
     *  \param[in]std::string d: the decoded message
     *  \param[in] std::string k: the keystream contructed thanks
     *  thanks to the key*/
    rc4(const std::string e, const std::string d, const std::string k) : encoded_message(e),decoded_message(d),keystream(k){}
    /*! \fn rc4
     *   Destructor of the rc4 class*/
    ~rc4(){}
    /*! \fn getEncoded
     *   Getter for the encoded_message attribute
     *  \param[out] std::string encoded_message: the current value of the encoded_message attribute*/
    std::string getEncoded(){return encoded_message;}
    /*! \fn getDecoded
     *   Getter for the decoded_message attribute
     *  \param[out] std::string decoded_message: the current value of the decoded_message attribute*/
    std::string getDecoded(){return decoded_message;}
    /*! \fn getKeystream
     *   Getter for the keystream attribute
     *  \param[out] std::string keystream: the current value of the keystream attribute*/
    std::string getKeystream(){return keystream;}
    /*! \fn setEncoded
     *   Setter for the encoded_message attribute
     *  \param[in] std::string e: the value to set the encoded_message attribute with*/
    void setEncoded(const std::string e){encoded_message=e;}
    /*! \fn setDecoded
     *   Setter for the decoded_message attribute
     *  \param[in] std::string d: the value to set the decoded_message attribute with*/
    void setDecoded(const std::string d){decoded_message=d;}
    /*! \fn setKeystream
     *   Setter for the keystream attribute
     *  \param[in] std::string k: the value to set the keystream attribute with*/
    void setKeystream(const std::string k){keystream=k;}
    /*! \fn cipher
     *   Implementation of the RC4 cipher
     *  \param[in] std::string plaintext: the plaintext to cipher
     *  \param[in] std::string key: the key to cipher the plaintext
     *  \param[in] bool isHex: a boolean variable to know whether we work with a hexadecimal plaintext or a string plaintext*/
    void cipher(const std::string plaintext, const std::string key, const bool isHex);
    /*! \fn decipher
     *   Implementation of the RC4 cipher
     *  \param[in] std::string ciphered: the ciphered text to decipher
     *  \param[in] std::string key: the key to cipher the plaintext*/
    void decipher(const std::string ciphered, const std::string key);
    /*! \fn stream_generation
     * \brief
     *   generation of the Stream for the cipher
     *  \param[in] std::string key: the key for the cipher used to create the Stream
     *  \param[in] int* Stream: an array containing the Stream generated by the key*/
    void stream_generation(const std::string key, int* Stream);
    /*! \fn keystream_generation
     *   generation of the Stream for the cipher
     *  \param[in] int* stream: an array containing the stream generated by the stream_generation function
     *  \param[in] int* keystream: an array containing the keystream generated by the stream*/
    void keystream_generation(int* const stream, int* keystream);
    /*! \fn string_to_hex
     *   get the hexadecimal conversion of a string
     *  \param[in] std::string input: the string to convert
     *  \param[out] std::string: the hexadecimal conversion of the input string*/
    std::string string_to_hex(const std::string& input);
    /*! \fn hex_to_string
     *   get the string represented by an hexadecimal value
     *  \param[in] std::string input: the hexadecimal string to convert
     *  \param[out] std::string: the string corresponding to the hexadecimal value input*/
    std::string hex_to_string(const std::string& input);

private:
    /*! the value of the encoded message*/
    std::string encoded_message;
    /*! the value of the decoded message*/
    std::string decoded_message;
    /*! the value of the keystream*/
    std::string keystream;
};

#endif // RC4_H
