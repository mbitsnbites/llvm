//===-- MRISC32.td - Describe the MRISC32 Target Machine ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This is the top level entry point for the MRISC32 target.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// Descriptions
//===----------------------------------------------------------------------===//

include "MRISC32RegisterInfo.td"
//include "MRISC32InstrInfo.td"
include "MRISC32CallingConv.td"

//def MRISC32InstrInfo : InstrInfo;

//===----------------------------------------------------------------------===//
// MRISC32 processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",      []>;

//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def MRISC32 : Target {
  // Pull in Instruction Info:
  //let InstructionSet = MRISC32InstrInfo;
}
