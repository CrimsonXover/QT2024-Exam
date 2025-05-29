#pragma once
#include<QWidget>
#include <QTcpSocket>
#include <QDataStream>

class QVBoxLayout;
class QLabel;
class QPushButton;
class QTableWidget;


struct LeaderboardItem
{
    QString name;
    quint32 score;

    bool operator<(const LeaderboardItem& other) const
    {
        return score < other.score;
    }
};

class LeaderboardView : public QWidget
{
    Q_OBJECT
public:
    LeaderboardView();
    void populateLeaderboard();
    void addScore(const QString& name, quint32 score);
    void requestLeaderboard();

signals:
    void backClicked();
    void scoreAddedSuccessfully();

private slots:
    void onReadyRead();

private:

    QVBoxLayout *m_layout;

    QLabel *m_titleLabel;
    QTableWidget *m_leaderboardTable;
    QPushButton *m_backButton;

    QTcpSocket *m_tcpSocket;
    quint32 m_nextBlockSize;

    QList<LeaderboardItem> m_items;
};
