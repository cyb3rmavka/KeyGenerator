#include "mainwindow.h"

unsigned char encryptionKey[AES_BLOCK_SIZE];
unsigned char iv[AES_BLOCK_SIZE];

void generateRandomBytes(unsigned char *buffer, size_t length) {
    if (RAND_bytes(buffer, length) != 1) {
        // Error handling
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    // Create the central widget
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Create the key entry field
    keyEntryField = new QLineEdit(centralWidget);

    // Create the key activation button
    activationButton = new QPushButton("Активація", centralWidget);
    connect(activationButton, &QPushButton::clicked, this, &MainWindow::activateKey);

    // Create the key deactivation button
    deactivationButton = new QPushButton("Деактивація", centralWidget);
    connect(deactivationButton, &QPushButton::clicked, this, &MainWindow::deactivateKey);

    // Create the key status button
    statusButton = new QPushButton("Перевірка статуса", centralWidget);
    connect(statusButton, &QPushButton::clicked, this, &MainWindow::checkStatus);

    // Create the layout
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->addWidget(keyEntryField);
    mainLayout->addWidget(activationButton);
    mainLayout->addWidget(deactivationButton);
    mainLayout->addWidget(statusButton);

    QFile file("activation.bin");
    if (file.exists()) {
        keyActive = true;
    } else {
        keyActive = false;
        QMessageBox::information(this, "Key Status", "The key is inactive.");
    }
}
void MainWindow::activateKey() {
    QString key = keyEntryField->text().trimmed();
    QSettings settings("config.ini", QSettings::IniFormat);
    if(settings.contains("KeyStatus")){
        QMessageBox::information(this, "Статус", "Ключ вже існує, повторна активація");
        keyEntryField->setPlaceholderText("");
        keyEntryField->setDisabled(true);
        keyActive = true;
        settings.setValue("Exist", keyActive);
        return;
    }
    keyActive = true;
    // Save the key status to the configuration file

    settings.setValue("KeyStatus", key);
    settings.setValue("Exist", keyActive);
    QMessageBox::information(this, "Статус", "Ключ активовано!");
    qDebug() << "Key activated";

    // Disable key entry field after activation
    keyEntryField->setDisabled(true);
}

void MainWindow::deactivateKey() {
    QString key = keyEntryField->text();
    keyEntryField->setDisabled(true);
    if (keyActive) {
        qDebug() << "Key deactivated: " << key;
        QMessageBox::information(this, "Деактивація ключа", "Ключ успішно деактивовано");
        keyActive = false;
        QSettings settings("config.ini", QSettings::IniFormat);
        settings.setValue("Exist", keyActive);
    } else {
        qDebug() << "Error deactivating the key";
        QMessageBox::critical(this, "Помилка", "Ключ не було деактивовано");
    }
}

void MainWindow::checkStatus() {
    QString key = keyEntryField->text();

    // TODO: Implement key status check logic here
    // For example, you can read and compare the saved key value

    // Example: Read the saved key value from the file
    QSettings settings("config.ini", QSettings::IniFormat);

    if (settings.contains("KeyStatus")) {
        QString savedKey = settings.value("KeyStatus").toString();
        bool k = settings.value("Exist").toBool();
        if (k) {
            qDebug() << "Key status: Active";
            QMessageBox::information(this, "Статус ключа", "Ключ активовано: " + savedKey);
        } else {
            qDebug() << "Key status: Inactive";
            QMessageBox::information(this, "Статус ключа", "Ключ деактивовано");
        }
    } else {
        qDebug() << "Key status: Inactive";
        QMessageBox::information(this, "Key Status", "The key is inactive.");
    }
}
MainWindow::~MainWindow()
{
}

