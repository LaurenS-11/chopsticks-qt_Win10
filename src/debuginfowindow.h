#ifndef DEBUGINFOWINDOW_H
#define DEBUGINFOWINDOW_H

#include <QWidget>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QSplitter>
#include <QTabWidget>
#include <QTimer>
#include <QScrollBar>

class DebugInfoWindow : public QWidget
{
    Q_OBJECT

public:
    explicit DebugInfoWindow(QWidget *parent = nullptr);
    
    void addMessage(const QString &category, const QString &message);
    void addServerInfo(const QString &info);
    void addNetworkEvent(const QString &event);
    void addGameEvent(const QString &event);
    
    void showWindow();
    void hideWindow();

public slots:
    void clearAllMessages();
    void saveToFile();

private slots:
    void onTabChanged(int index);
    void scrollToBottom();

private:
    void setupUI();
    void updateWindowTitle();
    
    QTabWidget *m_tabWidget;
    
    // Tabs
    QTextEdit *m_allMessagesEdit;
    QTextEdit *m_serverInfoEdit;
    QTextEdit *m_networkEventsEdit;
    QTextEdit *m_gameEventsEdit;
    
    // Controls
    QPushButton *m_clearButton;
    QPushButton *m_saveButton;
    QPushButton *m_closeButton;
    QLabel *m_statusLabel;
    
    // Auto-scroll timer
    QTimer *m_scrollTimer;
    
    // Message counters
    int m_totalMessages;
    int m_serverMessages;
    int m_networkMessages;
    int m_gameMessages;
};

#endif // DEBUGINFOWINDOW_H
