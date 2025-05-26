#include "mainmenuview.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>

MainMenuView::MainMenuView(QWidget *parent) : QWidget(parent)
{
    m_layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("2048 Game");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 24px; font-weight: bold;");
    m_layout->addWidget(m_titleLabel);

    m_startButton = new QPushButton("Start Game");
    m_leaderboardButton = new QPushButton("Leaderboard");
    m_settingsButton = new QPushButton("Settings");
    m_quitButton = new QPushButton("Quit");

    m_layout->addWidget(m_startButton);
    m_layout->addWidget(m_leaderboardButton);
    m_layout->addWidget(m_settingsButton);
    m_layout->addWidget(m_quitButton);

    connect(m_startButton, &QPushButton::clicked, this, &MainMenuView::startGameClicked);
    connect(m_leaderboardButton, &QPushButton::clicked, this, &MainMenuView::leaderboardClicked);
    connect(m_settingsButton, &QPushButton::clicked, this, &MainMenuView::settingsClicked);
    connect(m_quitButton, &QPushButton::clicked, this, &MainMenuView::quitClicked);
}
