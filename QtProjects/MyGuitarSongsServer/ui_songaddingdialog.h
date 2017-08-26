/********************************************************************************
** Form generated from reading UI file 'songaddingdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SONGADDINGDIALOG_H
#define UI_SONGADDINGDIALOG_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_SongAddingDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *songNameLineEdit;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_3;
    QLineEdit *songTextLineEdit;
    QPushButton *browseSongTextPushButton;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_2;
    QLineEdit *songTabLineEdit;
    QPushButton *browseSongTabPushButton;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer;
    QLineEdit *songAudiofileLineEdit;
    QPushButton *browseSongAudiofilePushButton;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_5;
    QLineEdit *songTranslationLineEdit;
    QPushButton *browseSongTranslationPushButton;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *singerNameLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *SongAddingDialog)
    {
        if (SongAddingDialog->objectName().isEmpty())
            SongAddingDialog->setObjectName(QStringLiteral("SongAddingDialog"));
        SongAddingDialog->resize(407, 378);
        gridLayout = new QGridLayout(SongAddingDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(SongAddingDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(140, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_4, 0, 1, 1, 4);

        songNameLineEdit = new QLineEdit(SongAddingDialog);
        songNameLineEdit->setObjectName(QStringLiteral("songNameLineEdit"));

        gridLayout->addWidget(songNameLineEdit, 0, 5, 1, 2);

        label_2 = new QLabel(SongAddingDialog);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(162, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 1, 2, 1, 5);

        songTextLineEdit = new QLineEdit(SongAddingDialog);
        songTextLineEdit->setObjectName(QStringLiteral("songTextLineEdit"));

        gridLayout->addWidget(songTextLineEdit, 2, 0, 1, 6);

        browseSongTextPushButton = new QPushButton(SongAddingDialog);
        browseSongTextPushButton->setObjectName(QStringLiteral("browseSongTextPushButton"));

        gridLayout->addWidget(browseSongTextPushButton, 2, 6, 1, 1);

        label_3 = new QLabel(SongAddingDialog);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 3, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(125, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 3, 3, 1, 4);

        songTabLineEdit = new QLineEdit(SongAddingDialog);
        songTabLineEdit->setObjectName(QStringLiteral("songTabLineEdit"));

        gridLayout->addWidget(songTabLineEdit, 4, 0, 1, 6);

        browseSongTabPushButton = new QPushButton(SongAddingDialog);
        browseSongTabPushButton->setObjectName(QStringLiteral("browseSongTabPushButton"));

        gridLayout->addWidget(browseSongTabPushButton, 4, 6, 1, 1);

        label_4 = new QLabel(SongAddingDialog);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 5, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(162, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 5, 2, 1, 5);

        songAudiofileLineEdit = new QLineEdit(SongAddingDialog);
        songAudiofileLineEdit->setObjectName(QStringLiteral("songAudiofileLineEdit"));

        gridLayout->addWidget(songAudiofileLineEdit, 6, 0, 1, 6);

        browseSongAudiofilePushButton = new QPushButton(SongAddingDialog);
        browseSongAudiofilePushButton->setObjectName(QStringLiteral("browseSongAudiofilePushButton"));

        gridLayout->addWidget(browseSongAudiofilePushButton, 6, 6, 1, 1);

        label_5 = new QLabel(SongAddingDialog);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 7, 0, 1, 5);

        horizontalSpacer_5 = new QSpacerItem(90, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_5, 7, 6, 1, 1);

        songTranslationLineEdit = new QLineEdit(SongAddingDialog);
        songTranslationLineEdit->setObjectName(QStringLiteral("songTranslationLineEdit"));

        gridLayout->addWidget(songTranslationLineEdit, 8, 0, 1, 6);

        browseSongTranslationPushButton = new QPushButton(SongAddingDialog);
        browseSongTranslationPushButton->setObjectName(QStringLiteral("browseSongTranslationPushButton"));

        gridLayout->addWidget(browseSongTranslationPushButton, 8, 6, 1, 1);

        label_6 = new QLabel(SongAddingDialog);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 9, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(126, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 9, 1, 1, 3);

        singerNameLineEdit = new QLineEdit(SongAddingDialog);
        singerNameLineEdit->setObjectName(QStringLiteral("singerNameLineEdit"));

        gridLayout->addWidget(singerNameLineEdit, 9, 4, 1, 3);

        buttonBox = new QDialogButtonBox(SongAddingDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 10, 0, 1, 7);


        retranslateUi(SongAddingDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), SongAddingDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), SongAddingDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(SongAddingDialog);
    } // setupUi

    void retranslateUi(QDialog *SongAddingDialog)
    {
        SongAddingDialog->setWindowTitle(QApplication::translate("SongAddingDialog", "Dialog", 0));
        label->setText(QApplication::translate("SongAddingDialog", "Enter the song name:", 0));
        label_2->setText(QApplication::translate("SongAddingDialog", "Enter the name of the song text file:", 0));
        browseSongTextPushButton->setText(QApplication::translate("SongAddingDialog", "Browse...", 0));
        label_3->setText(QApplication::translate("SongAddingDialog", "Enter the name of the song tabulature file:", 0));
        browseSongTabPushButton->setText(QApplication::translate("SongAddingDialog", "Browse...", 0));
        label_4->setText(QApplication::translate("SongAddingDialog", "Enter the name of the song audio file:", 0));
        browseSongAudiofilePushButton->setText(QApplication::translate("SongAddingDialog", "Browse...", 0));
        label_5->setText(QApplication::translate("SongAddingDialog", "Enter the name of the song translation file name:", 0));
        browseSongTranslationPushButton->setText(QApplication::translate("SongAddingDialog", "Browse..", 0));
        label_6->setText(QApplication::translate("SongAddingDialog", "Enter the singer name:", 0));
    } // retranslateUi

};

namespace Ui {
    class SongAddingDialog: public Ui_SongAddingDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SONGADDINGDIALOG_H
