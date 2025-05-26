#pragma once

#include <QWidget>

class QVBoxLayout;
class QPushButton;
class QLabel;

class SettingsView : public QWidget
{
    Q_OBJECT

public:
    SettingsView();

signals:
    void confirmClicked();

private:
    QVBoxLayout *m_layout;

    QLabel *m_titleLabel;
    QPushButton *m_confirmButton;

};
