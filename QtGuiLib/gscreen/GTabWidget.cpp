#include "GTabWidget.h"

GTabBar::GTabBar(QWidget* parent)
   : QTabBar(parent)
{
   //this->addTab(QString());

   //QLabel* lbl;
   //lbl = new QLabel();
   ////lbl->setPixmap(QPixmap(QString::fromUtf8("../../popup/5.png")));
   //lbl->setAlignment(Qt::AlignCenter);

   //QString textNew(QString(
   //   "<font color = 'red'>"
   //   "gfhdgfshdgfhdgf"
   //   "</font>"
   //));
   ////lbl->setText("gfhdgfshdgfhdgf");
   //lbl->setText(textNew);

   //// can set a larger size below too, but the icon is always center aligned
   ////lbl->setFixedSize(16, 16);
   //this->setTabButton(0, QTabBar::LeftSide, lbl);
}

void GTabBar::setTabText(int index, const QString &text, const gsa::t::ThemeFont &font_, const QColor &cfont_, const QColor &cground_)
{
   //QLabel* label = (QLabel*)this->tabButton(index, QTabBar::LeftSide);
   //if (label != nullptr) {
   //   delete label;
   //}

   this->setStyleSheet(QString("%1 "
      "QWidget { " //"QComboBox { " 
      "font-family: %2; "
      "font-size: %3pt; " //"font-size: %3px; " 
      "font-weight: %4; "
      "color: rgb(%5, %6, %7); "
      //"background-color: rgb(%8, %9, %10); "
      "} "
      "QTabBar::tab:selected{ "
      "background: rgb(%8, %9, %10); "
      "color: black; "
      "} "
   ).arg(this->styleSheet()).arg(QString::fromWCharArray(font_.family)).arg(font_.size).arg(QString::fromWCharArray(font_.style)).
      arg(cfont_.red()).arg(cfont_.green()).arg(cfont_.blue()).arg(cground_.red()).arg(cground_.green()).arg(cground_.blue())
   );

   QLabel* label = new QLabel(this);
   //scroll->setStyleSheet("background-color:transparent;");
   label->setStyleSheet(QLatin1String(
      "QLabel {\n"
      //"background-color: rgb(129,129,129); \n"
      "background-color: transparent; \n"
      "color: white; \n"
      "}\n"
      "\n"));

   QRegExp rx("[/]");
   QStringList valueParams = text.split(rx, QString::SkipEmptyParts);
   if (valueParams.size() > 1)
   {
      //QString textNew(QString(
      //   "<font size='8' color='red'>"
      //   "%1<br>%2"
      //   "</font>"
      //).arg(valueParams[0]).arg(valueParams[1]) );

      QString textNew(QString(
         //"<font size='3' color='white'>%1</font><br>"
         //"<font size='2' color='white'>%2</font>"
         //"<font size='2'>%1</font><br>"
         //"<font size='1'>%2</font>"
         "<!DOCTYPE html>"
         "<html>"
         "<body>"
         "<p1 style=\"font-size:%1px\">%2</p1><br>"
         "<p1 style=\"font-size:%3px\">%4</p1>"
         "</body>"
         "</html>"
      ).arg(font_.size).arg(valueParams[0]).arg((int)(0.80*font_.size)).arg(valueParams[1]));

      label->setText(textNew);
   }
   else {
      QString textNew(QString(
         "<font color='white' size='3'>"
         "%1"
         "</font>"
      ).arg(text));
      label->setText(textNew);
   }
   //label->setText(text);

   this->setTabButton(index, QTabBar::LeftSide, label);
}

//void GTabBar::setMyText(int index, const QString &text)
//{
//   QLabel* lbl = new QLabel(this);
//
//   QString textNew(QString(
//      "<font color = 'red'>"
//      "%1"
//      "</font>"
//   ).arg(text));
//   lbl->setText(textNew);
//
//   QLabel* label = (QLabel*)this->tabButton(index, QTabBar::LeftSide);
//   if (label != nullptr) {
//      delete label;
//   }
//
//   this->setTabButton(index, QTabBar::LeftSide, lbl);
//}

GTabWidget::GTabWidget(QWidget *parent)
    : QTabWidget(parent)
{
    ui.setupUi(this);

    //GTabBar* gTabBar;
    _gTabBar = new GTabBar(this);
    this->setTabBar(_gTabBar);
    //this->setTabBar(new GTabBar(this));
}

GTabWidget::~GTabWidget()
{
}

void GTabWidget::setTabTextNew(int index, const QString &text, const gsa::t::ThemeFont &font_, const QColor &cfont_, const QColor &cground_, const QColor &ctab_)
{
   ((QWidget*)this->parent())->setStyleSheet(QString("%1 "
      "QFrame{ "
      //"background-color: rgb(%1,%2,%3); "
      "background-color: rgb(%2,%3,%4); "
      "} "
   //).arg(((QWidget*)this->parent())->styleSheet()).arg(cground_.red()).arg(cground_.green()).arg(cground_.blue())
   ).arg(((QWidget*)this->parent())->styleSheet()).arg(cground_.red()).arg(cground_.green()).arg(cground_.blue())
   );

   //_gTabBar->setMyText(index, text);
   //_gTabBar->setTabText(index, text, font_, cfont_, cground_);
   _gTabBar->setTabText(index, text, font_, cfont_, ctab_);
   setTabText(index, "");
   index = index;
}

//void GTabWidget::setMyText(int index, const QString &text)
//{
//}

