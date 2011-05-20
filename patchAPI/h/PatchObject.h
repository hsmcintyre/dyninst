/* Plugin Interface */

#ifndef PATCHAPI_H_DYNINST_OBJECT_H_
#define PATCHAPI_H_DYNINST_OBJECT_H_

#include "common.h"

namespace Dyninst {
namespace PatchAPI {

class PatchFunction;

/* PatchObject represents a binary object, which could be either a library or
   executable. It is also an instrumentation  unit. */
class PatchObject {
  friend class AddrSpace;

  public:
    virtual ~PatchObject();
    static void destroy(PatchObject* obj);

    typedef std::vector<PatchFunction *> funclist;
    typedef std::map<ParseAPI::Function *, PatchFunction *> FuncMap;

    // Getters and setter
    Address codeBase() { return codeBase_; }

    ParseAPI::CodeObject* co() const { return co_; }
    ParseAPI::CodeSource* cs() const { return cs_; }

    AddrSpacePtr addrSpace() const { return addr_space_; }
    void setAddrSpace(AddrSpacePtr as) { addr_space_ = as; }

    FuncMap& funcMap() { return funcMap_; }

    PatchFunction *getFunc(ParseAPI::Function *);
    void addFunc(PatchFunction*);
    void removeFunc(PatchFunction*);

    // Called by Instrumenter
    virtual bool instrument(InstanceSet* /*insertion_set*/,
                         InstanceSet* /*deletion_set*/,
                         FuncRepMap*  /*func_rep*/,
                         CallRepMap*  /*call_rep*/,
                         CallRemoval* /*call_remove*/) = 0;

  protected:
    ParseAPI::CodeObject* co_;
    ParseAPI::CodeSource* cs_;
    Address codeBase_;
    AddrSpacePtr addr_space_;
    FuncMap funcMap_;

    PatchObject(ParseAPI::CodeObject* o, Address a);
    PatchObject(const PatchObject* par_obj, Address a);
};

}
}

#endif  // PATCHAPI_H_DYNINST_MODULE_H_
