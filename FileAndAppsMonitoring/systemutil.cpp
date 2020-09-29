#include "systemutil.h"
#include <QDebug>
#include <QStorageInfo>


SystemUtil::SystemUtil( QObject *parent )
    : QObject( parent )
{

    mTopProcess      =  new QProcess(parent);
    mEnv             =  QProcess::systemEnvironment();
    //---------------------------------------------------------//
    // Note:-
    // top command requires the value of  TERM environment variable
    // for execution of the process
    //
    // top command contains maximum 512 characters in single row and
    // hence we need to redefine COLUMNS environment variable also
    //
    //---------------------------------------------------------//
    mEnv << "TERM=vt100" << "COLUMNS=512";

    mTopProcess -> setEnvironment( mEnv );

}



SystemUtil::~SystemUtil(){
    delete mTopProcess;
}


int SystemUtil::getProcessesList(QList<Process> *processList){

    qDebug() <<"Getting Process List . . . . . . . . . ";

    mProcess = "top";

    //---------------------------------------------------------//
    // -b        for batch output
    // -n        for number of iterations
    //---------------------------------------------------------//
    mArguments.clear();
    mArguments << "-b" << "-n" << "1" ;

    mTopProcess -> start( mProcess , mArguments );

    if( !mTopProcess->waitForStarted() ) {
        qDebug() << "ERROR : " << mTopProcess->error();
    }

    mTopProcess->waitForFinished() ;

    return parseProcesses(processList);

}

/**
 * @brief SystemUtil::parseProcesses
 * @param processList
 * @return exit_status
 *
 * takes the output of top command, split it and store it in Process data structure
 * appends the process to processList
 */
int SystemUtil::parseProcesses(QList<Process> *processList){

    mOutputString.clear();
    mOutputString = QString( mTopProcess -> readAll() );

    mOutputList.clear();
    mOutputList = mOutputString.split('\n' , QString::SkipEmptyParts );


    int headerRowIndex = findHeaderRow();

    if(headerRowIndex == -1) {
        return ST_FAILED;
    }

    QString headerRow = mOutputList.at(headerRowIndex);
    QStringList splittedHeaderRow = headerRow.split(' ',QString::SkipEmptyParts );


    int indexId, indexUser, indexCpu, indexMemory;

    for(int i = 0 ; i < splittedHeaderRow.size() ; i++){
        QString val = splittedHeaderRow.at(i);
        if(val.toUpper() == "PID"){
            indexId = i;
        }else if(val.toUpper() == "USER"){
            indexUser = i;
        }else if(val.toUpper() == "%CPU"){
            indexCpu = i;
        }else if(val.toUpper() == "RES"){
            indexMemory = i;
        }
    }


    Process p;


    for(int  i = headerRowIndex+1 ; i < mOutputList.size() ; i++ ){

        QString str = mOutputList.at( i ) ;

        //---------------------------------------------------------//
        // splits one process string on the basis of whitespaces.
        //---------------------------------------------------------//
        QStringList splittedString = str.split( QRegExp("\\s"), QString::SkipEmptyParts );

        //------------------------------------------------------------------//
        //splits the numerical value of memory from string on the basis of m
        //------------------------------------------------------------------//
        QStringList memValue = splittedString[ indexMemory ]
                .split( QRegExp("m"), QString::SkipEmptyParts );

        QString pName   = splittedString.last() ;
        QString user    = splittedString[ indexUser ] ;
        quint64 pID     = splittedString[ indexId ].toLongLong();
        float cpuUsage  = splittedString[ indexCpu ].toDouble();
        double memUsage = memValue[0].toDouble();

        p.setProcessId(pID);
        p.setCpuUsage(cpuUsage);
        p.setMemoryUsage(memUsage);
        p.setProcessName(pName);
        p.setUser(user);

        processList->append( p );

    }

    return ST_SUCCESS;

}



int SystemUtil::findHeaderRow(){

    int iterator = 0;
    while(iterator < mOutputList.size()){

        QString singleRow = mOutputList.at(iterator);
        QStringList splittedSingleRow = singleRow.split(QRegExp("\\s"),QString::SkipEmptyParts);

        QString firstMember = splittedSingleRow.at(0);
        firstMember = firstMember.toUpper();
        if(firstMember == "PID"){
            return iterator;
        }
        iterator+=1;
    }
    return -1;
}

