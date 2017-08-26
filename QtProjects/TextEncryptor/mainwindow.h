#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QLineEdit *getLineEdit();
    void setLineEdit(QString qs);

    QTextEdit *getTextEdit();
    void setTextEdit(QString qs);

    QPushButton *getShowPosPushButton();

    QPushButton *getEncryptPushButton();

    QPushButton *getClearPushButton();

public slots:
    void appendTextToTextEdit(QString qs);

protected:
    void changeEvent(QEvent *e);
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
