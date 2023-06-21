#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QDialog>
#include <QLineEdit>
#include <QMessageBox>
#include <QSettings>
#include <QSysInfo>
#include <QCryptographicHash>
#include <QVBoxLayout>
#include <QClipboard>

class SoftwareKeyGenerator
{
public:
    QString generateSoftwareKey()
    {
        QString hardwareInfo = retrieveHardwareInfo();
        QByteArray concatenatedData = hardwareInfo.toUtf8();

        QByteArray hashedData = hashData(concatenatedData);

        QString softwareKey = encodeData(hashedData);

        return softwareKey;
    }


private:
    QString retrieveHardwareInfo()
    {
        QString hardwareInfo = QSysInfo::machineUniqueId();

        return hardwareInfo;
    }

    QByteArray hashData(const QByteArray& data)
    {
        return QCryptographicHash::hash(data, QCryptographicHash::Sha256);
    }

    QString encodeData(const QByteArray& data)
    {
        return data.toHex();
    }

};

class DongleWindow : public QMainWindow
{
    Q_OBJECT

public:
    DongleWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Dongle Window");

        SoftwareKeyGenerator keyGenerator;
        QString softwareKey = keyGenerator.generateSoftwareKey();

        QLabel *label = new QLabel(this);
        label->setText("Generated Dongle: " + softwareKey);
        label->setAlignment(Qt::AlignCenter);

        QPushButton *copyButton = new QPushButton("Copy Key", this);
        connect(copyButton, &QPushButton::clicked, [softwareKey]() {
            QApplication::clipboard()->setText(softwareKey);
            QMessageBox::information(nullptr, "Key Copied", "The key has been copied to the clipboard.");
        });

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(label);
        layout->addWidget(copyButton);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }
};
class ActivationDialog : public QDialog
{
    Q_OBJECT

public:
    ActivationDialog(QWidget *parent = nullptr)
        : QDialog(parent)
    {
        setWindowTitle("Activation Window");

        QLabel *label = new QLabel(this);
        label->setText("Enter Product Key:");
        label->setAlignment(Qt::AlignCenter);

        lineEdit = new QLineEdit(this);

        QPushButton *activateButton = new QPushButton("Activate", this);
        connect(activateButton, &QPushButton::clicked, this, &ActivationDialog::activateProduct);

        QVBoxLayout *layout = new QVBoxLayout(this);
        layout->addWidget(label);
        layout->addWidget(lineEdit);
        layout->addWidget(activateButton);

        setLayout(layout);
    }

signals:
    void productActivated(bool activated);

private slots:
    void activateProduct()
    {
        QString productKey = lineEdit->text();

        SoftwareKeyGenerator keyGenerator;
        QString dongleKey = keyGenerator.generateSoftwareKey();

        bool activated = (productKey == dongleKey);

        QSettings settings;
        settings.setValue("Activated", activated);

        emit productActivated(activated);
        close();
    }

private:
    QLineEdit *lineEdit;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr)
        : QMainWindow(parent)
    {
        setWindowTitle("Product Activation");

        QPushButton *dongleButton = new QPushButton("Show Dongle", this);
        connect(dongleButton, &QPushButton::clicked, this, &MainWindow::showDongleWindow);

        QPushButton *activationButton = new QPushButton("Activate Product", this);
        connect(activationButton, &QPushButton::clicked, this, &MainWindow::showActivationDialog);

        QVBoxLayout *layout = new QVBoxLayout();
        layout->addWidget(dongleButton);
        layout->addWidget(activationButton);

        QWidget *centralWidget = new QWidget(this);
        centralWidget->setLayout(layout);
        setCentralWidget(centralWidget);
    }

private slots:
    void showDongleWindow()
    {
        DongleWindow *dongleWindow = new DongleWindow(this);
        dongleWindow->show();
    }

    void showActivationDialog()
    {
        ActivationDialog *activationDialog = new ActivationDialog(this);
        connect(activationDialog, &ActivationDialog::productActivated, this, &MainWindow::handleActivationStatus);
        activationDialog->exec();
    }

    void handleActivationStatus(bool activated)
    {
        QString message;
        if (activated) {
            message = "Product is activated.";
        } else {
            message = "Product is not activated.";
        }

        QMessageBox::information(this, "Activation Status", message);
    }
};

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}

#include "main.moc"