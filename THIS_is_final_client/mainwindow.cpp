#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QMessageBox"
#include "game.h"
#include "user.h"
#include "go.h"
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent, int num, char** arg) :
    QMainWindow(parent), num(num), arg(arg), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exitbutton_clicked() // Выход.
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,"Exit", "Do you really want to leave the game?", QMessageBox::Yes | QMessageBox::No);
    if(reply == QMessageBox::Yes)
    {
        close();
    }
}

void MainWindow::on_infobutton_clicked() // Информация.
{
     QMessageBox::information(this, "About",
                              "EFace."
                              "\nCompleted:"
                              "\nGUI............BYKHOVETS MARK"
                              "\nSERVER.........RASPOPIN VLADISLAV"
                              "\nCLIENT.........PROKOFYEV EVGENY"
                              "\nEmojiDETECT....POPOV SERGEY"
                              "\nPress Enter to return to the menu...");
}

void MainWindow::on_startbutton_clicked()
{
    if(ui->lineEdit->text() == "")
    {
        QMessageBox::information(this,"ERROR","Imput your name","OK");
    }
    else
    {
        user = new User(ui->lineEdit->text());
        go(argc,argv, &user);
        Game *game = new Game();
        game->show();
        this->close();
    }
}
