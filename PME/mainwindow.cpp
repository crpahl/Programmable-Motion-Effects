#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent): QDialog (parent)
{
    /*myWin = new CSWindow(parent);
    quitButton = new QPushButton(tr("quit"));
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myWin);
    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addStretch();

    bLayout->addWidget(quitButton);
    layout->addLayout(bLayout);
    setGeometry(myWin->geometry());
    _title="So I put my hands up they playin ma song!";
    setWindowTitle(tr(_title));
    setLayout(layout);

    createActions();
    createMenus();*/

    myWin = new CSWindow(parent);
    //connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(myWin);
    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addStretch();
    //bLayout->addWidget(quitButton);
    layout->addLayout(bLayout);
    setGeometry(myWin->geometry());
    _title="Test";
    setWindowTitle(tr(_title));
    setLayout(layout);
}
