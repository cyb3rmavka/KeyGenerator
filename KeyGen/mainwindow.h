#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "keygenerator.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleBtnGenereteKey();
    void handleBtnCopyGenereteKey();

private:

    QPushButton *btn_generete_key;
    QPushButton *btn_copy_key;
    QTextEdit *out_text_key;
    QVBoxLayout *main_layout;
    QHBoxLayout *btn_layout;
};
#endif // MAINWINDOW_H
