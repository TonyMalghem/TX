#include <string>
#include <QMouseEvent>

#ifndef RSA_H
#define RSA_H

class rsa {
public:
    rsa(const int em, const std::string dm, const int im, const int ee, const int dd, const int nn) : encoded_message(em),decoded_message(dm),int_message(im),e(ee),d(dd),n(nn){}
    ~rsa(){}
    int getEncoded(){return encoded_message;}
    std::string getDecoded(){return decoded_message;}
    int get_m(){return int_message;}
    int get_e(){return e;}
    int get_d(){return d;}
    int get_n(){return n;}
    void setEncoded(const int em){encoded_message=em;}
    void setDecoded(const std::string dm){decoded_message=dm;}
    void set_m(const int im){int_message=im;}
    void set_e(const int ee){e=ee;}
    void set_d(const int dd){d=dd;}
    void set_n(const int nn){n=nn;}
    int calc_n(const int p, const int q){set_n(p*q);return p*q;}
    int calc_phi_n(const int p, const int q);
    int calc_e(const int phi_n);
    int calc_d(const int phi_n, const int e);
    bool isPrime(int A);
    int cipher(int plaintext, int n, int e);
private:
    int encoded_message;
    std::string decoded_message;
    int int_message;
    int e;
    int d;
    int n;
};

#endif // RSA_H
