#include "mainwindow.h"
#include <QKeyEvent>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent):
    QMainWindow(parent), m_gameRows(4), m_gameCols(4), m_game(4, 4), m_playerName("Player"), m_isGameOver(false)
{
    m_mainMenu = new MainMenuView(this);
    m_gameView = new GameView(m_gameRows, m_gameCols);
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

    connect(m_gameView, &GameView::resetClicked, this, &MainWindow::handleGameReset);
    connect(m_gameView, &GameView::backClicked, this, &MainWindow::handleLeaderboardBack);

    connect(m_leaderboardView, &LeaderboardView::backClicked, this, &MainWindow::handleLeaderboardBack);

    connect(m_settingsView, &SettingsView::settingsConfirmed, this, &MainWindow::handleSettingsConfirmed);
}

void MainWindow::handleStartGame()
{
    m_isGameOver = false;
    m_game.resetBoard();
    m_gameView->clearBoard();
    m_game.resetScore();
    m_gameView->updateScore(0);

    m_stack->setCurrentWidget(m_gameView);
    m_gameView->renderBoard(m_game);
}

void MainWindow::handleOpenSettings()
{
    m_settingsView->setDimensions(m_gameRows, m_gameCols);
    m_stack->setCurrentWidget(m_settingsView);
}

void MainWindow::handleSettingsConfirmed(quint32 rows, quint32 cols, const QString& playerName)
{
    m_gameRows = rows;
    m_gameCols = cols;
    m_playerName = playerName;

    m_game = Game(m_gameRows, m_gameCols);

    m_stack->removeWidget(m_gameView);
    delete m_gameView;

    m_gameView = new GameView(m_gameRows, m_gameCols);
    m_stack->addWidget(m_gameView);

    connect(m_gameView, &GameView::resetClicked, this, &MainWindow::handleGameReset);
    connect(m_gameView, &GameView::backClicked, this, &MainWindow::handleLeaderboardBack);

    m_stack->setCurrentWidget(m_mainMenu);
}

void MainWindow::handleOpenLeaderboard()
{
    m_leaderboardView->requestLeaderboard();
    m_stack->setCurrentWidget(m_leaderboardView);
}

void MainWindow::handleLeaderboardBack()
{
    m_stack->setCurrentWidget(m_mainMenu);
}

void MainWindow::handleGameReset()
{
    handleStartGame();
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (m_stack->currentWidget() == m_gameView && !m_isGameOver)
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
    if (m_stack->currentWidget() == m_gameView && m_game.isGameOver())
    {
        handleGameOver();
    }
}

void MainWindow::handleGameOver()
{
    m_isGameOver = true;

    m_leaderboardView->addScore(m_playerName, m_game.score());

    QMessageBox::information(this, "Game Over!", "You have run out of moves!");

    m_stack->setCurrentWidget(m_mainMenu);
}
