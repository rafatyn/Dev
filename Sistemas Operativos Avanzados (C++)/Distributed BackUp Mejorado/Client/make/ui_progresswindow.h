/********************************************************************************
** Form generated from reading UI file 'progresswindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROGRESSWINDOW_H
#define UI_PROGRESSWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProgressWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label_4;
    QLabel *FileNameLabel;
    QLabel *FileBytesRWLabel;
    QLabel *label_2;
    QLabel *TotalFileBytesLabel;
    QProgressBar *FileProgressBar;
    QHBoxLayout *horizontalLayout_2;
    QLabel *TotalBytesRWlabel;
    QLabel *label_3;
    QLabel *TotalBytesLabel;
    QProgressBar *TotalProgressBar;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ProgressWindow)
    {
        if (ProgressWindow->objectName().isEmpty())
            ProgressWindow->setObjectName(QStringLiteral("ProgressWindow"));
        ProgressWindow->resize(486, 253);
        centralwidget = new QWidget(ProgressWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label_4 = new QLabel(centralwidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout->addWidget(label_4);

        FileNameLabel = new QLabel(centralwidget);
        FileNameLabel->setObjectName(QStringLiteral("FileNameLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(8);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FileNameLabel->sizePolicy().hasHeightForWidth());
        FileNameLabel->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(FileNameLabel);

        FileBytesRWLabel = new QLabel(centralwidget);
        FileBytesRWLabel->setObjectName(QStringLiteral("FileBytesRWLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(5);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(FileBytesRWLabel->sizePolicy().hasHeightForWidth());
        FileBytesRWLabel->setSizePolicy(sizePolicy1);
        FileBytesRWLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(FileBytesRWLabel);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy2);

        horizontalLayout->addWidget(label_2);

        TotalFileBytesLabel = new QLabel(centralwidget);
        TotalFileBytesLabel->setObjectName(QStringLiteral("TotalFileBytesLabel"));
        sizePolicy1.setHeightForWidth(TotalFileBytesLabel->sizePolicy().hasHeightForWidth());
        TotalFileBytesLabel->setSizePolicy(sizePolicy1);

        horizontalLayout->addWidget(TotalFileBytesLabel);


        verticalLayout->addLayout(horizontalLayout);

        FileProgressBar = new QProgressBar(centralwidget);
        FileProgressBar->setObjectName(QStringLiteral("FileProgressBar"));
        FileProgressBar->setValue(0);

        verticalLayout->addWidget(FileProgressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        TotalBytesRWlabel = new QLabel(centralwidget);
        TotalBytesRWlabel->setObjectName(QStringLiteral("TotalBytesRWlabel"));
        sizePolicy1.setHeightForWidth(TotalBytesRWlabel->sizePolicy().hasHeightForWidth());
        TotalBytesRWlabel->setSizePolicy(sizePolicy1);
        TotalBytesRWlabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(TotalBytesRWlabel);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(1);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy3);
        label_3->setAlignment(Qt::AlignCenter);

        horizontalLayout_2->addWidget(label_3);

        TotalBytesLabel = new QLabel(centralwidget);
        TotalBytesLabel->setObjectName(QStringLiteral("TotalBytesLabel"));
        sizePolicy1.setHeightForWidth(TotalBytesLabel->sizePolicy().hasHeightForWidth());
        TotalBytesLabel->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(TotalBytesLabel);


        verticalLayout->addLayout(horizontalLayout_2);

        TotalProgressBar = new QProgressBar(centralwidget);
        TotalProgressBar->setObjectName(QStringLiteral("TotalProgressBar"));
        TotalProgressBar->setValue(0);

        verticalLayout->addWidget(TotalProgressBar);

        ProgressWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(ProgressWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 486, 17));
        ProgressWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(ProgressWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        ProgressWindow->setStatusBar(statusbar);

        retranslateUi(ProgressWindow);

        QMetaObject::connectSlotsByName(ProgressWindow);
    } // setupUi

    void retranslateUi(QMainWindow *ProgressWindow)
    {
        ProgressWindow->setWindowTitle(QString());
        label_4->setText(QApplication::translate("ProgressWindow", "Name:", Q_NULLPTR));
        FileNameLabel->setText(QString());
        FileBytesRWLabel->setText(QString());
        label_2->setText(QApplication::translate("ProgressWindow", "/", Q_NULLPTR));
        TotalFileBytesLabel->setText(QString());
        TotalBytesRWlabel->setText(QString());
        label_3->setText(QApplication::translate("ProgressWindow", "/", Q_NULLPTR));
        TotalBytesLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ProgressWindow: public Ui_ProgressWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESSWINDOW_H
