#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    const QString fileDirectory = QFileDialog::getExistingDirectory(this);
    if (!fileDirectory.isEmpty()) {
        ui->lineEdit->clear();
        ui->lineEdit->setText(fileDirectory);
        ui->lineEdit->setReadOnly(true);
    }
}


void MainWindow::on_pushButton_2_clicked()
{
start:
    if (ui->lineEdit->isReadOnly()) {
        const QString fileDirectory = ui->lineEdit->text();
        QDir currentDirectory = fileDirectory;
        QStringList theList;
        theList = currentDirectory.entryList(QDir::Files);

        foreach (QString fileName, theList) {
            QStringList splittedName = fileName.split(" ");
            if (splittedName.size() > 0) {
                if (splittedName[0].endsWith('.') && splittedName[0].size() >= 2) {
                    QStringList split2 = splittedName[0].split('.');
                    if (split2.size() == 2 && confirmOnlyIntegersExist(split2[0])) {
                        QString newName;
                        for (int i = 1; i < splittedName.size(); i++) {
                            if (i != splittedName.size() && i != 1) {
                                newName += " " + splittedName[i];
                            }else{
                                newName += splittedName[i];
                            }
                        }
                        currentDirectory.rename(fileName, newName);
                    }
                }
            }
        }

        QMessageBox::information(this,
                                 "Rename Success",
                                 "The list numbers \nhave been successfully \nbeen removed.");

    } else
    {
        on_pushButton_clicked();
        goto start;
    }
}

bool MainWindow::confirmOnlyIntegersExist(QString name)
{
    QString numbers = "0123456789";
    for (int i = 0; i < name.length(); i++) {
        if (!numbers.contains(name[i]))
            return false;
    }
    return true;
}
