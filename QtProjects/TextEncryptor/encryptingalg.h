#ifndef ENCRYPTINGALG_H
#define ENCRYPTINGALG_H

#include <QString>
#include <QChar>
#include "mainwindow.h"

class EncryptingAlg
{
public:
    EncryptingAlg(MainWindow *mw);

    QString getKeyWord();
    void setKeyWord(QString qs);

    QString getEncText();
    void setEncText(QString qs);

    QString getDict();
    void setDict(QString qs);

    int getPosFromChar(QChar ch);
    QChar getCharFromPos(int pos);

    QString showKeyCharsPos(MainWindow *mw, QString keyWord);

    QString encryptText(MainWindow *mw, QString keyWord);

    bool clearText(MainWindow *mw);

private:
    QString _keyWord;
    QString _encText;
    QString _dict;
};

#endif // ENCRYPTINGALG_H
