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
    //
    // Implements a register entry
    //
    public class Receiver_Register_A : Receiver_Register
    {
        public const uint _Off = 0;
        public const uint _MX = 1;
        public const uint _XM = 2;
        public const uint _KMX = 3;
        public const uint _KXM = 4;

        /// <summary>
        /// Inputs register name in the auto mode
        /// </summary>
        public Receiver_Register_A(MK52_Host parent)
            : base( parent)
        {
            Moniker = "REGISTER_A";
        }

        public override void setMode(uint mode)
        {
            if (mode > _KXM) mode = _Off;
            this._mode = mode;
        }

        protected override void completeEntry( string value)
        {
            Register_Memory rm = _parent._m_Register_Memory;
            switch (_mode)
            {
                case _MX:
                    rm.MtoX( value);
                    break;
                case _XM:
                    rm.XtoM( value);
                    break;
                case _KMX:
                    rm.K_MtoX( value);
                    break;
                case _KXM:
                    rm.K_XtoM( value);
                    break;
                default:
                    break;
            }
            _mode = _Off;
        }
    }
}
