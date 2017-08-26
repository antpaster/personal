/********************************************************************************
** Form generated from reading UI file 'invportfoliomakingmodule.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INVPORTFOLIOMAKINGMODULE_H
#define UI_INVPORTFOLIOMAKINGMODULE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InvPortfolioMakingModule
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *invPortfolioMakingLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *discountRateLabel;
    QSpacerItem *horizontalSpacer_3;
    QDoubleSpinBox *discountRateDoubleSpinBox;
    QRadioButton *enoughCapitalRadioButton;
    QSpacerItem *horizontalSpacer_4;
    QRadioButton *notEnoughCapitalRadioButton;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QRadioButton *shortCapitalLimitationTimeRadioButton;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_7;
    QRadioButton *longCapitalLimitationTimeRadioButton;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *toExactPortfMakingPushButton;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *InvPortfolioMakingModule)
    {
        if (InvPortfolioMakingModule->objectName().isEmpty())
            InvPortfolioMakingModule->setObjectName(QStringLiteral("InvPortfolioMakingModule"));
        InvPortfolioMakingModule->resize(800, 263);
        centralwidget = new QWidget(InvPortfolioMakingModule);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(448, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 0, 1, 4);

        invPortfolioMakingLabel = new QLabel(centralwidget);
        invPortfolioMakingLabel->setObjectName(QStringLiteral("invPortfolioMakingLabel"));

        gridLayout->addWidget(invPortfolioMakingLabel, 0, 4, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(251, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 5, 1, 2);

        discountRateLabel = new QLabel(centralwidget);
        discountRateLabel->setObjectName(QStringLiteral("discountRateLabel"));

        gridLayout->addWidget(discountRateLabel, 1, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(375, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 1, 1, 5);

        discountRateDoubleSpinBox = new QDoubleSpinBox(centralwidget);
        discountRateDoubleSpinBox->setObjectName(QStringLiteral("discountRateDoubleSpinBox"));

        gridLayout->addWidget(discountRateDoubleSpinBox, 1, 6, 1, 1);

        enoughCapitalRadioButton = new QRadioButton(centralwidget);
        enoughCapitalRadioButton->setObjectName(QStringLiteral("enoughCapitalRadioButton"));

        gridLayout->addWidget(enoughCapitalRadioButton, 2, 0, 1, 2);

        horizontalSpacer_4 = new QSpacerItem(449, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 2, 2, 1, 5);

        notEnoughCapitalRadioButton = new QRadioButton(centralwidget);
        notEnoughCapitalRadioButton->setObjectName(QStringLiteral("notEnoughCapitalRadioButton"));

        gridLayout->addWidget(notEnoughCapitalRadioButton, 3, 0, 1, 2);

        horizontalSpacer_5 = new QSpacerItem(449, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 3, 2, 1, 5);

        horizontalSpacer_6 = new QSpacerItem(266, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 4, 0, 1, 1);

        shortCapitalLimitationTimeRadioButton = new QRadioButton(centralwidget);
        shortCapitalLimitationTimeRadioButton->setObjectName(QStringLiteral("shortCapitalLimitationTimeRadioButton"));

        gridLayout->addWidget(shortCapitalLimitationTimeRadioButton, 4, 1, 1, 2);

        horizontalSpacer_8 = new QSpacerItem(394, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 4, 3, 1, 4);

        horizontalSpacer_7 = new QSpacerItem(266, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 5, 0, 1, 1);

        longCapitalLimitationTimeRadioButton = new QRadioButton(centralwidget);
        longCapitalLimitationTimeRadioButton->setObjectName(QStringLiteral("longCapitalLimitationTimeRadioButton"));

        gridLayout->addWidget(longCapitalLimitationTimeRadioButton, 5, 1, 1, 2);

        horizontalSpacer_9 = new QSpacerItem(394, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_9, 5, 3, 1, 4);

        horizontalSpacer_10 = new QSpacerItem(650, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_10, 6, 0, 1, 6);

        toExactPortfMakingPushButton = new QPushButton(centralwidget);
        toExactPortfMakingPushButton->setObjectName(QStringLiteral("toExactPortfMakingPushButton"));

        gridLayout->addWidget(toExactPortfMakingPushButton, 6, 6, 1, 1);

        InvPortfolioMakingModule->setCentralWidget(centralwidget);
        menubar = new QMenuBar(InvPortfolioMakingModule);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        InvPortfolioMakingModule->setMenuBar(menubar);
        statusbar = new QStatusBar(InvPortfolioMakingModule);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        InvPortfolioMakingModule->setStatusBar(statusbar);

        retranslateUi(InvPortfolioMakingModule);

        QMetaObject::connectSlotsByName(InvPortfolioMakingModule);
    } // setupUi

    void retranslateUi(QMainWindow *InvPortfolioMakingModule)
    {
        InvPortfolioMakingModule->setWindowTitle(QApplication::translate("InvPortfolioMakingModule", "MainWindow", 0));
        invPortfolioMakingLabel->setText(QApplication::translate("InvPortfolioMakingModule", "TextLabel", 0));
        discountRateLabel->setText(QApplication::translate("InvPortfolioMakingModule", "TextLabel", 0));
        enoughCapitalRadioButton->setText(QApplication::translate("InvPortfolioMakingModule", "RadioButton", 0));
        notEnoughCapitalRadioButton->setText(QApplication::translate("InvPortfolioMakingModule", "RadioButton", 0));
        shortCapitalLimitationTimeRadioButton->setText(QApplication::translate("InvPortfolioMakingModule", "RadioButton", 0));
        longCapitalLimitationTimeRadioButton->setText(QApplication::translate("InvPortfolioMakingModule", "RadioButton", 0));
        toExactPortfMakingPushButton->setText(QApplication::translate("InvPortfolioMakingModule", "PushButton", 0));
    } // retranslateUi

};

namespace Ui {
    class InvPortfolioMakingModule: public Ui_InvPortfolioMakingModule {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INVPORTFOLIOMAKINGMODULE_H
