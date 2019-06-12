#include "settings.h"
#include "ui_settings.h"

settings::settings(QWidget * parent) : QDialog(parent), ui(new Ui::settings)
{
    ui->setupUi(this);
    ui->checkBox->setChecked(isCheck());
}

settings::~settings()
{
    delete ui;
}

void settings::on_convButton_clicked(void) noexcept
{
    const QString fileName = QFileDialog::getOpenFileName(this, "Import database", "", "Database file (*.dat) ;; All files (*.*)");
    if(!fileName.isEmpty())
    {
        DataBase * db = DataBase::getInstance();
        db->importDatabase(fileName);
    }
}

void settings::on_okButton_clicked(void) noexcept
{
    this->close();
}

void settings::on_aboutButton_clicked(void) noexcept
{
    QMessageBox::about(this, "ABOUT US", "This program was created by BOXE Incorporated\nAll rights reserved © 2018 - " + QString::number(QDate::currentDate().year()));
}

bool settings::isCheck(void) const noexcept
{
#ifdef Q_OS_WIN32
    const QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    const QString pathOfLink = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + QDir::separator() + "Startup" + QDir::separator() + fileInfo.completeBaseName() + ".lnk";
    return QFile::exists(pathOfLink);
#else
    return false;
#endif
}

void settings::on_checkBox_stateChanged(int choose) noexcept
{
#ifdef Q_OS_WIN32
    const QFileInfo fileInfo(QCoreApplication::applicationFilePath());
    const QString pathOfLink = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + QDir::separator() + "Startup" + QDir::separator() + fileInfo.completeBaseName() + ".lnk";
    if(choose == 2)
        QFile::link(QCoreApplication::applicationFilePath(), pathOfLink);
    else
        QFile::remove(pathOfLink);
#else
    QMessageBox::warning(this, "SYSTEM", "Your system does not support autorun\n", "OKAY");
#endif
}
