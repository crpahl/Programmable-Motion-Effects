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

    // menu
    QLabel *Label;
    QMenuBar *menuBar;
    QMenu *fileMenu;
    QMenu *debugMenu;

    // button(s)
    QRadioButton *patchesButton;
    QPushButton *openButton;
    QPushButton *debugButton;

    CSWindow *myWin;
    char *_title;
};

#endif // MAINWINDOW_H
