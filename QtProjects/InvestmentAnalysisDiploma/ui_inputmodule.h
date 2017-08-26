/********************************************************************************
** Form generated from reading UI file 'inputmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTMODULE_H
#define UI_INPUTMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputModule
{
public:
    QAction *actionAdd_column_after_selected;
    QAction *actionRemove_column_after_selected;
    QAction *actionExit;
    QAction *actionAbout;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *inputDataLabel;
    QSpacerItem *horizontalSpacer_2;
    QTableWidget *invProjDataTableWidget;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *compareInvprojPushButton;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *makeInvPortfolioPushButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *InputModule)
    {
        if (InputModule->objectName().isEmpty())
            InputModule->setObjectName(QStringLiteral("InputModule"));
        InputModule->resize(795, 514);
        actionAdd_column_after_selected = new QAction(InputModule);
        actionAdd_column_after_selected->setObjectName(QStringLiteral("actionAdd_column_after_selected"));
        actionRemove_column_after_selected = new QAction(InputModule);
        actionRemove_column_after_selected->setObjectName(QStringLiteral("actionRemove_column_after_selected"));
        actionExit = new QAction(InputModule);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAbout = new QAction(InputModule);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(InputModule);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(346, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 1);

        inputDataLabel = new QLabel(centralWidget);
        inputDataLabel->setObjectName(QStringLiteral("inputDataLabel"));

        gridLayout->addWidget(inputDataLabel, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(367, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 2);

        invProjDataTableWidget = new QTableWidget(centralWidget);
        invProjDataTableWidget->setObjectName(QStringLiteral("invProjDataTableWidget"));

        gridLayout->addWidget(invProjDataTableWidget, 1, 0, 1, 4);

        horizontalSpacer_5 = new QSpacerItem(586, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 2, 0, 1, 3);

        compareInvprojPushButton = new QPushButton(centralWidget);
        compareInvprojPushButton->setObjectName(QStringLiteral("compareInvprojPushButton"));

        gridLayout->addWidget(compareInvprojPushButton, 2, 3, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(586, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 3, 0, 1, 3);

        makeInvPortfolioPushButton = new QPushButton(centralWidget);
        makeInvPortfolioPushButton->setObjectName(QStringLiteral("makeInvPortfolioPushButton"));

        gridLayout->addWidget(makeInvPortfolioPushButton, 3, 3, 1, 1);

        InputModule->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(InputModule);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 795, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QStringLiteral("menuEdit"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        InputModule->setMenuBar(menuBar);
        mainToolBar = new QToolBar(InputModule);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        InputModule->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(InputModule);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        InputModule->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionExit);
        menuEdit->addAction(actionAdd_column_after_selected);
        menuEdit->addAction(actionRemove_column_after_selected);
        menuHelp->addAction(actionAbout);

        retranslateUi(InputModule);

        QMetaObject::connectSlotsByName(InputModule);
    } // setupUi

    void retranslateUi(QMainWindow *InputModule)
    {
        InputModule->setWindowTitle(QApplication::translate("InputModule", "InputModule", 0));
        actionAdd_column_after_selected->setText(QApplication::translate("InputModule", "Add column after selected", 0));
        actionRemove_column_after_selected->setText(QApplication::translate("InputModule", "Remove column after selected", 0));
        actionExit->setText(QApplication::translate("InputModule", "Exit", 0));
        actionAbout->setText(QApplication::translate("InputModule", "About...", 0));
        inputDataLabel->setText(QApplication::translate("InputModule", "TextLabel", 0));
        compareInvprojPushButton->setText(QApplication::translate("InputModule", "PushButton", 0));
        makeInvPortfolioPushButton->setText(QApplication::translate("InputModule", "PushButton", 0));
        menuFile->setTitle(QApplication::translate("InputModule", "File", 0));
        menuEdit->setTitle(QApplication::translate("InputModule", "Edit", 0));
        menuHelp->setTitle(QApplication::translate("InputModule", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class InputModule: public Ui_InputModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTMODULE_H
