#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QFile>
#include <QMessageBox>
#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>
#include <QSettings>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QLineEdit *keyEntryField;
    QPushButton *activationButton;
    QPushButton *deactivationButton;
    QPushButton *statusButton;
    bool keyActive;

private slots:
    void activateKey();

    void deactivateKey();

    void checkStatus();

};
#endif // MAINWINDOW_H
