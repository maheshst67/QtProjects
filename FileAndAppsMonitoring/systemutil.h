#ifndef SYSTEMUTIL_H
#define SYSTEMUTIL_H

#include "process.h"

#include "defs.h"

#include <QObject>
#include <QProcess>
#include <QList>


class SystemUtil : public QObject
{

    Q_OBJECT

    QProcess     *mTopProcess;      // Qprocess mTopProcess handle the subprocess 'top'

    QString       mProcess;         // The path of subprocess 'top'
    QStringList   mEnv;             // Sets necessary TERM environment variable required for top command
    QStringList   mArguments;       // Arguments list to handle processes properly
    QString       mOutputString;    // To store the output produced by the commands
    QStringList   mOutputList;      // To store the split values of output

    int findHeaderRow();

public:
    explicit SystemUtil(QObject *parent = 0);
    ~SystemUtil();


    int getProcessesList(QList<Process> *processList);

    int parseProcesses(QList<Process> *processList);

    void showBatteryDetails();


signals:

public slots:

};

#endif // SYSTEMUTIL_H
