#ifndef IPADDRCTRL_H
#define IPADDRCTRL_H

#include <QLineEdit>

QT_BEGIN_NAMESPACE
class QRegExpValidator;
QT_END_NAMESPACE

class IPAddrCtrl : public QLineEdit
{
    Q_OBJECT
public:
    explicit IPAddrCtrl(QWidget *parent = 0);
private slots:
    void onTextChanged(const QString &value);
private:
    QRegExpValidator* ipAddrValidator;
};

#endif // IPADDRCTRL_H
