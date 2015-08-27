/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *equationLabel;
    QSpacerItem *horizontalSpacer;
    QLineEdit *equationLineEdit;
    QLabel *lowIntegrLimitLabel;
    QSpacerItem *horizontalSpacer_2;
    QDoubleSpinBox *lowIntegrLimitDoubleSpinBox;
    QLabel *highIntegrLimitLabel;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *highIntegrLimitDoubleSpinBox;
    QLabel *iterationCountLabel;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *iterationCountLineEdit;
    QGraphicsView *graphicsView;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *calcPushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(429, 416);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        equationLabel = new QLabel(centralWidget);
        equationLabel->setObjectName(QStringLiteral("equationLabel"));

        gridLayout->addWidget(equationLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(227, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        equationLineEdit = new QLineEdit(centralWidget);
        equationLineEdit->setObjectName(QStringLiteral("equationLineEdit"));

        gridLayout->addWidget(equationLineEdit, 0, 2, 1, 3);

        lowIntegrLimitLabel = new QLabel(centralWidget);
        lowIntegrLimitLabel->setObjectName(QStringLiteral("lowIntegrLimitLabel"));

        gridLayout->addWidget(lowIntegrLimitLabel, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 3);

        lowIntegrLimitDoubleSpinBox = new QDoubleSpinBox(centralWidget);
        lowIntegrLimitDoubleSpinBox->setObjectName(QStringLiteral("lowIntegrLimitDoubleSpinBox"));

        gridLayout->addWidget(lowIntegrLimitDoubleSpinBox, 1, 4, 1, 1);

        highIntegrLimitLabel = new QLabel(centralWidget);
        highIntegrLimitLabel->setObjectName(QStringLiteral("highIntegrLimitLabel"));

        gridLayout->addWidget(highIntegrLimitLabel, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(275, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 3);

        highIntegrLimitDoubleSpinBox = new QDoubleSpinBox(centralWidget);
        highIntegrLimitDoubleSpinBox->setObjectName(QStringLiteral("highIntegrLimitDoubleSpinBox"));

        gridLayout->addWidget(highIntegrLimitDoubleSpinBox, 2, 4, 1, 1);

        iterationCountLabel = new QLabel(centralWidget);
        iterationCountLabel->setObjectName(QStringLiteral("iterationCountLabel"));

        gridLayout->addWidget(iterationCountLabel, 3, 0, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(312, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 1, 1, 2);

        iterationCountLineEdit = new QLineEdit(centralWidget);
        iterationCountLineEdit->setObjectName(QStringLiteral("iterationCountLineEdit"));

        gridLayout->addWidget(iterationCountLineEdit, 3, 3, 1, 2);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        gridLayout->addWidget(graphicsView, 4, 0, 1, 5);

        horizontalSpacer_4 = new QSpacerItem(327, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 5, 0, 1, 4);

        calcPushButton = new QPushButton(centralWidget);
        calcPushButton->setObjectName(QStringLiteral("calcPushButton"));

        gridLayout->addWidget(calcPushButton, 5, 4, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 429, 21));
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
        equationLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        lowIntegrLimitLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        highIntegrLimitLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        iterationCountLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        calcPushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
