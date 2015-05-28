#ifndef DIALOG_H
#define DIALOG_H

#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void convert();

private:
    QLabel *imageLabel;
    QPushButton *convButton;
};

#endif // DIALOG_H
