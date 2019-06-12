#include "database.h"

DataBase::DataBase(void)
{
    if(!QDir(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME).exists() ||
            !QDir(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME + "\\" + SETT::APPLICATION_NAME).exists())
        QDir().mkpath(SETT::APPDATALOCATION + "\\" + SETT::COMPANY_NAME + "\\" + SETT::APPLICATION_NAME);

    if(QFile(SETT::pathToDB).exists())
    {
        QFile fileDataBase(SETT::pathToDB);
        if(!fileDataBase.open(QIODevice::ReadOnly) && !fileDataBase.isOpen())
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ERROR");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Error #2: the database file can not be read\n Our advice: try manually open the database file");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
        else
        {
            const uint8_t currentDay = static_cast<uint8_t>(QDate::currentDate().day());
            const uint8_t currentMonth = static_cast<uint8_t>(QDate::currentDate().month());

            while(!fileDataBase.atEnd())
            {
                const QString tempReadLine = fileDataBase.readLine();
                cacheData.push_back(tempReadLine);
                const QStringList tempStrList = tempReadLine.split(" ");
                const uint8_t day = static_cast<uint8_t>(tempStrList.at(2).toUShort());
                const uint8_t month = static_cast<uint8_t>(tempStrList.at(3).toUShort());
                const QString firstName = tempStrList.at(0);
                const QString lastName = tempStrList.at(1);
                const uint16_t year = static_cast<uint16_t>(tempStrList.at(4).toUShort());
                const uint16_t yearsOld = static_cast<uint16_t>(QDate::currentDate().year() - year);
                if((day == currentDay) && (month == currentMonth))
                {
                    QMessageBox messageBox;
                    messageBox.setWindowTitle("TODAY BIRTH DAY OF PERSON");
                    messageBox.setIcon(QMessageBox::Information);
                    messageBox.setText("The birth day of " + firstName + " " + lastName + " (" + QString::number(yearsOld) + " years old).");
                    messageBox.setButtonText(0, "OKAY");
                    messageBox.exec();
                }
                else
                {
                    const QDate date(QDate::currentDate().year(), currentMonth, currentDay);
                    if((((day - currentDay) == 1) && (month == currentMonth))
                            || ((date.daysInMonth() == currentDay) && (day == 1) && ((month - currentMonth) == 1))
                            || ((day == 1 && month == 1) && (currentDay == 31 && currentMonth == 12)) )
                    {
                        QMessageBox messageBox;
                        messageBox.setWindowTitle("TOMORROW BIRTH DAY OF PERSON");
                        messageBox.setIcon(QMessageBox::Information);
                        messageBox.setText("Tomorrow is the birthday of " + firstName + " " + lastName + " (" + QString::number(yearsOld) + " years old).");
                        messageBox.setButtonText(0, "OKAY");
                        messageBox.exec();
                    }
                }
            }
        }
        fileDataBase.close();
    }
}

DataBase * DataBase::getInstance(void) noexcept
{
    if (!p_instance)
        p_instance = new DataBase();
    return p_instance;
}

void DataBase::DestroyInstance(void) noexcept
{
    delete p_instance;
    p_instance = nullptr;
}

void DataBase::addPerson(QString && firstName, QString && lastName, QString && data) noexcept
{
    const QString stringToWrite = firstName + " " + lastName + " " + data + "\r\n";
    QFile fileDataBase(SETT::pathToDB);
    if(!fileDataBase.exists())
    {
        if(!fileDataBase.open(QIODevice::WriteOnly) && !fileDataBase.isOpen())
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ERROR");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Error #1: the database file can not be created");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
        else
        {
            fileDataBase.write(stringToWrite.toStdString().c_str());
            cacheData.push_back(stringToWrite);
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ADD");
            messageBox.setIcon(QMessageBox::Information);
            messageBox.setText("The person was added successfully");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
    }
    else
    {
        if(!fileDataBase.open(QIODevice::Append) && !fileDataBase.isOpen())
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ERROR");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Error #1: the database file can not be opened");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
        else
        {
            fileDataBase.write(stringToWrite.toStdString().c_str());
            cacheData.push_back(stringToWrite);
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ADD");
            messageBox.setIcon(QMessageBox::Information);
            messageBox.setText("The person was added successfully");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
    }
    fileDataBase.close();
}

bool DataBase::removePerson(QString && firstNameRemove, QString && lastNameRemove) noexcept
{
    uint8_t i = 0;
    for(const auto & line : cacheData)
    {
        const QStringList lineOfDataBase = line.split(" ");
        const QString firstNameDB = lineOfDataBase.at(0);
        const QString lastNameDB = lineOfDataBase.at(1);
        if(lastNameRemove == lastNameDB)
        {
            if(firstNameRemove == firstNameDB)
                break;
        }
        ++i;
    }

    if(i != cacheData.size())
    {
        cacheData.removeAt(i);
        return true;
    }
    return false;
}

void DataBase::updateDataBaseFile(void) const noexcept
{
    QFile fileDataBase(SETT::pathToDB);
    if(fileDataBase.exists())
    {
        if(!fileDataBase.open(QIODevice::WriteOnly | QIODevice::Truncate) && !fileDataBase.isOpen())
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ERROR");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Error #1: the database file can not be opened");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
        else
        {
            for(const auto & line : cacheData)
                fileDataBase.write(line.toStdString().c_str());
        }
    }
    fileDataBase.close();
}

void DataBase::getData(QList<QString> & list) const noexcept
{
    for(const auto & line : cacheData)
        list.push_back(line);
}

void DataBase::importDatabase(const QString & fileName) noexcept
{
    QFile importFile(fileName);
    if(!importFile.open(QIODevice::ReadOnly) && !importFile.isOpen())
    {
        QMessageBox messageBox;
        messageBox.setWindowTitle("B-DAY | ERROR");
        messageBox.setIcon(QMessageBox::Critical);
        messageBox.setText("Error #2: the file with import database can not be read\nOur advice: try to open the database file");
        messageBox.setButtonText(0, "OKAY");
        messageBox.exec();
    }
    else
    {
        QFile fileDataBase(SETT::pathToDB);
        if(!fileDataBase.open(QIODevice::Append) && !fileDataBase.isOpen())
        {
            QMessageBox messageBox;
            messageBox.setWindowTitle("B-DAY | ERROR");
            messageBox.setIcon(QMessageBox::Critical);
            messageBox.setText("Error #1: the database file can not be opened");
            messageBox.setButtonText(0, "OKAY");
            messageBox.exec();
        }
        else
        {
            const auto iteratorOfEnd = cacheData.end();
            while(!importFile.atEnd())
            {
                const QString tempStrImport = importFile.readLine();
                if(std::find(cacheData.begin(), cacheData.end(), tempStrImport) == iteratorOfEnd)
                {
                    cacheData.push_back(tempStrImport);
                    fileDataBase.write(tempStrImport.toStdString().c_str());
                }
                /*bool check = false;
                const QString tempStrImport = importFile.readLine();
                const QStringList tempStrImportList = tempStrImport.split(" ");
                const QString firstName = tempStrImportList.at(0);
                const QString lastName = tempStrImportList.at(1);
                const uint8_t day = static_cast<uint8_t>(tempStrImportList.at(2).toUShort());
                const uint8_t month = static_cast<uint8_t>(tempStrImportList.at(3).toUShort());
                const uint16_t year = static_cast<uint16_t>(tempStrImportList.at(4).toUShort());

                fileDataBase.seek(0); // go to start at file
                while(!fileDataBase.atEnd())
                {
                    QString tempStrDB = fileDataBase.readLine();
                    QStringList tempStrDBList = tempStrDB.split(" ");
                    QString fNameDB = tempStrDBList.at(0);
                    QString lNameDB = tempStrDBList.at(1);
                    if((fNameDB == firstName) && (lNameDB == lastName))
                    {
                        unsigned short int dayDB = tempStrDBList.at(2).toUShort();
                        unsigned short int monthDB = tempStrDBList.at(3).toUShort();
                        unsigned short int yearDB = tempStrDBList.at(4).toUShort();
                        if((dayDB == day) && (monthDB == month) && (yearDB == year))
                        {
                            check = true;
                            break;
                        }
                    }
                }
                if(check)
                    continue;

                QString strForWrite = firstName + " " + lastName + " " + QString::number(day) + " " + QString::number(month) + " " + QString::number(year) + "\r\n";
                fileDataBase.write(strForWrite.toStdString().c_str());*/
            }
        }
        fileDataBase.close();
    }
    importFile.close();
}
