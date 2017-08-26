/********************************************************************************
** Form generated from reading UI file 'filebrowserdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILEBROWSERDIALOG_H
#define UI_FILEBROWSERDIALOG_H

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
#include <QtWidgets/QTreeWidget>

QT_BEGIN_NAMESPACE

class Ui_FileBrowserDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QTreeWidget *fileSystemTreeWidget;
    QLineEdit *fileNameLineEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *FileBrowserDialog)
    {
        if (FileBrowserDialog->objectName().isEmpty())
            FileBrowserDialog->setObjectName(QStringLiteral("FileBrowserDialog"));
        FileBrowserDialog->resize(400, 309);
        gridLayout = new QGridLayout(FileBrowserDialog);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(FileBrowserDialog);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(160, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);

        fileSystemTreeWidget = new QTreeWidget(FileBrowserDialog);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        fileSystemTreeWidget->setHeaderItem(__qtreewidgetitem);
        fileSystemTreeWidget->setObjectName(QStringLiteral("fileSystemTreeWidget"));

        gridLayout->addWidget(fileSystemTreeWidget, 1, 0, 1, 2);

        fileNameLineEdit = new QLineEdit(FileBrowserDialog);
        fileNameLineEdit->setObjectName(QStringLiteral("fileNameLineEdit"));

        gridLayout->addWidget(fileNameLineEdit, 2, 0, 1, 2);

        buttonBox = new QDialogButtonBox(FileBrowserDialog);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(FileBrowserDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), FileBrowserDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), FileBrowserDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(FileBrowserDialog);
    } // setupUi

    void retranslateUi(QDialog *FileBrowserDialog)
    {
        FileBrowserDialog->setWindowTitle(QApplication::translate("FileBrowserDialog", "Dialog", 0));
        label->setText(QApplication::translate("FileBrowserDialog", "Choose the file from the file system:", 0));
    } // retranslateUi

};

namespace Ui {
    class FileBrowserDialog: public Ui_FileBrowserDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILEBROWSERDIALOG_H
