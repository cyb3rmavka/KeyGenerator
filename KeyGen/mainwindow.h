#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QPushButton *btn_generete_key;
    QPushButton *btn_copy_key;
    QLineEdit *out_text_key;
    QVBoxLayout *main_layout;
    QHBoxLayout *btn_layout;
};
#endif // MAINWINDOW_H
