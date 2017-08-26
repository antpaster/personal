#ifndef SONGADDINGDIALOG_H
#define SONGADDINGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSqlQuery>
#include "filebrowserdialog.h"

namespace Ui {
class SongAddingDialog;
}

class SongAddingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SongAddingDialog(QWidget *parent = 0);
    ~SongAddingDialog();

    QLineEdit *getSongTextLineEdit();
    QLineEdit *getSongTabLineEdit();
    QLineEdit *getSongTranslationLineEdit();
    QLineEdit *getSongAudiofileLineEdit();

    bool isEmpty(QLineEdit *qle);

    bool browseForTextFile(FileBrowserDialog *fbd);
    bool browseForTabFile(FileBrowserDialog *fbd);
    bool browseForTranslationFile(FileBrowserDialog *fbd);
    bool browseForAudiofile(FileBrowserDialog *fbd);

    bool acceptSongInput();

public slots:
    bool insertSongData();

private:
    Ui::SongAddingDialog *ui;
    QString _songName;
    QString _songTextlink;
    QString _songTablink;
    QString _songAudiofilelink;
    QString _songTranslationlink;
    QString _singerName;
    QSqlQuery _insertSongQuery;
};

#endif // SONGADDINGDIALOG_H
