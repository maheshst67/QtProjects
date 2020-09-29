#ifndef PROCESS_H
#define PROCESS_H

#include <QString>
#include <QDebug>

/**
 * @brief The Process class
 * This class acts as data sturcture to store the individual process details
 */
class Process
{
    quint64 mProcessId;
    QString mProcessName;
    float   mCpuUsage;
    double  mMemoryUsage;
    QString mUser;

public:

    explicit Process();


    explicit Process(quint64 processId,
                     QString processName,
                     float cpuUsage,
                     double memoryUsage,
                     QString user);
    void showInfo() const;

    quint64 getProcessId() const;

    QString getProcessName() const;

    float   getCpuUsage() const;

    double  getMemoryUsage() const;

    QString getUser() const;

    void setProcessId(quint64 val);

    void setProcessName(QString str);

    void setCpuUsage(float val);

    void setMemoryUsage(double val);

    void setUser(QString str);

};

#endif // PROCESS_H
