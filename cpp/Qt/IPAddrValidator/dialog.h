#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

#include "3rdparty/ipaddresslineedit.h"

#include "ipaddrctrl.h"

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = 0);
    ~Dialog();

private:
    Utils::IpAddressLineEdit *ipAddrLineEdit;
    IPAddrCtrl *ipAddrCtrl;
};

#endif // DIALOG_H
