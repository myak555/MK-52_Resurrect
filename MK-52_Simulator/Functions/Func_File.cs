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

namespace MK52Simulator
{
    public class Func_MkDir : RPN_Function
    {
        public Func_MkDir()
        {
            Description = "Creates a folder";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_MKDIR;
        }

        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }

        public override string Name()
        {
            return "MKDIR ";
        }

        public override void execute(MK52_Host components, string command)
        {
            //_SDM(components).createFolder(command);
        }
    }

    public class Func_UpDir : RPN_Function
    {
        public Func_UpDir()
        {
            Description = "Moves one directory up (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_UPDIR;
        }

        public override void execute(MK52_Host components, string command)
        {
            //_SDM(components).upFolder();
        }
    }

    public class Func_NextFile : RPN_Function
    {
        public Func_NextFile()
        {
            Description = "Move pointer to the next file (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_NEXTFILE;
        }

        public override void execute(MK52_Host components, string command)
        {
            //_SDM(components).nextListingPosition();
        }
    }

    public class Func_PrevFile : RPN_Function
    {
        public Func_PrevFile()
        {
            Description = "Moves pointer to the previous file (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_PREVFILE;
        }

        public override void execute(MK52_Host components, string command)
        {
            //_SDM(components).previousListingPosition();
        }
    }

    public class Func_Remove : RPN_Function
    {
        public Func_Remove()
        {
            Description = "Deletes a file or a folder";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_REMOVE;
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_StepIn : RPN_Function
    {
        public Func_StepIn()
        {
            Description = "Steps into a folder";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_STEPIN;
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_Save : RPN_Function
    {
        public Func_Save()
        {
            Description = "Saves a file (UI-only)";
        }

        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVE;
        }

        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_SaveAs : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEAS;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "SAVE AS ";
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_Load : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOAD;
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_LoadFrom : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADFROM;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "LOAD ";
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_SaveData : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEDATA;
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_SaveDataAs : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEDATAAS;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "SAVE DATA AS ";
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_LoadData : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADDATA;
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_LoadDataFrom : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADDATAFROM;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "LOADDATA ";
        }
        public override void execute(MK52_Host components, string command) { }
    }

    public class Func_Chain : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_CHAIN;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "CHAIN ";
        }
        public override void execute(MK52_Host components, string command) { }
    }
}
