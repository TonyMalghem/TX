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
    rsa(const int em, const std::string dm, const int im, const int ee, const int dd, const int nn) : encoded_message(em),decoded_message(dm),int_message(im),e(ee),d(dd),n(nn){}
    ~rsa(){}
    BigInt getEncoded(){return encoded_message;}
    std::string getDecoded(){return decoded_message;}
    BigInt get_m(){return int_message;}
    BigInt get_e(){return e;}
    BigInt get_d(){return d;}
    BigInt get_n(){return n;}
    void setEncoded(const BigInt em){encoded_message=em;}
    void setDecoded(const std::string dm){decoded_message=dm;}
    void set_m(const BigInt im){int_message=im;}
    void set_e(const BigInt ee){e=ee;}
    void set_d(const BigInt dd){d=dd;}
    void set_n(const int nn){n=nn;}
    int calc_n(const int p, const int q){set_n(p*q);return p*q;}
    int calc_phi_n(const int p, const int q);
    int calc_e(const int phi_n);
    int calc_d(const int phi_n, const int e);
    bool isPrime(int A);
    BigInt cipher(BigInt plaintext, int n, int e);
    BigInt M_to_m(const std::string message); //OS2IP from RFC
    std::string m_to_M(const BigInt message); //OS2IP reverse operation
private:
    BigInt encoded_message;
    std::string decoded_message;
    BigInt int_message;
    BigInt e;
    BigInt d;
    int n;
};

#endif // RSA_H
