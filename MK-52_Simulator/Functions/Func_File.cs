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

    //public class Func_Load : RPN_Function
    //{
    //    public override bool checkID(uint id)
    //    {
    //        return id == RPN_Functions.FUNC_LOAD;
    //    }
    //    public override void execute(MK52_Host components, string command)
    //    {
    //        components.getFunctions().loadProgram();
    //    }
    //}

    public class Func_Load : RPN_Function
    {
        public override bool checkID(uint id)
        {
            return id == RPN_Functions.FUNC_LOAD;
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
            components.getFunctions().loadProgram(command);
        }
    }
}
