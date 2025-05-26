#include "mainwindow.h"
#include <QGridLayout>
#include <QPushButton>
#include <QString>
#include <QWidget>
#include <QKeyEvent>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_game(4, 4)
{
    initUI();
    refreshUI();
    setWindowTitle("4x4 Grid");
}

MainWindow::~MainWindow() {}

void MainWindow::initUI()
{
    m_widget = new QWidget(this);
    m_layout = new QGridLayout;
    m_cells.resize(m_game.rows());

    for (int r = 0; r < m_game.rows(); ++r) {
        m_cells[r].resize(m_game.cols());
        for (int c = 0; c < m_game.cols(); ++c) {
            QPushButton *cell = new QPushButton;
            cell->setFixedSize(50, 50);
            cell->setStyleSheet("background-color: lightgray; border: 1px solid #ccc;");
            cell->setFocusPolicy(Qt::NoFocus);
            m_layout->addWidget(cell, r, c);
            m_cells[r][c] = cell;
        }
    }

    m_widget->setLayout(m_layout);
    setCentralWidget(m_widget);
}

void MainWindow::refreshUI()
{
    for (int row = 0; row < m_game.rows(); row++)
    {
        for (int col = 0; col < m_game.cols(); col++)
        {
            QString val = m_game.getCell(row, col);
            m_cells[row][col]->setText(val);
            setCellColor(m_cells[row][col]);
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_game.isGameOver())
        return;

    switch (event->key())
    {
        case Qt::Key_Left:  m_game.moveLeft();  break;
        case Qt::Key_Right: m_game.moveRight(); break;
        case Qt::Key_Up:    m_game.moveUp();    break;
        case Qt::Key_Down:  m_game.moveDown();  break;
        default:
            QMainWindow::keyPressEvent(event);
            return;
    }

    m_game.spawnRandomCell();
    refreshUI();
}

void MainWindow::setCellColor(QPushButton *cell)
{
    const int value = cell->text().toInt();
    switch (value)
    {
        case 2:    cell->setStyleSheet("background-color: #fbfced; color: black; border: 1px solid #ccc;"); break;
        case 4:    cell->setStyleSheet("background-color: #ecefc6; color: black; border: 1px solid #ccc;"); break;
        case 8:    cell->setStyleSheet("background-color: #ffb296; color: black; border: 1px solid #ccc;"); break;
        case 16:   cell->setStyleSheet("background-color: #ff7373; color: black; border: 1px solid #ccc;"); break;
        case 32:   cell->setStyleSheet("background-color: #f6546a; color: white; border: 1px solid #ccc;"); break;
        case 64:   cell->setStyleSheet("background-color: #8b0000; color: white; border: 1px solid #ccc;"); break;
        case 128:  cell->setStyleSheet("background-color: #794044; color: white; border: 1px solid #ccc;"); break;
        case 256:  cell->setStyleSheet("background-color: #31698a; color: white; border: 1px solid #ccc;"); break;
        case 512:  cell->setStyleSheet("background-color: #297A76; color: white; border: 1px solid #ccc;"); break;
        case 1024: cell->setStyleSheet("background-color: #2D8A68; color: white; border: 1px solid #ccc;"); break;
        case 2048: cell->setStyleSheet("background-color: #1C9F4E; color: white; border: 1px solid #ccc;"); break;
        default:   cell->setStyleSheet("background-color: lightgray; color: black; border: 1px solid #ccc;"); break;
    }
}
