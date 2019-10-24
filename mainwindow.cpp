   void MainWindow::putTheme(gsa::t::Theme *_theme)
   {
      typedef struct {
         gsa::t::ThemeItem background;
         gsa::t::ThemeItem border;
         gsa::t::ThemeItem size;
      } tagItem;

      std::map<QWidget*, gsa::t::ThemeFont> widgetFonts_;
      std::map<QWidget*, tagItem> widgetItems_;
      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeItem item_(themeItem); //__van__ 2019.08.08 

      if (_theme != nullptr) 
      {
         //gsa::t::ThemeFont *begin = _theme->themeFonts;
         //gsa::t::ThemeFont *end = begin + N;
         QString description("Default");
         gsa::t::ThemeFont *themeFont(std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts),
            [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; }) );
         gsa::t::ThemeItem *themeItem(std::find_if(std::begin(_theme->themeItems), std::end(_theme->themeItems),
            [&description](const gsa::t::ThemeItem& item) { return QString::fromWCharArray(item.description) == description; }));

         //if (std::end(_theme->themeFonts) != std::find_if(std::begin(_theme->themeFonts), std::end(_theme->themeFonts), 
         //   [&description](const gsa::t::ThemeFont& font) { return QString::fromWCharArray(font.description) == description; } ))
         if (themeFont == std::end(_theme->themeFonts)) font_.description = nullptr;
         else font_ = *themeFont;
         if (themeItem == std::end(_theme->themeItems)) item_.description = nullptr;
         else item_ = *themeItem;

         //list<S>::iterator it = find_if(l.begin(), l.end(), [](const S& s) { return s.S1 == 0; });
         //gsa::t::ThemeFont* it = find_if(l.begin(), l.end(), [](const S& s) { return s.S1 == 0; });

         //if (_fontindexes.find(L"Default") == _fontindexes.end()) {
         //   font_.description = nullptr;
         //}
         //else {
         //   font_ = _theme->themeFonts[(int)_fontindexes[L"Default"]];
         //}

         widgetFonts_[ui->comboBox] = font_;
         widgetItems_[ui->comboBox].background = item_;
         widgetItems_[ui->comboBox].size = item_;

         for (auto &font: _theme->themeFonts) {
            if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
               switch (_fontindexes[std::wstring(font.description)])
               {
               case gsa::t::FontIndex::CurrentMeasurement: //Current measurement selection area 
               case gsa::t::FontIndex::MeasurementScale: //Measurement scale 
               case gsa::t::FontIndex::PanelHeader: //Panel header 
               case gsa::t::FontIndex::QuickAccess: //Quick Access Area Tab 
                  break;
               case gsa::t::FontIndex::DropDownMenu: //Drop - down menu items(list of songs) 
               {
                  widgetFonts_[ui->comboBox] = font;
                  break;
               }
               case gsa::t::FontIndex::SelectedMenu: //Tabs of the selected menu(name of the subcomposition) 
               case gsa::t::FontIndex::ControlsSelectedTab: //Controls located in the selected tab 
               case gsa::t::FontIndex::ActiveMarker: //Displaying the active marker in the graphics area 
               case gsa::t::FontIndex::InactiveMarker: //Displaying inactive marker in the graphics area 
               case gsa::t::FontIndex::ActiveMarkerTable: //Displaying the active marker in the marker table 
               case gsa::t::FontIndex::Default: //Default 
               default:
                  break;
               }
            }
         } 

         //if (_colorindexes.size() > 18) {
         //   int  iiiii = 90;
         //}
         for (auto &item : _theme->themeItems) {
            switch (item.type)
            {
            case 0:
            {
               if (_colorindexes.find(std::wstring(item.description)) != _colorindexes.end()) {
                  switch (_colorindexes[std::wstring(item.description)])
                  {
                  case gsa::t::ColorIndex::DisplayArea:
                  case gsa::t::ColorIndex::GraphicPanelScale: //Graphic panel scale
                  case gsa::t::ColorIndex::TableBorders: //Borders of the table display
                  case gsa::t::ColorIndex::CurrentMeasurement: //Current measurement selection area
                  case gsa::t::ColorIndex::TabSelectionArea: //Tab in the general dimension selection area
                  case gsa::t::ColorIndex::QuickAccess: //Tabs in the quick access area
                     break;
                  case gsa::t::ColorIndex::DropDownMenu: //Drop down menu
                  {
                     widgetItems_[ui->comboBox].background = item;
                     break;
                  }
                  case gsa::t::ColorIndex::UnifyingFrame: //Unifying frame in the menu area
                  case gsa::t::ColorIndex::UnifyingFrameBorder: //Border of the unifying frame in the menu area
                  case gsa::t::ColorIndex::ControlDropDownMenu: //Control drop - down list in the menu area
                  case gsa::t::ColorIndex::ControlDropDownPanel: //Control drop - down list in the panel(additional data area)
                  case gsa::t::ColorIndex::PanelControl: //Control in the panel(additional data area)
                  case gsa::t::ColorIndex::SelectedLine: //Selected line in the expanded control drop - down list
                  case gsa::t::ColorIndex::UnselectedString: //Unselected string in expanded control drop - down list
                  case gsa::t::ColorIndex::ElementsBorders: //Borders of the elements of the drop-down menu
                  {
                     widgetItems_[ui->comboBox].border = item;
                     break;
                  }
                  case gsa::t::ColorIndex::CompositionMenu: //Menu area(composition)
                  case gsa::t::ColorIndex::ControlMenu: //Control in the menu area(composition)
                  case gsa::t::ColorIndex::Default: //Default
                  default:
                     break;
                  }
               }
               break;
            }
            case 1:
            {
               if (_sizeindexes.find(std::wstring(item.description)) != _sizeindexes.end()) {
                  switch (_sizeindexes[std::wstring(item.description)])
                  {
                  case gsa::t::SizeIndex::MenuItem: //Menu item in the drop-down menu 
                     widgetItems_[ui->comboBox].size = item;
                     break;
                  }
               }
               break;
            }
            case 2:
            {
               break;
            }
            default:
            {
               break;
            }
            }
         }

         if (widgetFonts_[ui->comboBox].description != nullptr)
         { 
            gsa::t::ThemeFont font(widgetFonts_[ui->comboBox]); 

            int r, g, b; 
            GetRgb(font.color, r, g, b); 

            ui->comboBox->setStyleSheet(QString("%1 " 
               "QWidget { " //"QComboBox { " 
               "font-family: %2; " 
               "font-size: %3pt; " //"font-size: %3px; " 
               "font-weight: %4; " 
               "color: rgb(%5, %6, %7); " 
               "}" 
               //"QListView::item{height: 200px}" 
            ).arg(ui->comboBox->styleSheet()).arg(QString::fromWCharArray(font.family)).arg(font.size).arg(QString::fromWCharArray(font.style)).arg(r).arg(g).arg(b) 
            ); 
         } 

         if (widgetItems_[ui->comboBox].background.description != nullptr) 
         { 
            gsa::t::ThemeItem background(widgetItems_[ui->comboBox].background);

            int r, g, b; 
            GetRgb(background.value, r, g, b);

            ui->comboBox->setStyleSheet(QString("%1 " 
               "QWidget { " //"QComboBox { " 
               "background-color: rgb(%2, %3, %4); " 
               "}" 
            ).arg(ui->comboBox->styleSheet()).arg(r).arg(g).arg(b) 
            ); 
         }
         if (widgetItems_[ui->comboBox].size.description != nullptr) 
         { 
            gsa::t::ThemeItem size(widgetItems_[ui->comboBox].size); 
            gsa::t::ThemeItem border(widgetItems_[ui->comboBox].border);

            double value; 
            GetValue(size.value, value); 

            int r, g, b;
            GetRgb(border.value, r, g, b);

            QListView *view = new QListView(ui->comboBox);
            view->setStyleSheet(QString("%1 " 
               "QListView::item { " 
               "height: %2px; " 
               //"border: 5px solid green; "
               "border: 2px solid rgb(%3, %4, %5); "
               "} "
            ).arg(view->styleSheet()).arg( (int)value).arg(r).arg(g).arg(b) 
            ); 
            ui->comboBox->setView(view); 

            //QComboBox QAbstractItemView::item{ 
            //margin - top: 2px; 
            //} 
         } 
      } 
   } 



   void MainWindow::slotSetMarker(int index, QString text, QColor color)
   {
      gsa::t::Theme *_theme(g_Parameter._theme);

      gsa::t::ThemeFont font_(themeFont); //__van__ 2019.08.08 
      gsa::t::ThemeFont fontInactive_(themeFont); //__van__ 2019.08.08 

      for (auto &font : _theme->themeFonts) {
         if (_fontindexes.find(std::wstring(font.description)) != _fontindexes.end()) {
            switch (_fontindexes[std::wstring(font.description)])
            {
            case gsa::t::FontIndex::ActiveMarkerTable: //Tabs of the selected menu(name of the subcomposition)
            {
               font_ = font;
               break;
            }
            case gsa::t::FontIndex::InactiveMarkerTable: //Tabs of the selected menu(name of the subcomposition)
            {
               fontInactive_ = font;
               break;
            }
            default:
               break;
            }
         }
      }

      int r, g, b;
      GetRgb(font_.color, r, g, b);
      QColor cfont_(r, g, b);

      int weight;
      if (QString::fromWCharArray(font_.style) == QString("normal")) weight = QFont::Normal;
      else if (QString::fromWCharArray(font_.style) == QString("bold")) weight = QFont::Bold;
      QFont qfont_(QString::fromWCharArray(font_.family), font_.size, weight);

      QFontMetrics fm(qfont_);
      
      QRect rect = fm.boundingRect(QString("012345678901234"));

#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
      uint32_t fontWidth = static_cast<int>(fm.horizontalAdvance(QString("012345678901234")));
#else
      uint32_t fontWidth = static_cast<int>(fm.width(QString("012345678901234567890123456789"))); //__van__
#endif
      uint32_t fontHeight = fm.height();
      uint32_t xHeight = fm.xHeight();

      int maxindex(0);
      bool _show(false);
      if (text.length() == 0)
         _visibles[index] = 0;
      else
         _visibles[index] = 1;

      int i(0);
      for (auto p : _visibles) {
         if (p.second == 1) {
            _show = true;
            maxindex = i; // index;
            //break; 
         }
         else {
            _labels[i]->setText(QString(""));
         }
         ++i;
      }

      if (index == 3) {
         int jjj(0);
      }
      if (_show == false) {
         ui->frame3Bottom1->setMinimumHeight(0);
         ui->frame3Bottom1->setMaximumHeight(0);
      }
      else {
         if (_visibles[index] == 1)
         {
            _labelHeight = fontHeight;
            _labelHeight = font_.size;

            int height = (maxindex / 3 + 1) * _labelHeight * 2.1;
            if (height != 78) {
               int jjj(0);
            }

            int left, top, right, bottom;
            ui->gridLayout->getContentsMargins(&left, &top, &right, &bottom);

            ui->frame3Bottom1->setMinimumHeight(height);
            ui->frame3Bottom1->setMaximumHeight(height);

            QString textNew(QString(
               "<!DOCTYPE html>"
               "<html>"
               "<body>"
               "<p1 style=\"font-size:%1px\">%2</p1>"
               "</body>"
               "</html>"
            ).arg(font_.size).arg(text));
            _labels[index]->setText(textNew);

            _labels[index]->setStyleSheet(QString(" "
               "QLabel { "
               "color : rgb(%1, %2, %3); "
               "} "
            ).arg(cfont_.red()).arg(cfont_.green()).arg(cfont_.blue())
            );
         }
      }
   }

