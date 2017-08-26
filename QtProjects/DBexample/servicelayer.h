#ifndef SERVICELAYER_H
#define SERVICELAYER_H

#include "mainwindow.h"

class ServiceLayer
{
public:
    ServiceLayer(MainWindow *mw);

    void makeViewService(MainWindow *mw);
    void makeViewnEditService(MainWindow *mw);
};

#endif // SERVICELAYER_H
