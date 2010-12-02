#include "mainwindow.h"
MainWindow::MainWindow(QWidget *parent): QDialog (parent)
{
    /*
    // create menubar on top
    //menuBar = new QMenuBar;

    myWin = new CSWindow(parent);
    quitButton = new QPushButton(tr("quit"));
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    //layout->addWidget(menuBar);		// put menubar on top
    layout->addWidget(myWin);
    QHBoxLayout *bLayout = new QHBoxLayout;
    bLayout->addStretch();

    bLayout->addWidget(quitButton);
    layout->addLayout(bLayout);
    setGeometry(myWin->geometry());
    _title="So I put my hands up they playin ma song!";
    setWindowTitle(tr(_title));
    setLayout(layout);

    //createMenus();*/

    // create menubar on top
    myWin = new CSWindow(parent);	// window to display image

    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(myWin);	// make this scrollable

    quitButton = new QPushButton(tr("quit"));
    connect(quitButton,SIGNAL(clicked()),qApp,SLOT(quit()));
    Label = new QLabel(tr("Threshold"));
    threshLabel = new QLabel(tr("128"));// initial value
    Slider = new QSlider(Qt::Horizontal,this);
    Slider->setRange(0,255);
    Slider->setMinimum(0);
    Slider->setValue(128);// initial value
    Slider->setMaximum(255);
    connect(Slider,SIGNAL(valueChanged(int)),myWin,SLOT(setThreshold(int)));
    connect(Slider,SIGNAL(valueChanged(int)),threshLabel,SLOT(setNum(int)));
    // create menubar on top
    menuBar = new QMenuBar;
    // create vertical layout
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(menuBar);		// put menubar on top
    layout->addWidget(scrollArea);	// put display window
    QHBoxLayout *bLayout = new QHBoxLayout;// create horizontal layout
    bLayout->addStretch();			// add stretch
    bLayout->addWidget(Label);		// add label
    bLayout->addWidget(Slider);		// add slider
    bLayout->addWidget(threshLabel);
    bLayout->addWidget(quitButton);	// add quit button
    layout->addLayout(bLayout);		// add horizontal layout to vertical
    setGeometry(100,100,500,500);	// set geometry
    _title="CMPUT 411/511 - Halftoning";
    createActions();				// create actions for menu
    createMenus();					// create menu
    setWindowTitle(tr(_title));		// set title
    setLayout(layout);
}

void MainWindow::createMenus()
{
    fileMenu = new QMenu(tr("&File"), this);
    //fileMenu->addAction(openAct);
    //fileMenu->addAction(exitAct);

    helpMenu = new QMenu(tr("&About"), this);
    //helpMenu->addAction(aboutAct);

    menuBar->addMenu(fileMenu);
    menuBar->addMenu(helpMenu);
}
