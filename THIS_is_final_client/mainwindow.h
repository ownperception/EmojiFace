#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(int num = 0, char** arg = 0,QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    int num;

    char **arg;

    void on_startbutton_clicked();

    void on_exitbutton_clicked();

    void on_infobutton_clicked();

    void on_line_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
