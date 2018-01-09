//===-- MRISC32TargetMachine.cpp - Define TargetMachine for MRISC32 -------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "MRISC32TargetMachine.h"
#include "MRISC32.h"
#include "MRISC32TargetObjectFile.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeMRISC32Target() {
  // Register the target.
  RegisterTargetMachine<MRISC32TargetMachine> X(getTheMRISC32Target());
}

static std::string computeDataLayout(const Triple &T) {
  return "e-m:e-p:32:32-i64:64-n32-S128";
}

static Reloc::Model getEffectiveRelocModel(const Triple &TT,
                                           Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

static CodeModel::Model getEffectiveCodeModel(Optional<CodeModel::Model> CM) {
  if (CM)
    return *CM;
  return CodeModel::Small;
}

MRISC32TargetMachine::MRISC32TargetMachine(
    const Target &T, const Triple &TT, StringRef CPU, StringRef FS,
    const TargetOptions &Options, Optional<Reloc::Model> RM,
    Optional<CodeModel::Model> CM, CodeGenOpt::Level OL, bool JIT, bool is64bit)
    : LLVMTargetMachine(
          T, computeDataLayout(TT), TT, CPU, FS, Options,
          getEffectiveRelocModel(TT, RM),
          getEffectiveCodeModel(CM),
          OL),
      TLOF(make_unique<MRISC32ELFTargetObjectFile>()),
      Subtarget(TT, CPU, FS, *this, is64bit) {
  initAsmInfo();
}

namespace {
/// MRISC32 Code Generator Pass Configuration Options.
class MRISC32PassConfig : public TargetPassConfig {
public:
  MRISC32PassConfig(MRISC32TargetMachine &TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  MRISC32TargetMachine &getMRISC32TargetMachine() const {
    return getTM<MRISC32TargetMachine>();
  }

  bool addInstSelector() override;
};
} // namespace

TargetPassConfig *MRISC32TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new MRISC32PassConfig(*this, PM);
}

bool MRISC32PassConfig::addInstSelector() {
  addPass(createMRISC32ISelDag(getMRISC32TargetMachine()));
  return false;
}

