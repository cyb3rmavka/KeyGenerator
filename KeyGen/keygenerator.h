#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QSettings>
#include <QDateTime>
#include <QRandomGenerator>


class KeyGenerator
{
public:
    QString generateUniqeSoftwareKey();
    QString generatedKey();

private:
    QString retrieveHardwareInfo();
    QByteArray hashData(const QByteArray& data);
    QString encodeData(const QByteArray& data);
};

#endif // KEYGENERATOR_H
