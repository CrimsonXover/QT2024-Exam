#include "leaderboardview.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include "../mainwindow.h"

LeaderboardView::LeaderboardView()
{
    m_layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("Leaderboard");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 12px; font-weight: bold;");
    m_layout->addWidget(m_titleLabel);

    m_backButton = new QPushButton("Back");
    m_layout->addWidget(m_backButton);

    connect(m_backButton, &QPushButton::clicked, this, &LeaderboardView::backClicked);
}
