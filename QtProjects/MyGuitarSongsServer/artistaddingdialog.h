#ifndef ARTISTADDINGDIALOG_H
#define ARTISTADDINGDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSqlQuery>

namespace Ui {
class ArtistAddingDialog;
}

class ArtistAddingDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArtistAddingDialog(QWidget *parent = 0);
    ~ArtistAddingDialog();

    bool isEmpty(QLineEdit *qle);

    bool acceptArtistInput();

public slots:
    bool insertArtistData();

private:
    Ui::ArtistAddingDialog *ui;
    QString _artistName;
    QString _artistCountry;
    QString _artistGenre;
    QSqlQuery _insertArtistQuery;
};

#endif // ARTISTADDINGDIALOG_H
