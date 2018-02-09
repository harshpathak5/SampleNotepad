#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDir>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QFont>
#include <QFontDialog>
#include <QColor>
#include <QColorDialog>
#include <QPrinter>
#include <QPrintDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionNew_triggered()
{
    file_path_="";
    ui->textEdit->setText("");
}

void MainWindow::on_actionOpen_triggered()
{
    QString file_name_=QFileDialog::getOpenFileName(this,"Open the file");
    QFile file(file_name_);
    file_path_=file_name_;
    if (!file.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this,"title","File not Open");
        return;
    }
    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setText(text);
    file.close();
}

void MainWindow::on_actionSave_triggered()
{
    QFile file(file_path_);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"title","File not Open");
        return;
    }
    QTextStream out(&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionSave_As_triggered()
{
    QString file_name_=QFileDialog::getSaveFileName(this,"Save the file");
    QFile file(file_name_);
    if (!file.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this,"title","File not Open");
        return;
    }
    QTextStream out (&file);
    QString text = ui->textEdit->toPlainText();
    out << text;
    file.flush();
    file.close();
}

void MainWindow::on_actionCut_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionRedo_triggered()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionAbout_triggered()
{
    QString about_text;
    about_text= "This is a sample notepad.";
    QMessageBox::about(this,"title",about_text);
}

void MainWindow::on_actionFont_triggered()
{
    bool ok;
    QFont font = QFontDialog::getFont(&ok,this);
    if(ok){
        ui->textEdit->setFont(font);
    }else return;
}

void MainWindow::on_actionColor_triggered()
{
    QColor color =QColorDialog::getColor(Qt::white,this,"Choose Color");
    if (color.isValid()){
        ui->textEdit->setTextColor(color);
    }else return;
}

void MainWindow::on_actionPrint_triggered()
{
    QPrinter printer; // add printersupport as an import in QtNotepadDemo.pro
    printer.setPrinterName(" "); //type printer name
    QPrintDialog dialog (&printer,this);
    if (dialog.exec()==QDialog::Rejected) return;
    ui->textEdit->print(&printer);
}
