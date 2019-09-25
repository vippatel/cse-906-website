#include <stdio.h>
#include "pin.H"

FILE *trace, *addrs;
PIN_LOCK pinLock;
long long int counter = 0;

std::vector<int> partpartitioning(long long int x) {    
    // Divide the given range into parts. size => 8, 4, 2, 1
    std::vector<int> ret;
    ret.emplace_back(x >> 3);
    ret.emplace_back((x % 8) >> 2);
    ret.emplace_back((x % 4) >> 1);
    ret.emplace_back((x % 2));
    return ret;
}

VOID trace_access_ip(VOID *ip, THREADID tid, VOID *addr, UINT32 size)
{ 
    PIN_GetLock(&pinLock, tid + 1);

    unsigned long long int base = (*(unsigned long long int*)addr) % 64; // Base modulo for index into 64-byte aligned blocks.
    unsigned long long int curr_addr = (*(unsigned long long int*)addr); // 64 bit address.

    if((base + size) > 64) {
                                                                //  __________________________________
       int buffer = 64 - base; // before 64 byte mark.              |___buffer_|____overflow_________|
       int overflow = base + size - 64; // after 64 byte mark.
       
        auto vec = partpartitioning(buffer);
        int x = 8;
        for(const auto item : vec) {
            for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %llu %u\n", tid, curr_addr, x);
                fprintf(addrs, "%d %llu\n", tid, curr_addr);
                counter++;
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
                fprintf(trace, "%d %llu %u\n", tid, curr_addr, x);
                fprintf(addrs, "%d %llu\n", tid, curr_addr);
                counter++;
                base += x;
                curr_addr += x;
            }
            x = x >> 1;
        }
    } 

    else {
        // no overflow accross the block so we can just partition directly. 
       auto vec = partpartitioning(size);
       int x = 8;
       for(const auto item : vec) {
           for(auto i = 0; i < item; i++) {
                fprintf(trace, "%d %llu %u\n", tid, curr_addr, x);
                fprintf(addrs, "%d %llu\n", tid, curr_addr);
                counter++;
                base += x;
                curr_addr += x;
           }
           x = x >> 1;
       }
   }

   fflush(trace);
   PIN_ReleaseLock(&pinLock);
}

// Thread spawn time. 
VOID ThreadStart(THREADID tid, CONTEXT *ctxt, INT32 flags, VOID *v)
{
    PIN_GetLock(&pinLock, tid + 1);
    fprintf(stdout, "Thread begin %d\n",tid);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

// Thread Kill time. 
VOID ThreadFini(THREADID tid, const CONTEXT *ctxt, INT32 code, VOID *v)
{
    PIN_GetLock(&pinLock, tid+1);
    fprintf(stdout, "Thread %d ended with code %d\n", tid, code);
    fflush(stdout);
    PIN_ReleaseLock(&pinLock);
}

VOID Instruction(INS ins, VOID *v)
{
    UINT32 memOperands = INS_MemoryOperandCount(ins);
    for (UINT32 memOp = 0; memOp < memOperands; memOp++) {

        UINT32 size = INS_MemoryOperandSize(ins, memOp);
        
        if (INS_MemoryOperandIsRead(ins, memOp)) {
            INS_InsertPredicatedCall(ins, 
            IPOINT_BEFORE, 
            (AFUNPTR)trace_access_ip, 
            IARG_INST_PTR,                
            IARG_THREAD_ID, 
            IARG_MEMORYOP_EA, memOp, 
            IARG_UINT32, size,
            IARG_END);
        } 

        if (INS_MemoryOperandIsWritten(ins, memOp)) {
            INS_InsertPredicatedCall(ins, 
            IPOINT_BEFORE, 
            (AFUNPTR)trace_access_ip, 
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
    fprintf(stdout, "\nTotal Traces %llu\n", counter);
    fclose(addrs);
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

int main (int argc, char *argv[], char *envp[])
{
    trace = fopen("addr_trace_offset.txt", "w");
    addrs = fopen("addr_trace.txt", "w");
    
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
