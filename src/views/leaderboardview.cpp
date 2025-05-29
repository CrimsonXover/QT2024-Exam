#include "leaderboardview.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QMessageBox>
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

    m_tcpSocket = new QTcpSocket(this);

    connect(m_tcpSocket, &QTcpSocket::readyRead, this, &LeaderboardView::onReadyRead);
}

void LeaderboardView::requestLeaderboard()
{
    if (m_tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        m_tcpSocket->connectToHost("127.0.0.1", 3000);
        if (!m_tcpSocket->waitForConnected(1500))
        {
            QMessageBox::warning(this, "Connection Error", "Could not connect");
            return;
        }
    }

    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << (quint32)0;
        out << QString("GET_LEADERBOARD");
        out.device()->seek(0);
        out << (quint32)(block.size() - sizeof(quint32));
        m_tcpSocket->write(block);
        m_tcpSocket->flush();
    }
}

void LeaderboardView::addScore(const QString& name, quint32 score)
{
    if (m_tcpSocket->state() == QAbstractSocket::UnconnectedState)
    {
        m_tcpSocket->connectToHost("127.0.0.1", 3000);
        if (!m_tcpSocket->waitForConnected(1500))
        {
            QMessageBox::warning(this, "Connection Error", "Could not connect");
            return;
        }
    }

    if (m_tcpSocket->state() == QAbstractSocket::ConnectedState)
    {
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_5_15);
        out << (quint32)0;
        out << QString(QString("ADD_SCORE,%1,%2").arg(name).arg(score));
        out.device()->seek(0);
        out << (quint32)(block.size() - sizeof(quint32));
        m_tcpSocket->write(block);
        m_tcpSocket->flush();
    }
}

void LeaderboardView::onReadyRead()
{
    QDataStream in(m_tcpSocket);
    in.setVersion(QDataStream::Qt_5_15);

    while (m_tcpSocket->bytesAvailable() >= (qint32)sizeof(quint32))
    {
        if (m_nextBlockSize == 0) in >> m_nextBlockSize;

        if (m_tcpSocket->bytesAvailable() < m_nextBlockSize) return;

        QString responseType;
        in >> responseType;

        if (responseType == "LEADERBOARD_DATA")
        {
            QString leaderboardData;
            in >> leaderboardData;

            m_items.clear();

            QStringList entries = leaderboardData.split(';', Qt::SkipEmptyParts);
            for (const QString& entry : entries)
            {
                QStringList parts = entry.split(':');
                if (parts.size() == 2) m_items.append({parts.at(0), parts.at(1).toUInt()});
            }

            populateLeaderboard();

        }
        else if (responseType == "OK_ADD_SCORE")
        {
            emit scoreAddedSuccessfully();
            requestLeaderboard();
        }
        m_nextBlockSize = 0;
    }
}

void LeaderboardView::populateLeaderboard()
{
    m_leaderboardTable->setRowCount(0);

    m_leaderboardTable->setRowCount(m_items.size());

    std::sort(m_items.rbegin(), m_items.rend());

    for (qint32 i = 0; i < m_items.size(); i++)
    {
        QTableWidgetItem *nameItem = new QTableWidgetItem(m_items[i].name);
        QTableWidgetItem *scoreItem = new QTableWidgetItem(QString::number(m_items[i].score));
        scoreItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

        m_leaderboardTable->setItem(i, 0, nameItem);
        m_leaderboardTable->setItem(i, 1, scoreItem);
    }
}
