set(LLVM_TARGET_DEFINITIONS MRISC32.td)

#tablegen(LLVM MRISC32GenRegisterInfo.inc -gen-register-info)
#tablegen(LLVM MRISC32GenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM MRISC32GenDisassemblerTables.inc -gen-disassembler)
#tablegen(LLVM MRISC32GenMCCodeEmitter.inc -gen-emitter)
#tablegen(LLVM MRISC32GenAsmWriter.inc -gen-asm-writer)
#tablegen(LLVM MRISC32GenAsmMatcher.inc -gen-asm-matcher)
#tablegen(LLVM MRISC32GenDAGISel.inc -gen-dag-isel)
#tablegen(LLVM MRISC32GenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM MRISC32GenCallingConv.inc -gen-callingconv)
#add_public_tablegen_target(MRISC32CommonTableGen)

add_llvm_target(MRISC32CodeGen
  #MRISC32AsmPrinter.cpp
  #MRISC32InstrInfo.cpp
  #MRISC32ISelDAGToDAG.cpp
  #MRISC32ISelLowering.cpp
  #MRISC32FrameLowering.cpp
  #MRISC32MachineFunctionInfo.cpp
  #MRISC32RegisterInfo.cpp
  MRISC32Subtarget.cpp
  MRISC32TargetMachine.cpp
  #MRISC32MCInstLower.cpp
  #MRISC32TargetObjectFile.cpp
  )

#add_subdirectory(TargetInfo)
#add_subdirectory(MCTargetDesc)
#add_subdirectory(InstPrinter)
#add_subdirectory(AsmParser)
#add_subdirectory(Disassembler)
