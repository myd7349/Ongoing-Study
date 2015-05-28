#include "dialog.h"

#include <QVBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    ipAddrLineEdit = new Utils::IpAddressLineEdit;
    ipAddrLineEdit->setInputMask("000.000.000.000");

    ipAddrCtrl = new IPAddrCtrl;

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(ipAddrLineEdit);
    mainLayout->addWidget(ipAddrCtrl);

    setLayout(mainLayout);
}

Dialog::~Dialog()
{
}
