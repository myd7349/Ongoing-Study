#include "mainwindow.h"

#include <QtCore/QStringList>
#include <QtGui/QAction>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTableWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QStringList columnNames;
    columnNames << tr("Name") << tr("Sex") << tr("Age");

    stuInfoWidget = new QTableWidget;

    stuInfoWidget->setColumnCount(columnNames.size());
    for (int i = 0; i < columnNames.size(); ++i) {
        QTableWidgetItem *headerItem = new QTableWidgetItem(columnNames[i]);
        stuInfoWidget->setHorizontalHeaderItem(i, headerItem);
    }

    stuInfoWidget->setRowCount(2);

    // Create main menu
    mainMenu = menuBar()->addMenu(tr("Show or hide columns"));
    for (int i = 0; i < columnNames.size(); ++i) {
        QAction *action = new QAction(columnNames[i], this);
        action->setCheckable(true);
        action->setChecked(true);
        action->setData(i);
        mainMenu->addAction(action);
    }
    connect(mainMenu, SIGNAL(triggered(QAction *)),
            this, SLOT(onShowOrHideColumn(QAction *)));

    // Add Context Menu onto the header view of the QTableWidget
    QHeaderView *headerView = stuInfoWidget->horizontalHeader();
    headerView->setContextMenuPolicy(Qt::ActionsContextMenu);
    headerView->addActions(mainMenu->actions());

    setCentralWidget(stuInfoWidget);
}

MainWindow::~MainWindow()
{
}

void MainWindow::onShowOrHideColumn(QAction *action)
{
#if 0
    // The wrong code
    bool isChecked = action->isChecked();
    stuInfoWidget->setColumnHidden(action->data().toInt(),
                                   isChecked);
    action->setChecked(!isChecked);
#else
    stuInfoWidget->setColumnHidden(action->data().toInt(),
                                   !action->isChecked());
#endif
}

