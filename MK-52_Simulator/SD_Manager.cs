//////////////////////////////////////////////////////////
//
//  MK-52 RESURRECT
//  Copyright (c) 2020 Mike Yakimov.  All rights reserved.
//  See main file for the license
//
//////////////////////////////////////////////////////////

using System;
using System.Collections.Generic;
using System.Text;
using System.IO;

namespace MK52Simulator
{
    public class SD_Manager
    {
        private Dictionary<string, DirectoryInfo> _directoryListing
            = new Dictionary<string, DirectoryInfo>();
        private Dictionary<string, FileInfo> _fileListing
            = new Dictionary<string, FileInfo>();
        private List<string> _itemListing = new List<string>();

        private string _current_Dir_Name = "C:/";
        private string _current_File_Name = "";
        private DateTime _lastDirectoryRead = DateTime.MinValue; // Windows-only

        public string StatusFileName = "";

        public const byte _LF_ = 10;
        public const byte _CR_ = 13;

        public bool SDMounted = false; // fake for simulator only
        public UInt64 cardSize = 4000000000L; // fake for simulator only
        public int listingPosition = -1;
        public int _nDirs = 0;
        public int _nItems = 0;

        public bool _current_File_open = false;
        public StreamReader __sr = null;
        public StreamWriter __sw = null;
        public FileStream __fs = null;
        public string __text = "";
        
        public void init()
        {
            _clearItems();
            _current_Dir_Name = Directory.GetParent(Environment.GetFolderPath(Environment.SpecialFolder.ApplicationData)).FullName;
            //if ( Environment.OSVersion.Version.Major >= 6 )
            //    _current_Dir_Name = Directory.GetParent(_current_Dir_Name).ToString();
            SDMounted = Directory.Exists(_current_Dir_Name);
            if (!SDMounted) return;
            _current_Dir_Name += "\\MK52Simulator";
            if (!Directory.Exists(_current_Dir_Name))
                Directory.CreateDirectory(_current_Dir_Name);
            SDMounted = Directory.Exists(_current_Dir_Name);
            StatusFileName = _current_Dir_Name + "\\_MK52_Status.DAT";
            _current_Dir_Name = _current_Dir_Name.Replace('\\', '/');
            setFolder_P(_current_Dir_Name);
        }

        public string getFolderName()
        {
            return _current_Dir_Name;
        }

        public string getWindowsFolderName()
        {
            return _current_Dir_Name.Replace('/', '\\');
        }

        public string getWindowsFileName()
        {
            return _current_File_Name.Replace('/', '\\');
        }

        public string getFolderNameTruncated( int n)
        {
            int ln = _current_Dir_Name.Length;
            if( ln >= n-1)
            {
                return _current_Dir_Name.Substring(ln - n + 1) + "/";
            }
            return _current_Dir_Name + "/";
        }

        public void nextListingPosition()
        {
            if (_nItems <= 0)
            {
                listingPosition = -1;
                return;
            }
            listingPosition++;
            if (listingPosition >= _nItems) listingPosition = _nItems - 1;
        }

        public void previousListingPosition()
        {
            if (_nItems <= 0)
            {
                listingPosition = -1;
                return;
            }
            listingPosition--;
            if (listingPosition < 0) listingPosition = 0;
        }
        
        public bool isAtFolder()
        {
            return listingPosition <_nDirs;
        }

        /// <summary>
        /// Gets an item from selector
        /// This is Windows-only implementation
        /// </summary>
        /// <returns></returns>
        public string getItemFromListing()
        {
            _current_File_Name = "";
            if( listingPosition<0 || listingPosition >= _nItems) return _current_File_Name;
            string searchKey = _itemListing[listingPosition];
            if (_directoryListing.ContainsKey(searchKey))
                _current_File_Name = _directoryListing[searchKey].FullName;
            if (_fileListing.ContainsKey(searchKey))
                _current_File_Name = _fileListing[searchKey].FullName; 
            return _current_File_Name;
        }

        //abstract public void checkRootExists();

        public bool checkEntityExists(string name)
        {
            name = name.Replace( '/', '\\');
            return File.Exists(name) || Directory.Exists(name);
        }
        
        public string makeEntityName( string name)
        {
            StringBuilder sb = new StringBuilder();
            if (name.Length <= 0) return sb.ToString(); // no name given
            sb.Append(_current_Dir_Name);
            sb.Append('/');
            sb.Append(name);
            return sb.ToString();
        }

        public string getItemString(int n)
        {
            if (n >= _itemListing.Count) return "";
            return _itemListing[n];
        }

        public void setFolder(string name)
        {
            setFolder_P(name);
        }

        public void setFolder_P(string name)
        {
            _current_Dir_Name = name.Replace('\\', '/');
            readFolderItems();
        }

        public void readFolderItems()
        {
            readFolderItems("", true);
        }

        public void readFolderItems(string location, bool resetListingPosition)
        {
            if( !SDMounted) return;
            _clearItems();
            if (resetListingPosition) listingPosition = -1;
            if( !checkEntityExists(_current_Dir_Name)) return;
            string wdn = getWindowsFolderName();
            if (!Directory.Exists(wdn)) return;
            DirectoryInfo root = new DirectoryInfo(wdn);
            DirectoryInfo[] dis = root.GetDirectories();
            foreach (DirectoryInfo di in dis)
            {
                string en = _formEntityName(di);
                if( _directoryListing.ContainsKey( en)) continue;
                _directoryListing[en] = di;
            }
            FileInfo[] fis = root.GetFiles();
            foreach (FileInfo fi in fis)
            {
                string en = _formEntityName(fi);
                if (_fileListing.ContainsKey(en)) continue;
                _fileListing[en] = fi;
            }
            List<string> tmp = new List<string>();
            foreach (string s in _directoryListing.Keys)tmp.Add(s);
            tmp.Sort();
            foreach (string s in tmp) _itemListing.Add(s);
            _nDirs = _itemListing.Count;
            tmp.Clear();
            foreach (string s in _fileListing.Keys) tmp.Add(s);
            tmp.Sort();
            foreach (string s in tmp) _itemListing.Add(s);
            _nItems = _itemListing.Count;
            if (location.Length == 0)
            {
                if (listingPosition < 0 && _nItems > 0) listingPosition = 0;
                if (listingPosition >= _nItems) listingPosition = _nItems - 1; 
                return;
            }
            for (int i = 0; i < _nDirs; i++)
            {
                if (!_itemListing[i].StartsWith(location)) continue;
                listingPosition = i;
                break;
            }
        }

        /// <summary>
        /// In Windows, we re-read the folder once in a while, as other processes may add files/folders
        /// </summary>
        /// <param name="Lines"></param>
        /// <param name="nLines"></param>
        /// <param name="lineLen"></param>
        /// <returns></returns>
        public string[] getFolderListing(string[] Lines, int nLines, int lineLen)
        {
            if (DateTime.Now - _lastDirectoryRead > TimeSpan.FromSeconds(10.0))
            {
                readFolderItems("", false);
                _lastDirectoryRead = DateTime.Now;
            }
            return getFolderListing( Lines, nLines, lineLen, null);
        }

        public string[] getFolderListing(string[] Lines, int nLines, int lineLen, string name)
        {
            if( SDMounted)
                Lines[0] = getFolderNameTruncated( LCD_Manager.SCREEN_COLS-1);
            else
                Lines[0] = "Insert SD card and reboot";
            int startLine = 0;
            int stopLine = nLines - 2;
            if (listingPosition > stopLine)
            {
                startLine = listingPosition - stopLine;
                stopLine += startLine;
            }
            for ( int i = 1; i < nLines; i++, startLine++)
            {
                Lines[i] = (startLine == listingPosition) ? "\u00ac ": "  ";
                Lines[i] += getItemString(startLine);
            }
            return Lines;
        }

        public void setListingPosition( int pos)
        {
            listingPosition = ( pos>=_nItems)? _nItems-1: pos;
        }

        /// <summary>
        /// Simulator-only (ESP32 is recursive)
        /// </summary>
        /// <param name="name"></param>
        /// <returns></returns>
        public bool deleteEntity(string name)
        {
            if( !SDMounted) return true;
            if( name.Length < 3) return false;
            if (Directory.Exists(name))
            {
                try
                {
                    Directory.Delete(name, true);
                    return false;
                }
                catch
                {
                    return true;
                }
            }
            if (File.Exists(name))
            {
                try
                {
                    File.Delete(name);
                    return false;
                }
                catch
                {
                    return true;
                }
            }
            return false;
        }

        public void createFolder(string name)
        {
            if( !SDMounted) return;
            if(name.Length <= 0) return; // no name given
            __text = makeEntityName( name);
            string tmp = __text.Replace('/', '\\');
            try
            {
                if( !Directory.Exists( tmp)) Directory.CreateDirectory(tmp);
                setFolder( __text);
            }
            catch
            {
            }
        }

        public void upFolder()
        {
            if( !SDMounted) return;
            if (_current_Dir_Name.Length <= 2) return; // already at root
            int index = _current_Dir_Name.LastIndexOf('/');
            if (index < 2) return;
            _current_File_Name = _current_Dir_Name.Substring(index+1);
            _current_Dir_Name = _current_Dir_Name.Substring(0, index);
            readFolderItems( _current_File_Name, true);
        }

        /// <summary>
        /// Steps into a folder or executes a file
        /// </summary>
        /// <param name="name"></param>
        /// <returns>returns true if a run is required</returns>
        public bool stepIn(string name)
        {
            if( !SDMounted) return false;
            if( Directory.Exists( name.Replace('/', '\\')))
            {
                setFolder( name);
                return false;
            }
            return true;
        }

        /// <summary>
        /// Simulates ESP32 SD utilities
        /// </summary>
        /// <param name="path">Fake "Linux" file name</param>
        /// <param name="write">true to write</param>
        /// <returns>True if an error</returns>
        public bool openFile(string path, bool write)
        {
            return openFile_P(path, write);
        }

        /// <summary>
        /// Simulates ESP32 SD utilities
        /// </summary>
        /// <param name="path">Windows file name</param>
        /// <param name="write">true to write</param>
        /// <returns>True if an error</returns>
        public bool openFile_P(string path, bool write)
        {
            if( !SDMounted) return true;
            closeFile();
            if( path.Length == 0){
                if( isAtFolder()) return true;
                path = getItemFromListing();
            }
            if( path.Length < 4 ) return true; // cannot overwrite root, e.g. C:\
            try
            {
                if (write)
                {
                    __fs = File.Open(path, FileMode.Create, FileAccess.Write, FileShare.Read);
                    __sw = new StreamWriter(__fs);
                }
                else
                {
                    __fs = File.Open(path, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
                    __sr = new StreamReader(__fs);
                }
                _current_File_Name = path.Replace('\\', '/');
                _current_File_open = true;
                return false;
            }
            catch
            {
                closeFile();
            }
            return true;
        }

        public void closeFile()
        {
            if( __sr != null)
            {
                __sr.Close();
                __sr = null;
            }
            if( __sw != null)
            {
                __sw.Close();
                __sw = null;
            }
            if( __fs != null)
            {
                __fs.Close();
                __fs = null;
            }
            _current_File_open = false;
        }

        public bool print(string message)
        {
            if( !SDMounted) return true;
            if( !_current_File_open) return true;
            try
            {
                __sw.Write(message);
            }
            catch
            {
                return true;
            }
            return false;
        }

        public bool print_P(string message)
        {
            return print(message);
        }

        public bool println(string message)
        {
            if( !SDMounted) return true;
            if( !_current_File_open) return true;
            try
            {
                __sw.WriteLine( message);
            }
            catch
            {
                return true;
            }
            return false;
        }

        public bool println_P(string message)
        {
            return println( message);
        }

        public bool read(string buffer, int n)
        {
            __text = "";
            if (!SDMounted) return true;
            if (!_current_File_open) return true;
            StringBuilder sb = new StringBuilder();
            while (n > 0 && !__sr.EndOfStream)
            {
                sb.Append((char)__sr.Read());
                n--;
            }
            __text = sb.ToString();
            return n > 0; // not all symbols read - file end
        }

        public bool readln( string buffer, int n)
        {
            __text = "";
            if (!SDMounted) return true;
            if (!_current_File_open) return true;
            byte b = 0;
            StringBuilder sb = new StringBuilder();
            while (!__sr.EndOfStream)
            {
                b = (byte)__sr.Read(); // to match ESP32 method
                if (b == _CR_) continue;
                if (b == _LF_) break;
                if (n > 0)
                {
                    sb.Append((char)b);
                    n--;
                }
            }
            __text = sb.ToString();
            return __sr.EndOfStream;
        }

        private void _clearItems()
        {
            _nDirs = 0;
            _nItems = 0;
            _directoryListing .Clear();
            _fileListing.Clear();
            _itemListing.Clear();
        }

        /// <summary>
        /// C++ dummy
        /// </summary>
        private int _locateAlphabetic(string name, bool isDir)
        {
            return 0;
        }

        /// <summary>
        /// C++ dummy
        /// </summary>
        private bool _insertItem(string name, int pos, int slot, bool isDir)
        {
            return true;
        } 
        
        private string _formEntityName(DirectoryInfo f)
        {
            StringBuilder sb = new StringBuilder();
            string name = f.Name;
            int nameLen = name.Length;
            if( nameLen > LCD_Manager.SCREEN_COLS - 9) nameLen = LCD_Manager.SCREEN_COLS - 9;
            sb.Append( name.Substring( 0, nameLen));
            while( sb.Length < LCD_Manager.SCREEN_COLS - 9) sb.Append(' ');
            sb.Append( " [DIR]");
            return sb.ToString();
        }

        private string _formEntityName(FileInfo f)
        {
            StringBuilder sb = new StringBuilder();
            string name = f.Name;
            int nameLen = name.Length;
            if (nameLen > LCD_Manager.SCREEN_COLS - 9) nameLen = LCD_Manager.SCREEN_COLS - 9;
            sb.Append(name.Substring(0, nameLen));
            while (sb.Length < LCD_Manager.SCREEN_COLS - 9) sb.Append(' ');
            sb.Append(_appendFileSize(f));
            return sb.ToString();
        }

        private string _appendFileSize(FileInfo f)
        {
            long size = f.Length;
            StringBuilder sb = new StringBuilder();
            sb.Append(' ');
            if (size < 8192L)
            {
                sb.Append( size.ToString("0000"));
                sb.Append('b');
                return sb.ToString();
            }
            size >>= 10;
            if (size < 8192L)
            {
                sb.Append(size.ToString("0000"));
                sb.Append('k');
                return sb.ToString();
            }
            size >>= 10;
            if (size < 8192L)
            {
                sb.Append(size.ToString("0000"));
                sb.Append('M');
                return sb.ToString();
            }
            size >>= 10;
            sb.Append(size.ToString("0000"));
            sb.Append('G');
            return sb.ToString();
        }
    }
}
