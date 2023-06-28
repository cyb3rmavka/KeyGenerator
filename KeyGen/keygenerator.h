#ifndef KEYGENERATOR_H
#define KEYGENERATOR_H

#include <QByteArray>
#include <QCryptographicHash>
#include <QSettings>


class KeyGenerator
{
public:
    QString generateSoftwareKey();
private:
    QString retrieveHardwareInfo();
    QByteArray hashData(const QByteArray& data);
    QString encodeData(const QByteArray& data);
};

#endif // KEYGENERATOR_H
