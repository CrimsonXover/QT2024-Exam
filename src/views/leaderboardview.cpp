#include "leaderboardview.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include "../mainwindow.h"

LeaderboardView::LeaderboardView()
{
    m_layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("Leaderboard");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 12px; font-weight: bold;");
    m_layout->addWidget(m_titleLabel);

    m_leaderboardTable = new QTableWidget();
    m_leaderboardTable->setColumnCount(2);
    m_leaderboardTable->setHorizontalHeaderLabels({"Player Name", "Score"});
    m_leaderboardTable->horizontalHeader()->setStretchLastSection(true);
    m_leaderboardTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_layout->addWidget(m_leaderboardTable);

    m_backButton = new QPushButton("Back");
    m_layout->addWidget(m_backButton);

    connect(m_backButton, &QPushButton::clicked, this, &LeaderboardView::backClicked);

    populateLeaderboard();
}

void LeaderboardView::populateLeaderboard()
{
    m_leaderboardTable->setRowCount(0);

    std::sort(items.rbegin(), items.rend());

    m_leaderboardTable->setRowCount(items.size());

    for (qint32 i = 0; i < items.size(); i++) {
        QTableWidgetItem *nameItem = new QTableWidgetItem(items[i].name);
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(items[i].score));
        scoreItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        m_leaderboardTable->setItem(i, 0, nameItem);
        m_leaderboardTable->setItem(i, 1, scoreItem);
    }
}

void LeaderboardView::addScore(const QString& name, quint32 score)
{
    items.append({name, score});
    populateLeaderboard();
}
