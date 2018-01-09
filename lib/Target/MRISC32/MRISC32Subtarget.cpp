//===-- MRISC32Subtarget.cpp - MRISC32 Subtarget Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the MRISC32 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "MRISC32Subtarget.h"
#include "MRISC32.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "mrisc32-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "MRISC32GenSubtargetInfo.inc"

void MRISC32Subtarget::anchor() {}

MRISC32Subtarget &
MRISC32Subtarget::initializeSubtargetDependencies(StringRef CPU, StringRef FS) {
  UseSoftMulDiv = true;
  UseSoftFloat = true;

  // Determine default and user specified characteristics
  std::string CPUName = CPU;
  if (CPUName.empty())
    CPUName = "v1";

  // Parse features string.
  ParseSubtargetFeatures(CPUName, FS);

  return *this;
}

MRISC32Subtarget::MRISC32Subtarget(const Triple &TT, const std::string &CPU,
                                   const std::string &FS,
                                   const TargetMachine &TM)
    : MRISC32GenSubtargetInfo(TT, CPU, FS), TargetTriple(TT),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this),
      FrameLowering(*this) {}
