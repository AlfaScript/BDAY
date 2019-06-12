#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget * parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // this->setWindowFlags(Qt::CustomizeWindowHint);
    // this->setWindowFlags(Qt::FramelessWindowHint);
    ui->setupUi(this);
    setMouseTracking(true);
    ui->centralWidget->setMouseTracking(true);
    ui->buttonAdd->setMouseTracking(true);
    ui->buttonRemove->setMouseTracking(true);
    ui->buttonSettings->setMouseTracking(true);
    ui->buttonShow->setMouseTracking(true);
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
    QFile fileDB(SETT::pathToDB);
    if(!fileDB.exists() || fileDB.size() <= 0)
    {
        QMessageBox::warning(this, "B-DAY | EMPTY LIST", "Your list is empty", "OKAY");
        fileDB.close();
        return;
    }
    fileDB.close();
    QPointer<Showdialog> newForm(new Showdialog(this));
    newForm->exec();
}

void MainWindow::on_buttonSettings_clicked(void) noexcept
{
    QPointer<settings> newForm(new settings(this));
    newForm->exec();
}

void MainWindow::mouseMoveEvent(const QMouseEvent * event) noexcept
{
    const uint16_t xPosition = static_cast<uint16_t>(event->pos().x());
    const uint16_t yPosition = static_cast<uint16_t>(event->pos().y());
    if(xPosition >= 20 && xPosition < 180)
    {
        if(yPosition >= 60 && yPosition < 120)
            ui->helpText->setText("This button is required to add\n a person to your list");
        else if(yPosition >= 120 && yPosition < 180)
            ui->helpText->setText("This button is required to remove\n a person from your list");
        else if(yPosition >= 180 && yPosition < 240)
            ui->helpText->setText("This button is required to show\n your list");
        else if(yPosition >= 240 && yPosition < 300)
            ui->helpText->setText("This button is required to configure\n the program and to import the data base");
        else
            ui->helpText->clear();
    }
    else
        ui->helpText->clear();
}
