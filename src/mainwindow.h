#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include "views/mainmenuview.h"
#include "views/gameview.h"
#include "views/leaderboardview.h"
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
    void handleSettingsConfirmed(quint32 newRows, quint32 newCols, const QString& playerName);
    void handleOpenLeaderboard();
    void handleLeaderboardBack();
    void handleGameReset();
    void handleGameOver();

private:
    QStackedWidget *m_stack = nullptr;

    void setupConnections();

    MainMenuView *m_mainMenu;
    GameView *m_gameView;

    SettingsView *m_settingsView;
    LeaderboardView *m_leaderboardView;

    Game m_game;

    quint32 m_gameRows;
    quint32 m_gameCols;
    QString m_playerName;
    bool m_isGameOver;
};
