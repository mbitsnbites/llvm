//===-- MRISC32RegisterInfo.td - MRISC32 Register defs -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the MRISC32 register files
//===----------------------------------------------------------------------===//

let Namespace = "MRISC32" in {

class MRISC32Reg<bits<5> Enc, string n, list<string> alt = []> : Register<n> {
  let HWEncoding{4-0} = Enc;
  let AltNames = alt;
}

def ABIRegAltName : RegAltNameIndex;

}  // Namespace = "MRISC32"


//===----------------------------------------------------------------------===//
// Integer registers
//===----------------------------------------------------------------------===//

let RegAltNameIndices = [ABIRegAltName] in {

def Z   : MRISC32Reg<0,  "z", ["s0"]>,   DwarfRegNum<[0]>;
def S1  : MRISC32Reg<1,  "s1">,          DwarfRegNum<[1]>;
def S2  : MRISC32Reg<2,  "s2">,          DwarfRegNum<[2]>;
def S3  : MRISC32Reg<3,  "s3">,          DwarfRegNum<[3]>;
def S4  : MRISC32Reg<4,  "s4">,          DwarfRegNum<[4]>;
def S5  : MRISC32Reg<5,  "s5">,          DwarfRegNum<[5]>;
def S6  : MRISC32Reg<6,  "s6">,          DwarfRegNum<[6]>;
def S7  : MRISC32Reg<7,  "s7">,          DwarfRegNum<[7]>;
def S8  : MRISC32Reg<8,  "s8">,          DwarfRegNum<[8]>;
def S9  : MRISC32Reg<9,  "s9">,          DwarfRegNum<[9]>;
def S10 : MRISC32Reg<10, "s10">,         DwarfRegNum<[10]>;
def S11 : MRISC32Reg<11, "s11">,         DwarfRegNum<[11]>;
def S12 : MRISC32Reg<12, "s12">,         DwarfRegNum<[12]>;
def S13 : MRISC32Reg<13, "s13">,         DwarfRegNum<[13]>;
def S14 : MRISC32Reg<14, "s14">,         DwarfRegNum<[14]>;
def S15 : MRISC32Reg<15, "s15">,         DwarfRegNum<[15]>;
def S16 : MRISC32Reg<16, "s16">,         DwarfRegNum<[16]>;
def S17 : MRISC32Reg<17, "s17">,         DwarfRegNum<[17]>;
def S18 : MRISC32Reg<18, "s18">,         DwarfRegNum<[18]>;
def S19 : MRISC32Reg<19, "s19">,         DwarfRegNum<[19]>;
def S20 : MRISC32Reg<20, "s20">,         DwarfRegNum<[20]>;
def S21 : MRISC32Reg<21, "s21">,         DwarfRegNum<[21]>;
def S22 : MRISC32Reg<22, "s22">,         DwarfRegNum<[22]>;
def S23 : MRISC32Reg<23, "s23">,         DwarfRegNum<[23]>;
def S24 : MRISC32Reg<24, "s24">,         DwarfRegNum<[24]>;
def S25 : MRISC32Reg<25, "s25">,         DwarfRegNum<[25]>;
def FP  : MRISC32Reg<26, "fp", ["s26"]>,         DwarfRegNum<[26]>;
def TP  : MRISC32Reg<27, "tp", ["s27"]>, DwarfRegNum<[27]>;
def SP  : MRISC32Reg<28, "sp", ["s28"]>, DwarfRegNum<[28]>;
def VL  : MRISC32Reg<29, "vl", ["s29"]>, DwarfRegNum<[29]>;
def LR  : MRISC32Reg<30, "lr", ["s30"]>, DwarfRegNum<[30]>;
def PC  : MRISC32Reg<31, "pc", ["s31"]>, DwarfRegNum<[31]>;

}  // RegAltNameIndices = [ABIRegAltName]


//===----------------------------------------------------------------------===//
// Register classes
//===----------------------------------------------------------------------===//

def GPR : RegisterClass<"MRISC32", [i32], 32,
  (add
    //===------------------------------------------------------------------===//
    // Allocatable registers
    //===------------------------------------------------------------------===//

    // Arguments and return values.
    (sequence "S%u", 1, 8),

    // Temporaries (caller saves).
    (sequence "S%u", 9, 15),

    // Preserved across procedure calls (callee saves).
    (sequence "S%u", 16, 25),

    //===------------------------------------------------------------------===//
    // Non-allocatable registers
    //===------------------------------------------------------------------===//

    // Special registers: fp, tp, sp
    FP, TP, SP,

    // Special registers: vl, lr
    VL, LR,

    // Read-only registers: z, pc
    Z, PC
  )>;

