//===- BashAliasPrinter.cpp - BashAliasPrinter TableGen backend          -*- C++ -*-===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This Tablegen backend emits ...
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringExtras.h"
#include "llvm/Support/Format.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/TableGen/Error.h"
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/TableGenBackend.h"
#include <algorithm>
#include <set>
#include <string>
#include <vector>

#define DEBUG_TYPE "bash-alias-printer"

using namespace llvm;

namespace {

// Any helper data structures can be defined here. Some backends use
// structs to collect information from the records.

class BashAliasPrinter {
private:
  RecordKeeper &Records;

public:
  BashAliasPrinter(RecordKeeper &RK) : Records(RK) {}

  void run(raw_ostream &OS);
}; // emitter class

} // anonymous namespace

void BashAliasPrinter::run(raw_ostream &OS) {
  emitSourceFileHeader("BashAliasPrinter data structures", OS);

   OS << "#=======Bash aliases=======\n";

   auto Steps = Records.getAllDerivedDefinitions("BashAliases");

   for (auto* SIRecord : Steps) {
     
     if (SIRecord->getValueAsBit("hasArg") == false) {

       OS <<"alias " ;
       OS << SIRecord->getValueAsString("Name");
       OS <<"=";
       OS << SIRecord->getValueAsString("Command") << "\n";
     }
     else {
      OS << SIRecord->getValueAsString("Name") << "(){\n";
      OS << SIRecord->getValueAsString("Command") << "\n";
      OS << "}\n";
     }
   }

//  (void)Records; // To suppress unused variable warning; remove on use.
}

namespace llvm {

// The only thing that should be in the llvm namespace is the
// emitter entry point function.

void EmitBashAliasPrinter(RecordKeeper &RK, raw_ostream &OS) {
  // Instantiate the emitter class and invoke run().
  BashAliasPrinter(RK).run(OS);
}

} // namespace llvm
