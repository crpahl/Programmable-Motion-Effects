#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "cswindow.h"
#include <QSpinBox>
#include <QSlider>
#include <QMainWindow>

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
private:
    void createMenus();

    // label
    QLabel *speedLines;
    QLabel *outputLabel;
    QLabel *blurLabel;
    QLabel *Label3;
    QLabel *Label2;
    QLabel *Label;

    // menu
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *debugMenu;

    // button(s)]
    QCheckBox *setGrid;
    QCheckBox *lockCamera;
    QCheckBox *patchesButton;
    QCheckBox *outputButton;
    QRadioButton *speedButton;
    QRadioButton *blurButton;
    QPushButton *switchButton;
    QPushButton *openButton;
    QPushButton *debugButton;
    QPushButton *animateButton;

    CSWindow *myWin;
    CSWindow *renWin;
    char *_title;
};

#endif // MAINWINDOW_H
