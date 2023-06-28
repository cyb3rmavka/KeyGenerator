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


QString KeyGenerator::generateUniqeSoftwareKey() {
    QString hardwareInfo = retrieveHardwareInfo();

    QByteArray concatenatedData = hardwareInfo.toUtf8();

    QByteArray hashedData = hashData(concatenatedData);

    QString softwareKey = encodeData(hashedData);

    return softwareKey;
}

QString KeyGenerator::generatedKey(){
    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 timestamp = currentDateTime.toMSecsSinceEpoch();

    QString key = QString::number(timestamp);
    key += QString::number(QRandomGenerator::global()->generate());

    // Add different characters to the key
    key += "ABCDEF1234567890!@#$%^&*()";

    QByteArray keyBytes = key.toUtf8();
    QByteArray hashedKey = hashData(keyBytes);
    QString encodedKey = encodeData(hashedKey);

    return encodedKey;
}

