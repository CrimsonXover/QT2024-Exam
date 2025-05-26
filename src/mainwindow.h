#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "views/mainmenuview.h"
#include "views/gameview.h"
#include "views/settingsview.h"
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
    void handleOpenSettings();

private:
    QStackedWidget *m_stack = nullptr;

    void setupConnections();

    MainMenuView *m_mainMenu;
    GameView *m_gameView;

    SettingsView *m_settingsView;

    Game m_game;
};
