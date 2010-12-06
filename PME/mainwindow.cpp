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
    Label2 = new QLabel(tr("Lock Camera"));
    Label3 = new QLabel(tr("Grid"));
    outputLabel = new QLabel(tr("Render"));
    lockCamera = new QCheckBox();
    patchesButton = new QCheckBox();
    setGrid = new QCheckBox();
    outputButton = new QCheckBox();
    setGrid->click();
    openButton = new QPushButton(tr("open"));
    debugButton = new QPushButton(tr("debug"));
    connect(openButton, SIGNAL(clicked()), myWin, SLOT(open()));
    connect(debugButton, SIGNAL(clicked()), myWin, SLOT(debug()));
    connect(patchesButton, SIGNAL(clicked()), myWin, SLOT(showPatches()));
    connect(lockCamera, SIGNAL(clicked()), myWin, SLOT(lockCamera()));
    connect(setGrid, SIGNAL(clicked()), myWin, SLOT(setGrid()));
    connect(outputButton, SIGNAL(clicked()), myWin, SLOT(displayOutput()));

    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addWidget(openButton);
    bLayout->addWidget(outputLabel);
    bLayout->addWidget(outputButton);
    bLayout->addStretch();
    bLayout->addWidget(Label);
    bLayout->addWidget(patchesButton);
    bLayout->addWidget(Label3);
    bLayout->addWidget(setGrid);
    bLayout->addWidget(Label2);
    bLayout->addWidget(lockCamera);
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
