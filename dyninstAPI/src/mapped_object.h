/*
 * Copyright (c) 1996-2011 Barton P. Miller
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

// $Id: mapped_object.h,v 1.23 2008/10/27 17:23:53 mlam Exp $

#if !defined(_mapped_object_h)
#define _mapped_object_h

#include <string>
#include "common/h/Types.h"
#include "dyninstAPI/src/symtab.h"
#include "dyninstAPI/h/BPatch_enums.h"
#include <list>
#include "dyninstAPI/src/Relocation/DynObject.h"

class block_instance;
class func_instance;
class edge_instance;

//  we really do not want to have this defined, but I'm defining it for the moment to get thru paradyn seperation
#define CHECK_ALL_CALL_POINTS  // we depend on this for Paradyn

using namespace Dyninst;

class mapped_module;

class int_symbol {
 public:
    int_symbol(SymtabAPI::Symbol *sym, Address base) : addr_(base + sym->getOffset()), sym_(sym) {}
    int_symbol() : addr_(0), sym_(NULL) {};

    Address getAddr() const { return addr_; }
    unsigned getSize() const { return sym_->getSize(); }
    const string &symTabName() const { return sym_->getMangledName(); }
    const string &prettyName() const { return sym_->getPrettyName(); }
    const string &typedName() const { return sym_->getTypedName(); }
    const SymtabAPI::Symbol *sym() const { return sym_; }

 private:
    Address addr_;
    const SymtabAPI::Symbol *sym_;
};


class int_variable {
    // Should subclass this and function off the same thing...

 private:
    int_variable() {};
 public:
    int_variable(image_variable *var, 
                 Address base,
                 mapped_module *mod);

    int_variable(int_variable *parVar, mapped_module *child);

    Address getAddress() const { return addr_; }
    // Can variables have multiple names?
    const string &symTabName() const;
    const vector<string>& prettyNameVector() const;
    const vector<string>& symTabNameVector() const;
    mapped_module *mod() const { return mod_; };
    //AddressSpace *as() const { return mod()->proc(); }
    const image_variable *ivar() const { return ivar_; }

    Address addr_;
    unsigned size_;
    // type?
    image_variable *ivar_;

    mapped_module *mod_;
};

struct edgeStub {
    edgeStub(block_instance *s, Address t, EdgeTypeEnum y) 
    { src = s; trg = t; type = y; }
    block_instance* src;
    Address trg;
    EdgeTypeEnum type;
};


/*
 * A class for link map information about a shared object that is mmapped 
 * by the dynamic linker into the applications address space at runtime. 
 */
#define 	SHAREDOBJECT_NOCHANGE	0
#define 	SHAREDOBJECT_ADDED	1
#define 	SHAREDOBJECT_REMOVED	2

// mapped_object represents a file in memory. It will be a collection
// of modules (basically, .o's) that are referred to as a unit and
// loaded as a unit.  The big reason for this is 1) per-process
// specialization and 2) a way to reduce memory; to create objects for
// all functions ahead of time is wasteful and expensive. So
// basically, the mapped_object "wins" if it can return useful
// information without having to allocate memory.

class mapped_object : public codeRange, public Dyninst::PatchAPI::DynObject {
    friend class mapped_module; // for findFunction
    friend class func_instance;
    friend class block_instance; // Adds to codeRangesByAddr_
    friend class edge_instance;

 private:
    mapped_object();
    mapped_object(fileDescriptor fileDesc, 
                  image *img,
                  AddressSpace *proc,
                  BPatch_hybridMode mode = BPatch_normalMode);

 public:
    // We need a way to check for errors; hence a "get" method
    static mapped_object *createMappedObject(fileDescriptor &desc,
                                             AddressSpace *p,
                                             BPatch_hybridMode m = BPatch_normalMode,
                                             bool parseGaps = true);

    // Copy constructor: for forks
    mapped_object(const mapped_object *par_obj, process *child);

    // Will delete all func_instances which were originally part of this object; including 
    // any that were relocated (we can always follow the "I was relocated" pointer).
    ~mapped_object();

    bool analyze();
    bool isAnalyzed() { return analyzed_; }

    const fileDescriptor &getFileDesc() const { return desc_; }
    // Full name, including path
    const string &fullName() const { return fullName_; }
    const string &fileName() const { return fileName_; }
    Address codeAbs() const { return codeBase() + imageOffset(); }
    Address codeBase() const { return codeBase_; }
    Address imageOffset() const { return parse_img()->imageOffset(); }
    unsigned imageSize() const { return parse_img()->imageLength(); }
    unsigned memoryEnd(); // largest allocated memory address + 1

    // Deprecated...
    Address getBaseAddress() const { return codeBase(); }

    Address dataAbs() const { return dataBase() + dataOffset(); }
    Address dataBase() const { return dataBase_; }
    Address dataOffset() const { return parse_img()->dataOffset(); }
    unsigned dataSize() const { return parse_img()->dataLength(); }

    image *parse_img() const { return image_; }
    bool isSharedLib() const;
    bool isStaticExec() const;
    static bool isSystemLib(const std::string &name);
    bool isMemoryImg() const { return memoryImg_; }

    void setMemoryImg() { memoryImg_ = true; };

    // Return an appropriate identification string for debug purposes.
    // Will eventually be required by a debug base class.
    const std::string debugString() const;

    // Used for codeRange ONLY! DON'T USE THIS! BAD USER!
    Address get_address() const { return codeAbs(); }
    void *get_local_ptr() const;
    unsigned get_size() const { return imageSize(); }

    AddressSpace *proc() const;

    mapped_module *findModule(string m_name, bool wildcard = false);
    mapped_module *findModule(pdmodule *mod);

    mapped_module *getDefaultModule();

    func_instance *findFuncByEntry(const Address addr);
    func_instance *findFuncByEntry(const block_instance *blk);

    void getInferiorHeaps(vector<pair<string, Address> > &infHeaps);

    bool findFuncsByAddr(const Address addr, std::set<func_instance *> &funcs);
    bool findBlocksByAddr(const Address addr, std::set<block_instance *> &blocks);
    block_instance *findBlockByEntry(const Address addr);
    block_instance *findOneBlockByAddr(const Address addr);
    
    // codeRange method
    void *getPtrToInstruction(Address addr) const;
    void *getPtrToData(Address addr) const;

    // Try to avoid using these if you can, since they'll trigger
    // parsing and allocation. 
    bool getAllFunctions(pdvector<func_instance *> &funcs);
    bool getAllVariables(pdvector<int_variable *> &vars);

    const pdvector<mapped_module *> &getModules();

    // begin exploratory and defensive mode functions //
    BPatch_hybridMode hybridMode() { return analysisMode_; }
    bool isExploratoryModeOn();
    bool parseNewEdges(const std::vector<edgeStub>& sources);
    bool parseNewFunctions(std::vector<Address> &funcEntryAddrs);
    void registerNewFunctions(); // register funcs found by recursive parsing
    bool updateCodeBytesIfNeeded(Address entryAddr); // ret true if was needed
    void updateCodeBytes(const std::list<std::pair<Address,Address> > &owRanges );
    void setCodeBytesUpdated(bool);
    void addProtectedPage(Address pageAddr); // adds to protPages_
    void removeProtectedPage(Address pageAddr);
    void removeEmptyPages();
    void removeFunction(func_instance *func);
    bool splitIntLayer();
    void splitBlock(ParseAPI::Block *first, ParseAPI::Block *second);
    bool findBlocksByRange(Address startAddr,
                          Address endAddr,
                          std::list<block_instance*> &pageBlocks);
    void findFuncsByRange(Address startAddr,
                          Address endAddr,
                          std::set<func_instance*> &pageFuncs);
    void addEmulInsn(Address insnAddr, Register effective_addr);
    bool isEmulInsn(Address insnAddr);
    Register getEmulInsnReg(Address insnAddr);
    void setEmulInsnVal(Address insnAddr, void * val);
private:
    // helper functions
    void updateCodeBytes(SymtabAPI::Region *reg);
    bool isUpdateNeeded(Address entryAddr);
    bool isExpansionNeeded(Address entryAddr);
    void expandCodeBytes(SymtabAPI::Region *reg);
    // end exploratory and defensive mode functions //
public:

    bool  getSymbolInfo(const std::string &n, int_symbol &sym);

    // All name lookup functions are vectorized, because you can have
    // multiple overlapping names for all sorts of reasons.
    // Demangled/"pretty": easy overlap (overloaded funcs, etc.).
    // Mangled: multiple modules with static/private functions and
    // we've lost the module name.

    const pdvector<func_instance *> *findFuncVectorByPretty(const std::string &funcname);
    const pdvector<func_instance *> *findFuncVectorByMangled(const std::string &funcname); 

    bool findFuncsByAddr(std::vector<func_instance *> &funcs);
    bool findBlocksByAddr(std::vector<block_instance *> &blocks);

    const pdvector<int_variable *> *findVarVectorByPretty(const std::string &varname);
    const pdvector<int_variable *> *findVarVectorByMangled(const std::string &varname); 
    const int_variable *getVariable(const std::string &varname);
    
	//this marks the shared object as dirty, mutated
	//so it needs saved back to disk
	void setDirty(){ dirty_=true;}
	bool isDirty() { return dirty_; }

    func_instance *findFunction(ParseAPI::Function *img_func);

    int_variable *findVariable(image_variable *img_var);

    block_instance *findBlock(ParseAPI::Block *);
    // If we already know the source or target hand them in for efficiency
    edge_instance *findEdge(ParseAPI::Edge *, block_instance *src = NULL, block_instance *trg = NULL);

    // These methods should be invoked to find the global constructor and
    // destructor functions in stripped, static binaries
    func_instance *findGlobalConstructorFunc(const std::string &ctorHandler);
    func_instance *findGlobalDestructorFunc(const std::string &dtorHandler);

    // We store callee names at the mapped_object level for
    // efficiency
    std::string getCalleeName(block_instance *);
    void setCalleeName(block_instance *, std::string name);

  private:
    //
    //     PRIVATE DATA MEMBERS
    //				
private:
    fileDescriptor desc_; // full file descriptor

    string  fullName_;	// full file name of the shared object
    string  fileName_; // name of shared object as it should be identified
			//  in mdl, e.g. as used for "exclude"....
    Address   codeBase_; // The OS offset where the text segment is loaded;
    // there is a corresponding codeOffset_ in the image class.

    // For example, an a.out often has a codeBase of 0, and a
    // codeOffset of 0x<valid>. Libraries are the reverse; codeBase_
    // of <valid>, codeOffset of 0. All of our incoming functions,
    // etc. from the image class have codeOffset built in.

    Address   dataBase_; // Where the data starts...

    void set_short_name();

    pdvector<mapped_module *> everyModule;

    typedef std::map<const ParseAPI::Block *, block_instance *> BlockMap;
    BlockMap blocks_;
    
    typedef std::map<const ParseAPI::Edge *, edge_instance *> EdgeMap;
    EdgeMap edges_;

    typedef std::map<const ParseAPI::Function *, func_instance *> FuncMap;
    FuncMap everyUniqueFunction;

    dictionary_hash<const image_variable *, int_variable *> everyUniqueVariable;

    dictionary_hash< std::string, pdvector<func_instance *> * > allFunctionsByMangledName;
    dictionary_hash< std::string, pdvector<func_instance *> * > allFunctionsByPrettyName;

    dictionary_hash< std::string, pdvector<int_variable *> * > allVarsByMangledName;
    dictionary_hash< std::string, pdvector<int_variable *> * > allVarsByPrettyName;

    codeRangeTree codeRangesByAddr_;

    // And those call...
    void addFunction(func_instance *func);
    void addVariable(int_variable *var);

    // Add a name after-the-fact
    typedef enum {
        mangledName = 1,
        prettyName = 2,
        typedName = 4 } nameType_t;
    void addFunctionName(func_instance *func, const std::string newName, nameType_t nameType);

    bool dirty_; // marks the shared object as dirty 
    bool dirtyCalled_;//see comment for setDirtyCalled
    
    image  *image_; // pointer to image if processed is true 
    bool dlopenUsed; //mark this shared object as opened by dlopen
    AddressSpace *proc_; // Parent process

    bool analyzed_; // Prevent multiple adds

    // exploratory and defensive mode variables
    typedef enum  {
        PROTECTED,
        REPROTECTED,
        UNPROTECTED,
    } WriteableStatus;
    BPatch_hybridMode analysisMode_;
    map<Address,WriteableStatus> protPages_;
    std::set<SymtabAPI::Region*> expansionCheckedRegions_;
    bool pagesUpdated_;
    typedef std::map<Address, std::pair<Register,void*> > EmulInsnMap;
    EmulInsnMap emulInsns_;

    Address memEnd_; // size of object in memory

    mapped_module *getOrCreateForkedModule(mapped_module *mod);

    // from a string that is a complete path name to a function in a module
    // (ie. "/usr/lib/libc.so.1/write") return a string with the function
    // part removed.  return 0 on error
    char *getModulePart(std::string &full_path_name) ;

    bool memoryImg_;

    std::map<block_instance *, std::string> calleeNames_;
};

// Aggravation: a mapped object might very well occupy multiple "ranges". 
class mappedObjData : public codeRange {
 public:
    mappedObjData(mapped_object *obj_) : obj(obj_) {};
    Address get_address() const { return obj->dataAbs(); }
    unsigned get_size() const { return obj->dataSize(); }
    mapped_object *obj;
};


#endif
