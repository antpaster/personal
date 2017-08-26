#include "artistaddingdialog.h"
#include "ui_artistaddingdialog.h"

ArtistAddingDialog::ArtistAddingDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArtistAddingDialog)
{
    ui->setupUi(this);
    this->setWindowTitle("Artist adding");
}

ArtistAddingDialog::~ArtistAddingDialog()
{
    delete ui;
}

bool ArtistAddingDialog::isEmpty(QLineEdit *qle)
{
    return qle->text().isEmpty();
}

bool ArtistAddingDialog::acceptArtistInput()
{
    return QObject::connect(this, SIGNAL(accepted()),
                            this, SLOT(insertArtistData()));
}

bool ArtistAddingDialog::insertArtistData()
{
    _artistName = ui->artistNameLineEdit->text();
    _artistCountry = ui->artistCountryLineEdit->text();
    _artistGenre = ui->artistGenreLineEdit->text();
    if (!this->isEmpty(ui->artistNameLineEdit) && !this->isEmpty(ui->artistCountryLineEdit))
        return _insertArtistQuery.exec("INSERT INTO Artists(artist_name, artist_country,"
                                       "artist_genre) VALUES('" + _artistName + "', '" + _artistCountry + "',"
                                       "'" +_artistGenre + "');");
}
