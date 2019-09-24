#include <stdio.h>
#include "pin.H"

FILE * trace;
PIN_LOCK pinLock;

// This function is called before every instruction is executed and prints the IP
VOID readprintip(VOID *ip, THREADID tid, VOID *addr, UINT32 size)
{ 
   PIN_GetLock(&pinLock, tid + 1);
   unsigned long long int base = *(unsigned long long int*)addr%64;
   unsigned long long int curr_addr = *(unsigned long long int*)addr; // 64 bit address.

    if((base + size) > 64) {
       
       int buffer = 64 - base; // before 64 byte mark.
       
       int overflow = base + size - 64; // after 64 byte mark.
       
       while(buffer) {
           if(buffer >= 8) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               buffer -= 8;
               base += 8;
               curr_addr += 8;
           }
            else if(buffer >= 4) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 4);
               buffer -= 4;
               base += 4;
               curr_addr += 4;
           }
            else if(buffer >= 2) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 2);
               buffer -= 2;
               base += 2;
               curr_addr += 2;
           }
            else if(buffer >= 1) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               buffer -= 1;
               base += 1;
               curr_addr += 1;
           }
           else {

           }
       }

        base = 0;
        while(overflow) {
           if(overflow >= 8) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               overflow -= 8;
               base += 8;
               curr_addr += 8;
           }
            else if(overflow >= 4) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 4);
               overflow -= 4;
               base += 4;
               curr_addr += 4;
           }
            else if(overflow >= 2) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 2);
               overflow -= 2;
               base += 2;
               curr_addr += 2;
           }
            else if(overflow >= 1) {
               fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               overflow -= 1;
               base += 1;
               curr_addr += 1;
           }
           else {

           }
       }
    } 

   if((base + size) <= 64 && (size <= 8)) {
        fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, size);
   } else {
    
    while((base + size) <= 64 && size >= 8) {
       fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 8);
       base += 8;
       size -= 8;
       curr_addr += 8;
   }
   
    while((base + size) <= 64 && size >= 4) {
       fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 4);
       base += 4;
       size -= 4;
       curr_addr += 4;
    }

    while((base + size) <= 64 && size >= 2) {
        fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 2);
       base += 2;
       size -= 2;
       curr_addr += 2;
    }
    
    while((base + size) <= 64 && size >= 1) {
       fprintf(trace, "%d %p R %llu %llu %u\n", tid, ip, curr_addr, base, 1);
       base += 1;
       size -= 1;
       curr_addr += 1;
    }
   }

   fflush(trace);
   PIN_ReleaseLock(&pinLock);
}


VOID writeprintip(VOID *ip, THREADID tid, VOID *addr, UINT32 size)
{ 
   PIN_GetLock(&pinLock, tid + 1);
   unsigned long long int base = *(unsigned long long int*)addr%64;
   unsigned long long int curr_addr = *(unsigned long long int*)addr;

    if((base + size) > 64) {
       
       int buffer = 64 - base; // before 64 byte mark.
       
       int overflow = base + size - 64; // after 64 byte mark.
       
       while(buffer) {
           if(buffer >= 8) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               buffer -= 8;
               base += 8;
               curr_addr += 8;
           }
            else if(buffer >= 4) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 4);
               buffer -= 4;
               base += 4;
               curr_addr += 4;
           }
            else if(buffer >= 2) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 2);
               buffer -= 2;
               base += 2;
               curr_addr += 2;
           }
            else if(buffer >= 1) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               buffer -= 1;
               base += 1;
               curr_addr += 1;
           }
           else {

           }
       }

        base = 0;
        while(overflow) {
           if(overflow >= 8) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               overflow -= 8;
               base += 8;
               curr_addr += 8;
           }
            else if(overflow >= 4) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 4);
               overflow -= 4;
               base += 4;
               curr_addr += 4;
           }
            else if(overflow >= 2) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 2);
               overflow -= 2;
               base += 2;
               curr_addr += 2;
           }
            else if(overflow >= 1) {
               fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 8);
               overflow -= 1;
               base += 1;
               curr_addr += 1;
           }
           else {

           }
       }
    } 
    
   if((base + size) <= 64 && (size <= 8)) {
        fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, size);
   } else {
    
    while((base + size) <= 64 && size >= 8) {
       fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 8);
       base += 8;
       size -= 8;
       curr_addr += 8;
   }
   
    while((base + size) <= 64 && size >= 4) {
       fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 4);
       base += 4;
       size -= 4;
       curr_addr += 4;
    }

    while((base + size) <= 64 && size >= 2) {
        fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 2);
       base += 2;
       size -= 2;
       curr_addr += 2;
    }
    
    while((base + size) <= 64 && size >= 1) {
       fprintf(trace, "%d %p W %llu %llu %u\n", tid, ip, curr_addr, base, 1);
       base += 1;
       size -= 1;
       curr_addr += 1;
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
    trace = fopen("addtrace.out", "w");
    
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
