/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *scanAction;
    QAction *exitAction;
    QAction *aboutAction;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *sourceIPLineEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *scanningTimeSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *scanNetworkPushButton;
    QProgressBar *netwScanningProgressBar;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menu_2;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(354, 179);
        scanAction = new QAction(MainWindow);
        scanAction->setObjectName(QStringLiteral("scanAction"));
        exitAction = new QAction(MainWindow);
        exitAction->setObjectName(QStringLiteral("exitAction"));
        aboutAction = new QAction(MainWindow);
        aboutAction->setObjectName(QStringLiteral("aboutAction"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(55, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 2);

        sourceIPLineEdit = new QLineEdit(centralWidget);
        sourceIPLineEdit->setObjectName(QStringLiteral("sourceIPLineEdit"));

        gridLayout->addWidget(sourceIPLineEdit, 0, 3, 1, 3);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(42, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 3);

        scanningTimeSpinBox = new QSpinBox(centralWidget);
        scanningTimeSpinBox->setObjectName(QStringLiteral("scanningTimeSpinBox"));

        gridLayout->addWidget(scanningTimeSpinBox, 1, 5, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(252, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 0, 1, 4);

        scanNetworkPushButton = new QPushButton(centralWidget);
        scanNetworkPushButton->setObjectName(QStringLiteral("scanNetworkPushButton"));

        gridLayout->addWidget(scanNetworkPushButton, 2, 4, 1, 2);

        netwScanningProgressBar = new QProgressBar(centralWidget);
        netwScanningProgressBar->setObjectName(QStringLiteral("netwScanningProgressBar"));
        netwScanningProgressBar->setValue(24);

        gridLayout->addWidget(netwScanningProgressBar, 3, 0, 1, 6);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 354, 21));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menu_2 = new QMenu(menuBar);
        menu_2->setObjectName(QStringLiteral("menu_2"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menu_2->menuAction());
        menu->addAction(scanAction);
        menu->addSeparator();
        menu->addAction(exitAction);
        menu_2->addAction(aboutAction);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        scanAction->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214...", 0));
        exitAction->setText(QApplication::translate("MainWindow", "\320\222\321\213\321\205\320\276\320\264", 0));
        aboutAction->setText(QApplication::translate("MainWindow", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265...", 0));
        label->setText(QApplication::translate("MainWindow", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 IP-\320\260\320\264\321\200\320\265\321\201 \321\203\320\267\320\273\320\260 \320\276\321\202\320\277\321\200\320\260\320\262\320\270\321\202\320\265\320\273\321\217:", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\243\320\272\320\260\320\266\320\270\321\202\320\265 \320\262\321\200\320\265\320\274\321\217 \321\201\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\320\275\320\270\321\217 \321\201\320\265\321\202\320\270 \320\262 \321\201\320\265\320\272\321\203\320\275\320\264\320\260\321\205:", 0));
        scanNetworkPushButton->setText(QApplication::translate("MainWindow", "\320\241\320\272\320\260\320\275\320\270\321\200\320\276\320\262\320\260\321\202\321\214", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\244\320\260\320\271\320\273", 0));
        menu_2->setTitle(QApplication::translate("MainWindow", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
