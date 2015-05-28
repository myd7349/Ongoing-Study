#include "ipaddrctrl.h"

#include <QDebug>
#include <QRegExp>
#include <QRegExpValidator>
#include <QStringList>

IPAddrCtrl::IPAddrCtrl(QWidget *parent) :
    QLineEdit(parent)
{
    QRegExp ipAddrREStr("^(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\."
                        "(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\."
                        "(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\."
                        "(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$");

    QRegExp ipAddrRegExp(ipAddrREStr);
    ipAddrValidator = new QRegExpValidator(ipAddrRegExp, this);

    setInputMask("000.000.000.000");

    connect(this, SIGNAL(textChanged(QString)), this, SLOT(onTextChanged(QString)));
}

void IPAddrCtrl::onTextChanged(const QString &value)
{
    int pos = 0;
    QString ipAddr = value;
    bool ok = ipAddrValidator->validate(ipAddr, pos) == QValidator::Acceptable;
    if (ok) {
        return;
    } else {
        QStringList ipAddrFields = ipAddr.split('.');
        Q_ASSERT(ipAddrFields.size() == 4);
        if (ipAddrFields.size() == 4) {
            bool isChanged = false;
            pos = cursorPosition();

            for (int i = 0; i < 4; ++i) {
                if (!ipAddrFields[i].isEmpty()) {
                    int fieldValue = ipAddrFields[i].toInt(&ok);

                    if (ok && fieldValue > 255) {
                        ipAddrFields[i] = "255";
                        if (!isChanged) {
                            isChanged = true;
                        }
                    }

                }
            }

            if (isChanged) {
                ipAddr = ipAddrFields.join('.');
                setText(ipAddr);
                setCursorPosition(pos);
            }
        }
    }
}
