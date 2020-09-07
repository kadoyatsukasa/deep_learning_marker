#include "MainWindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_centralWidget=new MainWidget(this);
    setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow()
{
}

