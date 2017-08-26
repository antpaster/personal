#include "encryptingalg.h"
#include "mainwindow.h"

#include <QClipboard>

EncryptingAlg::EncryptingAlg(MainWindow *mw)
{
    _keyWord = QString();
    _encText = QString();
    _dict = "abcdefghijklmnopqrstuvwxyz";
    mw->getLineEdit()->clear();
    mw->getTextEdit()->clear();
}

QString EncryptingAlg::getKeyWord()
{
    return _keyWord;
}

void EncryptingAlg::setKeyWord(QString qs)
{
    _keyWord = qs;
}

QString EncryptingAlg::getEncText()
{
    return _encText;
}

void EncryptingAlg::setEncText(QString qs)
{
    _encText = qs;
}

QString EncryptingAlg::getDict()
{
    return _dict;
}

void EncryptingAlg::setDict(QString qs)
{
    _dict = qs;
}

int EncryptingAlg::getPosFromChar(QChar ch)
{
    int i;
    for (i = 0; i < _dict.size(); i++)
        if (ch == _dict.at(i))
            break;
    return i;
}

QChar EncryptingAlg::getCharFromPos(int pos)
{
    return _dict.at(pos);
}

QString EncryptingAlg::showKeyCharsPos(MainWindow *mw, QString keyWord)
{
    QString line;
    for (int i = 0; i < keyWord.length(); i++)
        line.append(QString::number(getPosFromChar(keyWord.at(i))) + " ");
    return line;
//    QClipboard *qcb;
//    qcb->setText(line, QClipboard::Clipboard);
//    return QObject::connect(mw->getShowPosPushButton(), SIGNAL(clicked()),
//                            mw->getLineEdit(), SLOT(paste()));
}

QString EncryptingAlg::encryptText(MainWindow *mw, QString keyWord)
{
    int kl = keyWord.length();
    int *keysOffsets = new int[kl];
    for (int i = 0; i < kl; i++)
        keysOffsets[i] = getPosFromChar(keyWord.at(i));

    setEncText(mw->getTextEdit()->toPlainText());

    QString encrStr;
    int encrPos;
    for (int i = 0; i < _encText.length(); i++)
    {
        encrPos = getPosFromChar(_encText.at(i)) + keysOffsets[i % kl];
           if (encrPos > 25)
                encrPos %= 26;
        encrStr.insert(i, getCharFromPos(encrPos));
    }
    return encrStr;
//    QClipboard *qcb;
//    qcb->setText(encrStr, QClipboard::Clipboard);
//    return QObject::connect(mw->getEncryptPushButton(), SIGNAL(clicked()),
//                            mw->getTextEdit(), SLOT(paste()));
}

bool EncryptingAlg::clearText(MainWindow *mw)
{
    return QObject::connect(mw->getClearPushButton(), SIGNAL(clicked()),
                            mw->getTextEdit(), SLOT(clear()));
}

