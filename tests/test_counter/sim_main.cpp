#include "Vdut.h"
#include "verilated.h"

int main(int argc, char** argv) {
    Verilated::commandArgs(argc, argv);
    Vdut* dut = new Vdut;

    // Simulate for 100 clock cyclesss 
    dut->reset = 1; // Assert reset
    for (int i = 0; i < 200; i++) {
        dut->clk = !dut->clk; // Toggle clock
        
        // Release reset after 10 ticks
        if (i > 10) dut->reset = 0;
        
        dut->eval(); // Evaluate model
    }

    // Final check: Did it count?
    // After ~95 cycles (200 toggles / 2), count should be > 0
    if (dut->count > 0) {
        printf("SUCCESS: Counter value is %d\n", dut->count);
        delete dut;
        return 0; // Return 0 means PASS
    } else {
        printf("FAILURE: Counter did not increment.\n");
        delete dut;
        return 1; // Return 1 means FAIL
    }
}