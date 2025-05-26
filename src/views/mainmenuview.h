#pragma once

#include <QWidget>

class QPushButton;
class QVBoxLayout;
class QLabel;

class MainMenuView : public QWidget
{
    Q_OBJECT

public:
    MainMenuView(QWidget *parent = nullptr);

signals:
    void startGameClicked();
    void leaderboardClicked();
    void settingsClicked();
    void quitClicked();

private:
    QVBoxLayout *m_layout;

    QLabel *m_titleLabel;

    QPushButton *m_startButton;
    QPushButton *m_leaderboardButton;
    QPushButton *m_settingsButton;
    QPushButton *m_quitButton;
};
