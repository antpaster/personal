#ifndef INPUTMODULE_H
#define INPUTMODULE_H

#include <QMainWindow>

namespace Ui {
class InputModule;
}

class InputModule : public QMainWindow
{
    Q_OBJECT

public:
    explicit InputModule(QWidget *parent = 0);
    ~InputModule();

public slots:
    void actionAboutTriggered();

    void analysePushButtonClicked(int row);

signals:
    void analysePushButtonClick(int row);

private:
    Ui::InputModule *ui;

};

#endif // INPUTMODULE_H
