#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "views/mainmenuview.h"
#include "views/gameview.h"
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void handleStartGame();

private:
    QStackedWidget *m_stack = nullptr;

    void setupConnections();

    MainMenuView *m_mainMenu;
    GameView *m_gameView;

    Game m_game;
};
