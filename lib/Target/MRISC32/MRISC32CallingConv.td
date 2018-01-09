//===- MRISC32CallingConv.td - Calling Conventions for MRISC32 -*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
// This describes the calling conventions for MRISC32 architecture.
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
// MRISC32 Return Value Calling Convention
//===----------------------------------------------------------------------===//
def RetCC_MRISC32 : CallingConv<[
  // Promote all integer types with < 32 bits to i32.
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  // i32 and f32 are returned in registers S1-S8.
  CCIfType<[i32, f32], CCAssignToReg<[S1, S2, S3, S4, S5, S6, S7, S8]>>,

  // Remaining i32:s and f32:s get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i32, f32], CCAssignToStack<4, 4>>,

  // i64:s and f64:s always get stored in stack slots that are 8 bytes in size
  // and 8-byte aligned.
  // TODO(m): We should pass 64-bit values in register pairs instead.
  CCIfType<[i64, f64], CCAssignToStack<8, 8>>
]>;

//===----------------------------------------------------------------------===//
// MRISC32 Argument Calling Conventions
//===----------------------------------------------------------------------===//
def CC_MRISC32 : CallingConv<[
  // Promote all integer types with < 32 bits to i32.
  CCIfType<[i1, i8, i16], CCPromoteToType<i32>>,

  // The 'nest' parameter, if any, is passed in S9.
  // TODO(m): What is this?
  //CCIfNest<CCAssignToReg<[S9]>>,

  // i32 and f32 are passed in registers S1-S8.
  CCIfType<[i32, f32], CCAssignToReg<[S1, S2, S3, S4, S5, S6, S7, S8]>>,

  // Remaining i32:s and f32:s get stored in stack slots that are 4 bytes in
  // size and 4-byte aligned.
  CCIfType<[i32, f32], CCAssignToStack<4, 4>>,

  // i64:s and f64:s always get stored in stack slots that are 8 bytes in size
  // and 8-byte aligned.
  // TODO(m): We should pass 64-bit values in register pairs instead.
  CCIfType<[i64, f64], CCAssignToStack<8, 8>>
]>;

//===----------------------------------------------------------------------===//
// MRISC32 Callee saved registers
//===----------------------------------------------------------------------===//
def CSR_MRISC32 : CalleeSavedRegs<
  (add
    // LR, VL.
    LR, VL,

    // FP, TP, SP are implicitly saved?

    // S16-S25.
    (sequence "S%u", 16, 25)
  )>;

