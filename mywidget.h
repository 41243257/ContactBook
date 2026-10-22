#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class MyWidget;
}
QT_END_NAMESPACE

class MyWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MyWidget(QWidget *parent = nullptr);
    ~MyWidget() override;

private slots:
    void on_insetButton_1_clicked();

    void on_exportButton_2_clicked();

    void on_importButton_3_clicked();

private:
    Ui::MyWidget *ui;
};
#endif // MYWIDGET_H
