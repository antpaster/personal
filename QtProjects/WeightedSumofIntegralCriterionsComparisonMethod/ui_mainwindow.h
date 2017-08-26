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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *criterionsCountSpinBox;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_4;
    QSpinBox *variantsCountSpinBox;
    QPushButton *makeTablePushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *clearTablePushButton;
    QTableWidget *tableWidget;
    QPushButton *normalizeTablePushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *calculateTablePushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(398, 397);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 2);

        criterionsCountSpinBox = new QSpinBox(centralWidget);
        criterionsCountSpinBox->setObjectName(QStringLiteral("criterionsCountSpinBox"));

        gridLayout->addWidget(criterionsCountSpinBox, 0, 4, 1, 1);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(44, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 1, 2, 1, 2);

        variantsCountSpinBox = new QSpinBox(centralWidget);
        variantsCountSpinBox->setObjectName(QStringLiteral("variantsCountSpinBox"));

        gridLayout->addWidget(variantsCountSpinBox, 1, 4, 1, 1);

        makeTablePushButton = new QPushButton(centralWidget);
        makeTablePushButton->setObjectName(QStringLiteral("makeTablePushButton"));

        gridLayout->addWidget(makeTablePushButton, 2, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 1, 1, 2);

        clearTablePushButton = new QPushButton(centralWidget);
        clearTablePushButton->setObjectName(QStringLiteral("clearTablePushButton"));

        gridLayout->addWidget(clearTablePushButton, 2, 3, 1, 2);

        tableWidget = new QTableWidget(centralWidget);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 3, 0, 1, 5);

        normalizeTablePushButton = new QPushButton(centralWidget);
        normalizeTablePushButton->setObjectName(QStringLiteral("normalizeTablePushButton"));

        gridLayout->addWidget(normalizeTablePushButton, 4, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(135, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 4, 1, 1, 2);

        calculateTablePushButton = new QPushButton(centralWidget);
        calculateTablePushButton->setObjectName(QStringLiteral("calculateTablePushButton"));

        gridLayout->addWidget(calculateTablePushButton, 4, 3, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 398, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label->setText(QApplication::translate("MainWindow", "Enter the number of the comparison criterions:", 0));
        label_2->setText(QApplication::translate("MainWindow", "Enter the number of the compared variants:", 0));
        makeTablePushButton->setText(QApplication::translate("MainWindow", "Make the table", 0));
        clearTablePushButton->setText(QApplication::translate("MainWindow", "Clear the table", 0));
        normalizeTablePushButton->setText(QApplication::translate("MainWindow", "Normalize", 0));
        calculateTablePushButton->setText(QApplication::translate("MainWindow", "Calculate", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
