//===-- MRISC32TargetMachine.h - Define TargetMachine for MRISC32 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the MRISC32 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MRISC32_MRISC32TARGETMACHINE_H
#define LLVM_LIB_TARGET_MRISC32_MRISC32TARGETMACHINE_H

#include "MRISC32InstrInfo.h"
#include "MRISC32Subtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class MRISC32TargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  MRISC32Subtarget Subtarget;

public:
  MRISC32TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, Optional<CodeModel::Model> CM,
                     CodeGenOpt::Level OL, bool JIT);

  const MRISC32Subtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};

} // end namespace llvm

#endif
