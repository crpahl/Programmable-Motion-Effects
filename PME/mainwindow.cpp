#include "mainwindow.h"
#include <iostream>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent): QDialog (parent)
{
    myWin = new CSWindow(parent);
    QVBoxLayout *layout = new QVBoxLayout;

    menuBar = new QMenuBar(parent);
    layout->addWidget(myWin);
    //layout->addWidget(menuBar);

    // Adding button(s)
    Label = new QLabel(tr("Patches"));
    patchesButton = new QRadioButton();
    openButton = new QPushButton(tr("open"));
    debugButton = new QPushButton(tr("debug"));
    connect(openButton, SIGNAL(clicked()), myWin, SLOT(open()));
    connect(debugButton, SIGNAL(clicked()), myWin, SLOT(debug()));
    connect(patchesButton, SIGNAL(clicked()), myWin, SLOT(showPatches()));

    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addWidget(openButton);
    bLayout->addStretch();
    bLayout->addWidget(Label);
    bLayout->addWidget(patchesButton);
    //bLayout->addWidget(debugButton);
    layout->addLayout(bLayout);

    _title="Programmable Motion Effects";
    setWindowTitle(tr(_title));
    setGeometry(myWin->geometry());
    setLayout(layout);
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    //fileMenu->addAction(openAct);
    //fileMenu->addAction(exitAct);

    menuBar->addMenu(fileMenu);
}
