#include <stdio.h>
#include "pin.H"

FILE * trace;
PIN_LOCK pinLock;
long long int counter = 0;

std::vector<int> partpartitioning(long long int x) {    
    // Divide the given range into parts. size => 8, 4, 2, 1
    std::vector<int> ret;
    int eights = x >> 3;
    int fours = (x % 8) >> 2;
    int twos = (x % 4) >> 1;
    int ones = (x % 2);
    ret.push_back(eights);
    ret.push_back(fours);
    ret.push_back(twos);
    ret.push_back(ones);
    return ret;
}

// This function is called before every instruction is executed and prints the IP
VOID writeprintip(VOID *ip, THREADID tid, VOID *addr, UINT32 size)
{ 
    PIN_GetLock(&pinLock, tid + 1);
    unsigned long long int base = (*(unsigned long long int*)addr)%64;
    unsigned long long int curr_addr = *(unsigned long long int*)addr; // 64 bit address.

    if((base + size) > 64) {
       
       int buffer = 64 - base; // before 64 byte mark.
       int overflow = base + size - 64; // after 64 byte mark.
       
        auto vec = partpartitioning(buffer);
        int x = 8;
        for(const auto item : vec) {
            for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
            }
            x = x >> 1;
        }

        vec = partpartitioning(overflow);
        x = 8;
        base = 0;
        for(const auto item : vec) {
            for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
            }
            x = x >> 1;
        }
    } 

     else {
       auto vec = partpartitioning(size);
       int x = 8;
       for(const auto item : vec) {
           for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
           }
           x = x >> 1;
       }
   }

   fflush(trace);
   PIN_ReleaseLock(&pinLock);
}

// This function is called before every instruction is executed and prints the IP
VOID readprintip(VOID *ip, THREADID tid, VOID *addr, UINT32 size)
{ 
    PIN_GetLock(&pinLock, tid + 1);
    unsigned long long int base = (*(unsigned long long int*)addr)%64;
    unsigned long long int curr_addr = *(unsigned long long int*)addr; // 64 bit address.

    if((base + size) > 64) {
       
       int buffer = 64 - base; // before 64 byte mark.
       int overflow = base + size - 64; // after 64 byte mark.
       
        auto vec = partpartitioning(buffer);
        int x = 8;
        for(const auto item : vec) {
            for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
            }
            x = x >> 1;
        }

        vec = partpartitioning(overflow);
        x = 8;
        base = 0;
        for(const auto item : vec) {
            for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
            }
            x = x >> 1;
        }
    } 

    else {
       auto vec = partpartitioning(size);
       int x = 8;
       for(const auto item : vec) {
           for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, x);
                base += x;
                curr_addr += x;
           }
           x = x >> 1;
       }
   }

   fflush(trace);
   PIN_ReleaseLock(&pinLock);
}

// This routine is executed every time a thread is created.
VOID ThreadStart(THREADID tid, CONTEXT *ctxt, INT32 flags, VOID *v)
{
    PIN_GetLock(&pinLock, tid + 1);
 
    fprintf(stdout, "thread begin %d\n",tid);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

// This routine is executed every time a thread is destroyed.
VOID ThreadFini(THREADID tid, const CONTEXT *ctxt, INT32 code, VOID *v)
{
    PIN_GetLock(&pinLock, tid+1);
    fprintf(stdout, "thread end %d code %d\n",tid, code);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

// Pin calls this function every time a new instruction is encountered
VOID Instruction(INS ins, VOID *v)
{
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    for (UINT32 memOp = 0; memOp < memOperands; memOp++) {

        UINT32 size = INS_MemoryOperandSize(ins, memOp);
        
        if (INS_MemoryOperandIsRead(ins, memOp)) {
            INS_InsertPredicatedCall(ins, 
            IPOINT_BEFORE, 
            (AFUNPTR)readprintip, 
            IARG_INST_PTR,                
            IARG_THREAD_ID, 
            IARG_MEMORYOP_EA, memOp, 
            IARG_UINT32, size,
            IARG_END);
        } 
        if (INS_MemoryOperandIsWritten(ins, memOp)) {
            INS_InsertPredicatedCall(ins, 
            IPOINT_BEFORE, 
            (AFUNPTR)writeprintip, 
            IARG_INST_PTR, 
            IARG_THREAD_ID, 
            IARG_MEMORYOP_EA, memOp, 
            IARG_UINT32, size,
            IARG_END);
        }
    }
}

// This function is called when the application exits
VOID Fini(INT32 code, VOID *v)
{
    fprintf(trace, "#eof\n");
    fclose(trace);
}

/* ===================================================================== */
/* Print Help Message                                                    */
/* ===================================================================== */

INT32 Usage()
{
    PIN_ERROR("This Pintool prints the IPs of every instruction executed\n" 
              + KNOB_BASE::StringKnobSummary() + "\n");
    return -1;
}

/* ===================================================================== */
/* Main                                                                  */
/* ===================================================================== */

int main(int argc, char * argv[])
{
    trace = fopen("addrtrace.txt", "w");
    
    PIN_InitLock(&pinLock);

    // Initialize pin
    if (PIN_Init(argc, argv)) return Usage();

    // Register Instruction to be called to instrument instructions
    INS_AddInstrumentFunction(Instruction, 0);

    PIN_AddThreadStartFunction(ThreadStart, 0);
    PIN_AddThreadFiniFunction(ThreadFini, 0);

    // Register Fini to be called when the application exits
    PIN_AddFiniFunction(Fini, 0);
    
    // Start the program, never returns
    PIN_StartProgram();
    
    return 0;
}
