/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *startbutton;
    QPushButton *infobutton;
    QPushButton *exitbutton;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(-11, -41, 811, 611));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/bckg.jpg")));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(290, 420, 191, 51));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        font.setStyleStrategy(QFont::PreferDefault);
        label_2->setFont(font);
        label_2->setPixmap(QPixmap(QString::fromUtf8(":/images/name.png")));
        label_2->setScaledContents(true);
        startbutton = new QPushButton(centralWidget);
        startbutton->setObjectName(QStringLiteral("startbutton"));
        startbutton->setGeometry(QRect(110, 150, 561, 141));
        startbutton->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/SART.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/SART.png"), QSize(), QIcon::Normal, QIcon::On);
        icon.addFile(QStringLiteral(":/images/SART.png"), QSize(), QIcon::Active, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/SART2.png"), QSize(), QIcon::Active, QIcon::On);
        icon.addFile(QStringLiteral(":/images/SART.png"), QSize(), QIcon::Selected, QIcon::Off);
        icon.addFile(QStringLiteral(":/images/SART2.png"), QSize(), QIcon::Selected, QIcon::On);
        startbutton->setIcon(icon);
        startbutton->setIconSize(QSize(521, 139));
        startbutton->setAutoRepeat(false);
        startbutton->setAutoDefault(false);
        startbutton->setFlat(true);
        infobutton = new QPushButton(centralWidget);
        infobutton->setObjectName(QStringLiteral("infobutton"));
        infobutton->setGeometry(QRect(10, 450, 21, 71));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/images/info.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QStringLiteral(":/images/info.png"), QSize(), QIcon::Active, QIcon::On);
        infobutton->setIcon(icon1);
        infobutton->setIconSize(QSize(70, 70));
        infobutton->setFlat(true);
        exitbutton = new QPushButton(centralWidget);
        exitbutton->setObjectName(QStringLiteral("exitbutton"));
        exitbutton->setGeometry(QRect(740, 450, 51, 71));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/images/exit.png"), QSize(), QIcon::Active, QIcon::Off);
        exitbutton->setIcon(icon2);
        exitbutton->setIconSize(QSize(70, 70));
        exitbutton->setFlat(true);
        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setGeometry(QRect(280, 480, 211, 41));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        startbutton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label->setText(QString());
        label_2->setText(QString());
        startbutton->setText(QString());
        infobutton->setText(QString());
        exitbutton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
