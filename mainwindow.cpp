#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    std::future<bool> enableAutorun = std::async([]()
            {
            #ifdef Q_OS_WIN
                const QFileInfo fileInfo(QCoreApplication::applicationFilePath());
                const QString pathOfLink = QStandardPaths::writableLocation(QStandardPaths::ApplicationsLocation) + QDir::separator() + "Startup" + QDir::separator() + fileInfo.completeBaseName() + ".lnk";
                return QFile::exists(pathOfLink);
            #else
                return true;
            #endif
            });
    // this->setWindowFlags(Qt::CustomizeWindowHint);
    // this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->buttonAdd->setMouseTracking(true);
    ui->buttonRemove->setMouseTracking(true);
    ui->buttonSettings->setMouseTracking(true);
    ui->buttonShow->setMouseTracking(true);
    positionOfAddButton = ui->buttonAdd->mapToGlobal(QPoint(0, 0));
    sizeOfAddButton = ui->buttonAdd->size();
    positionOfRemoveButton = ui->buttonRemove->mapToGlobal(QPoint(0, 0));
    sizeOfRemoveButton = ui->buttonRemove->size();
    positionOfShowButton = ui->buttonShow->mapToGlobal(QPoint(0, 0));
    sizeOfShowButton = ui->buttonShow->size();
    positionOfSettingsButton = ui->buttonSettings->mapToGlobal(QPoint(0, 0));
    sizeOfSettingsButton = ui->buttonSettings->size();
    if(!enableAutorun.get())
        QMessageBox::warning(this, "B-DAY | AUTORUN", "Autostart program is turned off. Turn it on in the settings, so as not to forget about birthdays", "OKAY");
}

MainWindow::~MainWindow()
{
    delete ui;
    DataBase::DestroyInstance();
}

void MainWindow::on_buttonAdd_clicked(void) noexcept
{
    QPointer<Dialog> newForm(new Dialog(this));
    newForm->exec();
}

void MainWindow::on_buttonRemove_clicked(void) noexcept
{
    QPointer<Removedialog> newForm(new Removedialog(this));
    newForm->exec();
}

void MainWindow::on_buttonShow_clicked(void) noexcept
{
    if(QFile fileDB(SETT::pathToDB); !fileDB.exists() || fileDB.size() <= 0)
    {
        QMessageBox::warning(this, "B-DAY | EMPTY LIST", "Your list is empty", "OKAY");
        return;
    }
    QPointer<Showdialog> newForm(new Showdialog(this));
    newForm->exec();
}

void MainWindow::on_buttonSettings_clicked(void) noexcept
{
    QPointer<settings> newForm(new settings(this));
    newForm->exec();
}

void MainWindow::mouseMoveEvent(QMouseEvent * event) noexcept
{
    const QPoint mousePosition(event->pos());

    if(mousePosition.x() >= positionOfAddButton.x() && mousePosition.x() < (positionOfAddButton.x() + sizeOfAddButton.width())
            && mousePosition.y() >= positionOfAddButton.y() && mousePosition.y() < (positionOfAddButton.y() + sizeOfAddButton.height()))
        ui->helpText->setText("This button is required to add\n a person to your list");
    else if(mousePosition.x() >= positionOfRemoveButton.x() && mousePosition.x() < (positionOfRemoveButton.x() + sizeOfRemoveButton.width())
            && mousePosition.y() >= positionOfRemoveButton.y() && mousePosition.y() < (positionOfRemoveButton.y() + sizeOfRemoveButton.height()))
        ui->helpText->setText("This button is required to remove\n a person from your list");
    else if(mousePosition.x() >= positionOfShowButton.x() && mousePosition.x() < (positionOfShowButton.x() + sizeOfShowButton.width())
            && mousePosition.y() >= positionOfShowButton.y() && mousePosition.y() < (positionOfShowButton.y() + sizeOfShowButton.height()))
        ui->helpText->setText("This button is required to show\n your list");
    else if(mousePosition.x() >= positionOfSettingsButton.x() && mousePosition.x() < (positionOfSettingsButton.x() + sizeOfSettingsButton.width())
            && mousePosition.y() >= positionOfSettingsButton.y() && mousePosition.y() < (positionOfSettingsButton.y() + sizeOfSettingsButton.height()))
        ui->helpText->setText("This button is required to configure\n the program and to import the data base");
    else
        ui->helpText->clear();
}
