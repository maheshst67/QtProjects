#include "process.h"

/**
 * @brief Process::Process
 * Data structure to store the required process information
 */
Process::Process() {}

/**
 * @brief Process::Process
 * @param processId        PID of process
 * @param processName      Name of process
 * @param cpuUsage         CPU usage by process
 * @param memoryUsage      Memory usage by process
 * @param user             User that has invoked the process
 */
Process::Process(quint64 processId,
                 QString processName,
                 float cpuUsage,
                 double memoryUsage,
                 QString user)

{

    mProcessId   = processId;
    mProcessName = processName;
    mCpuUsage    = cpuUsage;
    mMemoryUsage = memoryUsage;
    mUser        = user;

}

void Process::showInfo() const{

    qDebug() << "----------------[ PROCESS ]----------------" ;
    qDebug() << "Process No  . . . . . : " << mProcessId ;
    qDebug() << "User . . . . . . . . .: " << mUser ;
    qDebug() << "Process Name . . . . .: " << mProcessName ;
    qDebug() << "Process CPU Usage  . .: " << mCpuUsage << " % ";
    qDebug() << "Process Memory Usage .: " << mMemoryUsage << " KiB ";
    qDebug() << "-------------------------------------------" ;

}

quint64 Process::getProcessId() const{
    return this->mProcessId;
}

QString Process::getProcessName() const{
    return this->mProcessName;
}

float Process::getCpuUsage() const{
    return this->mCpuUsage;
}

double Process::getMemoryUsage() const{
    return this->mMemoryUsage;
}

QString Process::getUser() const{
    return this->mUser;
}

void Process::setProcessId( quint64 val ){
    this->mProcessId = val ;
}

void Process::setProcessName( QString str ){
    this->mProcessName = str ;
}

void Process::setCpuUsage( float val ){
    this->mCpuUsage = val ;
}

void Process::setMemoryUsage( double val){
    this->mMemoryUsage = val ;
}

void Process::setUser( QString str ){
    this->mUser = str ;
}
