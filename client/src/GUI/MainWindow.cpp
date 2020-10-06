//
// Created by clementschmitte on 24/09/2020.
//

#include "MainWindow.hpp"

#include <QCoreApplication>
#include <QDebug>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGraphicsScene>
#include <QtWidgets/QGraphicsView>
#include <client/src/GUI/Scenes/MainScene.hpp>
#include <client/src/GUI/Scenes/LoginScene.hpp>
#include <QtWidgets/QComboBox>
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent)
{
    resize(1280, 720);
    setMinimumSize(900, 600);
    setWindowTitle("Babel");

    std::cout << "MainWindow constructor" << std::endl;
//    _sceneManager.addScene(new LoginScene(this), "login");
    _sceneManager.addScene(new MainScene(), "main");
    std::cout << "MainWindow constructor 2" << std::endl;
    setCentralWidget(&_sceneManager);
}

void MainWindow::setScene(std::string name) {
    _sceneManager.setScene(name);
}

//void MainWindow::notificationManager()
//{
//    QPushButton *notif_button = new QPushButton("Notif", this);
//    notif_button->setGeometry(QRect(QPoint(400, 400),
//                                    QSize(200, 50)));
//    connect(notif_button, SIGNAL (clicked()), this, SLOT (notificationManager()));
//
//    QLineEdit *notif = new QLineEdit("New call from XXX", this);
//    notif->setReadOnly(true);
//    notif->setTextMargins(50, 0, 0, 0);
//    notif->setGeometry(QRect(QPoint(200, -100),
//                             QSize(500, 100)));
//
//    QPushButton *accept_button = new QPushButton("Accept", notif);
//    accept_button->setGeometry(QRect(QPoint(260, 25),
//                                     QSize(100, 50)));
//
//    QPushButton *refuse_button = new QPushButton("Refuse", notif);
//    refuse_button->setGeometry(QRect(QPoint(380, 25),
//                                     QSize(100, 50)));
//
//    QPropertyAnimation *anim = new QPropertyAnimation(notif, "geometry");
//    anim->setDuration(300);
//    anim->setStartValue(notif->geometry());
//    notif->pos().y() == 0 ?
//    anim->setEndValue(QRect(200, -100, 500, 100)):
//    anim->setEndValue(QRect(200, 0, 500, 100));
//    anim->start();
//}
