#include "inputmodule.h"
#include "singleinvprojanalysismodule.h"
#include "database.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    if (!createConnection())
//        return -1;

    InputModule w;
    w.show();

//    SingleInvProjAnalysisModule sipam;
//    sipam.show();

    return a.exec();
}
