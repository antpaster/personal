/********************************************************************************
** Form generated from reading UI file 'ballcalcresults.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BALLCALCRESULTS_H
#define UI_BALLCALCRESULTS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_BallCalcResults
{
public:
    QVBoxLayout *verticalLayout;
    QTableWidget *ballCalcResTableWidget;
    QGraphicsView *ballCalcGraphicsView;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *BallCalcResults)
    {
        if (BallCalcResults->objectName().isEmpty())
            BallCalcResults->setObjectName(QStringLiteral("BallCalcResults"));
        BallCalcResults->resize(640, 480);
        verticalLayout = new QVBoxLayout(BallCalcResults);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        ballCalcResTableWidget = new QTableWidget(BallCalcResults);
        ballCalcResTableWidget->setObjectName(QStringLiteral("ballCalcResTableWidget"));

        verticalLayout->addWidget(ballCalcResTableWidget);

        ballCalcGraphicsView = new QGraphicsView(BallCalcResults);
        ballCalcGraphicsView->setObjectName(QStringLiteral("ballCalcGraphicsView"));

        verticalLayout->addWidget(ballCalcGraphicsView);

        buttonBox = new QDialogButtonBox(BallCalcResults);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(BallCalcResults);
        QObject::connect(buttonBox, SIGNAL(accepted()), BallCalcResults, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), BallCalcResults, SLOT(reject()));

        QMetaObject::connectSlotsByName(BallCalcResults);
    } // setupUi

    void retranslateUi(QDialog *BallCalcResults)
    {
        BallCalcResults->setWindowTitle(QApplication::translate("BallCalcResults", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class BallCalcResults: public Ui_BallCalcResults {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BALLCALCRESULTS_H
