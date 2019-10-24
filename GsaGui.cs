using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading;
using System.Reflection;
using System.ComponentModel.DataAnnotations;

using PhaseB.AbstractionLayer;

namespace PhaseB.GuiLib
{
    public enum ItemType
    {
        color, 
        size,
        indent
    };
    [StructLayout(LayoutKind.Sequential)]
    public struct ThemeFont
    {
        public int type;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string description;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string family;
        public int size;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string style;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string color;

    }
    [StructLayout(LayoutKind.Sequential)]
    public struct ThemeItem
    {
        public int type;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string description;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string value;
    }
    [StructLayout(LayoutKind.Sequential)]
    public class Theme
    {
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.LPStruct, SizeConst = 16)]
        public ThemeFont[] themeFonts;
        [MarshalAs(UnmanagedType.ByValArray, ArraySubType = UnmanagedType.LPStruct, SizeConst = 64)]
        public ThemeItem[] themeItems;
    }
    public struct GraphPanelStyle2
    {
        [MarshalAs(UnmanagedType.LPWStr)]
        public string XAxisName;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string YAxisName;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string XAxisUnit;
        [MarshalAs(UnmanagedType.LPWStr)]
        public string YAxisUnit;

        public int XScaling, YScaling;
        public ColourStruct AxisColour;
    }

    static class QtGuiLib
    {
        [DllImport("QtGuiLib.dll", EntryPoint = "run", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        //public static extern int pRun(char[] PathName, IntPtr _Fptr1, IntPtr _Fptr2);
        public static extern int pRun(string PathName, PhaseB.GuiLib.MBResult _Delegate1, PhaseB.GuiLib.SetValue _Delegate2, PhaseB.GuiLib.WheelRotate _Delegate3,
            PhaseB.GuiLib.CallActivator _Delegate4, PhaseB.GuiLib.MBExit _Delegate5, PhaseB.GuiLib.GSetFocus _Delegate6);

        [DllImport("QtGuiLib.dll", EntryPoint = "stop", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pStop();

        [DllImport("QtGuiLib.dll", EntryPoint = "putDevices", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutDevices(int uiType, int devType);

        [DllImport("QtGuiLib.dll", EntryPoint = "putCurrentIndexes", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutCurrentIndexes(long PreviousPosition, long CurrentPosition);

        [DllImport("QtGuiLib.dll", EntryPoint = "putDataLayer", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pDataLayer([In] double[] _XData, double[] _YData);

        [DllImport("QtGuiLib.dll", EntryPoint = "putModeMeasView", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutModeMeasView([In] GuiModeMeasView _modeMeasView);

        [DllImport("QtGuiLib.dll", EntryPoint = "putCurrentData", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        //public static extern int pPutCurrentData([In, MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(guilib.DataMarshaler))] GraphPanelData _Data);
        public static extern int pPutCurrentData([In] GraphPanelData _Data, int index, int length);

        [DllImport("QtGuiLib.dll", EntryPoint = "putTableData", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutTableData([In] TablePanelData _Table, int index, int length);

        [DllImport("QtGuiLib.dll", EntryPoint = "putTablePanel", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutTablePanel([In] Table _Table, int index);

        [DllImport("QtGuiLib.dll", EntryPoint = "putCarriage", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutCarriage([In] GraphPanelData _Data, int index);

        [DllImport("QtGuiLib.dll", EntryPoint = "changeData", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pChangetData(int item, double value, string unit);

        [DllImport("QtGuiLib.dll", EntryPoint = "uiPropertyChanged", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pUiPropertyChanged(int item, int type, int value);

        [DllImport("QtGuiLib.dll", EntryPoint = "putVSync", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pVSync(PhaseB.GuiLib.MBVoid _VSyncDelegate);

        [DllImport("QtGuiLib.dll", EntryPoint = "putResize", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pResize(PhaseB.GuiLib.VoidStringIntDelegate _ResizePixelsDelegate);

        [DllImport("QtGuiLib.dll", EntryPoint = "putRerangeX", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pRerangeX(PhaseB.GuiLib.VoidStringRangeDelegate _ResizeXDelegate);

        [DllImport("QtGuiLib.dll", EntryPoint = "putRerangeY", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pRerangeY(PhaseB.GuiLib.VoidStringRangeDelegate _ResizeYDelegate);

        [DllImport("QtGuiLib.dll", EntryPoint = "setXRange", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int setXRange(string _Panel, GraphPanelRange _Range);

        [DllImport("QtGuiLib.dll", EntryPoint = "setYRange", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int setYRange(string _Panel, GraphPanelRange _Range);

        [DllImport("QtGuiLib.dll", EntryPoint = "putCurrentMenu", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutCurrentMenu([In] GuiMenu _currentMenu);

        [DllImport("QtGuiLib.dll", EntryPoint = "putTheme", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int pPutTheme([In] Theme _theme);

        [DllImport("QtGuiLib.dll", EntryPoint = "setRestyle", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int setRestyle(int index, GraphPanelStyle2 _Style);

        [DllImport("QtGuiLib.dll", EntryPoint = "messageBox", CharSet = CharSet.Unicode, CallingConvention = CallingConvention.Cdecl)]
        public static extern int messageBox(string caption, string text);

    }

    public delegate int MBResult(int _InDigit);
    public delegate int SetValue(int itemIndex, double value, [MarshalAs(UnmanagedType.LPWStr)]string unit, int index);
    public delegate int GSetFocus(int itemIndex, int value);
    public delegate int WheelRotate(int itemIndex, int value);
    public delegate void CallActivator(int mode, int measurement, int view);
    public delegate void MBExit();
    public delegate void MBVoid();
    public delegate void VoidStringIntDelegate([MarshalAs(UnmanagedType.LPWStr)]string _Param1, int _Param2);    //public GuiMenu _guiMenu = new GuiMenu();
    public delegate void VoidStringRangeDelegate([MarshalAs(UnmanagedType.LPWStr)]string _Param1, GraphPanelRange _Param2);    //public GuiMenu _guiMenu = new GuiMenu();

    public class GsaGui
    {
        bool m_bExitFlag;
        Thread m_CallerThread;
        IMeasurement _meas;
        //public GuiMenu _guiMenu = new GuiMenu();
        GuiModeMeasView m_guiModeMeasView = new GuiModeMeasView();
        GuiMenu _guiMenu = new GuiMenu();
        GraphPanelStyle2 _graphPanelStyle2 = new GraphPanelStyle2();
        Theme _theme = new Theme();
        object m_StyleLocker = new object();
        List<IMeasurement> m_MeasurementsList;
        List<IMode> _modes;
        Table tableTemp = new Table(256, 2, 2, 4);
        private const int maxFont = 16;
        private const int maxItem = 64;

        private IHardwareProperty m_Period;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        double[] m_XBuffer;
        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 1024)]
        double[] m_YBuffer;

        [MarshalAs(UnmanagedType.ByValArray, SizeConst = 2048)]
        public static double[] values = new double[2048];

        private MBVoid m_VSyncDelegate;
        private VoidStringRangeDelegate m_ResizeXDelegate, m_ResizeYDelegate;
        private VoidStringIntDelegate m_ResizePixelXDelegate;

        private Action StopKerenel;
        private Action<IMeasurement, IView> Activator;

        private bool m_bGUIResize = false;

        private string guiTheme = $@"<?xml version = ""1.0"" encoding=""utf-8""?> 
        <theme url = ""https://www.nppgamma.ru/"">
            <font description=""Current measurement selection area"" family=""Courier"" size=""18"" style=""italic"" color=""ffffff"" /> 
            <font description=""Measurement scale"" family=""lucida"" size=""44"" style=""bold"" color=""00ff00"" /> 
            <font description=""Panel header"" family=""Times New Roman"" size=""44"" style=""bold"" color=""ff0000"" /> 
            <font description=""Quick Access Area Tab"" family=""Courier"" size=""10"" style="""" color=""ffffff"" /> 
            <font description=""Drop-down menu items (list of composition)"" family=""Trebuchet MS"" size=""28"" style=""italic"" color=""0b0dea"" /> 
            <font description=""Tabs of the selected menu (name of the subcomposition)"" family=""lucida"" size=""34"" style=""italic"" color=""019f9f"" /> 
            <font description=""Controls located in the selected tab"" family=""Courier"" size=""26"" style=""italic"" color=""0d0dfd"" /> 
            <font description=""Displaying the active marker in the graphics area"" family=""Courier"" size=""18"" style=""bold"" color=""0000ff"" /> 
            <font description=""Displaying inactive marker in the graphics area"" family=""Courier"" size=""18"" style=""italic"" color=""00ff00"" /> 
            <font description=""Displaying the active marker in the marker table"" family=""Courier"" size=""18"" style=""bold"" color=""0000ff"" /> 
            <font description=""Displaying the inactive marker in the marker table"" family=""Courier"" size=""18"" style=""bold"" color=""00ff00"" /> 
            <font description=""Control drop-down list in the panel (additional data area)"" family=""Courier"" size=""22"" style=""italic"" color=""00ff00"" /> 
            <font description=""Control located in the panel (additional data area)"" family=""Courier"" size=""22"" style=""italic"" color=""00ff00"" /> 
            <font description=""Default"" family=""Courier"" size=""28"" style=""bold"" color=""eaea00"" /> 

            <color description=""Display area background"" value=""0f3f3f"" /> 
            <color description=""Graphic panel scale"" value=""ff00ff"" /> 
            <color description=""Borders of the table display"" value=""ffff00"" /> 
            <color description=""Current measurement selection area"" value=""00ff00"" /> 
            <color description=""Tab in the general dimension selection area"" value=""9f0000"" /> 
            <color description=""Tabs in the quick access area"" value=""ffffff"" /> 
            <color description=""Drop down menu"" value=""0bea0d"" /> 
            <color description=""Unifying frame in the menu area"" value=""a0ffa0"" /> 
            <color description=""Border of the unifying frame in the menu area"" value=""0101ff"" /> 
            <color description=""Control drop-down list in the menu area (color)"" value=""0bea7d"" /> 
            <color description=""Control drop-down list in the panel (additional data area)"" value=""0000ff"" /> 
            <color description=""Control in the panel (additional data area)"" value=""0000ff"" /> 
            <color description=""Selected line in the expanded control drop-down list"" value=""ff00ff"" /> 
            <color description=""Unselected string in expanded control drop-down list"" value=""00ff00"" /> 
            <color description=""Borders of the elements of the drop-down menu"" value=""007f7f"" /> 
            <color description=""Menu area (composition)"" value=""0000ff"" /> 
            <color description=""Control in the menu area (composition)"" value=""ff0000"" /> 
            <color description=""Default"" value=""0f6f6f"" /> 

            <size description=""Menu item in the drop-down menu"" value=""70"" /> 
            <size description=""Control button in the menu area"" value=""36"" /> 
            <size description=""Control radio button in the menu area"" value=""36"" /> 
            <size description=""Control checkbox in the menu area"" value=""36"" /> 
            <size description=""Control drop-down list in the menu area (size)"" value=""36"" /> 
            <size description=""Control item is a switch in the menu area"" value=""36"" /> 
            <size description=""Control is a numeric value in the menu area"" value=""36"" /> 
            <size description=""Control located in the panel (additional data area)"" value=""36"" /> 

            <indent description=""Unifying frame of the menu area from the size of the control"" value=""9"" /> 
            <indent description=""The menu area, from the size of the unifying frame located in it"" value=""9"" /> 
            <indent description=""Borders of the table display from the text"" value=""9"" /> 
        </theme>";

        public void SetTheme(System.Xml.XmlDocument doc)
        {
            XmlElement rootItem = doc.DocumentElement;
            //int count = rootItem.Attributes.Count; 
            //string rootName = rootItem.Name; 
            //string Name = rootItem.Attributes[0].Name; 
            //string Value = rootItem.Attributes[0].Value; 

            if (_theme.themeFonts == null)
                _theme.themeFonts = new ThemeFont[maxFont];
            if (_theme.themeItems == null)
                _theme.themeItems = new ThemeItem[maxItem];
            for (int i = 0; i < maxFont; i++)
                _theme.themeFonts[i].type = -1;
            for (int i = 0; i < maxItem; i++)
                _theme.themeItems[i].type = -1;

            int indexFonts = 0;
            int indexItems = 0;
            foreach (XmlNode itemLevel1 in rootItem) 
            { 
                string Name1 = itemLevel1.Name; 
                string Name2 = itemLevel1.Attributes[0].Name; 
                string Value2 = itemLevel1.Attributes[0].Value; 
                string name = ""; 
                name = Value2;

                if (itemLevel1.Name == "font")
                {
                    _theme.themeFonts[indexFonts].description = itemLevel1.Attributes[0].Value;
                    _theme.themeFonts[indexFonts].family = itemLevel1.Attributes[1].Value;
                    _theme.themeFonts[indexFonts].size = Convert.ToInt32(itemLevel1.Attributes[2].Value);
                    _theme.themeFonts[indexFonts].style = itemLevel1.Attributes[3].Value;
                    _theme.themeFonts[indexFonts].color = itemLevel1.Attributes[4].Value;

                    if (indexFonts < 16 - 1) indexFonts++;
                    else { int error = 1; }
                }
                else
                {
                    if (itemLevel1.Name == "color")
                        _theme.themeItems[indexItems].type = (int)ItemType.color;
                    else if (itemLevel1.Name == "size")
                        _theme.themeItems[indexItems].type = (int)ItemType.size;
                    else if (itemLevel1.Name == "indent")
                        _theme.themeItems[indexItems].type = (int)ItemType.indent;
                    _theme.themeItems[indexItems].description = itemLevel1.Attributes[0].Value;
                    _theme.themeItems[indexItems].value = itemLevel1.Attributes[1].Value;

                    if (indexItems < 64 - 1) indexItems++;
                    else { int error = 1; }
                }

            }

            QtGuiLib.pPutTheme(_theme);
        }

        public GsaGui(Action _StopAction, Action<IMeasurement, IView> _ActivatorAction)
        {
            m_bExitFlag = false;
            m_CallerThread = Thread.CurrentThread;
            m_XBuffer = new double[1024];
            m_YBuffer = new double[1024];
            m_Period = null;
            m_VSyncDelegate = () => _meas.ActiveView.NeedAction.Set();

            XmlDocument doc = new XmlDocument();
            doc.LoadXml(guiTheme);
            SetTheme(doc);

            m_ResizeXDelegate = (_Name, _XLimits) => {
                IGraphPanel l_Pan = _meas.ActiveView.Panels.Find((_Panel) => _Panel.Name == _Name) as IGraphPanel;
                if (l_Pan != null)// && (l_Pan.XLimits != _XLimits))
                {
                    m_bGUIResize = true;
                    l_Pan.XLimits = _XLimits;
                    m_bGUIResize = false;
                }
            };

            m_ResizeYDelegate = (_Name, _YLimits) =>
            {
                IGraphPanel l_Pan = _meas.ActiveView.Panels.Find((_Panel) => _Panel.Name == _Name) as IGraphPanel;
                if (l_Pan != null)
                {
                    m_bGUIResize = true;
                    l_Pan.YLimits = _YLimits;
                    m_bGUIResize = false;
                }
            };

            m_ResizePixelXDelegate = (_Name, _Width) =>
            {
                IGraphPanel l_Pan = _meas.ActiveView.Panels.Find((_Panel) => _Panel.Name == _Name) as IGraphPanel;
                if (l_Pan != null) l_Pan.Width = _Width;
            };

            StopKerenel = _StopAction;
            Activator = _ActivatorAction;

            _guiMenu.length = 0;
            _guiMenu.capacity = 32;
            _guiMenu.guiPads = new GuiPad[_guiMenu.capacity];
            _guiMenu.guiScreenPads = new GuiScreenPad[_guiMenu.capacity];
            for (int i = 0; i < _guiMenu.capacity; i++)
            {
                //_guiMenu.guiPads[i].name = "frequency";
                _guiMenu.guiPads[i].length = 0;
                _guiMenu.guiPads[i].capacity = 64;
                _guiMenu.guiPads[i].items = new GuiItem[_guiMenu.guiPads[i].capacity];
                _guiMenu.guiScreenPads[i].length = 0;
                _guiMenu.guiScreenPads[i].capacity = 64;
                _guiMenu.guiScreenPads[i].items = new GuiItem[_guiMenu.guiScreenPads[i].capacity];
                for (int j = 0; j < _guiMenu.guiPads[i].capacity; j++)
                {
                    _guiMenu.guiPads[i].items[j].length = 0;
                    _guiMenu.guiPads[i].items[j].capacity = 32;
                    _guiMenu.guiPads[i].items[j].units = new string[_guiMenu.guiPads[i].items[j].capacity];
                    //_guiMenu.guiPads[i].items[j].name = "start";
                    _guiMenu.guiPads[i].items[j].guilist = new GuiList();
                    _guiMenu.guiPads[i].items[j].guilist.capacity = 32;
                    _guiMenu.guiPads[i].items[j].guilist.names = new string[_guiMenu.guiPads[i].items[j].guilist.capacity];
                    _guiMenu.guiPads[i].items[j].guiLocation = new GuiLocation();

                    _guiMenu.guiScreenPads[i].items[j].length = 0;
                    _guiMenu.guiScreenPads[i].items[j].capacity = 32;
                    _guiMenu.guiScreenPads[i].items[j].units = new string[_guiMenu.guiScreenPads[i].items[j].capacity];
                    //_guiMenu.guiScreenPads[i].items[j].name = "start";
                    _guiMenu.guiScreenPads[i].items[j].guilist = new GuiList();
                    _guiMenu.guiScreenPads[i].items[j].guilist.capacity = 32;
                    _guiMenu.guiScreenPads[i].items[j].guilist.names = new string[_guiMenu.guiScreenPads[i].items[j].guilist.capacity];
                    _guiMenu.guiScreenPads[i].items[j].guiLocation = new GuiLocation();
                }
            }

            m_guiModeMeasView.length = 0;
            m_guiModeMeasView.capacity = 32;
            m_guiModeMeasView.guiModes = new GuiMode[m_guiModeMeasView.capacity];
            for (int i = 0; i < m_guiModeMeasView.capacity; i++)
            {
                m_guiModeMeasView.guiModes[i].length = 0;
                m_guiModeMeasView.guiModes[i].capacity = 32;
                m_guiModeMeasView.guiModes[i].guiMeases = new GuiMeas[m_guiModeMeasView.guiModes[i].capacity];
                for (int j = 0; j < m_guiModeMeasView.guiModes[i].capacity; j++)
                {
                    m_guiModeMeasView.guiModes[i].guiMeases[j].length = 0;
                    m_guiModeMeasView.guiModes[i].guiMeases[j].capacity = 32;
                    m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes = new GuiView[m_guiModeMeasView.guiModes[i].guiMeases[j].capacity];

                    for (int k = 0; k < m_guiModeMeasView.guiModes[i].guiMeases[j].capacity; k++)
                    {
                        //_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k] = new string[_guiMenu.guiPads[i].items[j].capacity];
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].length = 0;
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].capacity = 32;
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels = new GuiPanel[m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].capacity];
                    }
                }
            }

        }

        void VSync()
        {
            _meas.ActiveView.NeedAction.Set();
        }

        public void PutModesCollection(List<IMode> modes_)
        {
            _modes = modes_;

            int count = modes_.Count();
            for (int i = 0; i < modes_.Count(); i++)
            {
                if (i < m_guiModeMeasView.capacity)
                {
                    string name = modes_.ElementAt(i).Name;
                    m_guiModeMeasView.guiModes[i].name = modes_.ElementAt(i).Name;
                    m_guiModeMeasView.length++;
                }
            }
        }

        public bool PutMeasurements(List<IMeasurement> list)
        {
            List<IPad> l_MenuPads = null;
            //List<IPad> _screenPads = null;
            List<IUIProperty> l_UIElements = null;

            m_MeasurementsList = list;

            //Передаётся несколько типов Pad. Реализован пока что только MenuPad
            if (list.Count() > 0)
            {
                if (list[0].Pads.Count > 0)
                {
                    //Получаем лист всех менюшек
                    //l_MenuPads = list[0].ActiveMeasurement.Pads.FindAll(Menu => (Menu as MenuPad) != null);
                    //Того же эффекта можно добиться через GetType - выбирай любой. По идее этот путь более скоростной так как выполняется только проверка а не преобразование
                    //l_MenuPads = list[0].Pads.FindAll(Menu => Menu.GetType().GetTypeInfo().BaseType == typeof(MenuPad));
                    l_MenuPads = list[0].Pads.FindAll(Menu => Menu.GetType() == typeof(MenuPad));
                    //Теперь у тебя лист всех менюшек
                    //l_MenuPads.Count - количество менюшек
                    string str = list[0].Pads[0].Caption.ToString();

                    //string str2 = ( as MenuPad).Caption.ToString();
                    QtGuiLib.pPutDevices(0, 0);
                }
                else
                {
                    ;
                }
                if (list[0].ActiveView.Panels.Count > 0)
                {
                    string strPanels = list[0].ActiveView.Panels[0].Name.ToString();//Так ты получаешь название панели

                    //list[0].ActiveMeasurement.ActiveView.OnNewDataCollected - подписавшись на это событие можно получать сообщения о том, что новые данные для графика готовы
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data Массив данных для отображения
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Type - тип примитива: пары линий полилиния маркер или карртека
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values - массив значений
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[0].Colour - цвет первой вершины
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[0].XValue и YValue - значение по оси X и Y
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style - описание стиля панели
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.AxisColour - цвет осей графика
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XAxisUnit - тип данных по оси X (YAxisUnit для оси Y)
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XAxisUnit.GetType() == typeof(FrequencyUnits) чтобы убдеиться, что по оси Х частота
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XMax и XMin - границы по оси X в еницах измереняи по оси X
                    //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.YMax и YMin - границы по оси X в еницах измереняи по оси Y

                    QtGuiLib.pPutDevices(0, 0);
                }
                else
                {
                    ;
                }

                if (list[0].UIElements.Count > 0)
                {
                    //Получить UIElements для конкретного меню (например первое меню из списка l_MenuPads
                    l_UIElements = list[0].UIElements.FindAll(Element => Element.Pad == l_MenuPads[0]);
                    //Тип элемента  l_UIElements[...].Type
                    //Цифровое значение записанное в элементе типа UIType.EditBox делается так (double)l_UIElements[...].Hardware.Value.Value
                    //Узнать в каких величинах измеряется величина (чтобы во всплывающем окне кнопки с размерностями нарисовать) Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

                    //Строкове значение записанное в элементе типа UIType.List  UIType.Switch  UIType.CheckList делается так (string)l_UIElements[...].Hardware.Value.Value
                    //Узнать набор строчек который надо отобразить Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

                    string strUIElements = list[0].UIElements[0].ToString();
                    if (list[0].UIElements[0].Type == PhaseB.AbstractionLayer.UIType.EditBox)
                    {
                        QtGuiLib.pPutDevices(0, 0);
                    }
                }
                else
                {
                    ;
                }

                //_screenPads = list[0].Pads.FindAll(Menu => Menu.GetType() == typeof(ScreenPad));
            }
            else
            {
                ;
            }

            //GuiModeMeasView _guiModeMeasView = new GuiModeMeasView();

            //event UIPropertyChanged OnUIPropertyChanged;
            //OnUIPropertyUpdate

            for (int i = 0; i < list.Count(); i++)
            {
                if(list[i].ActiveView.Panels[0] is ITablePanel)
                {
                    int iii = 0;
                }

                (list[i].ActiveView.Panels[0] as IGraphPanel).OnResize -= ActiveView_OnResize;
                (list[i].ActiveView.Panels[0] as IGraphPanel).OnRestyle -= ActiveView_OnRestyle;

                (list[i].ActiveView.Panels[0] as IGraphPanel).OnResize += ActiveView_OnResize;
                (list[i].ActiveView.Panels[0] as IGraphPanel).OnRestyle += ActiveView_OnRestyle;
            }

            int index = m_MeasurementsList.IndexOf(_meas);

            for (int i = 0; i < m_guiModeMeasView.length; i++)
            {
                string name = m_guiModeMeasView.guiModes[i].name;

                List<IMeasurement> modes = null;
                modes = list.FindAll(Mode => Mode.Mode.Name == m_guiModeMeasView.guiModes[i].name);

                m_guiModeMeasView.guiModes[i].length = modes.Count();
                for (int j = 0; j < m_guiModeMeasView.guiModes[i].length; j++)
                {
                    string name210 = modes[j].ToString();
                    string name234 = modes[j].Mode.ToString();
                    int count2 = modes[j].Views.Count();
                    m_guiModeMeasView.guiModes[i].name = modes[j].Mode.ToString();
                    m_guiModeMeasView.guiModes[i].guiMeases[j].name = modes[j].ToString();
                    m_guiModeMeasView.guiModes[i].guiMeases[j].length = modes[j].Views.Count();
                    m_guiModeMeasView.guiModes[i].guiMeases[j].Measurement = modes[j];
                    for (int k = 0; k < m_guiModeMeasView.guiModes[i].guiMeases[j].length; k++)
                    {
                        string name3 = modes[j].Views[k].ToString();
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].name = modes[j].Views[k].ToString();
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].length = modes[j].Views[k].Panels.Count();
                        m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].type = (int)modes[j].Views[k].Configuration;
                        for (int l = 0; l < m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].length; l++)
                        {
                            string name4 = modes[j].Views[k].Panels[l].Name; //.ToString();
                            m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].name = modes[j].Views[k].Panels[l].Name; //.ToString();
                            m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].position = (int)modes[j].Views[k].Panels[l].Position; //.ToString();
                            if(modes[j].Views[k].Panels[l] is ITablePanel)
                            {
                                m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].type = 1;
                            }
                            else if(modes[j].Views[k].Panels[l] is IGraphPanel)
                            {
                                m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].type = 0;
                            }
                            else
                            {
                                m_guiModeMeasView.guiModes[i].guiMeases[j].guiViewes[k].guiPanels[l].type = 2;
                            }
                        }
                    }
                }

            }

            QtGuiLib.pPutModeMeasView(m_guiModeMeasView);

            return true;
        }

        public bool setActiveMeasurement(IMeasurement meas_)
        {
            List<IPad> l_MenuPads = null;
            List<IPad> _screenPads = null;
            List<IUIProperty> l_UIElements = null;
            List<IUIProperty> _screenElements = null;

            bool first;

            if (_meas == null)
                first = true;
            else
                first = false;

            _meas = meas_;

            int indexMeas = m_MeasurementsList.IndexOf(_meas);
            int indexMode = _modes.IndexOf(_meas.Mode);
            int indexView = _meas.Views.IndexOf(_meas.ActiveView);

            List<IPanel> panels = _meas.ActiveView.Panels;
            string name111 = panels[0].Name;
            string name222 = _meas.ActiveView.Panels[0].Name;
            ViewConfiguration cnfg = _meas.ActiveView.Configuration;
            PanelPosition pos = panels[0].Position;

            //string measName = _list[indexMeas].ToString();
            //string modeName = _modes[indexMode].ToString();
            //string viewName = _meas.Views[indexView].ToString();

            QtGuiLib.pVSync(m_VSyncDelegate);
            QtGuiLib.pResize(m_ResizePixelXDelegate);
            QtGuiLib.pRerangeX(m_ResizeXDelegate);

            QtGuiLib.pRerangeY(m_ResizeYDelegate);

            if (first)
            {
                FloatingMessage.OnMessageSend += (_Caption, _Message) =>
                {
                    QtGuiLib.messageBox(_Caption, _Message);
                };
            }

            //Передаётся несколько типов Pad. Реализован пока что только MenuPad
            if (true)
            {
                string directory = System.IO.Directory.GetCurrentDirectory();
                Console.WriteLine(directory);

                if (meas_.Pads.Count > 0)
                {
                    l_MenuPads = meas_.Pads.FindAll(Menu => Menu.GetType() == typeof(MenuPad));

                    string str = meas_.Pads[0].Caption.ToString();

                    _guiMenu.length = l_MenuPads.Count();
                    for (int i = 0; i < l_MenuPads.Count(); i++)
                    {
                        char ch0 = (l_MenuPads[i] as MenuPad).Hotkey.Value.KeyChar;
                        ConsoleKey ckey0 = (l_MenuPads[i] as MenuPad).Hotkey.Value.Key;

                        _guiMenu.guiPads[i].keyCode = (int)(l_MenuPads[i] as MenuPad).Hotkey.Value.Key;
                        _guiMenu.guiPads[i].nativeModifiers = 512; // (int)(l_MenuPads[i] as MenuPad).Hotkey.Value.Key;

                        _guiMenu.guiPads[i].name = l_MenuPads[i].Caption.ToString();
                        _guiMenu.guiPads[i].tab = (l_MenuPads[i] as MenuPad).Tab.ToString();

                    }

                    //string str2 = ( as MenuPad).Caption.ToString();
                    string strrr = System.IO.Directory.GetCurrentDirectory();
                    QtGuiLib.pPutDevices(0, 0);

                    _screenPads = meas_.Pads.FindAll(Menu => Menu.GetType() == typeof(ScreenPad));
                    _guiMenu.lengthScreen = _screenPads.Count();
                    for (int i = 0; i < _screenPads.Count(); i++)
                    {
                        //char ch0 = (_screenPads[i] as ScreenPad).Hotkey.Value.KeyChar;
                        //ConsoleKey ckey0 = (_screenPads[i] as ScreenPad).Hotkey.Value.Key;

                        _guiMenu.guiScreenPads[i].keyCode = 0; // (int)(_screenPads[i] as ScreenPad).Hotkey.Value.Key;
                        _guiMenu.guiScreenPads[i].nativeModifiers = 512;

                        _guiMenu.guiScreenPads[i].name = _screenPads[i].Caption.ToString();

                        ScreenPadHPosition hPosition = (_screenPads[i] as ScreenPad).HPosition;
                        ScreenPadVPosition VPosition = (_screenPads[i] as ScreenPad).VPosition;
                    }
                }
                else
                {
                    ;
                }

                if (meas_.ActiveView.Panels.Count > 0)
                {
                    string strPanels = meas_.ActiveView.Panels[0].Name.ToString();//Так ты получаешь название панели
                    meas_.ActiveView.OnNewDataCollected -= ActiveView_OnNewDataCollected;
                    meas_.ActiveView.OnPanelUpdated -= ActiveView_OnPanelUpdated;

                    meas_.ActiveView.OnNewDataCollected += ActiveView_OnNewDataCollected; //подписавшись на это событие можно получать сообщения о том, что новые данные для графика готовы
                    meas_.ActiveView.OnPanelUpdated += ActiveView_OnPanelUpdated;
                    //(meas_.ActiveView.Panels[0] as IGraphPanel).Data; //Массив данных для отображения
                    PhaseB.AbstractionLayer.DataType type = (meas_.ActiveView.Panels[0] as IGraphPanel).Data[0].Type; //тип примитива: пары линий полилиния маркер или карртека

                    for (int panel = 0; panel < _meas.ActiveView.Panels.Count; panel++)
                    {
                        int index = 0; // _Args.ChangedPanelIndex;
                        //int length_ = 1; // _meas.ActiveView.Panels[panel].Data.Length;

                        if (_meas.ActiveView.Panels[panel] is ITablePanel)
                        {
                            Table table = (_meas.ActiveView.Panels[panel] as ITablePanel).Tables[index];
                            if(table.Cells.Length == 256)
                            {
                                QtGuiLib.pPutTablePanel((_meas.ActiveView.Panels[panel] as ITablePanel).Tables[index], 1);
                            }
                            else
                            {
                                int i = 0;
                            }
                        }
                        else if (_meas.ActiveView.Panels[panel] is IGraphPanel)
                        {
                            int iiiii = 0;
                            if (tableTemp != null && tableTemp.Cells != null && tableTemp.Cells.Length == 256)
                            //if (tableTemp.Cells != null && tableTemp.Cells.Length == 256)
                            {
                                //QtGuiLib.pPutTablePanel(tableTemp, 0);
                            }
                            else
                            {
                                int i = 0;
                            }
                        }
                    }

                    QtGuiLib.pPutDevices(0, 0);
                }
                else
                {
                    ;
                }

                if (meas_.UIElements.Count > 0)
                {
                    for (int i = 0; i < meas_.UIElements.Count(); ++i)
                    {
                        int hash = meas_.UIElements[i].GetHashCode();
                        int index1 = meas_.UIElements.IndexOf(meas_.UIElements[i]);
                        //int j = 0;
                    }

                    //l_MenuPads = meas_.Pads.FindAll(Menu => Menu.GetType().GetTypeInfo().BaseType == typeof(MenuPad)); <--Устарело
                    l_MenuPads = meas_.Pads.FindAll(Menu => Menu.GetType() == typeof(MenuPad));
                    for (int i = 0; i < l_MenuPads.Count(); i++)
                    {
                        //Получить UIElements для конкретного меню (например первое меню из списка l_MenuPads
                        l_UIElements = meas_.UIElements.FindAll(Element => Element.Pad == l_MenuPads[i]);
                        //Тип элемента  l_UIElements[...].Type
                        //Цифровое значение записанное в элементе типа UIType.EditBox делается так (double)l_UIElements[...].Hardware.Value.Value
                        //Узнать в каких величинах измеряется величина (чтобы во всплывающем окне кнопки с размерностями нарисовать) Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

                        _guiMenu.guiPads[i].length = l_UIElements.Count();
                        for (int j = 0; j < l_UIElements.Count(); j++)
                        {
                            ////У каждого перечисления, отображаемого на экране есть атрибут Display с параметром Description в котором сохранено строковое занчение подходящее для вывода на экран
                            ////В дальнейшем это пригодится и в локализации. Получить эту строчку можно так
                            //string desc = (CustomAttributeExtensions.GetCustomAttribute(l_UIElements[j].Hardware.Value.ValueEnum.GetType().GetFields()[1], typeof(DisplayAttribute)) as DisplayAttribute).GetDescription();

                            //int index2 = l_UIElements.IndexOf(l_UIElements[j]);
                            //int index3 = meas_.UIElements.IndexOf(l_UIElements[j]);

                            l_UIElements[j].Hardware.OnHardwarePropetyUpdate -= Hardware_OnHardwarePropetyUpdate;
                            l_UIElements[j].OnUIPropertyChanged -= event_UIPropertyChanged;

                            l_UIElements[j].Hardware.OnHardwarePropetyUpdate += Hardware_OnHardwarePropetyUpdate;
                            l_UIElements[j].OnUIPropertyChanged += event_UIPropertyChanged;

                            if (l_UIElements[j].IsVisible)
                                _guiMenu.guiPads[i].items[j].IsVisible = 1;
                            else
                                _guiMenu.guiPads[i].items[j].IsVisible = 0;

                            if (l_UIElements[j].IsEnabled)
                                _guiMenu.guiPads[i].items[j].IsEnabled = 1;
                            else
                                _guiMenu.guiPads[i].items[j].IsEnabled = 0;

                            //int hotkey = (int)l_UIElements[j].HotKey.Value.Key;

                            _guiMenu.guiPads[i].items[j].type = l_UIElements[j].Type.ToString();
                            _guiMenu.guiPads[i].items[j].name = l_UIElements[j].ToString();

                            //if (l_UIElements[j].Hardware.Value.Type == PhaseB.AbstractionLayer.ValueType.Value)
                            if (l_UIElements[j].Type == UIType.EditBox)
                            {
                                string str = l_UIElements[j].Hardware.Value.ValueEnum.Current;
                                //l_UIElements[j].Hardware.Value.ValueEnum
                                //char ch = l_UIElements[j].HotKey.Value.KeyChar;
                                //ConsoleKey ckey = l_UIElements[j].HotKey.Value.Key;

                                _guiMenu.guiPads[i].items[j].value = Convert.ToDouble(l_UIElements[j].Hardware.Value.Value);

                                _guiMenu.guiPads[i].items[j].unit = l_UIElements[j].Hardware.Value.ValueEnum.Current;
                                _guiMenu.guiPads[i].items[j].currentIndex = l_UIElements[j].Hardware.Value.ValueEnum.CurrentIndex;
                                _guiMenu.guiPads[i].items[j].length = l_UIElements[j].Hardware.Value.ValueEnum.Length;
                                for (int k = 0; k < l_UIElements[j].Hardware.Value.ValueEnum.Length; k++)
                                {
                                    string name = l_UIElements[j].Hardware.Value.ValueEnum[k];
                                    _guiMenu.guiPads[i].items[j].units[k] = l_UIElements[j].Hardware.Value.ValueEnum[k];
                                }
                            }
                            else if(l_UIElements[j].Type == UIType.ColourSelector)
                            {
                                _guiMenu.guiPads[i].items[j].unit = l_UIElements[j].ToString();
                            }
                            else
                            {
                                _guiMenu.guiPads[i].items[j].unit = l_UIElements[j].ToString();
                            }

                            if (l_UIElements[j].HotKey == null) {
                                _guiMenu.guiPads[i].items[j].keyCode = _guiMenu.guiPads[i].keyCode;
                                _guiMenu.guiPads[i].items[j].itemtype = 0;
                            }
                            else {
                                _guiMenu.guiPads[i].items[j].keyCode = (int)l_UIElements[j].HotKey.Value.Key;
                                _guiMenu.guiPads[i].items[j].itemtype = 1;
                            }
                            _guiMenu.guiPads[i].items[j].nativeModifiers = _guiMenu.guiPads[i].nativeModifiers;

                            _guiMenu.guiPads[i].items[j].itemIndex = meas_.UIElements.IndexOf(l_UIElements[j]);

                            string name3 = l_UIElements[j].ToString();

                            if (l_UIElements[j].Type == UIType.List || l_UIElements[j].Type == UIType.Switch || l_UIElements[j].Type == UIType.ComboBox ||
                                l_UIElements[j].Type == UIType.CheckBox || l_UIElements[j].Type == UIType.CheckList )
                            {
                                if (l_UIElements[j].Type == UIType.ComboBox)
                                {
                                    string name = l_UIElements[j].Hardware.ID;
                                    //int iiii = 0;
                                }

                                _guiMenu.guiPads[i].items[j].guilist.length = l_UIElements[j].Hardware.Value.ValueEnum.Length;
                                for (int k = 0; k < l_UIElements[j].Hardware.Value.ValueEnum.Length; k++)
                                {
                                    //    //_guiMenu.guiPads[i].items[j].type;
                                    //string name = _guiMenu.guiPads[i].items[j].guilist.name;
                                    //Names[i1] = l_UIElements[j].Hardware.Value.ValueEnum[i1];
                                    string name = l_UIElements[j].Hardware.Value.ValueEnum[k];

                                    _guiMenu.guiPads[i].items[j].guilist.names[k] = l_UIElements[j].Hardware.Value.ValueEnum[k];

                                    string name2 = _guiMenu.guiPads[i].items[j].guilist.names[k];
                                }

                                _guiMenu.guiPads[i].items[j].guilist.index = l_UIElements[j].Hardware.Value.ValueEnum.CurrentIndex;

                            } else if(l_UIElements[j].Type == UIType.ColourSelector)
                            {
                                HardwareValue Value = l_UIElements[j].Hardware.Value;
                                double value = Convert.ToDouble(l_UIElements[j].Hardware.Value.Value);
                                _guiMenu.guiPads[i].items[j].value = Convert.ToDouble(l_UIElements[j].Hardware.Value.Value);
                            }
                        }
                    }

                    //Строкове значение записанное в элементе типа UIType.List  UIType.Switch  UIType.CheckList делается так (string)l_UIElements[...].Hardware.Value.Value
                    //Узнать набор строчек который надо отобразить Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

                    string strUIElements = meas_.UIElements[0].ToString();
                    if (meas_.UIElements[0].Type == PhaseB.AbstractionLayer.UIType.EditBox)
                    {
                        QtGuiLib.pPutDevices(0, 0);
                    }

                    _screenPads = meas_.Pads.FindAll(Menu => Menu.GetType() == typeof(ScreenPad));
                    for (int i = 0; i < _screenPads.Count(); i++)
                    {
                        //Получить UIElements для конкретного меню (например первое меню из списка l_MenuPads
                        _screenElements = meas_.UIElements.FindAll(Element => Element.Pad == _screenPads[i]);

                        //Тип элемента  _screenElements[...].Type
                        //Цифровое значение записанное в элементе типа UIType.EditBox делается так (double)_screenElements[...].Hardware.Value.Value
                        //Узнать в каких величинах измеряется величина (чтобы во всплывающем окне кнопки с размерностями нарисовать) Enum.GetNames(_screenElements[...].Hardware.Value.ValueEnum.GetType())

                        ScreenPadHPosition hPosition = (_screenPads[i] as ScreenPad).HPosition;
                        ScreenPadVPosition VPosition = (_screenPads[i] as ScreenPad).VPosition;

                        _guiMenu.guiScreenPads[i].length = _screenElements.Count();
                        for (int j = 0; j < _screenElements.Count(); j++)
                        {
                            _screenElements[j].Hardware.OnHardwarePropetyUpdate -= Hardware_OnHardwarePropetyUpdate;
                            _screenElements[j].OnUIPropertyChanged -= event_UIPropertyChanged;

                            _screenElements[j].Hardware.OnHardwarePropetyUpdate += Hardware_OnHardwarePropetyUpdate;
                            _screenElements[j].OnUIPropertyChanged += event_UIPropertyChanged;

                            if (_screenElements[j].IsVisible)
                                _guiMenu.guiScreenPads[i].items[j].IsVisible = 1;
                            else
                                _guiMenu.guiScreenPads[i].items[j].IsVisible = 0;

                            if (_screenElements[j].IsEnabled)
                                _guiMenu.guiScreenPads[i].items[j].IsEnabled = 1;
                            else
                                _guiMenu.guiScreenPads[i].items[j].IsEnabled = 0;

                            _guiMenu.guiScreenPads[i].items[j].type = _screenElements[j].Type.ToString();
                            _guiMenu.guiScreenPads[i].items[j].name = _screenElements[j].ToString();
                            _guiMenu.guiScreenPads[i].items[j].guiLocation.vertical = (int)(_screenPads[i] as ScreenPad).VPosition;
                            _guiMenu.guiScreenPads[i].items[j].guiLocation.horizontal = (int)(_screenPads[i] as ScreenPad).HPosition;

                            if (_screenElements[j].Type == UIType.EditBox)
                            {
                                string str = _screenElements[j].Hardware.Value.ValueEnum.Current;

                                _guiMenu.guiScreenPads[i].items[j].value = Convert.ToDouble(_screenElements[j].Hardware.Value.Value);
                                _guiMenu.guiScreenPads[i].items[j].unit = _screenElements[j].Hardware.Value.ValueEnum.Current;
                                _guiMenu.guiScreenPads[i].items[j].currentIndex = _screenElements[j].Hardware.Value.ValueEnum.CurrentIndex;
                                _guiMenu.guiScreenPads[i].items[j].length = _screenElements[j].Hardware.Value.ValueEnum.Length;
                                for (int k = 0; k < _screenElements[j].Hardware.Value.ValueEnum.Length; k++)
                                {
                                    string name = _screenElements[j].Hardware.Value.ValueEnum[k];
                                    _guiMenu.guiScreenPads[i].items[j].units[k] = _screenElements[j].Hardware.Value.ValueEnum[k];
                                }
                            }
                            else if (_screenElements[j].Type == UIType.ColourSelector)
                            {
                                _guiMenu.guiScreenPads[i].items[j].unit = _screenElements[j].ToString();
                            }
                            else if (_screenElements[j].Type == UIType.ComboBox)
                            {
                                _guiMenu.guiScreenPads[i].items[j].value = Convert.ToDouble(_screenElements[j].Hardware.Value.Value);
                                _guiMenu.guiScreenPads[i].items[j].unit = _screenElements[j].ToString();
                                _guiMenu.guiScreenPads[i].items[j].currentIndex = _screenElements[j].Hardware.Value.ValueEnum.CurrentIndex;
                                _guiMenu.guiScreenPads[i].items[j].length = _screenElements[j].Hardware.Value.ValueEnum.Length;
                                for (int k = 0; k < _screenElements[j].Hardware.Value.ValueEnum.Length; k++)
                                {
                                    string name = _screenElements[j].Hardware.Value.ValueEnum[k];
                                    _guiMenu.guiScreenPads[i].items[j].units[k] = _screenElements[j].Hardware.Value.ValueEnum[k];
                                }
                            }
                            else {
                                _guiMenu.guiScreenPads[i].items[j].unit = _screenElements[j].ToString();
                            }

                            if (_screenElements[j].HotKey == null)
                            {
                                _guiMenu.guiScreenPads[i].items[j].keyCode = _guiMenu.guiScreenPads[i].keyCode;
                                _guiMenu.guiScreenPads[i].items[j].itemtype = 0;
                            } else {
                                _guiMenu.guiScreenPads[i].items[j].keyCode = (int)_screenElements[j].HotKey.Value.Key;
                                _guiMenu.guiScreenPads[i].items[j].itemtype = 1;
                            }
                            _guiMenu.guiScreenPads[i].items[j].nativeModifiers = _guiMenu.guiScreenPads[i].nativeModifiers;

                            _guiMenu.guiScreenPads[i].items[j].itemIndex = meas_.UIElements.IndexOf(_screenElements[j]);

                            string name3 = _screenElements[j].ToString();

                            if (_screenElements[j].Type == UIType.List || _screenElements[j].Type == UIType.Switch || _screenElements[j].Type == UIType.ComboBox ||
                                _screenElements[j].Type == UIType.CheckBox || _screenElements[j].Type == UIType.CheckList)
                            {
                                if (_screenElements[j].Type == UIType.ComboBox) {
                                    string name = _screenElements[j].Hardware.ID;
                                }

                                _guiMenu.guiScreenPads[i].items[j].guilist.length = _screenElements[j].Hardware.Value.ValueEnum.Length; 
                                for (int k = 0; k < _screenElements[j].Hardware.Value.ValueEnum.Length; k++) 
                                { 
                                    string name = _screenElements[j].Hardware.Value.ValueEnum[k]; 
                                    _guiMenu.guiScreenPads[i].items[j].guilist.names[k] = _screenElements[j].Hardware.Value.ValueEnum[k]; 
                                    string name2 = _guiMenu.guiScreenPads[i].items[j].guilist.names[k]; 
                                } 

                                _guiMenu.guiScreenPads[i].items[j].guilist.index = _screenElements[j].Hardware.Value.ValueEnum.CurrentIndex;
                            }
                            else if (_screenElements[j].Type == UIType.ColourSelector)
                            {
                                HardwareValue Value = _screenElements[j].Hardware.Value;
                                double value = Convert.ToDouble(_screenElements[j].Hardware.Value.Value);
                                _guiMenu.guiScreenPads[i].items[j].value = Convert.ToDouble(_screenElements[j].Hardware.Value.Value);
                            }

                        }  // for (int j = 0; j < _screenElements.Count(); j++) 

                    } //for (int i = 0; i < _screenPads.Count(); i++)
                }
                else
                {
                    ;
                }
            }
            else
            {
                ;
            }

            _guiMenu.indexMode = _modes.IndexOf(_meas.Mode);
            _guiMenu.indexMeas = m_MeasurementsList.IndexOf(_meas);
            _guiMenu.indexView = _meas.Views.IndexOf(_meas.ActiveView);

            _guiMenu.nameMeas = m_MeasurementsList[indexMeas].ToString();
            _guiMenu.nameMode = _modes[indexMode].ToString();
            _guiMenu.nameView = _meas.Views[indexView].ToString();

            QtGuiLib.pPutCurrentMenu(_guiMenu);

            if (first)
            {
                _graphPanelStyle2.XScaling = (int)(meas_.ActiveView.Panels[0] as IGraphPanel).Style.XScaling;
                _graphPanelStyle2.YScaling = (int)(meas_.ActiveView.Panels[0] as IGraphPanel).Style.YScaling;

                _graphPanelStyle2.XAxisUnit = (meas_.ActiveView.Panels[0] as IGraphPanel).Style.XAxisUnit;
                _graphPanelStyle2.YAxisUnit = (meas_.ActiveView.Panels[0] as IGraphPanel).Style.YAxisUnit;

                if ((meas_.ActiveView.Panels[0] as IGraphPanel).Style.XAxisName == null)
                    _graphPanelStyle2.XAxisName = "XAxisName";
                else
                    _graphPanelStyle2.XAxisName = (meas_.ActiveView.Panels[0] as IGraphPanel).Style.XAxisName;

                if ((meas_.ActiveView.Panels[0] as IGraphPanel).Style.YAxisName == null)
                    _graphPanelStyle2.YAxisName = "YAxisName";
                else
                    _graphPanelStyle2.YAxisName = (meas_.ActiveView.Panels[0] as IGraphPanel).Style.YAxisName;

                QtGuiLib.setRestyle(0, _graphPanelStyle2);
            }

            return true;
        }

        private void event_UIPropertyChanged(object _Sender, UIEventArgs _Args)
        {
            if (_Sender == this) return;

            foreach (IUIProperty _Element in _meas.UIElements.FindAll((_Property) => _Property == _Sender))
            {
                int itemIndex = _meas.UIElements.IndexOf(_Element);
                if (_Args.IsVisible == true)
                {
                    QtGuiLib.pUiPropertyChanged(itemIndex, 0, 1);
                }
                else
                {
                    QtGuiLib.pUiPropertyChanged(itemIndex, 0, 0);
                }
                if (_Args.IsEnabled == true)
                {
                    QtGuiLib.pUiPropertyChanged(itemIndex, 1, 1);
                }
                else
                {
                    QtGuiLib.pUiPropertyChanged(itemIndex, 1, 0);
                }
                //int itemIndex;

                HardwareValue Value = _meas.UIElements[itemIndex].Hardware.Value;
                //double value = (double)Value.Value;
                int index = Value.ValueEnum.CurrentIndex;
            }
        }

        private void Hardware_OnHardwarePropetyUpdate(object _Sender, HardwareEventArgs _Args)
        {
            //List<IUIProperty> l_List;
            //Обязательный фильтр сообщений
            if (_Sender == this) return;
            //if (_Sender as IUIProperty != null)
            //    l_List = _meas.UIElements.FindAll((_Property) => (_Property.Hardware == (_Sender as IUIProperty).Hardware) && (_Property != _Sender as IUIProperty));
            //else if (_Sender as IHardwareProperty != null)
            //    l_List = _meas.UIElements.FindAll((_Property) => _Property.Hardware == _Sender);
            //else return;

            foreach (IUIProperty _Element in _meas.UIElements.FindAll((_Property) => _Property.Hardware == _Sender))
            //foreach (IUIProperty _Element in l_List)
            {
                int itemIndex = _meas.UIElements.IndexOf(_Element);
                if (_Args.UISource == _Element)
                    continue;
                //int itemIndex;

                HardwareValue Value = _meas.UIElements[itemIndex].Hardware.Value;
                //double value = (double)Value.Value;
                int index = Value.ValueEnum.CurrentIndex;

                double value;
                string valueString;
                PhaseB.AbstractionLayer.ValueType valuetype = Value.Type;
                if (valuetype == AbstractionLayer.ValueType.List)
                {
                    if (Value.Value as string != null)
                        valueString = (string)Value.Value;
                    else
                        valueString = DescriptionAttribute.GetDescription((Enum)Value.Value);
                    value = (double)index;
                }
                else
                {
                    value = Convert.ToDouble(Value.Value);// (double)Value.Value;
                }
                string unit = (string)Value.ValueEnum.Current;
                //string[] unit = (string)Value.ValueEnum;

                string[] units = new string[Value.ValueEnum.Length];

                //for (l_N = 0; l_N < Value.ValueEnum.Length; l_N++)
                //< приёмник строки > = Value.ValueEnum[l_N];

                //QtGuiLib.pChangetData(itemIndex, (double)Value.Value, unit);
                QtGuiLib.pChangetData(itemIndex, value, unit);

                //Теперь в l_Index лежит нужный тебе индекс элемента GUI. К одному HardwareProperty может быть привязано несколько элементов гуя, 
                //поэтому я обхожу их в цикле. В принципе завоить переменную l_Index не обязательно. В то место где тебе его надо потсавлять 
                //просто пишешь выражение _meas.UIElements.IndexOf(_Element), но как тебе удобнее

            }

            //GraphPanelData Dat = (GraphPanelData)(_meas.ActiveView.Panels[panel] as IGraphPanel).Data[index];
        }

        private void ActiveView_OnPanelUpdated(object _Sender, PanelEventArgs _Args)
        {
            for (int panel = 0; panel < _meas.ActiveView.Panels.Count; panel++)
            {
                int index = _Args.ChangedPanelIndex;
                int length_ = _meas.ActiveView.Panels[panel].Data.Length;

                ////for (index = 0; index < _meas.ActiveView.Panels[panel].Data.Length; index++)
                ////{
                if (_meas.ActiveView.Panels[panel] is ITablePanel)
                {
                    Table table = (_meas.ActiveView.Panels[panel] as ITablePanel).Tables[index];
                    if (table.Cells.Length == 256)
                    {
                        QtGuiLib.pPutTablePanel((_meas.ActiveView.Panels[panel] as ITablePanel).Tables[index], 1);
                    }
                    else
                    {
                        int i = 0;
                    }
                }
                else if (_meas.ActiveView.Panels[panel] is IGraphPanel)
                {
                    if (tableTemp != null && tableTemp.Cells != null && tableTemp.Cells.Length == 256)
                    {
                        QtGuiLib.pPutTablePanel(tableTemp, 0);
                    }
                    else
                    {
                        int i = 0;
                    }
                }
                //if (_meas.ActiveView.Panels[panel].Data[index] is TablePanelData)
                //{
                //    _graphPanelStyle2.XAxisUnit = (meas_.ActiveView.Panels[panel] as ITablePanel).Style.XAxisUnit;
                //    int iii = 0;
                //    //QtGuiLib.pPutTablePanel(_meas.ActiveView.Panels[panel].Data[index] as TablePanelData);
                //    //putTablePanel(gsa::t::TablePanelData* _tablePanelData)
                //}
                //else if(_meas.ActiveView.Panels[panel].Data[index] is GraphPanelData)
                //{
                //    int iii = 0;
                //}
                ////}
            }
        }

        private void ActiveView_OnResize(IGraphPanel _Sender, ResizeEventArgs _Args)
        {
            switch (_Args.EventType)
            {
                case EventTypeEnum.XRange:
                    if (!m_bGUIResize)
                        QtGuiLib.setXRange(_Sender.Name, _Sender.XLimits);
                    break;
                case EventTypeEnum.YRange:
                    if (!m_bGUIResize)
                        QtGuiLib.setYRange(_Sender.Name, _Sender.YLimits);
                    break;
            }
        }
        private void ActiveView_OnRestyle(IGraphPanel _Sender, RestyleEventArgs _Args)
        {
            lock (m_StyleLocker)
            {
                switch (_Args.EventType)
                {
                    case StyleEventTypeEnum.AxisScaling:
                        AxisStyle pX = _Sender.Style.XScaling;
                        AxisStyle pY = _Sender.Style.YScaling;
                        break;
                    case StyleEventTypeEnum.AxisUnit:
                        //Enum yAxisUnit = _Sender.Style.YAxisUnit;
                        string name = _Sender.Style.YAxisUnit;
                        break;
                    case StyleEventTypeEnum.AxisColor:
                        ColourStruct axisColour = _Sender.Style.AxisColour;
                        break;
                    case StyleEventTypeEnum.FullReset:
                        //QtGuiLib.setRestyle(_Args.EventType, _Sender.Style);
                        break;
                }

                //GraphPanelStyle2 _graphPanelStyle2 = new GraphPanelStyle2();

                _graphPanelStyle2.XScaling = (int)_Sender.Style.XScaling;
                _graphPanelStyle2.YScaling = (int)_Sender.Style.YScaling;

                _graphPanelStyle2.XAxisUnit = _Sender.Style.XAxisUnit; // 0; // (int)_Sender.Style.XAxisUnit;
                _graphPanelStyle2.YAxisUnit = _Sender.Style.YAxisUnit; // 0; // (int)_Sender.Style.XAxisUnit;

                if (_Sender.Style.XAxisName == null)
                    _graphPanelStyle2.XAxisName = "XAxisName";
                else
                    _graphPanelStyle2.XAxisName = _Sender.Style.XAxisName;

                if (_Sender.Style.YAxisName == null)
                    _graphPanelStyle2.YAxisName = "YAxisName";
                else
                    _graphPanelStyle2.YAxisName = _Sender.Style.YAxisName;

                QtGuiLib.setRestyle(0, _graphPanelStyle2);
            }
        }

        private void ActiveView_OnNewDataCollected(object _Sender, ViewEventArgs _Args)
        {
            //int l_N;

            //XYValue value = (_meas.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[0];
            //QtGuiLib.pPutCurrentIndexes(_Args.PreviousPosition, _Args.CurrentPosition);
            //for(l_N = 0; l_N < (_meas.ActiveView.Panels[0] as IGraphPanel).Data[0].Values.Length && l_N<1024; l_N++)
            //{
            //    m_XBuffer[l_N] = (_meas.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[l_N].XValue;
            //    m_YBuffer[l_N] = (_meas.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[l_N].YValue;
            //}
            //QtGuiLib.pDataLayer(m_XBuffer, m_YBuffer);

            //int panel = 0;
            //int index = 0;
            //GraphPanelData Dat = (GraphPanelData)(_meas.ActiveView.Panels[panel] as IGraphPanel).Data[index];
            //int length = (_meas.ActiveView.Panels[panel] as IGraphPanel).Data.Length;
            //if(length > 1)
            //{
            //    int i = 0;
            //}

            //QtGuiLib.pPutCurrentData(Dat, index);

            //QtGuiLib.pPutCurrentData(_meas.ActiveView.Panels[0].Data[0] as GraphPanelData, 0);
            //QtGuiLib.pPutCarriage(_meas.ActiveView.Panels[0].Data[0] as GraphPanelData, 0);

            _meas.ActiveView.LockPanels.WaitOne();

            for (int panel = 0; panel < _meas.ActiveView.Panels.Count; panel++)
            {
                if (_meas.ActiveView.Panels[panel].Data.Length == 1)
                {
                    //int i = 0;
                }

                int index = 0;
                //int count = _meas.ActiveView.Panels.Count;
                int length_ = _meas.ActiveView.Panels[panel].Data.Length;
                for (index = 0; index < _meas.ActiveView.Panels[panel].Data.Length; index++)
                {
                    //if (_meas.ActiveView.Panels[panel].Data[index].GetType() == typeof(GraphPanelData)) { ; }
                    if (_meas.ActiveView.Panels[panel].Data[index] is GraphPanelData)
                    {
                        ((_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).SafeMutex as Mutex).WaitOne();

                        XYValue[] values = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values;

                        QtGuiLib.pPutCurrentData(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData, index, length_);

                        AbstractionLayer.DataType type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                        if (type == AbstractionLayer.DataType.Marker)
                        {
                            ////System.Threading.Thread.Sleep(32);

                            //GraphPanelData graphPanelData = new GraphPanelData();
                            //graphPanelData.Values = new XYValue[(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.Length];
                            //(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.CopyTo(graphPanelData.Values, 0);
                            //graphPanelData.Type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                            //graphPanelData.Length = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Length;
                            //for (int i = 0; i < graphPanelData.Values.Length; i++)
                            //{
                            //    graphPanelData.Values[i].XValue *= 100.0;
                            //    //graphPanelData.Values[i].YValue *= 1.02;
                            //    graphPanelData.Values[i].Colour.Red = 0xff;
                            //}
                            //QtGuiLib.pPutCurrentData(graphPanelData, index + 1);
                        }
                        if (type == AbstractionLayer.DataType.Carret)
                        {
                            //int iiiii = 0;
                            ////System.Threading.Thread.Sleep(32);
                        }
                        if (type == AbstractionLayer.DataType.VerticalLine || type == AbstractionLayer.DataType.HorisontalLine)
                        {
                            //int iiiii = 0;
                        }

                        ((_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).SafeMutex as Mutex).ReleaseMutex();

                        AbstractionLayer.DataType type2 = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;

                        if ((ColourStruct.ToInt((_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values[0].Colour) == 0) && (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type == AbstractionLayer.DataType.PolyLine)
                        {
                            //int i = 0;
                        }

                        //if (index != 2)
                        //{
                        //    QtGuiLib.pPutCurrentData(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData, index);
                        //}

                        //if (type == AbstractionLayer.DataType.Marker)
                        //{
                        //    int i = 0;
                        //}

                        //if (index == 0)
                        //{
                        //    GraphPanelData graphPanelData = new GraphPanelData();
                        //    graphPanelData.Values = new XYValue[(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.Length];
                        //    (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.CopyTo(graphPanelData.Values, 0);
                        //    graphPanelData.Type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                        //    graphPanelData.Length = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Length;
                        //    for (int i = 0; i < graphPanelData.Values.Length; i++)
                        //    {
                        //        graphPanelData.Values[i].YValue *= 1.02;
                        //        graphPanelData.Values[i].Colour.Red = 0xff;
                        //    }
                        //    QtGuiLib.pPutCurrentData(graphPanelData, index + 1);

                        //    GraphPanelData graphPanelData2 = new GraphPanelData();
                        //    graphPanelData2.Values = new XYValue[(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.Length];
                        //    (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.CopyTo(graphPanelData2.Values, 0);
                        //    graphPanelData2.Type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                        //    graphPanelData2.Length = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Length;
                        //    for (int i = 0; i < graphPanelData2.Values.Length; i++)
                        //    {
                        //        graphPanelData2.Values[i].YValue *= 0.98;
                        //        graphPanelData2.Values[i].Colour.Green = 0xff;
                        //    }
                        //    QtGuiLib.pPutCurrentData(graphPanelData2, index + 2);

                        //    GraphPanelData graphPanelData3 = new GraphPanelData();
                        //    graphPanelData3.Values = new XYValue[(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.Length];
                        //    (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.CopyTo(graphPanelData3.Values, 0);
                        //    graphPanelData3.Type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                        //    graphPanelData3.Length = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Length;
                        //    for (int i = 0; i < graphPanelData3.Values.Length; i++)
                        //    {
                        //        graphPanelData3.Values[i].YValue *= 0.96;
                        //        graphPanelData3.Values[i].Colour.Blue = 0xff;
                        //    }
                        //    QtGuiLib.pPutCurrentData(graphPanelData3, index + 3);

                        //}
                        //else if (index == 2)
                        //{
                        //    GraphPanelData graphPanelData = new GraphPanelData();
                        //    graphPanelData.Values = new XYValue[(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.Length];
                        //    (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Values.CopyTo(graphPanelData.Values, 0);
                        //    graphPanelData.Type = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Type;
                        //    //graphPanelData.Length = (_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData).Length;
                        //    graphPanelData.Length = 2;

                        //    double value_ = graphPanelData.Values[0].XValue;
                        //    graphPanelData.Values[0].XValue = value_ * 100.0;
                        //    graphPanelData.Values[1].XValue = value_ * 150.0;
                        //    graphPanelData.Values[1].YValue = graphPanelData.Values[0].YValue;

                        //    graphPanelData.Values[0].Colour.Red = 0xff;
                        //    graphPanelData.Values[0].Colour.Blue = 0xff;
                        //    graphPanelData.Values[1].Colour.Red = 0xff;
                        //    graphPanelData.Values[1].Colour.Blue = 0xff;

                        //    //for (int i = 0; i < graphPanelData.Values.Length; i++)
                        //    //{
                        //    //    //graphPanelData.Values[i].YValue *= 1.02;
                        //    //    graphPanelData.Values[i].XValue *= 10.00;
                        //    //    graphPanelData.Values[i].Colour.Red = 0xff;
                        //    //}
                        //    QtGuiLib.pPutCurrentData(graphPanelData, index);

                        //}
                        //else
                        //{
                        //    //QtGuiLib.pPutCurrentData(_meas.ActiveView.Panels[panel].Data[index] as GraphPanelData, index);
                        //}
                    }
                    else if (_meas.ActiveView.Panels[panel].Data[index] is TablePanelData)
                    {
                        int count = (_meas.ActiveView.Panels[panel] as ITablePanel).Tables.Count();

                        if (count > 0) {
                            Table table = (_meas.ActiveView.Panels[panel] as ITablePanel).Tables[count - 1];
                            int iii = 0;
                        }

                        TablePanelData _Table = _meas.ActiveView.Panels[panel].Data[index] as TablePanelData;
                        length_ = _Table.Length;
                        if(_Table.Values.Length == 256)
                        {
                            QtGuiLib.pPutTableData(_meas.ActiveView.Panels[panel].Data[index] as TablePanelData, index, length_);
                        } else
                        {
                            int i = 0;
                        }
                        //QtGuiLib.pPutTableData(_Table, index, length_);
                    }
                }
            }

            _meas.ActiveView.LockPanels.ReleaseMutex();
            //throw new NotImplementedException();
        }

        //public bool putDevices(List<IPcieDevice> list)
        //{
        //    List<IPad> l_MenuPads = null;
        //    List<IUIProperety> l_UIElements = null;

        //    //Передаётся несколько типов Pad. Реализован пока что только MenuPad
        //    if (list.Count() > 0) {
        //        if (list[0].ActiveMeasurement.Pads.Count > 0)
        //        {
        //            //Получаем лист всех менюшек
        //            //l_MenuPads = list[0].ActiveMeasurement.Pads.FindAll(Menu => (Menu as MenuPad) != null);
        //            //Того же эффекта можно добиться через GetType - выбирай любой. По идее этот путь более скоростной так как выполняется только проверка а не преобразование
        //            l_MenuPads = list[0].ActiveMeasurement.Pads.FindAll(Menu => Menu.GetType().GetTypeInfo().BaseType == typeof(MenuPad));
        //            //Теперь у тебя лист всех менюшек
        //            //l_MenuPads.Count - количество менюшек
        //            string str = list[0].ActiveMeasurement.Pads[0].Caption.ToString();

        //            //string str2 = ( as MenuPad).Caption.ToString();
        //            QtGuiLib.pPutDevices(0, 0);
        //        }
        //        else {
        //            ;
        //        }
        //        if (list[0].ActiveMeasurement.ActiveView.Panels.Count > 0) {
        //            string strPanels = list[0].ActiveMeasurement.ActiveView.Panels[0].Name.ToString();//Так ты получаешь название панели
        //            //list[0].ActiveMeasurement.ActiveView.OnNewDataCollected - подписавшись на это событие можно получать сообщения о том, что новые данные для графика готовы
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data Массив данных для отображения
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Type - тип примитива: пары линий полилиния маркер или карртека
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values - массив значений
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[0].Colour - цвет первой вершины
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Data[0].Values[0].XValue и YValue - значение по оси X и Y
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style - описание стиля панели
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.AxisColour - цвет осей графика
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XAxisUnit - тип данных по оси X (YAxisUnit для оси Y)
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XAxisUnit.GetType() == typeof(FrequencyUnits) чтобы убдеиться, что по оси Х частота
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.XMax и XMin - границы по оси X в еницах измереняи по оси X
        //            //(list[0].ActiveMeasurement.ActiveView.Panels[0] as IGraphPanel).Style.YMax и YMin - границы по оси X в еницах измереняи по оси Y

        //            QtGuiLib.pPutDevices(0, 0);
        //        }
        //        else {
        //            ;
        //        }
        //        if(list[0].ActiveMeasurement.UIElements.Count > 0 )
        //        {

        //            //Получить UIElements для конкретного меню (например первое меню из списка l_MenuPads
        //            l_UIElements = list[0].ActiveMeasurement.UIElements.FindAll(Element => Element.Pad == l_MenuPads[0]);
        //            //Тип элемента  l_UIElements[...].Type
        //            //Цифровое значение записанное в элементе типа UIType.EditBox делается так (double)l_UIElements[...].Hardware.Value.Value
        //            //Узнать в каких величинах измеряется величина (чтобы во всплывающем окне кнопки с размерностями нарисовать) Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

        //            //Строкове значение записанное в элементе типа UIType.List  UIType.Switch  UIType.CheckList делается так (string)l_UIElements[...].Hardware.Value.Value
        //            //Узнать набор строчек который надо отобразить Enum.GetNames(l_UIElements[...].Hardware.Value.ValueEnum.GetType())

        //            string strUIElements = list[0].ActiveMeasurement.UIElements[0].ToString();
        //            if(list[0].ActiveMeasurement.UIElements[0].Type == PhaseB.AbstractionLayer.UIType.EditBox) {
        //                QtGuiLib.pPutDevices(0, 0);
        //            }
        //        } else {
        //            ;
        //        }
        //    } else {
        //        ;
        //    }

        //    return true;
        //}

        public bool run(string str)
        {
            m_bExitFlag = true;

            Console.WriteLine();

            QtGuiLib.pRun("Вызов с передачей делеагата. Консольное окно ожидает закрытия этого диалогового окна",
                new MBResult(Result), new SetValue(SetValue), new WheelRotate(WheelRotate), new CallActivator(CallActivator), new MBExit(Exit), new GSetFocus(GSetFocus));

            //Console.Write("Ожидание закрытия окна в неуправляемом потоке:  ");
            Console.Write("Closing window wait in unmanaged thread:  ");

            //Result(1);

            //for (l_Counter = 0; !m_bExitFlag; l_Counter = (l_Counter + 1) % 2000)
            //{
            //    switch (l_Counter / 500)
            //    {
            //        case 0:
            //            Console.CursorLeft = 47;
            //            Console.Write("|");
            //            break;
            //        case 1:
            //            Console.CursorLeft = 47;
            //            Console.Write("/");
            //            break;
            //        case 2:
            //            Console.CursorLeft = 47;
            //            Console.Write("-");
            //            break;
            //        case 3:
            //            Console.CursorLeft = 47;
            //Console.Write("\\");
            //            break;
            //    }
            //    Thread.Sleep(1);
            //}

            while (m_bExitFlag)
            {
                Thread.Sleep(0);
                //int i = 0;
            }

            return true;
        }
        //        int Result(int _DialogResult)
        int Result(int _PeriodValue)
        {
            //StringBuilder l_Bld = new StringBuilder();
            int result = 0;
            HardwareValue lV = new HardwareValue();
            lV.Type = AbstractionLayer.ValueType.Value;
            //lV.ValueEnum = TimeUnits.ms;
            lV.ValueEnum = null;

            lV.Value = _PeriodValue;

            if (m_Period != null)
                m_Period.SetValue(this, lV);

            //m_bExitFlag = true;
            //Console.WriteLine();
            ////l_Bld.Append("Диалоговое окно вернуло ").Append(_DialogResult == 1 ? "IDOK" : "IDCANCEL");
            //l_Bld.Append("Dialog return ").Append(_DialogResult == 1 ? "IDOK" : "IDCANCEL");
            //Console.WriteLine(l_Bld.ToString());

            //try
            //{
            //    //Console.Write("Введите число которое будет возвращено в неуправляемую среду: ");
            //    Console.Write("Input value which will return to unmanaged context : ");
            //    //result = Convert.ToInt32(Console.ReadLine());
            //    while (m_bExitFlag)
            //        Thread.Sleep(100);
            //}
            //catch (System.Exception ex)
            //{
            //    string text = ex.ToString();
            //}

            //QtGuiLib.pStop();

            return result;
        }
        int SetValue(int itemIndex, double value, string unit, int index)
        {
            if (_meas.UIElements.Count() < itemIndex) return 0;

            HardwareValue Value = _meas.UIElements[itemIndex].Hardware.Value;

            //Thread.Sleep(1);

            switch (_meas.UIElements[itemIndex].Type)
            {
                case UIType.Button:
                    _meas.UIElements[itemIndex].Hardware.SetValue(_meas.UIElements[itemIndex], new HardwareValue(true));
                    break;
                case UIType.EditBox:
                    _meas.UIElements[itemIndex].Hardware.SetValue(_meas.UIElements[itemIndex], new HardwareValue(Value.ValueEnum.Clone(index), value));
                    break;
                case UIType.Switch:
                case UIType.List:
                case UIType.CheckBox:
                case UIType.CheckList:
                case UIType.ComboBox:
                    _meas.UIElements[itemIndex].Hardware.SetValue(_meas.UIElements[itemIndex], new HardwareValue(Value.ValueEnum.Clone((int)value), Value.ValueEnum[(int)value]));
                    break;
                case UIType.ColourSelector:
                    _meas.UIElements[itemIndex].Hardware.SetValue(_meas.UIElements[itemIndex], new HardwareValue(Value.ValueEnum.Clone(), (int)Convert.ToUInt32(value) & 0xffffff));
                    break;
            }

            return 0;
        }
        int GSetFocus(int itemIndex, int value)
        {
            if (value == 0)
                _meas.UIElements[itemIndex].IsFocused = false;
            else
                _meas.UIElements[itemIndex].IsFocused = true;

            return 0;
        }
        int WheelRotate(int itemIndex, int value)
        {
            HardwareValue Value = _meas.UIElements[itemIndex].Hardware.Value;
            _meas.UIElements[itemIndex].WheelRotate(value);

            return 0;
        }
        void CallActivator(int _Mode, int _Measurement, int _View)
        {
            //_meas.ActiveView.OnNewDataCollected -= ActiveView_OnNewDataCollected; 
            //_meas.ActiveView.OnPanelUpdated -= ActiveView_OnPanelUpdated;

            Activator(m_guiModeMeasView.guiModes[_Mode].guiMeases[_Measurement].Measurement, m_guiModeMeasView.guiModes[_Mode].guiMeases[_Measurement].Measurement.Views.ElementAt(_View));
            //Activator(m_MeasurementsList.ElementAt(_Measurement), m_MeasurementsList.ElementAt(_Measurement).Views.ElementAt(_View));
        }

        void Exit()
        {
            QtGuiLib.pStop();

            m_bExitFlag = false;
            StopKerenel();
            m_CallerThread.Join();
        }
    }
}
