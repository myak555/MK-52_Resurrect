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
            _SDM(components).createFolder(command);
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
            _SDM(components).upFolder();
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
            _SDM(components).nextListingPosition();
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
            _SDM(components).previousListingPosition();
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

        public override void execute(MK52_Host components, string command)
        {
            SD_Manager sd = components.getSD();
            sd.deleteEntity(sd.getItemFromListing());
            int tmp = sd.listingPosition;
            sd.readFolderItems();
            sd.setListingPosition(tmp);
        }
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

        public override void execute(MK52_Host components, string command)
        {
            SD_Manager sd = _SDM(components);
            string filename = sd.getItemFromListing();
            if( !sd.stepIn( filename)) return;
            RPN_Functions _rpnf = components.getFunctions();
            if( UniversalValue._endsWith_P( filename, ".DAT"))
                _rpnf.loadData( filename);
            else
                _rpnf.loadProgram( filename);
        }
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

        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveProgram();
        }
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

        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveProgram(command);
        }
    }

    public class Func_Load : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOAD;
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadProgram();
        }
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
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadProgram( command);
        }
    }

    public class Func_SaveData : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEDATA;
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveData();
        }
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
            return "SAVEDATA ";
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveData( command);
        }
    }

    public class Func_LoadData : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADDATA;
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadData(command);
        }
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
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadData(command);
        }
    }

    public class Func_SaveAll : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEALL;
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveAll(command);
        }
    }

    public class Func_SaveAllTo : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_SAVEALLTO;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "SAVEALL ";
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().saveAll(command);
        }
    }
    
    public class Func_LoadAll : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADALL;
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadAll(command);
        }
    }

    public class Func_LoadAllFrom : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOADALLFROM;
        }
        public override bool checkName(string name)
        {
            return UniversalValue._startsWith_P(name, Name());
        }
        public override string Name()
        {
            return "LOADALL ";
        }
        public override void execute(MK52_Host components, string command)
        {
            components.getFunctions().loadAll(command);
        }
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
        public override void execute(MK52_Host components, string command)
        {
            // TODO
            components.getFunctions().loadProgram(command);
        }
    }
}
