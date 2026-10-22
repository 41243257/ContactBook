#include "mywidget.h"
#include "ui_mywidget.h"
#include<QFile>
#include<QDebug>
#include <QTextStream>
#include<QMessageBox>
#include<QFileDialog>

QString mFilename="C:/Users/user/Desktop/1019";

MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MyWidget)
{
    ui->setupUi(this);//呼叫命名空間UI內的Mywidget物件之成員函數setupUi(自己的記憶體位址)<-----w
    ui->conetbook->setColumnCount(4);
    QStringList ColToal;
    ColToal<<"學號"<<"班級"<<"姓名"<<"電話";
    ui->conetbook->setHorizontalHeaderLabels(ColToal);
}

MyWidget::~MyWidget()
{
    delete ui;
}

void MyWidget::on_insetButton_1_clicked()
{
    QTableWidgetItem *col1, *col2, *col3, *col4;
    col1 = new QTableWidgetItem(ui->lineEdit->text());
    col2 = new QTableWidgetItem(ui->lineEdit_2->text());
    col3 = new QTableWidgetItem(ui->lineEdit_3->text());
    col4 = new QTableWidgetItem(ui->lineEdit_4->text());
    int row = ui->conetbook->rowCount();
    ui->conetbook->insertRow(row);//新增在第幾列第幾行
    ui->conetbook->setItem(row, 0, col1);
    ui->conetbook->setItem(row, 1, col2);
    ui->conetbook->setItem(row, 2, col3);
    ui->conetbook->setItem(row, 3, col4);

}

void Write(QString Filename, QString str)
{
    QFile mFile(Filename);
    if (!mFile.open(QFile::WriteOnly | QFile::Text)) {
        qDebug() << "could not open" << Filename;
        return;
    }
    QTextStream out(&mFile);
    out.setEncoding(QStringConverter::System);  // 讓 Excel 開啟時中文不會變亂碼
    out << str;

    mFile.close();
}

QString Read(QString Filename)
{
    QFile mFile(Filename);
    if (!mFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "could not open" << Filename;
        return "";
    }
    QTextStream in(&mFile);
    in.setEncoding(QStringConverter::System);
    QString str = in.readAll();

    mFile.close();
    return str;
}


void MyWidget::on_exportButton_2_clicked()
{
    QString fileName;
    QString saveStr;
    fileName = QFileDialog::getSaveFileName(this,"匯出通訊錄",".",
                                            "csv(*.csv);;text(*.txt)");
    if (fileName.isEmpty())    //按取消就不做事
        return;
    for(int i=0; i<ui->conetbook->rowCount();i++)
    {
        for(int j=0; j<ui->conetbook->columnCount();j++)
        {
            saveStr += ui->conetbook->item(i,j)->text()+(j<ui->conetbook->columnCount()-1 ? ",":"");
        }
        saveStr +="\n";
    }
    Write(fileName,saveStr);
}
void MyWidget::on_importButton_3_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "匯入", ".",
                                                    "CSV (*.csv);;Text (*.txt)");
    if (fileName.isEmpty())      // 使用者按了取消
        return;

    QString readStr = Read(fileName);                              // 先讀檔
    QStringList lines = readStr.split("\n", Qt::SkipEmptyParts);   // 用換行切成一列一列
    int cols = ui->conetbook->columnCount();
    for (int i = 0; i < lines.size(); i++) {

        QStringList items = lines[i].split(",");
        // 用逗號切成一格一格的
        ui->conetbook->insertRow(i);
        for (int j = 0; j < cols; j++) {
            ui->conetbook->setItem(i, j, new QTableWidgetItem(items.value(j)));  // 欄位不夠就放空字串
        }
    }
}
