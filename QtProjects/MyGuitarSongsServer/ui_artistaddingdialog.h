/********************************************************************************
** Form generated from reading UI file 'artistaddingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ARTISTADDINGDIALOG_H
#define UI_ARTISTADDINGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_ArtistAddingDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QLineEdit *artistNameLineEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *artistCountryLineEdit;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *artistGenreLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *ArtistAddingDialog)
    {
        if (ArtistAddingDialog->objectName().isEmpty())
            ArtistAddingDialog->setObjectName(QStringLiteral("ArtistAddingDialog"));
        ArtistAddingDialog->resize(400, 144);
        gridLayout = new QGridLayout(ArtistAddingDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ArtistAddingDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(130, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 3);

        artistNameLineEdit = new QLineEdit(ArtistAddingDialog);
        artistNameLineEdit->setObjectName(QStringLiteral("artistNameLineEdit"));

        gridLayout->addWidget(artistNameLineEdit, 0, 4, 1, 1);

        label_2 = new QLabel(ArtistAddingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        horizontalSpacer_2 = new QSpacerItem(111, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 2, 1, 2);

        artistCountryLineEdit = new QLineEdit(ArtistAddingDialog);
        artistCountryLineEdit->setObjectName(QStringLiteral("artistCountryLineEdit"));

        gridLayout->addWidget(artistCountryLineEdit, 1, 4, 1, 1);

        label_3 = new QLabel(ArtistAddingDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 3);

        horizontalSpacer_3 = new QSpacerItem(92, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 2, 3, 1, 1);

        artistGenreLineEdit = new QLineEdit(ArtistAddingDialog);
        artistGenreLineEdit->setObjectName(QStringLiteral("artistGenreLineEdit"));

        gridLayout->addWidget(artistGenreLineEdit, 2, 4, 1, 1);

        buttonBox = new QDialogButtonBox(ArtistAddingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 5);


        retranslateUi(ArtistAddingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), ArtistAddingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), ArtistAddingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(ArtistAddingDialog);
    } // setupUi

    void retranslateUi(QDialog *ArtistAddingDialog)
    {
        ArtistAddingDialog->setWindowTitle(QApplication::translate("ArtistAddingDialog", "Dialog", 0));
        label->setText(QApplication::translate("ArtistAddingDialog", "Enter the artist name:", 0));
        label_2->setText(QApplication::translate("ArtistAddingDialog", "Enter the artist country:", 0));
        label_3->setText(QApplication::translate("ArtistAddingDialog", "Enter the genre of the artist:", 0));
    } // retranslateUi

};

namespace Ui {
    class ArtistAddingDialog: public Ui_ArtistAddingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ARTISTADDINGDIALOG_H
