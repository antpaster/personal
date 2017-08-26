#ifndef FILEBROWSERDIALOG_H
#define FILEBROWSERDIALOG_H

#include <QDialog>
#include <QFileSystemModel>
#include "songaddingdialog.h"

namespace Ui {
class FileBrowserDialog;
}

class FileBrowserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FileBrowserDialog(QWidget *parent = 0);
    ~FileBrowserDialog();

    void setFileBrowserModel();

    bool setFileToParentLineEdit();

    bool acceptFileChoice();
    bool acceptFileName(SongAddingDialog *sad);

public slots:
    bool setChosenFileToLineEdit();
    bool insertFileName(SongAddingDialog *sad);

private:
    Ui::FileBrowserDialog *ui;
    QFileSystemModel _fileSystemModel;
};

#endif // FILEBROWSERDIALOG_H
