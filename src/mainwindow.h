#pragma once

#include <QMainWindow>
#include <QKeyEvent>
#include "game.h"

class QPushButton;
class QWidget;
class QGridLayout;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void initUI();
    void refreshUI();
    void setCellColor(QPushButton *cell);

    Game m_game;
    QWidget *m_widget;
    QGridLayout *m_layout;
    QVector<QVector<QPushButton*>> m_cells;
};
