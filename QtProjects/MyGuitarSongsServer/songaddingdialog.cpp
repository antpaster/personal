#include "songaddingdialog.h"
#include "ui_songaddingdialog.h"
#include "filebrowserdialog.h"

SongAddingDialog::SongAddingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SongAddingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Song adding");
}

SongAddingDialog::~SongAddingDialog()
{
    delete ui;
}

QLineEdit *SongAddingDialog::getSongTextLineEdit()
{
    return ui->songTextLineEdit;
}

QLineEdit *SongAddingDialog::getSongTabLineEdit()
{
    return ui->songTabLineEdit;
}

QLineEdit *SongAddingDialog::getSongTranslationLineEdit()
{
    return ui->songTranslationLineEdit;
}

QLineEdit *SongAddingDialog::getSongAudiofileLineEdit()
{
    return ui->songAudiofileLineEdit;
}

bool SongAddingDialog::isEmpty(QLineEdit *qle)
{
    return qle->text().isEmpty();
}

bool SongAddingDialog::browseForTextFile(FileBrowserDialog *fbd)
{
    fbd->setWindowTitle("Browse for text file");
    return QObject::connect(ui->browseSongTextPushButton, SIGNAL(clicked()),
                            fbd, SLOT(open()));
}

bool SongAddingDialog::browseForTabFile(FileBrowserDialog *fbd)
{
    fbd->setWindowTitle("Browse for tabulature file");
    return QObject::connect(ui->browseSongTabPushButton, SIGNAL(clicked()),
                            fbd, SLOT(open()));
}

bool SongAddingDialog::browseForTranslationFile(FileBrowserDialog *fbd)
{
    fbd->setWindowTitle("Browse for translation file");
    return QObject::connect(ui->browseSongTranslationPushButton, SIGNAL(clicked()),
                            fbd, SLOT(open()));
}

bool SongAddingDialog::browseForAudiofile(FileBrowserDialog *fbd)
{
    fbd->setWindowTitle("Browse for audio file");
    return QObject::connect(ui->browseSongAudiofilePushButton, SIGNAL(clicked()),
                            fbd, SLOT(open()));
}

bool SongAddingDialog::acceptSongInput()
{
    return QObject::connect(this, SIGNAL(accepted()),
                            this, SLOT(insertSongData()));
}

bool SongAddingDialog::insertSongData()
{
    _songName = ui->songNameLineEdit->text();
    _songTextlink = ui->songTextLineEdit->text();
    _songTablink = ui->songTabLineEdit->text();
    _songTranslationlink = ui->songTranslationLineEdit->text();
    _songAudiofilelink = ui->songAudiofileLineEdit->text();
    _singerName = ui->singerNameLineEdit->text();
    QSqlQuery selectArtistQuery;
    int artistIDFK = selectArtistQuery.exec("SELECT ID_artist FROM Artists WHERE"
                                            "artist_name = '" + _singerName + "';");
    if (!this->isEmpty(ui->songNameLineEdit) && !this->isEmpty(ui->songAudiofileLineEdit)
        && artistIDFK)
        return _insertSongQuery.exec("INSERT INTO Songs(song_name, song_textlink, song_tablink,"
                                     "song_translationlink, ID_artist_fk, song_audiofilelink)"
                                     "VALUES('" + _songName + "', '" + _songTextlink + ","
                                     "'" + _songTablink + "', '" + _songTranslationlink + "',"
                                     "" + QString);
}
