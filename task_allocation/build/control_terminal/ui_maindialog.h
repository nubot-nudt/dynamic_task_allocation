/********************************************************************************
** Form generated from reading UI file 'maindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINDIALOG_H
#define UI_MAINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainDialog
{
public:
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QGridLayout *gridLayout;
    QLabel *width;
    QLabel *height;
    QLabel *room_num;
    QSpinBox *height_in;
    QSpinBox *width_in;
    QSpinBox *room_in;
    QPushButton *init_map;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QSpinBox *power_10;
    QPushButton *agent_10;
    QSpinBox *power_9;
    QPushButton *agent_9;
    QSpinBox *power_8;
    QPushButton *agent_8;
    QSpinBox *power_7;
    QPushButton *agent_7;
    QSpinBox *power_6;
    QPushButton *agent_6;
    QSpinBox *power_5;
    QPushButton *agent_5;
    QSpinBox *power_4;
    QPushButton *agent_4;
    QSpinBox *power_3;
    QPushButton *agent_3;
    QSpinBox *power_2;
    QPushButton *agent_2;
    QSpinBox *power_1;
    QPushButton *agent_1;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *start_pause;
    QPushButton *step;
    QPushButton *stop;
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *steps_label;
    QLineEdit *steps_show;
    QLabel *time_label;
    QLineEdit *time_show;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *region_label;
    QLineEdit *region_show;
    QLabel *target_label;
    QLineEdit *target_show;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QRadioButton *probability;
    QRadioButton *greed;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *record;
    QRadioButton *not_record;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *distance;
    QRadioButton *power;
    QWidget *horizontalLayoutWidget_5;
    QHBoxLayout *horizontalLayout_5;
    QRadioButton *prediction;
    QRadioButton *market_base;
    QCheckBox *show_agent;
    QCheckBox *constant_start;
    QLabel *logo;
    QLabel *title;

    void setupUi(QDialog *MainDialog)
    {
        if (MainDialog->objectName().isEmpty())
            MainDialog->setObjectName(QStringLiteral("MainDialog"));
        MainDialog->resize(370, 690);
        QIcon icon;
        icon.addFile(QStringLiteral(":/logo.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainDialog->setWindowIcon(icon);
        horizontalLayoutWidget = new QWidget(MainDialog);
        horizontalLayoutWidget->setObjectName(QStringLiteral("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(20, 90, 331, 103));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        width = new QLabel(horizontalLayoutWidget);
        width->setObjectName(QStringLiteral("width"));

        gridLayout->addWidget(width, 1, 0, 1, 1);

        height = new QLabel(horizontalLayoutWidget);
        height->setObjectName(QStringLiteral("height"));

        gridLayout->addWidget(height, 0, 0, 1, 1);

        room_num = new QLabel(horizontalLayoutWidget);
        room_num->setObjectName(QStringLiteral("room_num"));

        gridLayout->addWidget(room_num, 2, 0, 1, 1);

        height_in = new QSpinBox(horizontalLayoutWidget);
        height_in->setObjectName(QStringLiteral("height_in"));
        height_in->setMinimum(8);
        height_in->setMaximum(20);

        gridLayout->addWidget(height_in, 0, 1, 1, 1);

        width_in = new QSpinBox(horizontalLayoutWidget);
        width_in->setObjectName(QStringLiteral("width_in"));
        width_in->setMinimum(8);
        width_in->setMaximum(20);
        width_in->setValue(8);

        gridLayout->addWidget(width_in, 1, 1, 1, 1);

        room_in = new QSpinBox(horizontalLayoutWidget);
        room_in->setObjectName(QStringLiteral("room_in"));
        room_in->setMinimum(15);
        room_in->setMaximum(200);
        room_in->setValue(20);

        gridLayout->addWidget(room_in, 2, 1, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        init_map = new QPushButton(horizontalLayoutWidget);
        init_map->setObjectName(QStringLiteral("init_map"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(init_map->sizePolicy().hasHeightForWidth());
        init_map->setSizePolicy(sizePolicy);
        init_map->setFocusPolicy(Qt::StrongFocus);

        horizontalLayout->addWidget(init_map);

        gridLayoutWidget_2 = new QWidget(MainDialog);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(20, 210, 331, 181));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        power_10 = new QSpinBox(gridLayoutWidget_2);
        power_10->setObjectName(QStringLiteral("power_10"));
        power_10->setMinimum(1);
        power_10->setMaximum(10);
        power_10->setValue(10);

        gridLayout_2->addWidget(power_10, 3, 4, 1, 1);

        agent_10 = new QPushButton(gridLayoutWidget_2);
        agent_10->setObjectName(QStringLiteral("agent_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(agent_10->sizePolicy().hasHeightForWidth());
        agent_10->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_10, 2, 4, 1, 1);

        power_9 = new QSpinBox(gridLayoutWidget_2);
        power_9->setObjectName(QStringLiteral("power_9"));
        power_9->setMinimum(1);
        power_9->setMaximum(10);
        power_9->setValue(10);

        gridLayout_2->addWidget(power_9, 3, 3, 1, 1);

        agent_9 = new QPushButton(gridLayoutWidget_2);
        agent_9->setObjectName(QStringLiteral("agent_9"));
        sizePolicy1.setHeightForWidth(agent_9->sizePolicy().hasHeightForWidth());
        agent_9->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_9, 2, 3, 1, 1);

        power_8 = new QSpinBox(gridLayoutWidget_2);
        power_8->setObjectName(QStringLiteral("power_8"));
        power_8->setMinimum(1);
        power_8->setMaximum(10);
        power_8->setValue(10);

        gridLayout_2->addWidget(power_8, 3, 2, 1, 1);

        agent_8 = new QPushButton(gridLayoutWidget_2);
        agent_8->setObjectName(QStringLiteral("agent_8"));
        sizePolicy1.setHeightForWidth(agent_8->sizePolicy().hasHeightForWidth());
        agent_8->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_8, 2, 2, 1, 1);

        power_7 = new QSpinBox(gridLayoutWidget_2);
        power_7->setObjectName(QStringLiteral("power_7"));
        power_7->setMinimum(1);
        power_7->setMaximum(10);
        power_7->setValue(10);

        gridLayout_2->addWidget(power_7, 3, 1, 1, 1);

        agent_7 = new QPushButton(gridLayoutWidget_2);
        agent_7->setObjectName(QStringLiteral("agent_7"));
        sizePolicy1.setHeightForWidth(agent_7->sizePolicy().hasHeightForWidth());
        agent_7->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_7, 2, 1, 1, 1);

        power_6 = new QSpinBox(gridLayoutWidget_2);
        power_6->setObjectName(QStringLiteral("power_6"));
        power_6->setMinimum(1);
        power_6->setMaximum(10);
        power_6->setValue(10);

        gridLayout_2->addWidget(power_6, 3, 0, 1, 1);

        agent_6 = new QPushButton(gridLayoutWidget_2);
        agent_6->setObjectName(QStringLiteral("agent_6"));
        sizePolicy1.setHeightForWidth(agent_6->sizePolicy().hasHeightForWidth());
        agent_6->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_6, 2, 0, 1, 1);

        power_5 = new QSpinBox(gridLayoutWidget_2);
        power_5->setObjectName(QStringLiteral("power_5"));
        power_5->setMinimum(1);
        power_5->setMaximum(10);
        power_5->setValue(10);

        gridLayout_2->addWidget(power_5, 1, 4, 1, 1);

        agent_5 = new QPushButton(gridLayoutWidget_2);
        agent_5->setObjectName(QStringLiteral("agent_5"));
        sizePolicy1.setHeightForWidth(agent_5->sizePolicy().hasHeightForWidth());
        agent_5->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_5, 0, 4, 1, 1);

        power_4 = new QSpinBox(gridLayoutWidget_2);
        power_4->setObjectName(QStringLiteral("power_4"));
        power_4->setMinimum(1);
        power_4->setMaximum(10);
        power_4->setValue(8);

        gridLayout_2->addWidget(power_4, 1, 3, 1, 1);

        agent_4 = new QPushButton(gridLayoutWidget_2);
        agent_4->setObjectName(QStringLiteral("agent_4"));
        sizePolicy1.setHeightForWidth(agent_4->sizePolicy().hasHeightForWidth());
        agent_4->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_4, 0, 3, 1, 1);

        power_3 = new QSpinBox(gridLayoutWidget_2);
        power_3->setObjectName(QStringLiteral("power_3"));
        power_3->setMinimum(1);
        power_3->setMaximum(10);
        power_3->setValue(6);

        gridLayout_2->addWidget(power_3, 1, 2, 1, 1);

        agent_3 = new QPushButton(gridLayoutWidget_2);
        agent_3->setObjectName(QStringLiteral("agent_3"));
        sizePolicy1.setHeightForWidth(agent_3->sizePolicy().hasHeightForWidth());
        agent_3->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_3, 0, 2, 1, 1);

        power_2 = new QSpinBox(gridLayoutWidget_2);
        power_2->setObjectName(QStringLiteral("power_2"));
        power_2->setMinimum(1);
        power_2->setMaximum(10);
        power_2->setValue(4);

        gridLayout_2->addWidget(power_2, 1, 1, 1, 1);

        agent_2 = new QPushButton(gridLayoutWidget_2);
        agent_2->setObjectName(QStringLiteral("agent_2"));
        sizePolicy1.setHeightForWidth(agent_2->sizePolicy().hasHeightForWidth());
        agent_2->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_2, 0, 1, 1, 1);

        power_1 = new QSpinBox(gridLayoutWidget_2);
        power_1->setObjectName(QStringLiteral("power_1"));
        power_1->setMinimum(1);
        power_1->setMaximum(10);
        power_1->setValue(2);

        gridLayout_2->addWidget(power_1, 1, 0, 1, 1);

        agent_1 = new QPushButton(gridLayoutWidget_2);
        agent_1->setObjectName(QStringLiteral("agent_1"));
        sizePolicy1.setHeightForWidth(agent_1->sizePolicy().hasHeightForWidth());
        agent_1->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(agent_1, 0, 0, 1, 1);

        horizontalLayoutWidget_2 = new QWidget(MainDialog);
        horizontalLayoutWidget_2->setObjectName(QStringLiteral("horizontalLayoutWidget_2"));
        horizontalLayoutWidget_2->setGeometry(QRect(20, 430, 331, 51));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        start_pause = new QPushButton(horizontalLayoutWidget_2);
        start_pause->setObjectName(QStringLiteral("start_pause"));
        sizePolicy1.setHeightForWidth(start_pause->sizePolicy().hasHeightForWidth());
        start_pause->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(start_pause);

        step = new QPushButton(horizontalLayoutWidget_2);
        step->setObjectName(QStringLiteral("step"));
        sizePolicy1.setHeightForWidth(step->sizePolicy().hasHeightForWidth());
        step->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(step);

        stop = new QPushButton(horizontalLayoutWidget_2);
        stop->setObjectName(QStringLiteral("stop"));
        sizePolicy1.setHeightForWidth(stop->sizePolicy().hasHeightForWidth());
        stop->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(stop);

        horizontalLayoutWidget_3 = new QWidget(MainDialog);
        horizontalLayoutWidget_3->setObjectName(QStringLiteral("horizontalLayoutWidget_3"));
        horizontalLayoutWidget_3->setGeometry(QRect(20, 500, 331, 31));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        steps_label = new QLabel(horizontalLayoutWidget_3);
        steps_label->setObjectName(QStringLiteral("steps_label"));

        horizontalLayout_3->addWidget(steps_label);

        steps_show = new QLineEdit(horizontalLayoutWidget_3);
        steps_show->setObjectName(QStringLiteral("steps_show"));
        steps_show->setReadOnly(true);

        horizontalLayout_3->addWidget(steps_show);

        time_label = new QLabel(horizontalLayoutWidget_3);
        time_label->setObjectName(QStringLiteral("time_label"));

        horizontalLayout_3->addWidget(time_label);

        time_show = new QLineEdit(horizontalLayoutWidget_3);
        time_show->setObjectName(QStringLiteral("time_show"));
        time_show->setReadOnly(true);

        horizontalLayout_3->addWidget(time_show);

        horizontalLayoutWidget_4 = new QWidget(MainDialog);
        horizontalLayoutWidget_4->setObjectName(QStringLiteral("horizontalLayoutWidget_4"));
        horizontalLayoutWidget_4->setGeometry(QRect(20, 540, 331, 31));
        horizontalLayout_4 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        region_label = new QLabel(horizontalLayoutWidget_4);
        region_label->setObjectName(QStringLiteral("region_label"));

        horizontalLayout_4->addWidget(region_label);

        region_show = new QLineEdit(horizontalLayoutWidget_4);
        region_show->setObjectName(QStringLiteral("region_show"));
        region_show->setReadOnly(true);

        horizontalLayout_4->addWidget(region_show);

        target_label = new QLabel(horizontalLayoutWidget_4);
        target_label->setObjectName(QStringLiteral("target_label"));

        horizontalLayout_4->addWidget(target_label);

        target_show = new QLineEdit(horizontalLayoutWidget_4);
        target_show->setObjectName(QStringLiteral("target_show"));
        target_show->setReadOnly(true);

        horizontalLayout_4->addWidget(target_show);

        verticalLayoutWidget = new QWidget(MainDialog);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(20, 620, 103, 54));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        probability = new QRadioButton(verticalLayoutWidget);
        probability->setObjectName(QStringLiteral("probability"));
        probability->setChecked(true);

        verticalLayout->addWidget(probability);

        greed = new QRadioButton(verticalLayoutWidget);
        greed->setObjectName(QStringLiteral("greed"));

        verticalLayout->addWidget(greed);

        verticalLayoutWidget_2 = new QWidget(MainDialog);
        verticalLayoutWidget_2->setObjectName(QStringLiteral("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(140, 620, 115, 54));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        record = new QRadioButton(verticalLayoutWidget_2);
        record->setObjectName(QStringLiteral("record"));
        record->setChecked(true);

        verticalLayout_2->addWidget(record);

        not_record = new QRadioButton(verticalLayoutWidget_2);
        not_record->setObjectName(QStringLiteral("not_record"));

        verticalLayout_2->addWidget(not_record);

        verticalLayoutWidget_3 = new QWidget(MainDialog);
        verticalLayoutWidget_3->setObjectName(QStringLiteral("verticalLayoutWidget_3"));
        verticalLayoutWidget_3->setGeometry(QRect(270, 620, 86, 54));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        distance = new QRadioButton(verticalLayoutWidget_3);
        distance->setObjectName(QStringLiteral("distance"));
        distance->setChecked(true);

        verticalLayout_3->addWidget(distance);

        power = new QRadioButton(verticalLayoutWidget_3);
        power->setObjectName(QStringLiteral("power"));

        verticalLayout_3->addWidget(power);

        horizontalLayoutWidget_5 = new QWidget(MainDialog);
        horizontalLayoutWidget_5->setObjectName(QStringLiteral("horizontalLayoutWidget_5"));
        horizontalLayoutWidget_5->setGeometry(QRect(20, 580, 331, 31));
        horizontalLayout_5 = new QHBoxLayout(horizontalLayoutWidget_5);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        prediction = new QRadioButton(horizontalLayoutWidget_5);
        prediction->setObjectName(QStringLiteral("prediction"));
        prediction->setChecked(true);

        horizontalLayout_5->addWidget(prediction);

        market_base = new QRadioButton(horizontalLayoutWidget_5);
        market_base->setObjectName(QStringLiteral("market_base"));
        market_base->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_5->addWidget(market_base);

        show_agent = new QCheckBox(MainDialog);
        show_agent->setObjectName(QStringLiteral("show_agent"));
        show_agent->setGeometry(QRect(21, 390, 111, 41));
        show_agent->setChecked(true);
        constant_start = new QCheckBox(MainDialog);
        constant_start->setObjectName(QStringLiteral("constant_start"));
        constant_start->setGeometry(QRect(230, 400, 121, 23));
        constant_start->setChecked(true);
        logo = new QLabel(MainDialog);
        logo->setObjectName(QStringLiteral("logo"));
        logo->setGeometry(QRect(45, 15, 60, 60));
        logo->setPixmap(QPixmap(QString::fromUtf8(":/logo.png")));
        logo->setScaledContents(true);
        title = new QLabel(MainDialog);
        title->setObjectName(QStringLiteral("title"));
        title->setGeometry(QRect(130, 15, 201, 61));
        QFont font;
        font.setPointSize(20);
        font.setBold(true);
        font.setWeight(75);
        title->setFont(font);

        retranslateUi(MainDialog);

        QMetaObject::connectSlotsByName(MainDialog);
    } // setupUi

    void retranslateUi(QDialog *MainDialog)
    {
        MainDialog->setWindowTitle(QApplication::translate("MainDialog", "Task Allocation", 0));
        width->setText(QApplication::translate("MainDialog", "Width", 0));
        height->setText(QApplication::translate("MainDialog", "Height", 0));
        room_num->setText(QApplication::translate("MainDialog", "Region", 0));
        init_map->setText(QApplication::translate("MainDialog", "INIT_MAP", 0));
        agent_10->setText(QApplication::translate("MainDialog", "AgentX", 0));
        agent_9->setText(QApplication::translate("MainDialog", "Agent9", 0));
        agent_8->setText(QApplication::translate("MainDialog", "Agent8", 0));
        agent_7->setText(QApplication::translate("MainDialog", "Agent7", 0));
        agent_6->setText(QApplication::translate("MainDialog", "Agent6", 0));
        agent_5->setText(QApplication::translate("MainDialog", "Agent5", 0));
        agent_4->setText(QApplication::translate("MainDialog", "Agent4", 0));
        agent_3->setText(QApplication::translate("MainDialog", "Agent3", 0));
        agent_2->setText(QApplication::translate("MainDialog", "Agent2", 0));
        agent_1->setText(QApplication::translate("MainDialog", "Agent1", 0));
        start_pause->setText(QApplication::translate("MainDialog", "START", 0));
        step->setText(QApplication::translate("MainDialog", "STEP", 0));
        stop->setText(QApplication::translate("MainDialog", "STOP", 0));
        steps_label->setText(QApplication::translate("MainDialog", "Steps", 0));
        time_label->setText(QApplication::translate("MainDialog", "Time", 0));
        region_label->setText(QApplication::translate("MainDialog", "Region", 0));
        target_label->setText(QApplication::translate("MainDialog", "Target", 0));
        probability->setText(QApplication::translate("MainDialog", "Probability", 0));
        greed->setText(QApplication::translate("MainDialog", "Greed", 0));
        record->setText(QApplication::translate("MainDialog", "Record_drop", 0));
        not_record->setText(QApplication::translate("MainDialog", "Not record", 0));
        distance->setText(QApplication::translate("MainDialog", "Distance", 0));
        power->setText(QApplication::translate("MainDialog", "Power", 0));
        prediction->setText(QApplication::translate("MainDialog", "Prediction", 0));
        market_base->setText(QApplication::translate("MainDialog", "Market_base", 0));
        show_agent->setText(QApplication::translate("MainDialog", "Show_agent", 0));
        constant_start->setText(QApplication::translate("MainDialog", "Constant_start", 0));
        logo->setText(QString());
        title->setText(QApplication::translate("MainDialog", "Task Allocation", 0));
    } // retranslateUi

};

namespace Ui {
    class MainDialog: public Ui_MainDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINDIALOG_H
