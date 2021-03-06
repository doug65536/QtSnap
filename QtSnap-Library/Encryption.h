#ifndef ENCRYPTION_H
#define ENCRYPTION_H


#include <QUuid>
#include <QDebug>
#include <QByteArray>

#include "Crypto/aes.h"

class Encryption
{
public:
    static QByteArray encryptSnapOrStory(QByteArray data);
    static QByteArray decryptSnap(QByteArray data);
    static QByteArray decryptStory(QByteArray data, QString keyStr, QString ivStr);

    static QString randomMediaID(QString username);

private:
    static QByteArray& PKCS7Padding(QByteArray &bytes);
    static QByteArray& RemovePKCS7Padding(QByteArray &bytes);

    static const QString AES_KEY;
};

#endif // ENCRYPTION_H
