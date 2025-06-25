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
    setupUI();
    
    // Auto-scroll timer for smooth scrolling
    m_scrollTimer = new QTimer(this);
    m_scrollTimer->setSingleShot(true);
    connect(m_scrollTimer, &QTimer::timeout, this, &DebugInfoWindow::scrollToBottom);
    
    updateWindowTitle();
}

void DebugInfoWindow::setupUI()
{
    setWindowTitle("Chopsticks Qt - Server & Debug Information");
    
    // Make window bigger and centered
    QScreen *screen = QApplication::primaryScreen();
    if (!screen) {
        // Fallback if no screen available
        resize(800, 600);
    } else {
        QRect screenGeometry = screen->availableGeometry();
        int width = qMin(900, static_cast<int>(screenGeometry.width() * 0.7));
        int height = qMin(700, static_cast<int>(screenGeometry.height() * 0.8));
        resize(width, height);
        
        // Center the window
        move((screenGeometry.width() - width) / 2, (screenGeometry.height() - height) / 2);
    }
    
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Title label
    QLabel *titleLabel = new QLabel("Chopsticks Qt - Game Information & Debug Console");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("QLabel { color: #2c3e50; margin: 10px; }");
    mainLayout->addWidget(titleLabel);
    
    // Tab widget for different categories
    m_tabWidget = new QTabWidget();
    connect(m_tabWidget, &QTabWidget::currentChanged, this, &DebugInfoWindow::onTabChanged);
    
    // All Messages tab
    m_allMessagesEdit = new QTextEdit();
    m_allMessagesEdit->setReadOnly(true);
    m_allMessagesEdit->setFont(QFont("Consolas", 10));
    m_allMessagesEdit->setStyleSheet(
        "QTextEdit { "
        "background-color: #f8f9fa; "
        "border: 1px solid #dee2e6; "
        "border-radius: 4px; "
        "padding: 8px; "
        "}"
    );
    m_tabWidget->addTab(m_allMessagesEdit, "All Messages");
    
    // Server Info tab
    m_serverInfoEdit = new QTextEdit();
    m_serverInfoEdit->setReadOnly(true);
    m_serverInfoEdit->setFont(QFont("Consolas", 10));
    m_serverInfoEdit->setStyleSheet(
        "QTextEdit { "
        "background-color: #f0f8f0; "
        "border: 1px solid #c3e6c3; "
        "border-radius: 4px; "
        "padding: 8px; "
        "}"
    );
    m_tabWidget->addTab(m_serverInfoEdit, "Server Info");
    
    // Network Events tab
    m_networkEventsEdit = new QTextEdit();
    m_networkEventsEdit->setReadOnly(true);
    m_networkEventsEdit->setFont(QFont("Consolas", 10));
    m_networkEventsEdit->setStyleSheet(
        "QTextEdit { "
        "background-color: #f0f4f8; "
        "border: 1px solid #c3d9e6; "
        "border-radius: 4px; "
        "padding: 8px; "
        "}"
    );
    m_tabWidget->addTab(m_networkEventsEdit, "Network Events");
    
    // Game Events tab
    m_gameEventsEdit = new QTextEdit();
    m_gameEventsEdit->setReadOnly(true);
    m_gameEventsEdit->setFont(QFont("Consolas", 10));
    m_gameEventsEdit->setStyleSheet(
        "QTextEdit { "
        "background-color: #fff8f0; "
        "border: 1px solid #e6d9c3; "
        "border-radius: 4px; "
        "padding: 8px; "
        "}"
    );
    m_tabWidget->addTab(m_gameEventsEdit, "Game Events");
    
    mainLayout->addWidget(m_tabWidget);
    
    // Status and controls
    QHBoxLayout *controlsLayout = new QHBoxLayout();
    
    m_statusLabel = new QLabel("Ready - No messages yet");
    m_statusLabel->setStyleSheet("QLabel { color: #6c757d; font-size: 11px; }");
    controlsLayout->addWidget(m_statusLabel);
    
    controlsLayout->addStretch();
    
    m_clearButton = new QPushButton("Clear All");
    m_clearButton->setToolTip("Clear all messages from all tabs");
    connect(m_clearButton, &QPushButton::clicked, this, &DebugInfoWindow::clearAllMessages);
    controlsLayout->addWidget(m_clearButton);
    
    m_saveButton = new QPushButton("Save to File");
    m_saveButton->setToolTip("Save all messages to a text file");
    connect(m_saveButton, &QPushButton::clicked, this, &DebugInfoWindow::saveToFile);
    controlsLayout->addWidget(m_saveButton);
    
    m_closeButton = new QPushButton("Close");
    m_closeButton->setToolTip("Close this information window");
    connect(m_closeButton, &QPushButton::clicked, this, &DebugInfoWindow::hideWindow);
    controlsLayout->addWidget(m_closeButton);
    
    mainLayout->addLayout(controlsLayout);
    
    // Initial message
    QString welcomeMsg = QString("Chopsticks Qt Debug Console Started - %1\n")
                         .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    welcomeMsg += "========================================================================\n";
    welcomeMsg += "This window shows all server information, network events, and debug messages.\n";
    welcomeMsg += "Use tabs above to filter by category. The window stays on top for easy monitoring.\n";
    welcomeMsg += "You can save all messages to a file using the 'Save to File' button.\n\n";
    
    addMessage("System", welcomeMsg);
}

void DebugInfoWindow::updateWindowTitle()
{
    setWindowTitle("Chopsticks Qt - Debug Information");
}

void DebugInfoWindow::addMessage(const QString& category, const QString& message)
{
    QString timestamp = QDateTime::currentDateTime().toString("hh:mm:ss");
    QString formattedMessage = QString("[%1] %2: %3\n").arg(timestamp, category, message);
    
    // Add to all messages
    m_allMessagesEdit->append(formattedMessage);
    m_totalMessages++;
    
    // Add to specific category tabs
    if (category.contains("Server", Qt::CaseInsensitive) || 
        category.contains("Network Server", Qt::CaseInsensitive)) {
        m_serverInfoEdit->append(formattedMessage);
        m_serverMessages++;
    } else if (category.contains("Network", Qt::CaseInsensitive) || 
               category.contains("Client", Qt::CaseInsensitive)) {
        m_networkEventsEdit->append(formattedMessage);
        m_networkMessages++;
    } else if (category.contains("Game", Qt::CaseInsensitive) || 
               category.contains("AI", Qt::CaseInsensitive) ||
               category.contains("Player", Qt::CaseInsensitive)) {
        m_gameEventsEdit->append(formattedMessage);
        m_gameMessages++;
    }
    
    updateWindowTitle();
    
    // Auto-scroll to bottom after a short delay
    m_scrollTimer->start(100);
}

void DebugInfoWindow::addServerInfo(const QString &info)
{
    addMessage("Server", info);
}

void DebugInfoWindow::addNetworkEvent(const QString &event)
{
    addMessage("Network", event);
}

void DebugInfoWindow::addGameEvent(const QString &event)
{
    addMessage("Game", event);
}

void DebugInfoWindow::showWindow()
{
    // Set window flags before showing
    setWindowFlags(windowFlags() | Qt::WindowStaysOnTopHint);
    
    show();
    raise();
    activateWindow();
    
    // Make sure it's visible and not minimized
    setWindowState(windowState() & ~Qt::WindowMinimized);
}

void DebugInfoWindow::hideWindow()
{
    hide();
}

void DebugInfoWindow::clearAllMessages()
{
    QMessageBox::StandardButton reply = QMessageBox::question(
        this, 
        "Clear All Messages", 
        "Are you sure you want to clear all messages from all tabs?\n\nThis action cannot be undone.",
        QMessageBox::Yes | QMessageBox::No,
        QMessageBox::No
    );
    
    if (reply == QMessageBox::Yes) {
        m_allMessagesEdit->clear();
        m_serverInfoEdit->clear();
        m_networkEventsEdit->clear();
        m_gameEventsEdit->clear();
        
        m_totalMessages = 0;
        m_serverMessages = 0;
        m_networkMessages = 0;
        m_gameMessages = 0;
        
        updateWindowTitle();
        
        QString clearMsg = QString("Messages cleared at %1\n\n")
                           .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
        addMessage("System", clearMsg);
    }
}

void DebugInfoWindow::saveToFile()
{
    QString defaultName = QString("chopsticks_debug_%1.txt")
                         .arg(QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
    
    QString fileName = QFileDialog::getSaveFileName(
        this,
        "Save Debug Information",
        defaultName,
        "Text Files (*.txt);;All Files (*)"
    );
    
    if (!fileName.isEmpty()) {
        QFile file(fileName);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            
            out << "Chopsticks Qt - Debug Information Export\n";
            out << "Generated: " << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << "\n";
            out << "==============================================================\n\n";
            
            out << "ALL MESSAGES:\n";
            out << "=============\n";
            out << m_allMessagesEdit->toPlainText() << "\n\n";
            
            out << "SERVER INFORMATION:\n";
            out << "==================\n";
            out << m_serverInfoEdit->toPlainText() << "\n\n";
            
            out << "NETWORK EVENTS:\n";
            out << "===============\n";
            out << m_networkEventsEdit->toPlainText() << "\n\n";
            
            out << "GAME EVENTS:\n";
            out << "============\n";
            out << m_gameEventsEdit->toPlainText() << "\n";
            
            QMessageBox::information(this, "Export Successful", 
                QString("Debug information saved to:\n%1").arg(fileName));
        } else {
            QMessageBox::warning(this, "Export Failed", 
                QString("Could not write to file:\n%1\n\nError: %2")
                .arg(fileName, file.errorString()));
        }
    }
}

void DebugInfoWindow::scrollToBottom()
{
    if (!m_tabWidget) return;
    
    QTextEdit *currentEdit = nullptr;
    
    switch (m_tabWidget->currentIndex()) {
        case 0: currentEdit = m_allMessagesEdit; break;
        case 1: currentEdit = m_serverInfoEdit; break;
        case 2: currentEdit = m_networkEventsEdit; break;
        case 3: currentEdit = m_gameEventsEdit; break;
        default: return;
    }
    
    if (currentEdit) {
        QScrollBar *scrollBar = currentEdit->verticalScrollBar();
        if (scrollBar) {
            scrollBar->setValue(scrollBar->maximum());
            currentEdit->ensureCursorVisible();
        }
    }
}

void DebugInfoWindow::onTabChanged(int index)
{
    // Auto-scroll the newly selected tab to bottom
    if (m_scrollTimer) {
        m_scrollTimer->start(50);
    }
}
