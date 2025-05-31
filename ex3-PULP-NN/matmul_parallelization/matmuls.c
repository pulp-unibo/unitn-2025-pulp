#include "pmsis.h"


// generic matrix multiplication
void gemm(int * MatA, int * MatB, int* MatC, int NN, int MM, int KK){
    uint32_t core_id, i_chunk, i_start, i_end;
    uint32_t i = 0;

    core_id = pi_core_id();
    i_chunk = (NN + NUM_CORES-1) / NUM_CORES;
    i_start = core_id * i_chunk;
    i_end   = i_start + i_chunk < NN ? i_start + i_chunk : NN;

    // task to profile
    for (i = i_start; i < i_end; i ++) {
      for (int j = 0; j < MM; j++) {
        int acc = 0;
        for (int k = 0; k < KK; k++) {
          acc += MatA[i*KK+k] * MatB[k*MM+j];
        } //k
        MatC[i*MM+j] = acc;
      }//j
    }//i
    pi_cl_team_barrier();

}
/* TASK 1.3: Loop unrolling technique
 *
 * Does the scheduling of the instructions avoid the stalls?
 * If you have the following pattern:
 *
 * lw A, off(B)
 * lw C, off(D)
 * lw E, off(F)
 * lw G, off(H)
 * mac A, C, Z
 * mac E, G, Y
 *
 * would there be any load stall?
 * This approach is known as loop unrolling. This method is
 * one of the most powerful technique you have to optimize code.
 * Especially in regular accesses tasks such as array operations,
 * loops might be always unrolled and, in fact, the compiler tends
 * to apply the unrolling whenever he can.
 *
 * 1.3.2: Implement loop unrolling with factor of 2, 4, 8, 16 and
 * fill the table with the overall MACs/cycle for 8 cores execution.
 * Do you see a regression doing more aggressive loop unrolling? Why?
 * The problem is that implenting unrolling, you are forcing multiple
 * loads from the memory, loading the values in the internal core
 * registers. They are not infinite, especially in embedded architecture
 * such as PULP. The available registers in the register file
 * of the core are 32, but not all are general purpose registers.
 * This fact actually limits the unrolling, because, if you saturate
 * the available registers in your architecture, you would face with
 * spilling issues, where the compiler pushes and pops over and over
 * to and from the stack (memory) the values on the registers to reuse
 * the register for another operand. This effect would destroy all the
 * performance metrics.
 *
 * BONUS TASK 1.4: Is there a smarter way to compute it? If you look deeper
 * into the kernel implemetation you should see that the index of matrix A
 * depends on i and k, which are the outermost and the innermost loop indexes
 * respectively, while the one of matrix B depends on the j and k. This means
 * that this operation exposes a kind of reuse of the matrix A to compute different
 * output. The reuse in general increases the performance and especially the
 * OPEF (operation efficiency). This metric tells us the ratio between the
 * "useful" operations with respect the total amount of executed instructions.
 * The higher is the OPEF the higher is the efficiency of the code.
 * Therefore, in our case the OPEF is the following:
 *
 *                                 NB_MACS
 *                  OPEF = -----------------------
 *                             NB_INSTRUCTIONS
 *
 * To calculate it you just have to consider the number of MACs in the
 * innermost loop with respect to the total amount of instructions (loads
 * + macs).
 * Fill the table with the OPEF for 8 cores execution, varying the reusing
 * with 2, 4, 8 factor.
 *
 */
void gemm_unroll(int * MatA, int * MatB, int* MatC, int NN, int MM, int KK){

  // Parallelization of the workload
  // int core_id = pi_core_id();
  // int i_chunk = (NN + NUM_CORES-1) / NUM_CORES;
  // int i_start = core_id * i_chunk;
  // int i_end   = i_start + i_chunk < NN ? i_start + i_chunk : NN;

  // Implement Below The unrolled version of the matmul
  // for (int i = i_start; i < i_end; i ++) {
  //   for (int j = 0; j < MM; j++) {
  //     int acc = 0;
  //     for (int k = 0; k < KK; /*YOUR CORE HERE*/) {
  //       // memory insns (loads)
           /* YOUR CODE HERE*/
  

  //       // use compiler fence to explicitly separate the memory insns from alu insns
  //       asm volatile("":::"memory");

  //       // alu/mul insns
           /* YOUR CODE HERE*/
  //     } //k
         
        // store the accumulator to Matrix C location
        /* YOUR CODE HERE*/
  //   }//j
  // }//i

  // pi_cl_team_barrier();

}

void gemm_reuse(int * MatA, int * MatB, int* MatC, int NN, int MM, int KK){

  // int core_id = pi_core_id();
  // int i_chunk = (NN + NUM_CORES-1) / NUM_CORES;
  // int i_start = core_id * i_chunk;
  // int i_end   = i_start + i_chunk < NN ? i_start + i_chunk : NN;

  // for (int i = i_start; i < i_end; i ++) {
  //   for (int j = 0; j < MM; /* YOUR CODE HERE*/) {
         // define the accumulators
         /* YOUR CODE HERE*/

  //     for (int k = 0; k < KK; k++) {

           // identify the operand that can be reused multiple times over different operands
           /* YOUR CODE HERE*/

           // complete the matmul innermost loop by multiplying
           // reused operand with all the others
           /* YOUR CODE HERE*/

  //     } //k

         // store the results into the MAtrix C location
         /* YOUR CODE HERE*/
         
  //   }//j
  // }//i

  // parallel barrier
  // pi_cl_team_barrier();

}