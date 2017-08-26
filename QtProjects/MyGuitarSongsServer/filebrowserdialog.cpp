#include "filebrowserdialog.h"
#include "ui_filebrowserdialog.h"
#include <QTreeWidget>
#include "songaddingdialog.h"

FileBrowserDialog::FileBrowserDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FileBrowserDialog)
{
    ui->setupUi(this);
}

FileBrowserDialog::~FileBrowserDialog()
{
    delete ui;
}

void FileBrowserDialog::setFileBrowserModel()
{
    _fileSystemModel.setRootPath(QDir::currentPath());
    ui->fileSystemTreeWidget->setModel(_fileSystemModel);
}

bool FileBrowserDialog::acceptFileChoice()
{
    QTreeWidgetItem *qtwi = ui->fileSystemTreeWidget->currentItem();
    return QObject::connect(ui->fileSystemTreeWidget, SIGNAL(itemClicked(qtwi, 1)),
                            ui->fileNameLineEdit, SLOT(setChosenFileToLineEdit()));
}

bool FileBrowserDialog::acceptFileName(SongAddingDialog *sad)
{
    return QObject::connect(this, SIGNAL(accepted()),
                            sad, SLOT(insertFileName(sad)));
}

bool FileBrowserDialog::setChosenFileToLineEdit()
{
    ui->fileNameLineEdit->setText(ui->fileSystemTreeWidget->currentItem()->text(1));
}

bool FileBrowserDialog::insertFileName(SongAddingDialog *sad)
{
    sad->getSongTextLineEdit()->setText(ui->fileNameLineEdit->text());
}
