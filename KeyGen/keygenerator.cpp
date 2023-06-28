#include "keygenerator.h"
QByteArray KeyGenerator::hashData(const QByteArray& data) {
    return QCryptographicHash::hash(data, QCryptographicHash::Sha256);
}

QString KeyGenerator::encodeData(const QByteArray& data) {
    return data.toHex();
}

QString KeyGenerator::retrieveHardwareInfo() {
    QString hardwareInfo = QSysInfo::machineUniqueId();

    return hardwareInfo;
}


QString KeyGenerator::generateSoftwareKey() {
    QString hardwareInfo = retrieveHardwareInfo();

    QByteArray concatenatedData = hardwareInfo.toUtf8();

    QByteArray hashedData = hashData(concatenatedData);

    QString softwareKey = encodeData(hashedData);

    return softwareKey;
}


