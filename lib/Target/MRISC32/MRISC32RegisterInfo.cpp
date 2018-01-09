//===-- MRISC32RegisterInfo.cpp - MRISC32 Register Information --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the MRISC32 implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "MRISC32RegisterInfo.h"
#include "MRISC32.h"
#include "MRISC32Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/CodeGen/TargetFrameLowering.h"
#include "llvm/CodeGen/TargetInstrInfo.h"
#include "llvm/Support/ErrorHandling.h"

#define GET_REGINFO_TARGET_DESC
#include "MRISC32GenRegisterInfo.inc"

using namespace llvm;

MRISC32RegisterInfo::MRISC32RegisterInfo(unsigned HwMode)
    : MRISC32GenRegisterInfo(MRISC32::LR,  // RA (return address)
                             0,            // DwarfFlavour
                             0,            // EHFlavor
                             MRISC32::PC,  // PC
                             HwMode) {}

const MCPhysReg *
MRISC32RegisterInfo::getCalleeSavedRegs(const MachineFunction * /*MF*/) const {
  return CSR_MRISC32_SaveList;
}

const uint32_t *
MRISC32RegisterInfo::getCallPreservedMask(const MachineFunction & /*MF*/,
                                          CallingConv::ID /*CC*/) const {
  return CSR_MRISC32_RegMask;
}

BitVector MRISC32RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());

  // These registers are always reserved.
  markSuperRegs(Reserved, MRISC32::Z);
  markSuperRegs(Reserved, MRISC32::TP);
  markSuperRegs(Reserved, MRISC32::SP);
  markSuperRegs(Reserved, MRISC32::VL);
  markSuperRegs(Reserved, MRISC32::LR);
  markSuperRegs(Reserved, MRISC32::PC);

  // Reserve the frame pointer if necessary.
  const MRISC32FrameLowering *TFI = getFrameLowering(MF);
  if (TFI->hasFP(MF)) {
    markSuperRegs(Reserved, MRISC32::FP);
  }

  assert(checkAllSuperRegsMarked(Reserved));
  return Reserved;
}

unsigned MRISC32RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  // Use FP as the frame pointer when enabled, else the stack pointer.
  // TODO(m): Should we really fall back to the SP, or should we assert?
  const MRISC32FrameLowering *TFI = getFrameLowering(MF);
  return TFI->hasFP(MF) ? MRISC32::FP : MRISC32::SP;
}

void MRISC32RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                              int SPAdj, unsigned FIOperandNum,
                                              RegScavenger *RS) const {
  // TODO(m): Implement this correctly!

  assert(SPAdj == 0 && "Unexpected non-zero SPAdj value");

  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  int FrameIndex = MI.getOperand(FIOperandNum).getIndex();
  unsigned FrameReg;
  int Offset =
      getFrameLowering(MF)->getFrameIndexReference(MF, FrameIndex, FrameReg) +
      MI.getOperand(FIOperandNum + 1).getImm();

  assert(MF.getSubtarget().getFrameLowering()->hasFP(MF) &&
         "eliminateFrameIndex currently requires hasFP");

  MI.getOperand(FIOperandNum).ChangeToRegister(FrameReg, false);
  MI.getOperand(FIOperandNum + 1).ChangeToImmediate(Offset);
}

