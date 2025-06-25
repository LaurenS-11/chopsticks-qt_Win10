#include "debuginfowindow.h"
#include <QApplication>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QDateTime>
#include <QFont>
#include <QFontMetrics>
#include <QScreen>

DebugInfoWindow::DebugInfoWindow(QWidget *parent)
    : QWidget(parent)
    , m_totalMessages(0)
    , m_serverMessages(0)
    , m_networkMessages(0)
    , m_gameMessages(0)
{
    fprintf(stderr, "DebugInfoWindow constructor starting...\n");
    fflush(stderr);
    
    setupUI();
    
    // Auto-scroll timer for smooth scrolling
    m_scrollTimer = new QTimer(this);
    m_scrollTimer->setSingleShot(true);
    connect(m_scrollTimer, &QTimer::timeout, this, &DebugInfoWindow::scrollToBottom);
    
    updateWindowTitle();
    
    fprintf(stderr, "DebugInfoWindow constructor completed\n");
    fflush(stderr);
}

DebugInfoWindow::~DebugInfoWindow()
{
    // Empty destructor for minimal version
}

void DebugInfoWindow::setupUI()
{
    setWindowTitle("Chopsticks Qt - Server & Debug Information");
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        resize(800, 600);
    } else {
        QRect screenGeometry = screen->availableGeometry();
        int width = qMin(900, static_cast<int>(screenGeometry.width() * 0.7));
        int height = qMin(700, static_cast<int>(screenGeometry.height() * 0.8));
        resize(width, height);
        move((screenGeometry.width() - width) / 2, (screenGeometry.height() - height) / 2);
    }
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    QLabel *titleLabel = new QLabel("Chopsticks Qt - Game Information & Debug Console");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("QLabel { color: #2c3e50; margin: 10px; }");
    mainLayout->addWidget(titleLabel);
    m_tabWidget = new QTabWidget();
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &DebugInfoWindow::onTabChanged);
    // Minimal test: no font, no stylesheet
    m_allMessagesEdit = new QTextEdit();
    m_allMessagesEdit->setReadOnly(true);
    m_tabWidget->addTab(m_allMessagesEdit, "All Messages");
    mainLayout->addWidget(m_tabWidget);
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
