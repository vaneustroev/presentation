/********************************************************************************
** Form generated from reading UI file 'menutrace.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENUTRACE_H
#define UI_MENUTRACE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MenuTrace
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBoxCenter_9;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_12;
    QComboBox *TraceList;
    QToolBox *MarkerPages;
    QWidget *pageSettings;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_10;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_13;
    QRadioButton *TraceClear;
    QRadioButton *TraceAver;
    QRadioButton *TraceMax;
    QRadioButton *TraceMin;
    QRadioButton *TraceView;
    QRadioButton *TraceBlank;
    QSpacerItem *verticalSpacer_3;
    QWidget *pagePeakSearch;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_7;
    QRadioButton *DetectorApeak;
    QRadioButton *DetectorNegative;
    QRadioButton *DetectorPositive;
    QRadioButton *DetectorSample;
    QRadioButton *DetectorRms;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_8;
    QRadioButton *DetectorAuto;
    QRadioButton *DetectorMan;
    QPushButton *DetectorAutoAll;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_3;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_2;
    QComboBox *comboBox;
    QGroupBox *groupBox_3;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_3;
    QComboBox *comboBox_2;
    QGroupBox *groupBoxCenter_7;
    QVBoxLayout *verticalLayout_9;
    QLabel *label_10;
    QComboBox *RbwFilterType_3;
    QSpacerItem *verticalSpacer;
    QWidget *page_4;
    QVBoxLayout *verticalLayout_25;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_19;
    QLabel *label_16;
    QComboBox *comboBox_3;
    QGroupBox *groupBoxCenter_10;
    QVBoxLayout *verticalLayout_20;
    QLabel *label_17;
    QComboBox *RbwFilterType_6;
    QPushButton *pushButton_13;
    QPushButton *pushButton_4;
    QLabel *label_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer_4;
    QWidget *page_5;
    QVBoxLayout *verticalLayout_32;
    QGroupBox *groupBox_14;
    QVBoxLayout *verticalLayout_26;
    QLabel *label_22;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QPushButton *pushButton_7;
    QGroupBox *groupBoxCenter_15;
    QVBoxLayout *verticalLayout_27;
    QLabel *label_23;
    QLabel *label_5;
    QRadioButton *radioButton_3;
    QRadioButton *radioButton_4;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout_28;
    QLabel *label_24;
    QLineEdit *EditSpan_7;
    QGroupBox *groupBox_16;
    QVBoxLayout *verticalLayout_29;
    QLabel *label_25;
    QLineEdit *EditSpan_8;
    QPushButton *pushButton_14;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QWidget *MenuTrace)
    {
        if (MenuTrace->objectName().isEmpty())
            MenuTrace->setObjectName(QStringLiteral("MenuTrace"));
        MenuTrace->resize(824, 732);
        MenuTrace->setStyleSheet(QLatin1String("QWidget:disabled {\n"
"	/*background-color: rgb(144,144,144);*/\n"
"	color: rgb(96,96,96); \n"
"}\n"
"\n"
"QGroupBox::title { \n"
"/*    background-color: transparent;*/\n"
"    subcontrol-position: top left; /* position at the top left*/ \n"
"    padding:2 13px;\n"
" } \n"
"\n"
"QGroupBox { \n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"	border: 2px solid green; \n"
"	border-radius: 9px; \n"
" } \n"
"\n"
"QLineEdit { \n"
"	background-color: white; \n"
"/*	border: 2px solid rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"	border-radius: 5px; \n"
"/*	color: rgb(16,16,16); */\n"
"	color: rgb(250,250,250); \n"
" } \n"
"\n"
"QLabel { \n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"/*	color: rgb(16,16,16); */\n"
"	color: rgb(250,250,250); \n"
" } \n"
"\n"
"QRadioButton { \n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"/*	color: rgb(16,16,16); */\n"
"	color: rgb(250,2"
                        "50,250); \n"
" } \n"
"\n"
"QTabWidget { \n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"	border: 2px solid green; \n"
"	border-radius: 9px; \n"
" } \n"
"\n"
"QTabWidget::pane { /* The tab widget frame */\n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"	/*border-top: 2px solid #C2C7CB;*/\n"
"}\n"
"\n"
"QTabWidget::tab-bar {\n"
"	left: 0px; /* move to the right by 5px */\n"
"}\n"
"\n"
"/* Style the tab using the tab sub-control. Note that it reads QTabBar _not_ QTabWidget */\n"
"QTabBar::tab {\n"
"/*	background-color: rgb(129,129,19); */\n"
"/*	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);*/\n"
"	background-color: rgb(159,159,159); \n"
"	border: 2px solid #C4C4C3;\n"
"	border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"	border-top-left-radius: 4px;\n"
""
                        "	border-top-right-radius: 4px;\n"
"	color: rgb(16,16,16); \n"
"	min-width: 5ex;\n"
"	padding: 3px;\n"
"}\n"
"\n"
"QTabBar::tab:selected, QTabBar::tab:hover {\n"
"/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"/*	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #fafafa, stop: 0.4 #f4f4f4,\n"
"                                     stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);*/\n"
"}\n"
"\n"
"QTabBar::tab:selected {\n"
"	/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(199,199,199); \n"
"	/*border-color: #9B9B9B;*/\n"
"	/* same as pane color */\n"
"	border-bottom-color: #C2C7CB; \n"
"}\n"
"\n"
"QTabBar::tab:!selected {\n"
"	/*	background-color: rgb(129,129,19); */\n"
"	background-color: rgb(159,159,159); \n"
"	margin-top: 3px; /* make non-selected tabs look smaller */\n"
"}\n"
"\n"
"/*QTabBar::tab:only-one { \n"
"	width: 0; \n"
"	height: 0; \n"
"	border-style: none; \n"
"}*/\n"
"\n"
"/* Style the tab using "
                        "the tab sub-control. Note that it reads QTabBar _not_ QTabWidget */\n"
"QToolBox::tab {\n"
"/*	background-color: rgb(129,129,19); */\n"
"/*	background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\n"
"                                     stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\n"
"                                     stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);*/\n"
"	background-color: rgb(159,159,159); \n"
"	border: 2px solid #C4C4C3;\n"
"	border-bottom-color: #C2C7CB; /* same as the pane color */\n"
"	border-top-left-radius: 4px;\n"
"	border-top-right-radius: 4px;\n"
"	color: rgb(16,16,16); \n"
"	min-width: 5ex;\n"
"	padding: 3px;\n"
"}\n"
"\n"
"QPushButton { \n"
"     background-color: rgb(159,159,149);\n"
"     color: rgb(250,250,250); \n"
"     border-style: outset;\n"
"     border-width: 2px;\n"
"     border-radius: 10px;\n"
"     border-color: beige;\n"
"     font: bold 16px;\n"
"     min-width: 10em;\n"
"     padding: 6px;\n"
" } \n"
"\n"
"QPushButton#EditCorrection { \n"
"     background-color: rgb(159,159,149);"
                        " \n"
" } \n"
"\n"
"QPushButton#DeleteAllCorrections { \n"
"     background-color: rgb(159,159,149); \n"
" } \n"
"\n"
""));
        verticalLayout = new QVBoxLayout(MenuTrace);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        groupBoxCenter_9 = new QGroupBox(MenuTrace);
        groupBoxCenter_9->setObjectName(QStringLiteral("groupBoxCenter_9"));
        groupBoxCenter_9->setAutoFillBackground(false);
        groupBoxCenter_9->setStyleSheet(QStringLiteral(""));
        groupBoxCenter_9->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBoxCenter_9->setFlat(false);
        groupBoxCenter_9->setCheckable(false);
        verticalLayout_13 = new QVBoxLayout(groupBoxCenter_9);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_12 = new QLabel(groupBoxCenter_9);
        label_12->setObjectName(QStringLiteral("label_12"));

        verticalLayout_13->addWidget(label_12);

        TraceList = new QComboBox(groupBoxCenter_9);
        TraceList->setObjectName(QStringLiteral("TraceList"));

        verticalLayout_13->addWidget(TraceList);


        verticalLayout->addWidget(groupBoxCenter_9);

        MarkerPages = new QToolBox(MenuTrace);
        MarkerPages->setObjectName(QStringLiteral("MarkerPages"));
        pageSettings = new QWidget();
        pageSettings->setObjectName(QStringLiteral("pageSettings"));
        pageSettings->setGeometry(QRect(0, 0, 824, 503));
        verticalLayout_18 = new QVBoxLayout(pageSettings);
        verticalLayout_18->setSpacing(2);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        verticalLayout_18->setContentsMargins(0, 0, 0, 0);
        groupBox_10 = new QGroupBox(pageSettings);
        groupBox_10->setObjectName(QStringLiteral("groupBox_10"));
        groupBox_10->setStyleSheet(QStringLiteral(""));
        verticalLayout_15 = new QVBoxLayout(groupBox_10);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        label_13 = new QLabel(groupBox_10);
        label_13->setObjectName(QStringLiteral("label_13"));

        verticalLayout_15->addWidget(label_13);

        TraceClear = new QRadioButton(groupBox_10);
        TraceClear->setObjectName(QStringLiteral("TraceClear"));
        TraceClear->setChecked(true);

        verticalLayout_15->addWidget(TraceClear);

        TraceAver = new QRadioButton(groupBox_10);
        TraceAver->setObjectName(QStringLiteral("TraceAver"));

        verticalLayout_15->addWidget(TraceAver);

        TraceMax = new QRadioButton(groupBox_10);
        TraceMax->setObjectName(QStringLiteral("TraceMax"));

        verticalLayout_15->addWidget(TraceMax);

        TraceMin = new QRadioButton(groupBox_10);
        TraceMin->setObjectName(QStringLiteral("TraceMin"));
        TraceMin->setChecked(false);

        verticalLayout_15->addWidget(TraceMin);

        TraceView = new QRadioButton(groupBox_10);
        TraceView->setObjectName(QStringLiteral("TraceView"));
        TraceView->setChecked(false);

        verticalLayout_15->addWidget(TraceView);

        TraceBlank = new QRadioButton(groupBox_10);
        TraceBlank->setObjectName(QStringLiteral("TraceBlank"));

        verticalLayout_15->addWidget(TraceBlank);


        verticalLayout_18->addWidget(groupBox_10);

        verticalSpacer_3 = new QSpacerItem(20, 50, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_3);

        MarkerPages->addItem(pageSettings, QStringLiteral("Control"));
        pagePeakSearch = new QWidget();
        pagePeakSearch->setObjectName(QStringLiteral("pagePeakSearch"));
        pagePeakSearch->setEnabled(true);
        pagePeakSearch->setGeometry(QRect(0, 0, 824, 503));
        verticalLayout_3 = new QVBoxLayout(pagePeakSearch);
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        groupBox_7 = new QGroupBox(pagePeakSearch);
        groupBox_7->setObjectName(QStringLiteral("groupBox_7"));
        groupBox_7->setStyleSheet(QStringLiteral(""));
        verticalLayout_11 = new QVBoxLayout(groupBox_7);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_7 = new QLabel(groupBox_7);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_11->addWidget(label_7);

        DetectorApeak = new QRadioButton(groupBox_7);
        DetectorApeak->setObjectName(QStringLiteral("DetectorApeak"));
        DetectorApeak->setChecked(true);

        verticalLayout_11->addWidget(DetectorApeak);

        DetectorNegative = new QRadioButton(groupBox_7);
        DetectorNegative->setObjectName(QStringLiteral("DetectorNegative"));

        verticalLayout_11->addWidget(DetectorNegative);

        DetectorPositive = new QRadioButton(groupBox_7);
        DetectorPositive->setObjectName(QStringLiteral("DetectorPositive"));

        verticalLayout_11->addWidget(DetectorPositive);

        DetectorSample = new QRadioButton(groupBox_7);
        DetectorSample->setObjectName(QStringLiteral("DetectorSample"));

        verticalLayout_11->addWidget(DetectorSample);

        DetectorRms = new QRadioButton(groupBox_7);
        DetectorRms->setObjectName(QStringLiteral("DetectorRms"));

        verticalLayout_11->addWidget(DetectorRms);


        verticalLayout_3->addWidget(groupBox_7);

        groupBox_8 = new QGroupBox(pagePeakSearch);
        groupBox_8->setObjectName(QStringLiteral("groupBox_8"));
        groupBox_8->setStyleSheet(QStringLiteral(""));
        verticalLayout_12 = new QVBoxLayout(groupBox_8);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        label_8 = new QLabel(groupBox_8);
        label_8->setObjectName(QStringLiteral("label_8"));

        verticalLayout_12->addWidget(label_8);

        DetectorAuto = new QRadioButton(groupBox_8);
        DetectorAuto->setObjectName(QStringLiteral("DetectorAuto"));
        DetectorAuto->setChecked(false);

        verticalLayout_12->addWidget(DetectorAuto);

        DetectorMan = new QRadioButton(groupBox_8);
        DetectorMan->setObjectName(QStringLiteral("DetectorMan"));
        DetectorMan->setChecked(true);

        verticalLayout_12->addWidget(DetectorMan);


        verticalLayout_3->addWidget(groupBox_8);

        DetectorAutoAll = new QPushButton(pagePeakSearch);
        DetectorAutoAll->setObjectName(QStringLiteral("DetectorAutoAll"));

        verticalLayout_3->addWidget(DetectorAutoAll);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        MarkerPages->addItem(pagePeakSearch, QStringLiteral("Detector"));
        page_3 = new QWidget();
        page_3->setObjectName(QStringLiteral("page_3"));
        page_3->setEnabled(false);
        page_3->setGeometry(QRect(0, 0, 824, 503));
        verticalLayout_2 = new QVBoxLayout(page_3);
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        groupBox_2 = new QGroupBox(page_3);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QStringLiteral(""));
        verticalLayout_4 = new QVBoxLayout(groupBox_2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        verticalLayout_4->addWidget(label_2);

        comboBox = new QComboBox(groupBox_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        verticalLayout_4->addWidget(comboBox);


        verticalLayout_2->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(page_3);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setStyleSheet(QStringLiteral(""));
        verticalLayout_5 = new QVBoxLayout(groupBox_3);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_5->addWidget(label_3);

        comboBox_2 = new QComboBox(groupBox_3);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        verticalLayout_5->addWidget(comboBox_2);


        verticalLayout_2->addWidget(groupBox_3);

        groupBoxCenter_7 = new QGroupBox(page_3);
        groupBoxCenter_7->setObjectName(QStringLiteral("groupBoxCenter_7"));
        groupBoxCenter_7->setAutoFillBackground(false);
        groupBoxCenter_7->setStyleSheet(QStringLiteral(""));
        groupBoxCenter_7->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBoxCenter_7->setFlat(false);
        groupBoxCenter_7->setCheckable(false);
        verticalLayout_9 = new QVBoxLayout(groupBoxCenter_7);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        label_10 = new QLabel(groupBoxCenter_7);
        label_10->setObjectName(QStringLiteral("label_10"));

        verticalLayout_9->addWidget(label_10);

        RbwFilterType_3 = new QComboBox(groupBoxCenter_7);
        RbwFilterType_3->setObjectName(QStringLiteral("RbwFilterType_3"));

        verticalLayout_9->addWidget(RbwFilterType_3);


        verticalLayout_2->addWidget(groupBoxCenter_7);

        verticalSpacer = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        MarkerPages->addItem(page_3, QStringLiteral("Math"));
        page_4 = new QWidget();
        page_4->setObjectName(QStringLiteral("page_4"));
        page_4->setEnabled(false);
        page_4->setGeometry(QRect(0, 0, 824, 503));
        verticalLayout_25 = new QVBoxLayout(page_4);
        verticalLayout_25->setSpacing(2);
        verticalLayout_25->setObjectName(QStringLiteral("verticalLayout_25"));
        verticalLayout_25->setContentsMargins(0, 0, 0, 0);
        groupBox_13 = new QGroupBox(page_4);
        groupBox_13->setObjectName(QStringLiteral("groupBox_13"));
        groupBox_13->setStyleSheet(QStringLiteral(""));
        verticalLayout_19 = new QVBoxLayout(groupBox_13);
        verticalLayout_19->setObjectName(QStringLiteral("verticalLayout_19"));
        label_16 = new QLabel(groupBox_13);
        label_16->setObjectName(QStringLiteral("label_16"));

        verticalLayout_19->addWidget(label_16);

        comboBox_3 = new QComboBox(groupBox_13);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));

        verticalLayout_19->addWidget(comboBox_3);


        verticalLayout_25->addWidget(groupBox_13);

        groupBoxCenter_10 = new QGroupBox(page_4);
        groupBoxCenter_10->setObjectName(QStringLiteral("groupBoxCenter_10"));
        groupBoxCenter_10->setAutoFillBackground(false);
        groupBoxCenter_10->setStyleSheet(QStringLiteral(""));
        groupBoxCenter_10->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBoxCenter_10->setFlat(false);
        groupBoxCenter_10->setCheckable(false);
        verticalLayout_20 = new QVBoxLayout(groupBoxCenter_10);
        verticalLayout_20->setObjectName(QStringLiteral("verticalLayout_20"));
        label_17 = new QLabel(groupBoxCenter_10);
        label_17->setObjectName(QStringLiteral("label_17"));

        verticalLayout_20->addWidget(label_17);

        RbwFilterType_6 = new QComboBox(groupBoxCenter_10);
        RbwFilterType_6->setObjectName(QStringLiteral("RbwFilterType_6"));

        verticalLayout_20->addWidget(RbwFilterType_6);


        verticalLayout_25->addWidget(groupBoxCenter_10);

        pushButton_13 = new QPushButton(page_4);
        pushButton_13->setObjectName(QStringLiteral("pushButton_13"));

        verticalLayout_25->addWidget(pushButton_13);

        pushButton_4 = new QPushButton(page_4);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        verticalLayout_25->addWidget(pushButton_4);

        label_4 = new QLabel(page_4);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_25->addWidget(label_4);

        pushButton_5 = new QPushButton(page_4);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        verticalLayout_25->addWidget(pushButton_5);

        pushButton_6 = new QPushButton(page_4);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        verticalLayout_25->addWidget(pushButton_6);

        verticalSpacer_4 = new QSpacerItem(20, 17, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_25->addItem(verticalSpacer_4);

        MarkerPages->addItem(page_4, QStringLiteral("Trace Function"));
        page_5 = new QWidget();
        page_5->setObjectName(QStringLiteral("page_5"));
        page_5->setEnabled(false);
        page_5->setGeometry(QRect(0, 0, 824, 503));
        verticalLayout_32 = new QVBoxLayout(page_5);
        verticalLayout_32->setSpacing(6);
        verticalLayout_32->setObjectName(QStringLiteral("verticalLayout_32"));
        verticalLayout_32->setContentsMargins(0, 0, 0, 0);
        groupBox_14 = new QGroupBox(page_5);
        groupBox_14->setObjectName(QStringLiteral("groupBox_14"));
        groupBox_14->setStyleSheet(QStringLiteral(""));
        verticalLayout_26 = new QVBoxLayout(groupBox_14);
        verticalLayout_26->setObjectName(QStringLiteral("verticalLayout_26"));
        label_22 = new QLabel(groupBox_14);
        label_22->setObjectName(QStringLiteral("label_22"));

        verticalLayout_26->addWidget(label_22);

        radioButton = new QRadioButton(groupBox_14);
        radioButton->setObjectName(QStringLiteral("radioButton"));

        verticalLayout_26->addWidget(radioButton);

        radioButton_2 = new QRadioButton(groupBox_14);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));

        verticalLayout_26->addWidget(radioButton_2);


        verticalLayout_32->addWidget(groupBox_14);

        pushButton_7 = new QPushButton(page_5);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        verticalLayout_32->addWidget(pushButton_7);

        groupBoxCenter_15 = new QGroupBox(page_5);
        groupBoxCenter_15->setObjectName(QStringLiteral("groupBoxCenter_15"));
        groupBoxCenter_15->setAutoFillBackground(false);
        groupBoxCenter_15->setStyleSheet(QStringLiteral(""));
        groupBoxCenter_15->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        groupBoxCenter_15->setFlat(false);
        groupBoxCenter_15->setCheckable(false);
        verticalLayout_27 = new QVBoxLayout(groupBoxCenter_15);
        verticalLayout_27->setObjectName(QStringLiteral("verticalLayout_27"));
        label_23 = new QLabel(groupBoxCenter_15);
        label_23->setObjectName(QStringLiteral("label_23"));

        verticalLayout_27->addWidget(label_23);

        label_5 = new QLabel(groupBoxCenter_15);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_27->addWidget(label_5);

        radioButton_3 = new QRadioButton(groupBoxCenter_15);
        radioButton_3->setObjectName(QStringLiteral("radioButton_3"));

        verticalLayout_27->addWidget(radioButton_3);

        radioButton_4 = new QRadioButton(groupBoxCenter_15);
        radioButton_4->setObjectName(QStringLiteral("radioButton_4"));

        verticalLayout_27->addWidget(radioButton_4);


        verticalLayout_32->addWidget(groupBoxCenter_15);

        groupBox_15 = new QGroupBox(page_5);
        groupBox_15->setObjectName(QStringLiteral("groupBox_15"));
        groupBox_15->setStyleSheet(QStringLiteral(""));
        verticalLayout_28 = new QVBoxLayout(groupBox_15);
        verticalLayout_28->setObjectName(QStringLiteral("verticalLayout_28"));
        label_24 = new QLabel(groupBox_15);
        label_24->setObjectName(QStringLiteral("label_24"));

        verticalLayout_28->addWidget(label_24);

        EditSpan_7 = new QLineEdit(groupBox_15);
        EditSpan_7->setObjectName(QStringLiteral("EditSpan_7"));

        verticalLayout_28->addWidget(EditSpan_7);


        verticalLayout_32->addWidget(groupBox_15);

        groupBox_16 = new QGroupBox(page_5);
        groupBox_16->setObjectName(QStringLiteral("groupBox_16"));
        groupBox_16->setStyleSheet(QStringLiteral(""));
        verticalLayout_29 = new QVBoxLayout(groupBox_16);
        verticalLayout_29->setObjectName(QStringLiteral("verticalLayout_29"));
        label_25 = new QLabel(groupBox_16);
        label_25->setObjectName(QStringLiteral("label_25"));

        verticalLayout_29->addWidget(label_25);

        EditSpan_8 = new QLineEdit(groupBox_16);
        EditSpan_8->setObjectName(QStringLiteral("EditSpan_8"));

        verticalLayout_29->addWidget(EditSpan_8);


        verticalLayout_32->addWidget(groupBox_16);

        pushButton_14 = new QPushButton(page_5);
        pushButton_14->setObjectName(QStringLiteral("pushButton_14"));

        verticalLayout_32->addWidget(pushButton_14);

        verticalSpacer_5 = new QSpacerItem(20, 58, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_32->addItem(verticalSpacer_5);

        MarkerPages->addItem(page_5, QStringLiteral("Normalize"));

        verticalLayout->addWidget(MarkerPages);


        retranslateUi(MenuTrace);

        MarkerPages->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MenuTrace);
    } // setupUi

    void retranslateUi(QWidget *MenuTrace)
    {
        MenuTrace->setWindowTitle(QApplication::translate("MenuTrace", "Form", 0));
        groupBoxCenter_9->setTitle(QString());
        label_12->setText(QApplication::translate("MenuTrace", "Select Trace", 0));
        groupBox_10->setTitle(QString());
        label_13->setText(QApplication::translate("MenuTrace", "Marker Mode", 0));
        TraceClear->setText(QApplication::translate("MenuTrace", "Clear / Write", 0));
        TraceAver->setText(QApplication::translate("MenuTrace", "Trace Average", 0));
        TraceMax->setText(QApplication::translate("MenuTrace", "Max Hold", 0));
        TraceMin->setText(QApplication::translate("MenuTrace", "Min Hold", 0));
        TraceView->setText(QApplication::translate("MenuTrace", "View", 0));
        TraceBlank->setText(QApplication::translate("MenuTrace", "Blank", 0));
        MarkerPages->setItemText(MarkerPages->indexOf(pageSettings), QApplication::translate("MenuTrace", "Control", 0));
        groupBox_7->setTitle(QString());
        label_7->setText(QApplication::translate("MenuTrace", "Detector", 0));
        DetectorApeak->setText(QApplication::translate("MenuTrace", "Apeak", 0));
        DetectorNegative->setText(QApplication::translate("MenuTrace", "Negative", 0));
        DetectorPositive->setText(QApplication::translate("MenuTrace", "Positive", 0));
        DetectorSample->setText(QApplication::translate("MenuTrace", "Sample", 0));
        DetectorRms->setText(QApplication::translate("MenuTrace", "RMS", 0));
        groupBox_8->setTitle(QString());
        label_8->setText(QApplication::translate("MenuTrace", "Detector Select", 0));
        DetectorAuto->setText(QApplication::translate("MenuTrace", "Auto", 0));
        DetectorMan->setText(QApplication::translate("MenuTrace", "Man", 0));
        DetectorAutoAll->setText(QApplication::translate("MenuTrace", "Detector Auto All Traces", 0));
        MarkerPages->setItemText(MarkerPages->indexOf(pagePeakSearch), QApplication::translate("MenuTrace", "Detector", 0));
        groupBox_2->setTitle(QString());
        label_2->setText(QApplication::translate("MenuTrace", "Math Function", 0));
        groupBox_3->setTitle(QString());
        label_3->setText(QApplication::translate("MenuTrace", "Operand 1", 0));
        groupBoxCenter_7->setTitle(QString());
        label_10->setText(QApplication::translate("MenuTrace", "Operand 2", 0));
        MarkerPages->setItemText(MarkerPages->indexOf(page_3), QApplication::translate("MenuTrace", "Math", 0));
        groupBox_13->setTitle(QString());
        label_16->setText(QApplication::translate("MenuTrace", "From Trace", 0));
        groupBoxCenter_10->setTitle(QString());
        label_17->setText(QApplication::translate("MenuTrace", "To Trace", 0));
        pushButton_13->setText(QApplication::translate("MenuTrace", "Copy", 0));
        pushButton_4->setText(QApplication::translate("MenuTrace", "Exchange", 0));
        label_4->setText(QApplication::translate("MenuTrace", "Preset / Clear", 0));
        pushButton_5->setText(QApplication::translate("MenuTrace", "Preset All Traces", 0));
        pushButton_6->setText(QApplication::translate("MenuTrace", "Clear All Traces", 0));
        MarkerPages->setItemText(MarkerPages->indexOf(page_4), QApplication::translate("MenuTrace", "Trace Function", 0));
        groupBox_14->setTitle(QString());
        label_22->setText(QApplication::translate("MenuTrace", "Normalize", 0));
        radioButton->setText(QApplication::translate("MenuTrace", "On", 0));
        radioButton_2->setText(QApplication::translate("MenuTrace", "Off", 0));
        pushButton_7->setText(QApplication::translate("MenuTrace", "Store Reference", 0));
        groupBoxCenter_15->setTitle(QString());
        label_23->setText(QApplication::translate("MenuTrace", "Show Reference", 0));
        label_5->setText(QApplication::translate("MenuTrace", "(Trace 1)", 0));
        radioButton_3->setText(QApplication::translate("MenuTrace", "On", 0));
        radioButton_4->setText(QApplication::translate("MenuTrace", "Off", 0));
        groupBox_15->setTitle(QString());
        label_24->setText(QApplication::translate("MenuTrace", "Norm Ref Lvl", 0));
        EditSpan_7->setText(QApplication::translate("MenuTrace", "0.00 dB", 0));
        groupBox_16->setTitle(QString());
        label_25->setText(QApplication::translate("MenuTrace", "Norm Ref Position", 0));
        EditSpan_8->setText(QApplication::translate("MenuTrace", "10", 0));
        pushButton_14->setText(QApplication::translate("MenuTrace", "Open Short Cal", 0));
        MarkerPages->setItemText(MarkerPages->indexOf(page_5), QApplication::translate("MenuTrace", "Normalize", 0));
    } // retranslateUi

};

namespace Ui {
    class MenuTrace: public Ui_MenuTrace {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENUTRACE_H
