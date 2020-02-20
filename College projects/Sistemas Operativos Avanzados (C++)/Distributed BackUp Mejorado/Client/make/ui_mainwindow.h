/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *ConnectButton;
    QSpinBox *PortNumber;
    QVBoxLayout *verticalLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *ServerAddress;
    QSpinBox *ServerPort;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *SourceDirAddress;
    QPushButton *SourceFindDirButton;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *DestinationDirAddress;
    QPushButton *DestinationFindDirAddress;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_5;
    QSpinBox *DestNumber;
    QPushButton *SendFileButton;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *ImportButton;
    QPushButton *ExportButton;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_8;
    QTableView *tableView;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(453, 479);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_7 = new QVBoxLayout(tab);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_2->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        ConnectButton = new QPushButton(tab);
        ConnectButton->setObjectName(QStringLiteral("ConnectButton"));

        horizontalLayout->addWidget(ConnectButton);

        PortNumber = new QSpinBox(tab);
        PortNumber->setObjectName(QStringLiteral("PortNumber"));

        horizontalLayout->addWidget(PortNumber);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_7->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        verticalLayout_3->addWidget(label);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        ServerAddress = new QLineEdit(tab);
        ServerAddress->setObjectName(QStringLiteral("ServerAddress"));

        horizontalLayout_2->addWidget(ServerAddress);

        ServerPort = new QSpinBox(tab);
        ServerPort->setObjectName(QStringLiteral("ServerPort"));

        horizontalLayout_2->addWidget(ServerPort);


        verticalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_7->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_4->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        SourceDirAddress = new QLineEdit(tab);
        SourceDirAddress->setObjectName(QStringLiteral("SourceDirAddress"));
        SourceDirAddress->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_3->addWidget(SourceDirAddress);

        SourceFindDirButton = new QPushButton(tab);
        SourceFindDirButton->setObjectName(QStringLiteral("SourceFindDirButton"));

        horizontalLayout_3->addWidget(SourceFindDirButton);


        verticalLayout_4->addLayout(horizontalLayout_3);


        verticalLayout_7->addLayout(verticalLayout_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_5->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        DestinationDirAddress = new QLineEdit(tab);
        DestinationDirAddress->setObjectName(QStringLiteral("DestinationDirAddress"));
        DestinationDirAddress->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_4->addWidget(DestinationDirAddress);

        DestinationFindDirAddress = new QPushButton(tab);
        DestinationFindDirAddress->setObjectName(QStringLiteral("DestinationFindDirAddress"));

        horizontalLayout_4->addWidget(DestinationFindDirAddress);


        verticalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_7->addLayout(verticalLayout_5);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_6->addWidget(label_5);

        DestNumber = new QSpinBox(tab);
        DestNumber->setObjectName(QStringLiteral("DestNumber"));
        DestNumber->setMinimum(1);

        verticalLayout_6->addWidget(DestNumber);


        verticalLayout_7->addLayout(verticalLayout_6);

        SendFileButton = new QPushButton(tab);
        SendFileButton->setObjectName(QStringLiteral("SendFileButton"));

        verticalLayout_7->addWidget(SendFileButton);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        ImportButton = new QPushButton(tab);
        ImportButton->setObjectName(QStringLiteral("ImportButton"));

        horizontalLayout_5->addWidget(ImportButton);

        ExportButton = new QPushButton(tab);
        ExportButton->setObjectName(QStringLiteral("ExportButton"));

        horizontalLayout_5->addWidget(ExportButton);


        verticalLayout_7->addLayout(horizontalLayout_5);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_8 = new QVBoxLayout(tab_2);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableView->horizontalHeader()->setStretchLastSection(true);

        verticalLayout_8->addWidget(tableView);

        tabWidget->addTab(tab_2, QString());

        verticalLayout->addWidget(tabWidget);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 453, 22));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Client", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindow", "Client port:", Q_NULLPTR));
        ConnectButton->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindow", "Server address and port:", Q_NULLPTR));
        ServerAddress->setText(QApplication::translate("MainWindow", "127.0.0.1", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindow", "Source directory:", Q_NULLPTR));
        SourceFindDirButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label_4->setText(QApplication::translate("MainWindow", "Destination directory:", Q_NULLPTR));
        DestinationFindDirAddress->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindow", "Number of clients:", Q_NULLPTR));
        SendFileButton->setText(QApplication::translate("MainWindow", "Send", Q_NULLPTR));
        ImportButton->setText(QApplication::translate("MainWindow", "Import config", Q_NULLPTR));
        ExportButton->setText(QApplication::translate("MainWindow", "Export config", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Main", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "History", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
