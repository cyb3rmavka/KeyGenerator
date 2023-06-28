#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {

    btn_generete_key = new QPushButton("Генерація ключа");
    btn_copy_key = new QPushButton("Копіювати ключ");
    out_text_key = new QTextEdit();

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

    connect(btn_copy_key, &QPushButton::clicked, this, &MainWindow::handleBtnCopyGenereteKey);
    connect(btn_generete_key, &QPushButton::clicked, this, &MainWindow::handleBtnGenereteKey);


}


void MainWindow::handleBtnCopyGenereteKey(){

    QString text = out_text_key->toPlainText(); // Get the text from the text field

    QClipboard *clipboard = QApplication::clipboard();
    clipboard->setText(text);
}

void MainWindow::handleBtnGenereteKey(){
    KeyGenerator kg;
    QString key = kg.generatedKey();
    out_text_key->setText(key);

}
MainWindow::~MainWindow(){

}
