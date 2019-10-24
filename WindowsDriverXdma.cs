// neustroev 2018.07.16  -  2019.03.20 

using System;
using System.Text;
using System.Runtime.InteropServices;
using System.Collections.Generic;
using System.Reflection;
using System.Threading;
using System.IO;

using GammaShared;
using PhaseB.DriverUtils;
using PhaseB.AbstractionLayer;

#if XDMA_DRIVER
using PhaseB.FPGADevice.XdmaDriverWrapperDataTypes;
using PhaseB.FPGADevice.XdmaDriverWrapper;
#else
using PhaseB.FPGADevice.FpgaDriverDataTypes;
using PhaseB.FPGADevice.DriverInterface;
#endif

//XDMA_DRIVER;  DriverSupport;  FPGADevice

#pragma warning disable CS0168, CS0169, CS0219, CS0414 

namespace PhaseB.FPGADevice.DriverSupport
{
    internal class WindowsDriverXdma : IBasicDriverInterface
    {
        public readonly static IntPtr INVALID_HANDLE_VALUE = new IntPtr(-1);
        public readonly UInt64 ConfRomOffset = 0x05010000;

        public NodeType _nodeType = NodeType.ZERO;

        private unsafe byte[] buffer;

#if Console_Xdma
        //  /console_xdma:true
        private Pipe m_Pipe;
#endif
        string currentDirectory;
        public FpgaDriver _fpgaDriver = null;

        const int maxnumber = 32;
        //string m_DriverName;
        string[] m_DriverNames = new string[maxnumber] {
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "",
            "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "" };

        //IntPtr m_FileHandle = INVALID_HANDLE_VALUE;
        IntPtr[] m_FileHandles = new IntPtr[maxnumber] {
            INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE,
            INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE,
            INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE,
            INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE
        };

        UInt32[] offsets = new UInt32[maxnumber] {
            0x01000000, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
            0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };

        private List<Thread> eventThreades = new List<Thread>(0);
        private SortedDictionary<int, bool> stopEventThreades = new SortedDictionary<int, bool>();
        private SortedDictionary<int, bool> startEventThreades = new SortedDictionary<int, bool>();
        private SortedDictionary<int, Thread> handleEventThreades = new SortedDictionary<int, Thread>();
        private const int eventThreadCount = 16;
        private Guid xdmaGuid = new Guid("{74c7e4a9-6d5d-4a70-bc0d-20691dff9e9d}");
        private string xdmaPath = new string("");

        private NodeKey nodeKey = new NodeKey(NodeType.USER, OperationType.read);
        private NodeParam nodeParam = new NodeParam(IntPtr.Zero, 0x0);

        //uint BUFFER_SIZE = 1024;
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto)]
        struct SP_DEVICE_INTERFACE_DETAIL_DATA
        {
            public int cbSize;
            //[MarshalAs(UnmanagedType.ByValArray, SizeConst = 4096)] //BUFFER_SIZE //ByValTStr
            //public byte[] DevicePath;
            [MarshalAs(UnmanagedType.ByValTStr, SizeConst = 4096)] //BUFFER_SIZE //ByValTStr
            public string DevicePath;
        }
        public enum Direction
        {
            C2H = 0, // client to host - read
            H2C = 1,  // host to client - write
        }

        public struct NodeKey : IComparable<NodeKey>
        {
            public NodeType _nodeType;
            public OperationType _operationType;

            public NodeKey(NodeType nodeType, OperationType operationType)
            {
                _nodeType = nodeType;
                _operationType = operationType;
            }
            public int CompareTo(NodeKey other)
            {
                return (_operationType - other._operationType) * 16 + (_nodeType - other._nodeType);
            }
        }

        public struct NodeParam
        {
            public IntPtr _filehandle;
            public UInt64 _offset;

            public NodeParam(IntPtr filehandle, UInt64 offset)
            {
                _filehandle = filehandle;
                _offset = offset;
            }
        }

        public class SortNodeKeyComparer : IComparer<NodeKey>
        {
            public int Compare(NodeKey nodeKey1, NodeKey nodeKey2)
            {
                int compare = (int)nodeKey1._nodeType - (int)nodeKey2._nodeType;
                if(compare == 0)
                {
                    return (int)nodeKey1._operationType - (int)nodeKey2._operationType;
                }
                else
                {
                    return compare;
                }
            }
        }

        SortedDictionary<NodeKey, NodeParam> NodeList = new SortedDictionary<NodeKey, NodeParam>( new SortNodeKeyComparer() );

        public WindowsDriverXdma() 
        { 
            string[] strings = Environment.GetCommandLineArgs(); 

            currentDirectory = Directory.GetCurrentDirectory();

            //NodeKey nodeKey = new NodeKey(NodeType.USER, OperationType.read); 
            //NodeParam nodeParam = new NodeParam(IntPtr.Zero, 0x0); 

            //nodeKey._nodeType = NodeType.USER; 
            //nodeKey._operationType = OperationType.read; 
            //NodeList.Add(nodeKey, nodeParam); 
            //nodeKey._operationType = OperationType.write; 
            //NodeList.Add(nodeKey, nodeParam); 

            //nodeKey._nodeType = NodeType.CONTROL; 
            //nodeKey._operationType = OperationType.read; 
            //NodeList.Add(nodeKey, nodeParam); 
            //nodeKey._operationType = OperationType.write; 
            //NodeList.Add(nodeKey, nodeParam); 

#if Console_Xdma

            for (int i = 0; i <eventThreadCount; i++)
            {
                stopEventThreades[i] = true;
                startEventThreades[i] = false;
                handleEventThreades[i] = null;
            }

            if (checkArgs(Environment.GetCommandLineArgs(), "/console_xdma:", false))
            {
                m_Pipe = Pipe.Create("PhaseB_driving", "PHASEB>");
                m_Pipe.Title = "PhaseB xdma console";
                m_Pipe.Invite = "PHASEB";
                m_Pipe.FontColor = ConsoleColor.Yellow;
                m_Pipe.BackgroundColor = ConsoleColor.DarkBlue;

                //m_Pipe.RegisterCommand(new ConsoleCommand("SetProperty", ChangeProperty, new string[] { "Using \"SetProperty <prop_name> [new value]\"" }));
                m_Pipe.RegisterCommand(new ConsoleCommand("read", ChangePropertyRead, new string[] {
                    "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ",
                    "- DEVNODE : One of: control | user | hc2_* | c2h_*,",
                    "where the * is a numeric wildcard (0-15 for events, 0 - 3 for hc2 and c2h).",
                    "",  
                    "- ADDR : The target offset address of the read / write operation.",
                    "Can be in hex or decimal.",
                    "",
                    " - IPCORE_NAME : ipcore from list in current.xml or fpga ",
                    "- OPTIONS :",
                    "",
                    "-l(length of data to read / write)",
                    "-b open file as binary",
                    "-f use data file as input / output(for write / read respectively).",
                    "",
                    "- DATA : Space separated byte data in decimal or hex,",
                    "e.g.:  17 34 51 68   or:   0x11 0x22 0x33 0x44"
                    }));
                m_Pipe.RegisterCommand(new ConsoleCommand("write", ChangePropertyWrite, new string[] {
                    "Using \"write <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"write <IPCORE_NAME> [OPTIONS] [DATA]\" ",
                    "- DEVNODE : One of: control | user | hc2_* | c2h_*,",
                    "where the * is a numeric wildcard (0-15 for events, 0 - 3 for hc2 and c2h).",
                    "",
                    "- ADDR : The target offset address of the read / write operation.",
                    "Can be in hex or decimal.",
                    "",
                    " - IPCORE_NAME : ipcore from list in current.xml or fpga ",
                    "- OPTIONS :",
                    "",
                    "-l(length of data to read / write)",
                    "-b open file as binary",
                    "-f use data file as input / output(for write / read respectively).",
                    "",
                    "- DATA : Space separated byte data in decimal or hex,",
                    "e.g.:  17 34 51 68   or:   0x11 0x22 0x33 0x44"
                }));
                m_Pipe.RegisterCommand(new ConsoleCommand("wait", ChangePropertyWait, new string[] {
                    "Using \"wait event <start | stop> [DATA]\" ",
                    "- DATA : Space separated byte data in decimal ,",
                    "e.g.:  0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 "
                }));
            }

#endif

        }

        ~WindowsDriverXdma()
        {
            Dispose();
        }

        public void Dispose()
        {

#if Console_Xdma

            for (int i = 0; i < eventThreadCount; i++)
            {
                if (stopEventThreades[i] == false)
                {
                    stopEventThreades[i] = true;
                    startEventThreades[i] = false;
                    handleEventThreades[i].Join();
                }
            }
            CloseEventDriver();

#endif

            CloseDriver();
            GC.SuppressFinalize(this);
        }


        [StructLayout(LayoutKind.Explicit, Size = 8)]
        public struct LARGE_INTEGER
        {
            [FieldOffset(0)] public UInt64 QuadPart;
            [FieldOffset(0)] public UInt32 LowPart;
            [FieldOffset(4)] public Int32 HighPart;
        }

        [Serializable]
        [StructLayout(LayoutKind.Sequential, Pack = 4)]
        internal struct Options
        {
            public bool verbose;
            public char[] device;
            public char[] file;
            public byte[] data;
            //public IntPtr data;
            public LARGE_INTEGER address;
            public Int32 size;
            public Direction direction;
            public Int32 alignment;
            public bool binary;

            //BOOL verbose;
            //char* device;
            //char* file;
            //BYTE* data;
            //LARGE_INTEGER address;
            //DWORD size;
            //enum Direction direction;
            //size_t alignment;
            //BOOL binary;
        }

        public static LARGE_INTEGER tmp;
        Options options = new Options { verbose = false, device = null, file = null, data = null, address = tmp, size = 0, direction = Direction.C2H, alignment = 0, binary = false };

        [Flags]
        public enum DiGetClassFlags : uint
        {
            DIGCF_DEFAULT = 0x00000001,  // only valid with DIGCF_DEVICEINTERFACE
            DIGCF_PRESENT = 0x00000002,
            DIGCF_ALLCLASSES = 0x00000004,
            DIGCF_PROFILE = 0x00000008,
            DIGCF_DEVICEINTERFACE = 0x00000010,
        }

        //static BYTE* allocate_buffer(size_t size, size_t alignment)
        unsafe public byte* allocate_buffer(ulong size, ulong alignment)
        {

            if (size == 0)
                size = 4;

            if (alignment == 0)
            {
                SYSTEM_INFO sys_info;
                GetSystemInfo(out sys_info);
                alignment = sys_info.PageSize;
            }

            //verbose_msg("Allocating host-side buffer of size %llu, aligned to %llu bytes\n", size, alignment);
            //return (byte*)_aligned_malloc(size, alignment);
            return (byte*)0;
        }

        unsafe public ulong get_devices(Guid xdmaGuid, ref string xdmaPath)
        {
            //xdmaPath = xdmaGuid.ToString();

            IntPtr device_info = SetupDiGetClassDevs(ref xdmaGuid, IntPtr.Zero, IntPtr.Zero, (uint)DiGetClassFlags.DIGCF_PRESENT | (uint)DiGetClassFlags.DIGCF_DEVICEINTERFACE);
            if (device_info == (IntPtr)INVALID_HANDLE_VALUE) {
                return 0;
            } else {
                SP_DEVICE_INTERFACE_DATA device_interface = new SP_DEVICE_INTERFACE_DATA();
                device_interface.cbSize = Marshal.SizeOf(device_interface);

                // enumerate through devices
                uint index;
                for (index = 0; SetupDiEnumDeviceInterfaces(device_info, IntPtr.Zero, ref xdmaGuid, index, ref device_interface); ++index)
                {
                    // get required buffer size
                    UInt32 detailLength = 0;
                    if (!SetupDiGetDeviceInterfaceDetail(device_info, ref device_interface, IntPtr.Zero, 0, ref detailLength, IntPtr.Zero) && GetLastError() != ResultWin32.ERROR_INSUFFICIENT_BUFFER)
                    {
                        //fprintf(stderr, "SetupDiGetDeviceInterfaceDetail - get length failed\n");
                        break;
                    } else
                    {
                        // build a Device Interface Detail Data structure
                        SP_DEVICE_INTERFACE_DETAIL_DATA dev_detail = new SP_DEVICE_INTERFACE_DETAIL_DATA();
                        if (detailLength > 4096) detailLength = 4096;
                        //dev_detail.cbSize = (int)detailLength;
                        dev_detail.cbSize = (int)8;
                        //dev_detail.DevicePath = new byte[dev_detail.cbSize];

                        // get device interface detail
                        if (!SetupDiGetDeviceInterfaceDetail(device_info, ref device_interface, ref dev_detail, detailLength, IntPtr.Zero, IntPtr.Zero))
                        {
                            //fprintf(stderr, "SetupDiGetDeviceInterfaceDetail - get detail failed\n");
                            //HeapFree(GetProcessHeap(), 0, dev_detail);
                            break;
                        } else
                        {
                            //StringCchCopy(devpath, len_devpath, dev_detail->DevicePath);
                            //devpath = dev_detail->DevicePath;
                            xdmaPath = dev_detail.DevicePath;
                            //xdmaPath = dev_detail.DevicePath.ToString();
                        }
                    }
                }

                SetupDiDestroyDeviceInfoList(device_info);
            }

            return 0;
        }

        unsafe public int ReadMem(NodeParam nodeParam, UInt64 BufOffset, void* OutBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false; 

            options.address.QuadPart = nodeParam._offset + offset; 
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(nodeParam._filehandle, options.address.QuadPart, IntPtr.Zero, 0)) 
            { 
                // log error 
                Console.WriteLine("ReadMem() SetFilePointerEx() INVALID_SET_FILE_POINTER _filehandle = {0:X}", nodeParam._filehandle); 
                return 1; //log error 
            } 
            else 
            {
                int sizeOut = 0;
                if (ReadFile(nodeParam._filehandle, (byte*)OutBuffer + BufOffset, size, &sizeOut, 0) == false) 
                { 
                    // log error  
                    Console.WriteLine("ReadFile() ERROR _filehandle = {0:X} size = {1} {2} ", nodeParam._filehandle, size, sizeOut); 
                    return 1; 
                } 
                else 
                {
                    // ok 
                    //Console.WriteLine("ReadFile() OK _filehandle = {0:X} size = {1} {2} ", nodeParam._filehandle, size, sizeOut);
                    return 0; 
                } 
            } 
        } 

        unsafe public int WriteMem(NodeParam nodeParam, UInt64 BufOffset, void* InBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false;

            options.address.QuadPart = nodeParam._offset + offset;
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(nodeParam._filehandle, options.address.QuadPart, IntPtr.Zero, 0))
            {
                // log error 
                Console.WriteLine("WriteMem() SetFilePointerEx() INVALID_SET_FILE_POINTER _filehandle = {0:X}", nodeParam._filehandle);
                return 1; //log error 
            }
            else
            {
                if (WriteFile(nodeParam._filehandle, (byte*)InBuffer + BufOffset, size, &size, 0) == false)
                {
                    // log error 
                    Console.WriteLine("WriteFile() ERROR _filehandle = {0:X} size = {1} ", nodeParam._filehandle, size);
                    return 1; //log error 
                }
                else
                {
                    // ok 
                    return 0;
                }
            }
        }

        unsafe public int ReadMem(int index, void* OutBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false;

            options.address.QuadPart = offsets[index] + offset; // 0x01000000;
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(m_FileHandles[index], options.address.QuadPart, IntPtr.Zero, 0))
            {
                int i = 0;
            }
            else
            {
                int i = 0;
            }

            if (ReadFile(m_FileHandles[index], (byte*)OutBuffer + offset, size, &size, 0) == false)
            {
                int i = 0;
            }
            else
            {
                int i = 0;
            }

            return 0;
        }

        unsafe public int WriteMem(int index, void* InBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false;

            options.address.QuadPart = offsets[index] + offset; // 0x01000000;
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(m_FileHandles[index], options.address.QuadPart, IntPtr.Zero, 0))
            {
                int i = 0;
            }
            else
            {
                int i = 0;
            }

            if (WriteFile(m_FileHandles[index], (byte*)InBuffer + offset, size, &size, 0) == false)
            {
                int i = 0;
            }
            else
            {
                int j = 0;
            }

            return 0;
        }

        unsafe public int ReadMem(int index, byte[] OutBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false;

            options.address.QuadPart = offsets[index] + offset; // 0x01000000;
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(m_FileHandles[index], options.address.QuadPart, IntPtr.Zero, 0)) {
                int i = 0;
                //fprintf(stderr, "Error setting file pointer, win32 error code: %ld\n", GetLastError());
                //goto CleanupDevice;
            } else {
                int i = 0;
            }

            options.size = OutBuffer.Length; // 1024;
            int size_ = size; // 1024;

            fixed (void* pdata = &OutBuffer[offset])
            {
                //fixed (int* psize = &options.size)
                int* psize = &size_;
                {
                    //if (!ReadFile(m_FileHandle, (void*)options.data, options.size, pNumberOfBytesRead, 0))
                    if (ReadFile(m_FileHandles[index], pdata, *psize, psize, 0) == false)
                    {
                        int i = 0;
                    }
                    else
                    {
                        int j = 0;
                    }
                }

                int jj = 0;
            }

            return 0;
        }

        unsafe public int WriteMem(int index, byte[] InBuffer, UInt64 offset = 0, int size = 0)
        {
            bool INVALID_SET_FILE_POINTER = false;

            options.address.QuadPart = offsets[index] + offset; // 0x01000000;
            if (INVALID_SET_FILE_POINTER == SetFilePointerEx(m_FileHandles[index], options.address.QuadPart, IntPtr.Zero, 0))
            {
                int i = 0;
                //fprintf(stderr, "Error setting file pointer, win32 error code: %ld\n", GetLastError());
                //goto CleanupDevice;
            }
            else
            {
                int i = 0;
            }

            options.size = InBuffer.Length; // 1024;
            int size_ = size; // 1024;

            fixed (void* pdata = &InBuffer[offset])
            {
                int* psize = &size_;
                {
                    //int _size;
                    //if (!ReadFile(m_FileHandle, (void*)options.data, options.size, pNumberOfBytesRead, 0))
                    if (WriteFile(m_FileHandles[index], pdata, *psize, psize, 0) == false)
                    {
                        int i = 0;
                        //fprintf(stderr, "ReadFile from device %s failed with Win32 error code: %ld\n",
                        //device_path, GetLastError());
                        //goto CleanupDevice;
                    }
                    else
                    {
                        int j = 0;
                    }
                }

                int jj = 0;
            }

            return 0;
        }

        public bool checkArgs(string[] args, string param, bool ret)
        {
            string value;
            List<string> listArgs = new List<string>(args);

            value = listArgs.Find((_Name) => _Name.StartsWith(param));
            if (value == null)
                return ret;
            else
                value = value.Substring(param.Length);

            if (value == "false")
                return false;
            else if (value == "true")
                return true;
            else
                return ret;
        }

        public void fillNodeList(BarType barType, NodeType nodeType, ref NodeKey nodeKey, ref NodeParam nodeParam)
        {
            nodeParam._filehandle = m_FileHandles[(int)barType];
            nodeKey._nodeType = nodeType;
            nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x00000000; 

            switch (barType)
            {
                case BarType.USER:
                    {
                        //nodeParam._filehandle = m_FileHandles[(int)barType];
                        //nodeKey._nodeType = nodeType;
                        //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x01000000; 
                        nodeKey._operationType = OperationType.read;
                        NodeList.Add(nodeKey, nodeParam);
                        nodeKey._operationType = OperationType.write;
                        NodeList.Add(nodeKey, nodeParam);
                        break;
                    }
                case BarType.H2C_0:
                case BarType.H2C_1:
                case BarType.H2C_2:
                case BarType.H2C_3:
                    {
                        //nodeParam._filehandle = m_FileHandles[(int)barType];
                        //nodeKey._nodeType = nodeType; // host to client - write
                        //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x00000000; 
                        nodeKey._operationType = OperationType.write;
                        NodeList.Add(nodeKey, nodeParam);
                        break;
                    }
                case BarType.C2H_0:
                case BarType.C2H_1:
                case BarType.C2H_2:
                case BarType.C2H_3:
                    {
                        //nodeParam._filehandle = m_FileHandles[(int)barType];
                        //nodeKey._nodeType = nodeType; // client to host - read
                        //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x00000000; 
                        nodeKey._operationType = OperationType.read;
                        NodeList.Add(nodeKey, nodeParam);
                        break;
                    }
                case BarType.CONTROL:
                    {
                        nodeKey._operationType = OperationType.read;
                        NodeList.Add(nodeKey, nodeParam);
                        nodeKey._operationType = OperationType.write;
                        NodeList.Add(nodeKey, nodeParam);
                        break;
                    }
                case BarType.EVENT_0:
                case BarType.EVENT_1:
                case BarType.EVENT_2:
                case BarType.EVENT_3:
                case BarType.EVENT_4:
                case BarType.EVENT_5:
                case BarType.EVENT_6:
                case BarType.EVENT_7:
                case BarType.EVENT_8:
                case BarType.EVENT_9:
                case BarType.EVENT_10:
                case BarType.EVENT_11:
                case BarType.EVENT_12:
                case BarType.EVENT_13:
                case BarType.EVENT_14:
                case BarType.EVENT_15:
                    {
                        nodeKey._operationType = OperationType.read;
                        NodeList.Add(nodeKey, nodeParam);
                        break;
                    }
            }
        }

        public void FillConfig(string currentXml, ref NodeKey nodeKey, ref NodeParam nodeParam)
        {
            //read ipcore list from file 
            string l_Path = Assembly.GetExecutingAssembly().Location; 
            l_Path = l_Path.Remove(l_Path.LastIndexOf('\\') + 1); 
            //if (BaseAddressReader.CurrentReader.InitFromXml(l_Path + "BuildResources\\current.xml")) 
            if (BaseAddressReader.CurrentReader.InitFromXml(l_Path + currentXml)) 
            { 
                nodeKey._nodeType = NodeType.CONF_ROM; 
                nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; 
                if (nodeParam._offset == 0xffffffffffffffff) 
                    nodeParam._offset = ConfRomOffset; // (UInt64)0x05010000; 
            } 
            else 
            { 
                nodeKey._nodeType = NodeType.CONF_ROM; 
                nodeParam._offset = ConfRomOffset; // (UInt64)0x05010000; 
            } 

            //IPCore ipCore = new IPCore(); 

            //fill main ipcore address (conf_rom) get from config-file current.xml 
            nodeParam._filehandle = m_FileHandles[(int)BarType.USER]; 
            //nodeKey._nodeType = NodeType.CONF_ROM; 
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; 
            nodeKey._operationType = OperationType.read; 
            NodeList.Add(nodeKey, nodeParam); 
            nodeKey._operationType = OperationType.write; 
            NodeList.Add(nodeKey, nodeParam); 

            if (nodeParam._offset != 0xffffffffffffffff && checkArgs(Environment.GetCommandLineArgs(), "/conf_rom:", true)) 
            { 
                //read ipcore list from fpga 
                const int OutSize = 4096;
                byte[] buffer = new byte[OutSize];
                readFromFpga(buffer);
                if (BaseAddressReader.CurrentReader.InitFromBuffer(buffer))
                {
                    BaseAddressReader.CurrentReader.CompareXML();
                }
            }
        }

        public int OpenEventDriver()
        {
            ulong num_devices = get_devices(xdmaGuid, ref xdmaPath);

            for (int i = 0; i < eventThreadCount; i++)
            {
                if(startEventThreades[i] == true)
                {
                    if (m_FileHandles[(int)BarType.EVENT_0 + i] == INVALID_HANDLE_VALUE)
                    {
                        m_DriverNames[(int)BarType.EVENT_0 + i] = xdmaPath + "\\event_" + i.ToString();
                        m_FileHandles[(int)BarType.EVENT_0 + i] = CreateFile(m_DriverNames[(int)BarType.EVENT_0 + i], GENERIC_READ, 0, IntPtr.Zero, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, IntPtr.Zero);
                        IntPtr intPtr = m_FileHandles[(int)BarType.EVENT_0 + i];

                        fillNodeList(BarType.EVENT_0 + i, NodeType.EVENT_0 + i, ref nodeKey, ref nodeParam); 
                    } 
                } 
            } 

            return 0; 
        } 

        public int CloseEventDriver()
        {
            for (int i = 0; i < eventThreadCount; i++)
            {
                if (m_FileHandles[(int)BarType.EVENT_0 + i] != INVALID_HANDLE_VALUE)
                {
                    CloseHandle(m_FileHandles[(int)BarType.EVENT_0 + i]);
                    m_FileHandles[(int)BarType.EVENT_0 + i] = INVALID_HANDLE_VALUE;
                }
            }

            return 0;
        }

        public int OpenDriver(string driver, IFpgaDriverInterface fpgaDriver)
        {
            if (fpgaDriver != null)
                _fpgaDriver = (FpgaDriver)fpgaDriver;

            for (int i = 0; i < maxnumber; i++)
                if (m_FileHandles[i] != INVALID_HANDLE_VALUE)
                    return HRESULT_FROM_WIN32(WindowsErrors.ERROR_ALREADY_INITIALIZED);

            //// 74c7e4a9-6d5d-4a70-bc0d-20691dff9e9d
            ////DEFINE_GUID(GUID_DEVINTERFACE_XDMA, 0x74c7e4a9, 0x6d5d, 0x4a70, 0xbc, 0x0d, 0x20, 0x69, 0x1d, 0xff, 0x9e, 0x9d);
            //Guid xdmaGuid = new Guid("{74c7e4a9-6d5d-4a70-bc0d-20691dff9e9d}");
            //string xdmaPath = new string("");

            ulong num_devices = get_devices(xdmaGuid, ref xdmaPath);

            m_DriverNames[(int)BarType.USER] = xdmaPath + "\\user";
            m_FileHandles[(int)BarType.USER] = CreateFile(m_DriverNames[(int)BarType.USER], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.C2H_0] = xdmaPath + "\\c2h_0";
            m_FileHandles[(int)BarType.C2H_0] = CreateFile(m_DriverNames[(int)BarType.C2H_0], GENERIC_READ, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.C2H_1] = xdmaPath + "\\c2h_1";
            m_FileHandles[(int)BarType.C2H_1] = CreateFile(m_DriverNames[(int)BarType.C2H_1], GENERIC_READ, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.C2H_2] = xdmaPath + "\\c2h_2";
            m_FileHandles[(int)BarType.C2H_2] = CreateFile(m_DriverNames[(int)BarType.C2H_2], GENERIC_READ, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.C2H_3] = xdmaPath + "\\c2h_3";
            m_FileHandles[(int)BarType.C2H_3] = CreateFile(m_DriverNames[(int)BarType.C2H_3], GENERIC_READ, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.H2C_0] = xdmaPath + "\\h2c_0";
            m_FileHandles[(int)BarType.H2C_0] = CreateFile(m_DriverNames[(int)BarType.H2C_0], GENERIC_WRITE, FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.H2C_1] = xdmaPath + "\\h2c_1";
            m_FileHandles[(int)BarType.H2C_1] = CreateFile(m_DriverNames[(int)BarType.H2C_1], GENERIC_WRITE, FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.H2C_2] = xdmaPath + "\\h2c_2";
            m_FileHandles[(int)BarType.H2C_2] = CreateFile(m_DriverNames[(int)BarType.H2C_2], GENERIC_WRITE, FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.H2C_3] = xdmaPath + "\\h2c_3";
            m_FileHandles[(int)BarType.H2C_3] = CreateFile(m_DriverNames[(int)BarType.H2C_3], GENERIC_WRITE, FILE_SHARE_WRITE, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            m_DriverNames[(int)BarType.CONTROL] = xdmaPath + "\\control";
            m_FileHandles[(int)BarType.CONTROL] = CreateFile(m_DriverNames[(int)BarType.CONTROL], GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, IntPtr.Zero, OPEN_EXISTING, 0, IntPtr.Zero);

            FillConfig("BuildResources\\current.xml", ref nodeKey, ref nodeParam);

            fillNodeList(BarType.C2H_0, NodeType.DDR4_1, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.C2H_0, NodeType.DDR4_2, ref nodeKey, ref nodeParam);

            fillNodeList(BarType.H2C_0, NodeType.DDR4_1, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.H2C_0, NodeType.DDR4_2, ref nodeKey, ref nodeParam);

            fillNodeList(BarType.C2H_0, NodeType.C2H, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.C2H_1, NodeType.C2H_1, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.C2H_2, NodeType.C2H_2, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.C2H_3, NodeType.C2H_3, ref nodeKey, ref nodeParam);

            fillNodeList(BarType.H2C_0, NodeType.H2C, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.H2C_1, NodeType.H2C_1, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.H2C_2, NodeType.H2C_2, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.H2C_3, NodeType.H2C_3, ref nodeKey, ref nodeParam);

            fillNodeList(BarType.USER, NodeType.ZERO, ref nodeKey, ref nodeParam);
            fillNodeList(BarType.CONTROL, NodeType.CONTROL, ref nodeKey, ref nodeParam);

            //nodeParam._filehandle = m_FileHandles[(int)BarType.USER];
            fillNodeList(BarType.USER, NodeType.USER, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.USER; 
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x01000000; 
            //nodeKey._operationType = OperationType.read; 
            //NodeList.Add(nodeKey, nodeParam); 
            //nodeKey._operationType = OperationType.write; 
            //NodeList.Add(nodeKey, nodeParam); 

            fillNodeList(BarType.USER, NodeType.UART_DAC, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.DAC;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x04b00000;
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.UART_FPGA, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.HOSTR;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x04b10000;
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.UART_GPS_EXT, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.EXTERN;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x04b20000;
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.UART_GPS_INT, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.INTERN;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x04b30000;
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.SPI_0, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.SPI0;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; 
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.UART_ADC12, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.ADC12;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType];
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.UART_ADC16, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.ADC16;
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType];
            //nodeKey._operationType = OperationType.read;
            //NodeList.Add(nodeKey, nodeParam);
            //nodeKey._operationType = OperationType.write;
            //NodeList.Add(nodeKey, nodeParam);

            fillNodeList(BarType.USER, NodeType.IO_BRAM, ref nodeKey, ref nodeParam);
            //nodeKey._nodeType = NodeType.IO_BRAM; 
            //nodeParam._offset = (UInt64)BaseAddressReader.CurrentReader[nodeKey._nodeType]; // 0x00000000; 
            //nodeKey._operationType = OperationType.read; 
            //NodeList.Add(nodeKey, nodeParam); 
            //nodeKey._operationType = OperationType.write; 
            //NodeList.Add(nodeKey, nodeParam); 

            //if (NodeList.ContainsKey(nodeKey))
            //{
            //    NodeParam nodeParam2 = NodeList[nodeKey];
            //    UInt64 _offset = nodeParam2._offset;
            //    IntPtr _filehandle2 = nodeParam2._filehandle;
            //}

            for (int i = 0; i < 3; i++)
                if (m_FileHandles[i] == INVALID_HANDLE_VALUE)
                    return HRESULT_FROM_WIN32(Marshal.GetLastWin32Error());

            //SortedDictionary<string, string> openWith = new SortedDictionary<string, string>();

            //byte[] InBuffer = new byte[1024];
            //byte[] OutBuffer = new byte[1024];

            //MemSet(OutBuffer, 0, OutBuffer.Length);
            //ReadMem(0, OutBuffer, 0, OutBuffer.Length);

            //MemSet(InBuffer, 0xa, InBuffer.Length);
            //WriteMem(2, InBuffer, 0, OutBuffer.Length);

            //MemSet(OutBuffer, 0, OutBuffer.Length);
            //ReadMem(1, OutBuffer, 0, OutBuffer.Length);

            return 0;
        }

        public void CloseDriver()
        {
            //if (m_FileHandle != INVALID_HANDLE_VALUE) {
            //    CloseHandle(m_FileHandle);
            //    m_FileHandle = INVALID_HANDLE_VALUE;
            //}
            for (int i = 0; i < maxnumber; i++) {
                if (m_FileHandles[i] != INVALID_HANDLE_VALUE) {
                    CloseHandle(m_FileHandles[i]);
                    m_FileHandles[i] = INVALID_HANDLE_VALUE;
                }
            }
        }

        //unsafe public int WriteMem(int index, byte[] InBuffer, UInt64 offset = 0, int size = 0)
        unsafe public int readFromFpga(byte[] buffer)
        {
            UInt64 OutBufOffset = 0;
            UInt64 OutOffset = 0;
            int OutSize = buffer.Length;

            fixed (void* OutBuffer = &buffer[0])
            {
                //CallDriver(NodeType.CONF_ROM, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                if (_fpgaDriver == null)
                    CallDriver(NodeType.CONF_ROM, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                else
                    _fpgaDriver.Read(NodeType.CONF_ROM, OutBufOffset, OutBuffer, OutOffset, OutSize);
            }

            return 0;
        }

        unsafe public int readFromEvent(byte[] buffer, int index)
        {
            UInt64 OutBufOffset = 0;
            UInt64 OutOffset = 0;
            int OutSize = buffer.Length;

            fixed (void* OutBuffer = &buffer[0])
            {
                int ret = CallDriver(NodeType.EVENT_0 + index, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                //int ret = 0;
                //if (_fpgaDriver == null)
                //    ret = CallDriver(NodeType.EVENT_0 + index, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                //else
                //    ret = _fpgaDriver.Read(NodeType.EVENT_0 + index, OutBufOffset, OutBuffer, OutOffset, OutSize);
                if (ret == 0)
                {
                    int i = 0;
                }
            }

            return 0;
        }

        unsafe public UInt64 FpgaRead(NodeType nodeType, ref byte[] buffer, UInt64 offset)
        {
            UInt64 OutBufOffset = 0;
            UInt64 OutOffset = offset;
            int OutSize = buffer.Length;

            //UInt64 InBufOffset = 0;
            //UInt64 InOffset = offset;
            //int InSize = buffer.Length;

            fixed (void* OutBuffer = &buffer[0])
            //fixed (void* InBuffer = &buffer[0])
            {
                //CallDriver(nodeType, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                int ret = 0;
                if (_fpgaDriver == null)
                    ret = CallDriver(nodeType, OperationType.read, 0, null, 0, 0, OutBufOffset, OutBuffer, OutOffset, OutSize);
                else
                    ret = _fpgaDriver.Read(nodeType, OutBufOffset, OutBuffer, OutOffset, OutSize);
            }

            return (UInt64)0;
        }

        unsafe public UInt64 FpgaWrite(NodeType nodeType, ref byte[] buffer, UInt64 offset)
        {
            //UInt64 OutBufOffset = 0;
            //UInt64 OutOffset = 0;
            //int OutSize = buffer.Length;

            UInt64 InBufOffset = 0;
            UInt64 InOffset = offset;
            int InSize = buffer.Length;

            //fixed (void* OutBuffer = &buffer[0])
            fixed (void* InBuffer = &buffer[0])
            {
                //CallDriver(nodeType, OperationType.write, InBufOffset, InBuffer, InOffset, InSize, 0, null, 0, 0);
                int ret = 0;
                if (_fpgaDriver == null)
                    ret = CallDriver(nodeType, OperationType.write, InBufOffset, InBuffer, InOffset, InSize, 0, null, 0, 0);
                else
                    ret = _fpgaDriver.Write(nodeType, InBufOffset, InBuffer, InOffset, InSize);
            }

            return (UInt64)0;
        }

        unsafe public int CallDriver(NodeType nodeType, OperationType operationType, UInt64 InBufOffset, void* InBuffer, UInt64 InOffset, int InSize,
            UInt64 OutBufOffset, void* OutBuffer, UInt64 OutOffset, int OutSize)
        {
            int ret = 1;
            int index = 0;
            //if (m_FileHandle == INVALID_HANDLE_VALUE)
            //    return HRESULT_FROM_WIN32(WindowsErrors.ERROR_PATH_NOT_FOUND);
            //if (m_FileHandles[index] == INVALID_HANDLE_VALUE)
            //    return HRESULT_FROM_WIN32(WindowsErrors.ERROR_PATH_NOT_FOUND);

            uint SizeofInBuffer = (uint)InSize;
            uint SizeofOutBuffer = (uint)OutSize;

            //bool dioc = DeviceIoControl(m_FileHandle, ControlCode, InBuffer, SizeofInBuffer, OutBuffer, SizeofOutBuffer, ref dwRet, IntPtr.Zero);
            //lpOutBuffer[out, optional]
            //A pointer to the output buffer that is to receive the data returned by the operation. The format of this data depends on the value of the dwIoControlCode parameter
            bool dioc = true;

            //if (nodeType >= NodeType.EVENT_0 && nodeType <= NodeType.EVENT_15)
            if (true)
            {
                NodeKey nodeKey = new NodeKey(nodeType, operationType);
                if (NodeList.ContainsKey(nodeKey) == true)
                {
                    NodeParam nodeParam = NodeList[nodeKey];

                    if (operationType == OperationType.read)
                        if (SizeofOutBuffer > 0) ret = ReadMem(nodeParam, OutBufOffset, OutBuffer, OutOffset, OutSize);
                    if (operationType == OperationType.write)
                        if (SizeofInBuffer > 0) ret = WriteMem(nodeParam, InBufOffset, InBuffer, InOffset, InSize);
                }
            }

            if (dioc == false)
                return HRESULT_FROM_WIN32(Marshal.GetLastWin32Error());

            return ret;
        }

        public int CallDriver(uint ControlCode, byte[] InBuffer, byte[] OutBuffer, uint anytype, UInt64 offset, int size)
        {
            int index = 0;
            //if (m_FileHandle == INVALID_HANDLE_VALUE)
            //    return HRESULT_FROM_WIN32(WindowsErrors.ERROR_PATH_NOT_FOUND);
            if (m_FileHandles[index] == INVALID_HANDLE_VALUE)
                return HRESULT_FROM_WIN32(WindowsErrors.ERROR_PATH_NOT_FOUND);

            uint dwRet = 0;
            uint SizeofInBuffer = InBuffer == null ? 0 : (uint)InBuffer.Length,
                 SizeofOutBuffer = OutBuffer == null ? 0 : (uint)OutBuffer.Length;

            //bool dioc = DeviceIoControl(m_FileHandle, ControlCode, InBuffer, SizeofInBuffer, OutBuffer, SizeofOutBuffer, ref dwRet, IntPtr.Zero);
            //lpOutBuffer[out, optional]
            //A pointer to the output buffer that is to receive the data returned by the operation. The format of this data depends on the value of the dwIoControlCode parameter.
            bool dioc = true;

            switch (anytype)
            {
                case 0:
                    {
                        if (SizeofInBuffer > 0) WriteMem(0, InBuffer, offset, size);
                        if (SizeofOutBuffer > 0) ReadMem(0, OutBuffer, offset, size);
                        break;
                    }
                case 1:
                    {
                        if (SizeofInBuffer > 0) WriteMem(2, InBuffer, offset, size);
                        if (SizeofOutBuffer > 0) ReadMem(1, OutBuffer, offset, size);
                        break;
                    }
            }

            if (dioc == false)
                return HRESULT_FROM_WIN32(Marshal.GetLastWin32Error());

            return 0;
        }

        unsafe public int CallDriver(uint ControlCode, void* InBuffer, void* OutBuffer, uint anytype, UInt64 InOffset, int InSize, UInt64 OutOffset, int OutSize)
        {
            int index = 0;
            if (m_FileHandles[index] == INVALID_HANDLE_VALUE)
                return HRESULT_FROM_WIN32(WindowsErrors.ERROR_PATH_NOT_FOUND);

            uint SizeofInBuffer = (uint)InSize;
            uint SizeofOutBuffer = (uint)OutSize;

            bool dioc = true;

            switch (anytype)
            {
                case 0:
                    {
                        if (SizeofInBuffer > 0) WriteMem(0, InBuffer, InOffset, InSize);
                        if (SizeofOutBuffer > 0) ReadMem(0, OutBuffer, OutOffset, OutSize);
                        break;
                    }
                case 1:
                    {
                        if (SizeofInBuffer > 0) WriteMem(2, InBuffer, InOffset, InSize);
                        if (SizeofOutBuffer > 0) ReadMem(1, OutBuffer, OutOffset, OutSize);
                        break;
                    }
            }

            if (dioc == false)
                return HRESULT_FROM_WIN32(Marshal.GetLastWin32Error());

            return 0;
        }

        private void findOption_events(ref string[] parameters, ref string result)
        {
            result = "";
            int index;

            if(parameters.Length > 2)
            {
                for (int i = 2; i < parameters.Length; i++)
                {
                    if (parameters[i].Contains("0x") || parameters[i].Contains("0X"))
                        index = Convert.ToByte(parameters[i], 16);
                    else
                        index = Convert.ToByte(parameters[i], 10);

                    if (index >= 0 && index < eventThreadCount)
                        startEventThreades[index] = true;
                }
            } else if (parameters.Length == 2)
            {
                for (int i = 0; i < eventThreadCount; i++)
                {
                    startEventThreades[i] = true;
                }
            } else
            {
                result = "Using \"wait event start [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]\" ";
            }
        }

        private void findOption_offset(ref string[] parameters, ref string result, ref UInt64 offset)
        {
            result = "";
            offset = 0;

            if (parameters[1] != "")
            {
                offset = Convert.ToUInt64(parameters[1], 16);
                result = "OK";
            }
            else
                result = "Using \"write <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"write <IPCORE_NAME> [OPTIONS] [DATA]\" ";
        }

        private void findOption_l(ref string[] parameters, ref string result, ref int size)
        {
            result = "";
            size = 0;

            for (int i=0; i< parameters.Length; i++)
            {
                if (parameters[i].Contains("-l") )
                {
                    result = "OK";

                    if (i + 1 < parameters.Length)
                    {
                        if (parameters[i + 1].Contains("0x") || parameters[i + 1].Contains("0X"))
                            size = Convert.ToByte(parameters[i + 1], 16);
                        else
                            size = Convert.ToByte(parameters[i + 1], 10);
                    }
                    else
                    {
                        result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                        return;
                    }
                }
            }
        }

        private void findOption_b(ref string[] parameters, ref string result, ref bool binary)
        {
            result = "";
            binary = false;

            for (int i = 0; i < parameters.Length; i++)
            {
                if (parameters[i].Contains("-b"))
                {
                    binary = true;
                    result = "OK";
                }
            }
        }
        private void findOption_h(ref string[] parameters, ref string result, ref bool hex)
        {
            result = "";
            hex = false;

            for (int i = 0; i < parameters.Length; i++)
            {
                if (parameters[i].Contains("-h"))
                {
                    hex = true;
                    result = "OK";
                }
            }
        }

        private void findOption_f(ref string[] parameters, ref string result, ref string filename)
        {
            result = "";
            filename = "";

            for (int i = 0; i < parameters.Length; i++)
            {
                if (parameters[i].Contains("-f"))
                {
                    if (i + 1 < parameters.Length)
                    {
                        filename = parameters[i + 1];
                        result = "OK";
                    }
                    else
                        result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                }
            }
        }

        private void findOption_v(ref string[] parameters, ref string result, ref bool verbose)
        {
            result = "";
            verbose = false;

            for (int i = 0; i < parameters.Length; i++)
            {
                if (parameters[i].Contains("-v"))
                {
                    verbose = true;
                    result = "OK";
                }
            }
        }

        private void findOption_a(ref string[] parameters, ref string result, ref int alignment)
        {
            result = "";
            alignment = 0;

            for (int i = 0; i < parameters.Length; i++)
            {
                if (parameters[i].Contains("-a"))
                {
                    if (i + 1 < parameters.Length)
                    {
                        result = "OK";
                        if (parameters[i + 1].Contains("0x") || parameters[i + 1].Contains("0X"))
                            alignment = Convert.ToByte(parameters[i + 1], 16);
                        else
                            alignment = Convert.ToByte(parameters[i + 1], 10);
                    }
                    else
                    {
                        result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                        return;
                    }
                }
            }
        }

        private void readFromFile(string filename, bool binary, bool hex, ref byte[] buffer, ref string result)
        {
            result = "";

            try
            {
                Directory.SetCurrentDirectory(currentDirectory);

                if (binary == false)
                {
                    string text = File.ReadAllText(filename, Encoding.UTF8);

                    string[] values = text.Split(" ");

                    int Length = 0;
                    foreach (string value in values)
                    {
                        if (value.Length > 0) Length++;
                    }

                    buffer = new byte[Length];

                    int index = 0;
                    if(hex == false)
                    {
                        foreach (string value in values)
                        {
                            if (value.Length > 0)
                            {
                                if (value.Contains("0x") || value.Contains("0X"))
                                    buffer[index] = Convert.ToByte(value, 16);
                                else
                                    buffer[index] = Convert.ToByte(value, 10);

                                ++index;
                            }
                        }
                    }
                    else
                    {
                        foreach (string value in values)
                        {
                            if (value.Length == 2)
                            {
                                //if (value.Contains("0x") || value.Contains("0X"))
                                //    buffer[index] = Convert.ToByte(value, 16);
                                //else
                                //    buffer[index] = Convert.ToByte(value, 10);

                                buffer[index] = Convert.ToByte(value, 16);

                                ++index;
                            }
                        }
                    }

                    result = "OK";
                }
                else
                {
                    buffer = File.ReadAllBytes(filename);

                }

            }
            catch (IOException e) //FileLoadException
            {
                string message = e.Message;
            }
        }

        private void writeToFile(string filename, bool binary, bool hex, UInt64 offset, ref byte[] buffer, ref string result)
        {
            result = "";

            try
            {
                Directory.SetCurrentDirectory(currentDirectory);

                if (binary == false)
                {
                    StringBuilder textBuilder = new StringBuilder("");

                    if (hex == false)
                    {
                        for (int i = 0; i < buffer.Length; i++)
                        {
                            textBuilder.Append(String.Format("0x{0, 2:X2}", buffer[i]));
                            textBuilder.Append(" ");
                        }
                    }
                    else
                    {
                        UInt64 rowlenth = 16;
                        UInt64 rowcount = (UInt64)buffer.Length / rowlenth;
                        UInt64 partlength = (UInt64)buffer.Length % rowlenth;

                        UInt64 r;
                        for (r = 0; r < rowcount; r++)
                        {
                            textBuilder.Append(String.Format("0x{0, 8:X8}", (offset + r * rowlenth)));
                            textBuilder.Append(" : ");
                            for (UInt64 i = 0; i < rowlenth; i++)
                            {
                                //textBuilder.Append(String.Format("0x{0, 2:X2}", buffer[i + r * rowlenth]));
                                textBuilder.Append(String.Format("{0, 2:X2}", buffer[i + r * rowlenth]));
                                textBuilder.Append(" ");
                            }
                            textBuilder.Append("\n");
                        }
                        if (partlength > 0)
                        {
                            textBuilder.Append(String.Format("0x{0, 8:X8}", (offset + r * rowlenth)));
                            textBuilder.Append(" : ");
                            for (UInt64 i = 0; i < partlength; i++)
                            {
                                //textBuilder.Append(String.Format("0x{0, 2:X2}", buffer[i + r * rowlenth]));
                                textBuilder.Append(String.Format("{0, 2:X2}", buffer[i + r * rowlenth]));
                                textBuilder.Append(" ");
                            }
                            textBuilder.Append("\n");
                        }
                    }

                    File.WriteAllText(filename, textBuilder.ToString());

                } else
                {
                    BinaryWriter writer = new BinaryWriter(File.Open(filename, FileMode.Create));
                    for (int i = 0; i < buffer.Length; i++)
                    {
                        writer.Write(buffer[i]);
                    }
                    writer.Close();
                }
            }
            catch (IOException e) //FileLoadException
            {
                string message = e.Message;
            }
        }

        private void doReadCommand(NodeType nodeType, UInt64 offset, ref string[] parameters, ref byte[] buffer, ref string result, int index)
        {
            int start = 1 + index;
            int size = 0;
            bool binary = false;
            bool hex = false;
            string filename = "";
            bool verbose = false;
            int alignment = 0;

            findOption_l(ref parameters, ref result, ref size);
            if (result == "OK") start += 2;
            findOption_b(ref parameters, ref result, ref binary);
            if (result == "OK") start += 1;
            findOption_h(ref parameters, ref result, ref hex);
            if (result == "OK") start += 1;
            findOption_f(ref parameters, ref result, ref filename);
            if (result == "OK") start += 2;
            findOption_v(ref parameters, ref result, ref verbose);
            if (result == "OK") start += 1;
            findOption_a(ref parameters, ref result, ref alignment);
            if (result == "OK") start += 2;

            if (filename.Length > 0)
            {
                buffer = new byte[size];

                FpgaRead(nodeType, ref buffer, offset);

                writeToFile(filename, binary, hex, offset, ref buffer, ref result);
            }
            else
            {
                buffer = new byte[size];

                FpgaRead(nodeType, ref buffer, offset);
            }

            return;
        }

        private void doWriteCommand(NodeType nodeType, UInt64 offset, ref string[] parameters, ref string result, int index)
        {
            int start = 1 + index;
            int size = 0;
            bool binary = false;
            bool hex = false;
            string filename = "";
            bool verbose = false;
            int alignment = 0;

            findOption_l(ref parameters, ref result, ref size);
            if (result == "OK") start += 2;
            findOption_b(ref parameters, ref result, ref binary);
            if (result == "OK") start += 1;
            findOption_h(ref parameters, ref result, ref hex);
            if (result == "OK") start += 1;
            findOption_f(ref parameters, ref result, ref filename);
            if (result == "OK") start += 2;
            findOption_v(ref parameters, ref result, ref verbose);
            if (result == "OK") start += 1;
            findOption_a(ref parameters, ref result, ref alignment);
            if (result == "OK") start += 2;

            if (filename.Length > 0)
            {
                byte[] buffer = null;

                readFromFile(filename, binary, hex, ref buffer, ref result);

                FpgaWrite(nodeType, ref buffer, offset);
            }
            else {
                int Length = 0;
                foreach (string param in parameters)
                {
                    if (param.Length > 0) Length++;
                }
                if (size == 0) size = Length - start;
                if (Length == start + size)
                {
                    byte[] buffer = new byte[size];
                    for (int i = 0; i < size; i++)
                    {
                        if (parameters[start + i].Contains("0x") || parameters[start + i].Contains("0X"))
                            buffer[i] = Convert.ToByte(parameters[start + i], 16);
                        else
                            buffer[i] = Convert.ToByte(parameters[start + i], 10);
                    }
                    FpgaWrite(nodeType, ref buffer, offset);
                }
                else
                {
                    result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                }
            }

            return;
        }

#if Console_Xdma

        //public Thread _handleEventThread;

        //private static void ThreadEvent(object data)
        unsafe private void ThreadEvent(object data)
        {
            DateTime l_D = DateTime.Now;
            TimeSpan l_T;
            bool l_bQueueFlag = false;

            //Console.WriteLine("ThreadEvent id = " + data.ToString());
            Console.WriteLine("Input in ThreadEvent() id = {0}", (int)data);

            if (stopEventThreades.ContainsKey((int)data))
            {
                byte[] buffer = new byte[1];

                while (stopEventThreades[(int)data] == false)
                {
                    //Thread.Sleep(128);
                    //Console.WriteLine("Cycle in ThreadEvent() id = {0}", (int)data);

                    if(readFromEvent(buffer, (int)data) == 0) 
                    { 
                        if (buffer[0].ToString() == "1") { 
                            m_Pipe.Print("Event_" + ((int)data).ToString() + " set " ); 
                        } 
                    } 
                }

            }

            m_Pipe.Print("<<<>>> Exit from ThreadEvent() id = " + ((int)data).ToString() );
            Console.WriteLine("<<<>>> Exit from ThreadEvent() id = {0}", (int)data);
        }

        private string ChangePropertyWait(string[] parameters)
        {
            string result = "OK";

            foreach (Thread eventThread in eventThreades)
            {
                ;
            }

            if (parameters.Length > 0 && parameters[0] != "")
            {
                if (parameters[0] == "event")
                {
                    if(parameters[1] == "start")
                    {
                        for (int i = 0; i < eventThreadCount; i++)
                        {
                            if(stopEventThreades[i] == false)
                            {
                                if (handleEventThreades[i] != null)
                                {
                                    stopEventThreades[i] = true;
                                    handleEventThreades[i].Join();
                                }
                            }
                        }

                        CloseEventDriver();

                        findOption_events(ref parameters, ref result);

                        OpenEventDriver();

                        for (int i = 0; i < eventThreadCount; i++)
                        {
                            if (startEventThreades[i] == true)
                            {
                                if (stopEventThreades[i] == true)
                                {
                                    stopEventThreades[i] = false;

                                    ////_handleEventThread = new Thread(new ThreadStart(ThreadAction));
                                    //_handleEventThread = new Thread(new ParameterizedThreadStart(ThreadEvent));
                                    ////eventThreades.Add(_handleEventThread);
                                    //handleEventThreades[i] = _handleEventThread;
                                    handleEventThreades[i] = new Thread(new ParameterizedThreadStart(ThreadEvent));
                                    //_handleEventThread = new Thread(WindowsDriverXdma.ThreadEvent);
                                    ////_handleEventThread.Priority = ThreadPriority.Highest;
                                    //stopEventThreades[i] = false;

                                    //Thread.Sleep(1);

                                    //_handleEventThread.Start(i);
                                    handleEventThreades[i].Start(i);
                                }
                            }
                        }
                    } else if (parameters[1] == "stop")
                    {
                        for (int i = 0; i < eventThreadCount; i++)
                        {
                            if (stopEventThreades[i] == false)
                            {
                                stopEventThreades[i] = true;
                                handleEventThreades[i].Join();
                            }
                        }

                        CloseEventDriver();
                    }
                }
            }
            else
            {
                result = "Using \"wait event [DATA]\" ";
            }

            return result;
        }

        private string ChangePropertyRead(string[] parameters)
        {
            string result = "OK";

            if (parameters.Length > 0 && parameters[0] != "")
            {
                //if (parameters[0] == "user" || parameters[0].Contains("c2h") || parameters[0].Contains("ddr4") || parameters[0] == "control")
                if (parameters[0] == "user" || parameters[0].Contains("c2h") || parameters[0] == "control")
                {
                    //<DEVNODE> <ADDR> [OPTIONS] [DATA]
                    UInt64 offset = 0;
                    findOption_offset(ref parameters, ref result, ref offset);

                    if (result == "OK")
                    {
                        NodeType nodeType = NodeType.ZERO;
                        //if (parameters[0].Contains("user"))
                        //    nodeType = NodeType.USER;
                        //else 
                        if (parameters[0].Contains("c2h_1"))
                            nodeType = NodeType.C2H_1;
                        else if (parameters[0].Contains("c2h_2"))
                            nodeType = NodeType.C2H_2;
                        else if (parameters[0].Contains("c2h_3"))
                            nodeType = NodeType.C2H_3;
                        else if (parameters[0].Contains("c2h"))
                            nodeType = NodeType.C2H; //C2H_0 = 0, // client to host - read
                        else if (parameters[0] == "control")
                            nodeType = NodeType.CONTROL;
                        else if (parameters[0] == "ddr4_1")
                            nodeType = NodeType.DDR4_1;
                        else if (parameters[0] == "ddr4_2")
                            nodeType = NodeType.DDR4_2;

                        doReadCommand(nodeType, offset, ref parameters, ref buffer, ref result, 1); //[OPTIONS]

                        StringBuilder text = new StringBuilder("");
                        for (int i = 0; i < buffer.Length; i++)
                        {
                            text.Append(String.Format("0x{0, 2:X2}", buffer[i]));
                            text.Append(" ");
                        }
                        result = text.ToString();
                    }
                    else
                    {
                        result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                    }
                }
                else
                {
                    //<IPCORE_NAME> [OPTIONS] [DATA]
                    NodeType nodeType = (NodeType)BaseAddressReader.CurrentReader[parameters[0]];
                    UInt64 offset = (UInt64)BaseAddressReader.CurrentReader[nodeType];

                    if (nodeType == NodeType.C2H || nodeType == NodeType.H2C)
                        nodeType = NodeType.C2H; //C2H_0 = 0, // client to host - read
                    else
                        nodeType = NodeType.ZERO;

                    doReadCommand(nodeType, offset, ref parameters, ref buffer, ref result, 0); //[OPTIONS]

                    StringBuilder text = new StringBuilder("");
                    for (int i = 0; i < buffer.Length; i++)
                    {
                        text.Append(String.Format("0x{0, 2:X2}", buffer[i]));
                        text.Append(" ");
                    }
                    result = text.ToString();
                }
            }
            else
            {
                result = "Using \"read <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"read <IPCORE_NAME> [OPTIONS] [DATA]\" ";
            }

            return result;
        }

        private string ChangePropertyWrite(string[] parameters)
        {
            string result = "OK";

            if (parameters.Length > 0 && parameters[0] != "")
            {
                //if (parameters[0] == "user" || parameters[0].Contains("h2c") || parameters[0] == "control")
                if (parameters[0] == "user" || parameters[0].Contains("h2c") || parameters[0].Contains("ddr4"))
                {
                    //<DEVNODE> <ADDR> [OPTIONS] [DATA]
                    UInt64 offset = 0;
                    findOption_offset(ref parameters, ref result, ref offset);

                    if (result == "OK")
                    {
                        NodeType nodeType = NodeType.ZERO; 
                        //if (parameters[0].Contains("user")) 
                        //    nodeType = NodeType.USER;
                        //else 
                        if (parameters[0].Contains("h2c_1"))
                            nodeType = NodeType.H2C_1;
                        else if (parameters[0].Contains("h2c_2"))
                            nodeType = NodeType.H2C_2;
                        else if (parameters[0].Contains("h2c_3")) 
                            nodeType = NodeType.H2C_3; 
                        else if (parameters[0].Contains("h2c")) 
                            nodeType = NodeType.H2C; //H2C_0 = 1,  // host to client - write 
                        //else if ( parameters[0].Contains("control") ) 
                        //    nodeType = NodeType.CONTROL;
                        else if (parameters[0] == "ddr4_1")
                            nodeType = NodeType.DDR4_1;
                        else if (parameters[0] == "ddr4_2")
                            nodeType = NodeType.DDR4_2;

                        doWriteCommand(nodeType, offset, ref parameters, ref result, 1); //[OPTIONS]
                    }
                    else
                    {
                        result = "Using \"write <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"write <IPCORE_NAME> [OPTIONS] [DATA]\" ";
                    }
                }
                else
                {
                    //<IPCORE_NAME> [OPTIONS] [DATA]
                    NodeType nodeType = (NodeType)BaseAddressReader.CurrentReader[parameters[0]];
                    UInt64 offset = (UInt64)BaseAddressReader.CurrentReader[nodeType];

                    if (nodeType == NodeType.C2H || nodeType == NodeType.H2C)
                        nodeType = NodeType.H2C; //H2C_0 = 1,  // host to client - write
                    else
                        nodeType = NodeType.ZERO;

                    doWriteCommand(nodeType, offset, ref parameters, ref result, 0); //[OPTIONS]
                }
            }
            else
            {
                result = "Using \"write <DEVNODE> <ADDR> [OPTIONS] [DATA]\" or \"write <IPCORE_NAME> [OPTIONS] [DATA]\" ";
            }

            return result;
        }

        // --- command for test --- 

        //write user 0x05020000 -l 8 0xBE 0xBA 0xCE 0xCA 0xDE 0xDA 0xFE 0xFA 
        //read user 0x05020000 -l 8 
        //write io_bram -l 8 0xFE 0xFA 0xDE 0xDA 0xCE 0xCA 0xBE 0xBA 
        //read io_bram -l 8 
        //write h2c_0 0x0 -l 8 0xBE 0xB1 0xCE 0xC2 0xDE 0xD3 0xFE 0xF4 
        //read c2h_0 0x0 -l 8 

        //read user 0x05020000 -l 32 -f data3_r.txt
        //read user 0x05020000 -l 32 -b -f data3_r.bin
        //read user 0x05020000 -l 47 -h -f data3_r.hex
        //write user 0x05020000 -l 32 -f data3_w.txt
        //write user 0x05020000 -l 32 -b -f data3_w.bin
        //write user 0x05020000 -l 47 -h -f data3_r.hex

        //read control 0x0 -l 32

        //wait event start 
        //wait event stop 

        // --- other command --- 

        //read io_bram -l 8 
        //write io_bram -l 8 01 02 03 04 03 02 01 f5 
        //write io_bram -l 8 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xc7 
        //write io_bram -l 8 0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 
        //read user 0x05020000 -l 8 
        //write user 0x05020000 -l 8 01 02 03 04 03 02 01 f5 
        //write user 0x05020000 -l 8 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xf5 
        //write user 0x05020000 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xf5 

        //read user 0x05020000 -l 16 -f data_r.txt
        //read user 0x05020000 -l 16 -b -f data_r.bin

        //xdma_rw user write 0x05020000 0xc3 0xb2 0xa1 0x04 0x03 0x02 0x01 0xf5
        //xdma_rw user write 0x05020000 - l 8  0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 

        //xdma_rw c2h_0 read 0x0 -l 8 
        //xdma_rw user read 0x05020000 -l 8 
        //xdma_rw user write 0x05020000 -l 8  0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 
        //write user 0x05020000 -l 8 01 02 03 04 03 02 01 15 
        //write user 0x05020000 -l 8 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xf1 
        //write io_bram -l 8 0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 
        //write h2c_0 0x0 -l 8 01 02 03 04 03 02 01 15 
        //read c2h_0 0x0 -l 8 

        //write user 0x05020000 -l 8 01 02 03 04 03 02 01 15 

        //read io_bram -l 8 
        //write io_bram -l 8 01 02 03 04 03 02 01 f5 
        //write io_bram -l 8 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xc7 
        //write io_bram -l 8 0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 
        //read user 0x05020000 -l 8 
        //write user 0x05020000 -l 8 01 02 03 04 03 02 01 f5 
        //write user 0x05020000 -l 8 0xb1 0xc2 0xd3 0xa4 0xb3 0xc2 0xd1 0xe5 

        //read control 0x0 -l 8 

        //xdma_rw user read 0x05020000 -l 8 
        //xdma_rw user write 0x05020000 -l 8  0x04 0x03 0x02 0x01 0x00 0x01 0x02 0xc2 
        //xdma_rw control read 0x0 -l 8 

        //write user 0x05020000 0x01 0x02 0x03 0x04 0x03 0x02 0x01 0xf5 

        //read ddr4_1 -l 8

#endif

        public bool IsInitialized()
        {
            int index = 0;
            //return m_FileHandle != INVALID_HANDLE_VALUE;
            return m_FileHandles[index] != INVALID_HANDLE_VALUE;
        }

        public IntPtr GetDriverHandle()
        {
            int index = 0;
            return m_FileHandles[index];
        }

        /// Private stuff:
        private const uint GENERIC_READ = 0x80000000;
        private const uint GENERIC_WRITE = 0x40000000;
        private const uint GENERIC_EXECUTE = 0x20000000;
        private const uint GENERIC_ALL = 0x10000000;
        private const uint FILE_SHARE_READ = 1;
        private const uint FILE_SHARE_WRITE = 2;
        private const uint OPEN_EXISTING = 3;
        private const uint FILE_ATTRIBUTE_NORMAL = 128;
        private const uint IOCTL_SHOCKMGR_READ_ACCELEROMETER_DATA = 0x733fc;
        private const int  FACILITY_WIN32 = unchecked((int)0x80000000);

        [DllImport("kernel32", SetLastError = true)]
        private static extern IntPtr CreateFile(string lpFileName, uint dwDesiredAccess, uint dwShareMode, IntPtr lpSecurityAttributes, 
                                                uint dwCreationDisposition, uint dwFlagsAndAttributes, IntPtr hTemplateFile);

        [DllImport("kernel32")]
        private static extern void CloseHandle(IntPtr handle);

        [DllImport("kernel32", SetLastError = true)]
        private static extern bool DeviceIoControl(IntPtr hDevice, uint dwIoControlCode, 
                                                   byte[] lpInBuffer, uint nInBufferSize, 
                                                   byte[] lpOutBuffer, uint nOutBufferSize, 
                                                   ref uint lpBytesReturned, IntPtr lpOverlapped);

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern IntPtr SetupDiGetClassDevs( ref Guid ClassGuid,
                                                IntPtr Enumerator, //[MarshalAs(UnmanagedType.LPTStr)] string Enumerator,
                                                IntPtr hwndParent,
                                                uint Flags );

        [StructLayout(LayoutKind.Explicit)]
        public struct SYSTEM_INFO_UNION
        {
            [FieldOffset(0)]
            public UInt32 OemId;
            [FieldOffset(0)]
            public UInt16 ProcessorArchitecture;
            [FieldOffset(2)]
            public UInt16 Reserved;
        }

        [StructLayout(LayoutKind.Sequential, Pack = 1)]
        public struct SYSTEM_INFO
        {
            public SYSTEM_INFO_UNION CpuInfo;
            public UInt32 PageSize;
            public UInt32 MinimumApplicationAddress;
            public UInt32 MaximumApplicationAddress;
            public UInt32 ActiveProcessorMask;
            public UInt32 NumberOfProcessors;
            public UInt32 ProcessorType;
            public UInt32 AllocationGranularity;
            public UInt16 ProcessorLevel;
            public UInt16 ProcessorRevision;
        }

        [DllImport("kernel32.dll", SetLastError = false)]
        public static extern void GetSystemInfo(out SYSTEM_INFO Info);

        [StructLayout(LayoutKind.Sequential)]
        struct SP_DEVINFO_DATA
        {
            public UInt32 cbSize;
            public Guid ClassGuid;
            public UInt32 DevInst;
            public IntPtr Reserved;
        }
        [StructLayout(LayoutKind.Sequential)]
        struct SP_DEVICE_INTERFACE_DATA
        {
            public Int32 cbSize;
            public Guid interfaceClassGuid;
            public Int32 flags;
            private UIntPtr reserved;
        }
        [StructLayout(LayoutKind.Sequential, CharSet = CharSet.Auto, Pack = 1)]
        struct NativeDeviceInterfaceDetailData
        {
            public int size;
            public char devicePath;
        }

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern Boolean SetupDiEnumDeviceInterfaces(
           IntPtr hDevInfo,
           IntPtr devInfo,
           ref Guid interfaceClassGuid,
           UInt32 memberIndex,
           ref SP_DEVICE_INTERFACE_DATA deviceInterfaceData
        );

        [DllImport("setupapi.dll", SetLastError = true)]
        private static extern bool SetupDiDestroyDeviceInfoList
        (
             IntPtr DeviceInfoSet
        );

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern Boolean SetupDiGetDeviceInterfaceDetail(
           IntPtr hDevInfo,
           ref SP_DEVICE_INTERFACE_DATA deviceInterfaceData,
           //ref SP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData,
           IntPtr deviceInterfaceDetailData,
           UInt32 deviceInterfaceDetailDataSize,
           ref UInt32 requiredSize,
           //ref SP_DEVINFO_DATA deviceInfoData
           IntPtr deviceInfoData
        );

        [DllImport("setupapi.dll", SetLastError = true, CharSet = CharSet.Auto)]
        private static extern Boolean SetupDiGetDeviceInterfaceDetail(
           IntPtr hDevInfo,
           ref SP_DEVICE_INTERFACE_DATA deviceInterfaceData,
           ref SP_DEVICE_INTERFACE_DETAIL_DATA deviceInterfaceDetailData,
           //IntPtr deviceInterfaceDetailData,
           UInt32 deviceInterfaceDetailDataSize,
           //ref UInt32 requiredSize,
           IntPtr requiredSize,
           //ref SP_DEVINFO_DATA deviceInfoData
           IntPtr deviceInfoData
        );

        [DllImport("kernel32.dll", SetLastError = true)]
        static extern bool SetFilePointerEx(IntPtr hFile, UInt64 liDistanceToMove, IntPtr lpNewFilePointer, uint dwMoveMethod);

        [DllImport("kernel32.dll")]
        static extern uint GetLastError();

        [DllImport("msvcrt.dll", EntryPoint = "memset", CallingConvention = CallingConvention.Cdecl, SetLastError = true)]
        //public static extern IntPtr MemSet(IntPtr dest, int c, int byteCount);
        //public static extern byte[] MemSet(byte[] dest, int c, int byteCount);
        public static extern void MemSet(byte[] dest, int c, int byteCount);

        [System.Runtime.InteropServices.DllImport("kernel32", SetLastError = true)]
        static extern unsafe bool ReadFile(System.IntPtr hFile,  void* pBuffer, int NumberOfBytesToRead, int* pNumberOfBytesRead, int Overlapped);

        [System.Runtime.InteropServices.DllImport("kernel32", SetLastError = true)]
        static extern unsafe bool WriteFile(System.IntPtr hFile, void* pBuffer, int NumberOfBytesToRead, int* pNumberOfBytesRead, int Overlapped);

        private int HRESULT_FROM_WIN32(WindowsErrors error)
        {
            return HRESULT_FROM_WIN32((int)error);
        }

        private static int HRESULT_FROM_WIN32(int x)
        {
            return x <= 0 ? x : ((x & 0x0000FFFF) | FACILITY_WIN32);
        }
    }
}
