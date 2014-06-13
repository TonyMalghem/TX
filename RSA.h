#include <string>
#include <QMouseEvent>
#include <math.h>
#include <iostream>
#include "BigInt.h"

#ifndef RSA_H
#define RSA_H

/*! \class rsa
 *  \brief Class implementing the functions for the RSA cryptographic algorithm.
 *  This class contains the definition of the different functions allowing the user to realize the
 *  demonstration of the RSA encryption.*/

class rsa {
public:
    /*! \fn rsa
     *  Constructor of the rsa class
     *  \param[in] int em: the encoded message
     *  \param[in] std::string dm: the decoded message
     *  \param[in] int im: the integer representing the message
     *  \param[in] int ee: the number e calculated by the algorithm (the public key)
     *  \param[in] int dd: the number d calculated by the algorithm (the private key)
     *  \param[in] int nn: the number n calculated by the algorithm (argument of the totient function)*/
    rsa(const int em, const std::string dm, const int im, const int ee, const int dd, const int nn) : encoded_message(em),decoded_message(dm),int_message(im),e(ee),d(dd),n(nn){}
    /*! \fn ~rsa
     *  Destructor of the rsa class*/
    ~rsa(){}
    /*! \fn getEncoded
     *  Getter for the encoded_message attribute
     *  \param[out] BigInt: the current value of the encoded_message attribute*/
    BigInt getEncoded(){return encoded_message;}
    /*! \fn getDecoded
     *  Getter for the decoded_message attribute
     *  \param[out] std::string: the current value of the decoded_message attribute*/
    std::string getDecoded(){return decoded_message;}
    /*! \fn get_m
     *  Getter for the int_message attribute
     *  \param[out] BigInt: the current value of the int_message attribute*/
    BigInt get_m(){return int_message;}
    /*! \fn get_e
     *  Getter for the e attribute
     *  \param[out] BigInt: the current value of the e attribute*/
    BigInt get_e(){return e;}
    /*! \fn get_d
     *  Getter for the d attribute
     *  \param[out] BigInt: the current value of the d attribute*/
    BigInt get_d(){return d;}
    /*! \fn get_n
     *  Getter for the n attribute
     *  \param[out] BigInt: the current value of the n attribute*/
    BigInt get_n(){return n;}
    /*! \fn setEncoded
     *  Setter for the encoded_message attribute
     *  \param[in] BigInt em: the value to set the encoded_message attribute to*/
    void setEncoded(const BigInt em){encoded_message=em;}
    /*! \fn setDecoded
     *  Setter for the decoded_message attribute
     *  \param[in] std_string em: the value to set the decoded_message attribute to*/
    void setDecoded(const std::string dm){decoded_message=dm;}
    /*! \fn set_m
     *  Setter for the int_message attribute
     *  \param[in] BigInt em: the value to set the encoded_message attribute to*/
    void set_m(const BigInt im){int_message=im;}
    /*! \fn set_e
     *  Setter for the e attribute
     *  \param[in] BigInt em: the value to set the e attribute to*/
    void set_e(const BigInt ee){e=ee;}
    /*! \fn set_d
     *  Setter for the d attribute
     *  \param[in] BigInt em: the value to set the d attribute to*/
    void set_d(const BigInt dd){d=dd;}
    /*! \fn set_n
     *  Setter for the n attribute
     *  \param[in] BigInt em: the value to set the n attribute to*/
    void set_n(const int nn){n=nn;}
    /*! \fn calc_n
     *  Calculation of the n parameter
     *  \param[in] int p: the first prime number to calculate n
     *  \param[in] int q: the second prime number to calculate n
     *  \param[out] int n: the result of the product p * q */
    int calc_n(const int p, const int q){set_n(p*q);return p*q;}
    /*! \fn calc_phi_n
     *  Calculation of the totient function
     *  \param[in] int p: the first prime number to calculate the totient
     *  \param[in] int q: the second prime number to calculate the totient
     *  \param[out] int phi(n): the result of the product (p-1) * (q-1) */
    int calc_phi_n(const int p, const int q);
    /*! \fn calc_e
     *  Calculation of the e parameter (the public key)
     *  \param[in] int phi_n: the totient
     *  \param[out] int e: the e number randomly chosen between 0 and phi(n)*/
    int calc_e(const int phi_n);
    /*! \fn calc_d
     *  Calculation of the d parameter (the private key)
     *  \param[in] int phi_n: the totient function
     *  \param[in] int e: the public key
     *  \param[out] int d: the private key calculated using the reverse Euclide algorithm*/
    int calc_d(const int phi_n, const int e);
    /*! \fn isPrime
     *  Check is the input is a prime number
     *  \param[in] int A: the input number to check
     *  \param[out] bool prime: true if the number is a prime number, else false*/
    bool isPrime(int A);
    /*! \fn cipher
     *  Calculation of the ciphered int representing the ciphered message
     *  \param[in] BigInt plaintext: the integer representing the plaintext message to cipher
     *  \param[in] int n: the n parameter
     *  \param[in] int e: the e parameter, the public key
     *  \param[out] BigInt c: the integer number (modulo n) representing the ciphered message*/
    BigInt cipher(BigInt plaintext, int n, int e);
    /*! \fn M_to_m
     *  OS2IP operation as defined in the RFC 3447 (http://tools.ietf.org/html/rfc3447)
     *  \param[in] std::string message: the string message to convert
     *  \param[out] BigInt m: the integer number representing the string*/
    BigInt M_to_m(const std::string message);
    /*! \fn m_to_M
     *  I2OSP operation as defined in the RFC 3447 (http://tools.ietf.org/html/rfc3447)
     *  \param[in] BigInt message: the number representing a string message
     *  \param[out] BigInt m: the string represented by the int message*/
    std::string m_to_M(const BigInt message);
private:
    /*! The encoded message represented by its integer representation*/
    BigInt encoded_message;
    /*! The plaintext decoded message*/
    std::string decoded_message;
    /*! The integer reprenting the plaintext message input*/
    BigInt int_message;
    /*! The public key*/
    BigInt e;
    /*! The private key*/
    BigInt d;
    /*! The number n calculated with the prime number input*/
    int n;
};

#endif // RSA_H
