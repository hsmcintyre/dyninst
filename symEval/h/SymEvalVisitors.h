/*
 * Copyright (c) 2007-2009 Barton P. Miller
 * 
 * We provide the Paradyn Parallel Performance Tools (below
 * described as "Paradyn") on an AS IS basis, and do not warrant its
 * validity or performance.  We reserve the right to update, modify,
 * or discontinue this software at any time.  We shall have no
 * obligation to supply such updates or modifications or any other
 * form of support to you.
 * 
 * By your use of Paradyn, you understand and agree that we (or any
 * other person or entity with proprietary rights in Paradyn) are
 * under no obligation to provide either maintenance services,
 * update services, notices of latent defects, or correction of
 * defects for Paradyn.
 * 
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * 
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#if !defined(_SYM_EVAL_VISITORS_H_)
#define _SYM_EVAL_VISITORS_H_

#include "dyninstAPI/src/stackanalysis.h"
#include "dynutil/h/AST.h"
#include "symEval/h/Absloc.h"
#include "SymEvalPolicy.h"
#include <string>

// A collection of visitors for SymEval AST classes

namespace Dyninst {
namespace SymbolicEvaluation {

class StackVisitor : public ASTVisitor {
 public:
    StackVisitor(std::string funcname,
		 StackAnalysis::Height &stackHeight,
		 StackAnalysis::Height &frameHeight) :
    func_(funcname), stack_(stackHeight), frame_(frameHeight) {};

    virtual AST::Ptr visit(AST *);
    virtual AST::Ptr visit(IntAST *);
    virtual AST::Ptr visit(FloatAST *);
    virtual AST::Ptr visit(BottomAST *);
    virtual AST::Ptr visit(ConstantAST *);
    virtual AST::Ptr visit(AbsRegionAST *);
    virtual AST::Ptr visit(RoseAST *);
    virtual AST::Ptr visit(StackAST *);
  
  virtual ~StackVisitor() {};

  private:
  std::string func_;
  StackAnalysis::Height stack_;
  StackAnalysis::Height frame_;
};

class StackEquivalenceVisitor : public ASTVisitor {
 public:
  StackEquivalenceVisitor() {};
  void addPair(AbsRegion &old, AbsRegion &n) {
    repl[old] = n;
  }
  
  virtual AST::Ptr visit(AST *);
  virtual AST::Ptr visit(IntAST *);
  virtual AST::Ptr visit(FloatAST *);
  virtual AST::Ptr visit(BottomAST *);
  virtual AST::Ptr visit(ConstantAST *);
  virtual AST::Ptr visit(AbsRegionAST *);
  virtual AST::Ptr visit(RoseAST *);
  virtual AST::Ptr visit(StackAST *);
  
  virtual ~StackEquivalenceVisitor() {};

 private:
  std::map<AbsRegion, AbsRegion> repl;
};

};
};

#endif