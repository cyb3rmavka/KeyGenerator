#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    btn_generete_key = new QPushButton("Генерація ключа");
    btn_copy_key = new QPushButton("Копіювати ключ");
    out_text_key = new QLineEdit();

    btn_layout = new QHBoxLayout();
    btn_layout->addWidget(btn_generete_key);
    btn_layout->addWidget(btn_copy_key);

    main_layout = new QVBoxLayout;
    main_layout->addWidget(out_text_key);
    main_layout->addStretch(1);
    main_layout->addLayout(btn_layout);

    QWidget *centralWidget = new QWidget();
    centralWidget->setLayout(main_layout);
    setCentralWidget(centralWidget);

}

MainWindow::~MainWindow(){

}
