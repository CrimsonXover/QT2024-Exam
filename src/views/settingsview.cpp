#include "settingsview.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>

SettingsView::SettingsView()
{
    m_layout = new QVBoxLayout(this);

    m_titleLabel = new QLabel("Settings");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet("font-size: 12px; font-weight: bold;");
    m_layout->addWidget(m_titleLabel);

    m_confirmButton = new QPushButton("Confirm");
    m_layout->addWidget(m_confirmButton);
}
