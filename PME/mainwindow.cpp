#include "mainwindow.h"
#include <iostream>
#include <QMainWindow>

MainWindow::MainWindow(QWidget *parent): QDialog (parent)
{
    myWin = new CSWindow(parent);

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *aLayout = new QHBoxLayout;
    switchButton = new QPushButton(tr("Switch View"));
    //aLayout->addStretch();
    aLayout->addWidget(switchButton);

    layout->addLayout(aLayout);
    layout->addWidget(myWin);

    // Adding button(s)
    Label = new QLabel(tr("Patches"));
    Label2 = new QLabel(tr("Lock Camera"));
    Label3 = new QLabel(tr("Grid"));
    speedLines = new QLabel(tr("Speed Lines"));
    blurLabel = new QLabel(tr("Motion Blur"));

    lockCamera = new QCheckBox();
    patchesButton = new QCheckBox();
    setGrid = new QCheckBox();
    speedButton = new QRadioButton();
    blurButton = new QRadioButton();
    setGrid->click();
    speedButton->click();
    openButton = new QPushButton(tr("open"));
    debugButton = new QPushButton(tr("debug"));
    animateButton = new QPushButton(tr("animate"));

    connect(openButton, SIGNAL(clicked()), myWin, SLOT(open()));
    connect(debugButton, SIGNAL(clicked()), myWin, SLOT(debug()));
    connect(patchesButton, SIGNAL(clicked()), myWin, SLOT(showPatches()));
    connect(lockCamera, SIGNAL(clicked()), myWin, SLOT(lockCamera()));
    connect(setGrid, SIGNAL(clicked()), myWin, SLOT(setGrid()));
    connect(switchButton, SIGNAL(clicked()), myWin, SLOT(displayOutput()));
    connect(animateButton, SIGNAL(clicked()), myWin, SLOT(animate()));
    connect(speedButton, SIGNAL(clicked()), myWin, SLOT(speed()));
    connect(blurButton, SIGNAL(clicked()), myWin, SLOT(blur()));

    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addWidget(openButton);
    bLayout->addStretch();
    bLayout->addWidget(Label);
    bLayout->addWidget(patchesButton);
    bLayout->addWidget(Label3);
    bLayout->addWidget(setGrid);
    bLayout->addWidget(Label2);
    bLayout->addWidget(lockCamera);
    layout->addLayout(bLayout);

    QHBoxLayout *cLayout = new QHBoxLayout;
    cLayout->addWidget(animateButton);
    cLayout->addStretch();
    cLayout->addWidget(blurLabel);
    cLayout->addWidget(blurButton);
    cLayout->addWidget(speedLines);
    cLayout->addWidget(speedButton);
    layout->addLayout(cLayout);

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
