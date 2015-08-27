/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
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
    QAction *actionBayesian_Laplace;
    QAction *actionLaplace;
    QAction *actionMaxi;
    QAction *actionWilde;
    QAction *actionGurvitz;
    QAction *actionExit;
    QAction *actionCriterions_info;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *variantsLabel;
    QSpacerItem *horizontalSpacer;
    QSpinBox *variantsSpinBox;
    QLabel *conditionsLabel;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *conditionsSpinBox;
    QLabel *gammaLabel;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *gammaDoubleSpinBox;
    QPushButton *setTablePushButton;
    QSpacerItem *horizontalSpacer_8;
    QTableWidget *inputDataTableWidget;
    QPushButton *bayeasianLaplacePushButton;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *laplacePushButton;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *maxiPushButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *gurvitzPushButton;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *wildePushButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(700, 394);
        actionBayesian_Laplace = new QAction(MainWindow);
        actionBayesian_Laplace->setObjectName(QStringLiteral("actionBayesian_Laplace"));
        actionLaplace = new QAction(MainWindow);
        actionLaplace->setObjectName(QStringLiteral("actionLaplace"));
        actionMaxi = new QAction(MainWindow);
        actionMaxi->setObjectName(QStringLiteral("actionMaxi"));
        actionWilde = new QAction(MainWindow);
        actionWilde->setObjectName(QStringLiteral("actionWilde"));
        actionGurvitz = new QAction(MainWindow);
        actionGurvitz->setObjectName(QStringLiteral("actionGurvitz"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionCriterions_info = new QAction(MainWindow);
        actionCriterions_info->setObjectName(QStringLiteral("actionCriterions_info"));
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        variantsLabel = new QLabel(centralWidget);
        variantsLabel->setObjectName(QStringLiteral("variantsLabel"));

        gridLayout->addWidget(variantsLabel, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(583, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 9);

        variantsSpinBox = new QSpinBox(centralWidget);
        variantsSpinBox->setObjectName(QStringLiteral("variantsSpinBox"));

        gridLayout->addWidget(variantsSpinBox, 0, 10, 1, 1);

        conditionsLabel = new QLabel(centralWidget);
        conditionsLabel->setObjectName(QStringLiteral("conditionsLabel"));

        gridLayout->addWidget(conditionsLabel, 1, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(583, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 1, 1, 9);

        conditionsSpinBox = new QSpinBox(centralWidget);
        conditionsSpinBox->setObjectName(QStringLiteral("conditionsSpinBox"));

        gridLayout->addWidget(conditionsSpinBox, 1, 10, 1, 1);

        gammaLabel = new QLabel(centralWidget);
        gammaLabel->setObjectName(QStringLiteral("gammaLabel"));

        gridLayout->addWidget(gammaLabel, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(545, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 1, 1, 8);

        gammaDoubleSpinBox = new QDoubleSpinBox(centralWidget);
        gammaDoubleSpinBox->setObjectName(QStringLiteral("gammaDoubleSpinBox"));

        gridLayout->addWidget(gammaDoubleSpinBox, 2, 9, 1, 2);

        setTablePushButton = new QPushButton(centralWidget);
        setTablePushButton->setObjectName(QStringLiteral("setTablePushButton"));

        gridLayout->addWidget(setTablePushButton, 3, 0, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(598, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 3, 2, 1, 9);

        inputDataTableWidget = new QTableWidget(centralWidget);
        inputDataTableWidget->setObjectName(QStringLiteral("inputDataTableWidget"));

        gridLayout->addWidget(inputDataTableWidget, 4, 0, 1, 11);

        bayeasianLaplacePushButton = new QPushButton(centralWidget);
        bayeasianLaplacePushButton->setObjectName(QStringLiteral("bayeasianLaplacePushButton"));

        gridLayout->addWidget(bayeasianLaplacePushButton, 5, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 5, 2, 1, 1);

        laplacePushButton = new QPushButton(centralWidget);
        laplacePushButton->setObjectName(QStringLiteral("laplacePushButton"));

        gridLayout->addWidget(laplacePushButton, 5, 3, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(63, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 5, 4, 1, 1);

        maxiPushButton = new QPushButton(centralWidget);
        maxiPushButton->setObjectName(QStringLiteral("maxiPushButton"));

        gridLayout->addWidget(maxiPushButton, 5, 5, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(61, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 5, 6, 1, 1);

        gurvitzPushButton = new QPushButton(centralWidget);
        gurvitzPushButton->setObjectName(QStringLiteral("gurvitzPushButton"));

        gridLayout->addWidget(gurvitzPushButton, 5, 7, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(62, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 5, 8, 1, 1);

        wildePushButton = new QPushButton(centralWidget);
        wildePushButton->setObjectName(QStringLiteral("wildePushButton"));

        gridLayout->addWidget(wildePushButton, 5, 9, 1, 2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 700, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionBayesian_Laplace);
        menuFile->addAction(actionLaplace);
        menuFile->addAction(actionMaxi);
        menuFile->addAction(actionWilde);
        menuFile->addAction(actionGurvitz);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuAbout->addAction(actionCriterions_info);
        menuAbout->addSeparator();
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        actionBayesian_Laplace->setText(QApplication::translate("MainWindow", "Bayesian-Laplace", 0));
        actionLaplace->setText(QApplication::translate("MainWindow", "Laplace", 0));
        actionMaxi->setText(QApplication::translate("MainWindow", "Maxi", 0));
        actionWilde->setText(QApplication::translate("MainWindow", "Wilde", 0));
        actionGurvitz->setText(QApplication::translate("MainWindow", "Gurvitz", 0));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0));
        actionCriterions_info->setText(QApplication::translate("MainWindow", "Criterions info", 0));
        actionAbout->setText(QApplication::translate("MainWindow", "About", 0));
        variantsLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        conditionsLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        gammaLabel->setText(QApplication::translate("MainWindow", "TextLabel", 0));
        setTablePushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        bayeasianLaplacePushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        laplacePushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        maxiPushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        gurvitzPushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        wildePushButton->setText(QApplication::translate("MainWindow", "PushButton", 0));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0));
        menuAbout->setTitle(QApplication::translate("MainWindow", "About", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
