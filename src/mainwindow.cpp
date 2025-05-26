#include "mainwindow.h"
#include <QKeyEvent>
#include <QApplication>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), m_game(4, 4)
{
    m_mainMenu = new MainMenuView();
    m_gameView = new GameView(4, 4);
    m_leaderboardView = new LeaderboardView();
    m_settingsView = new SettingsView();

    m_stack = new QStackedWidget(this);

    m_stack->addWidget(m_mainMenu);
    m_stack->addWidget(m_gameView);
    m_stack->addWidget(m_leaderboardView);
    m_stack->addWidget(m_settingsView);
    setCentralWidget(m_stack);

    setWindowTitle("2048 Game");

    setupConnections();
}

void MainWindow::setupConnections()
{
    connect(m_mainMenu, &MainMenuView::startGameClicked, this, &MainWindow::handleStartGame);
    connect(m_mainMenu, &MainMenuView::leaderboardClicked, this, &MainWindow::handleOpenLeaderboard);
    connect(m_mainMenu, &MainMenuView::settingsClicked, this, &MainWindow::handleOpenSettings);
    connect(m_mainMenu, &MainMenuView::quitClicked, qApp, &QApplication::quit);

    connect(m_leaderboardView, &LeaderboardView::backClicked, this, &MainWindow::handleLeaderboardBack);

    connect(m_settingsView, &SettingsView::confirmClicked, this, &MainWindow::handleSettingsConfirmed);
}

void MainWindow::handleStartGame()
{
    m_game.resetBoard();
    m_gameView->clearBoard();

    m_stack->setCurrentWidget(m_gameView);
    m_gameView->renderBoard(m_game);
}

void MainWindow::handleOpenSettings()
{
    m_stack->setCurrentWidget(m_settingsView);
}

void MainWindow::handleSettingsConfirmed()
{
    m_stack->setCurrentWidget(m_mainMenu);
}

void MainWindow::handleOpenLeaderboard()
{
    m_stack->setCurrentWidget(m_leaderboardView);
}

void MainWindow::handleLeaderboardBack()
{
    m_stack->setCurrentWidget(m_mainMenu);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_stack->currentWidget() == m_gameView && !m_game.isGameOver())
    {
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
        m_gameView->renderBoard(m_game);
    }
}
