#ifndef SETTHEADER_H
#define SETTHEADER_H

#include <QString>
#include <QStandardPaths>
#include <QWidget>

namespace SETT
{
    const QString COMPANY_NAME = "BOXE";
    const QString APPLICATION_NAME = "BDAY";
    const QString APPDATALOCATION = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    const QString pathToDB = APPDATALOCATION + "\\" + COMPANY_NAME +
            "\\" + APPLICATION_NAME + "\\database.dat";
}

#endif // SETTHEADER_H
