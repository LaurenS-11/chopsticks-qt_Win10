#include "debuginfowindow.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QLabel>

DebugInfoWindow::DebugInfoWindow(QWidget *parent)
    : QWidget(parent)
    , m_totalMessages(0)
    , m_serverMessages(0)
    , m_networkMessages(0)
    , m_gameMessages(0)
    , m_scrollTimer(nullptr)
    , m_tabWidget(nullptr)
    , m_allMessagesEdit(nullptr)
    , m_serverInfoEdit(nullptr)
    , m_networkInfoEdit(nullptr)
    , m_gameInfoEdit(nullptr)
{
    fprintf(stderr, "Minimal DebugInfoWindow constructor starting...\n");
    fflush(stderr);
    
    // Just create a simple window with a label
    setWindowTitle("Chopsticks Qt - Debug Window (Minimal)");
    resize(400, 300);
    
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel("Debug window created successfully!");
    layout->addWidget(label);
    
    fprintf(stderr, "Minimal DebugInfoWindow constructor completed\n");
    fflush(stderr);
}

DebugInfoWindow::~DebugInfoWindow()
{
    // Empty destructor for minimal version
}

void DebugInfoWindow::setupUI()
{
    // Empty for minimal version
}

void DebugInfoWindow::updateWindowTitle()
{
    // Empty for minimal version
}

void DebugInfoWindow::addMessage(const QString& message, MessageCategory category)
{
    // Empty for minimal version
}

void DebugInfoWindow::showWindow()
{
    show();
    raise();
    activateWindow();
}

void DebugInfoWindow::exportMessages()
{
    // Empty for minimal version
}

void DebugInfoWindow::clearMessages()
{
    // Empty for minimal version
}

void DebugInfoWindow::scrollToBottom()
{
    // Empty for minimal version
}

void DebugInfoWindow::onTabChanged(int index)
{
    // Empty for minimal version
}
