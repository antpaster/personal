#ifndef SINGLEINVPROJANALYSISRESULTS_H
#define SINGLEINVPROJANALYSISRESULTS_H

#include <QMainWindow>

namespace Ui {
class SingleInvProjAnalysisResults;
}

class SingleInvProjAnalysisResults : public QMainWindow
{
    Q_OBJECT

public:
    explicit SingleInvProjAnalysisResults(QWidget *parent = 0);
    ~SingleInvProjAnalysisResults();

public slots:


private:
    Ui::SingleInvProjAnalysisResults *ui;
};

#endif // SINGLEINVPROJANALYSISRESULTS_H
