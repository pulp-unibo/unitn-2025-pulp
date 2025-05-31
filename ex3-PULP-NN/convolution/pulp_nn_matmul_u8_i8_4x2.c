/*
 * pulp_nn_matmul_u8_i8.c
 * Nazareno Bruschi <nazareno.bruschi@unibo.it>
 *
 * Copyright (C) 2019-2020 University of Bologna
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "pmsis.h"
#include "pulp_nn_utils.h"


uint8_t *pulp_nn_matmul_u8_i8_4x2 (
                        uint8_t *pIn,
                        int8_t *pBias,
                        uint8_t *pOut,
                        uint8_t *pOut2,
                        int8_t *pWeight,
                        uint16_t out_shift,
                        uint16_t num_col_im2col,
                        uint16_t ch_out
){
  
  // This will be your 4x2 matmul kernel that you
  // will implement

  // define the SIMD variables/vectors here with v4s data type
  /* YOUR CODE HERE*/

  uint16_t ch_out_r = ch_out;
  uint16_t num_col_im2col_w = num_col_im2col;

  //uint8_t *pOut2 = pOut + ch_out_r;
  int8_t *pA = pWeight;

  uint16_t chan_left = ch_out & 0x3;

  for(int i=0; i < (ch_out >> /* YOUR CODE HERE*/); i++)
  {
    // define here all the pointers you need (take inspiration from 2x2 version)
    /* YOUR CODE HERE*/

    // define the accumulators and initialize them to zero
    /* YOUR CODE HERE*/

    if (pBias != NULL)
    {
      // handle the biases
      /* YOUR CODE HERE*/
    }

    for(int j=0; j<(num_col_im2col_w >> 2); j++)
    {
      // implement the innermost loop
      // of 4x2 matmul

      /* YOUR CODE HERE*/
    }
    uint16_t col_cnt_im2col = num_col_im2col & 0x3;
    while (col_cnt_im2col)
    {
      //handle leftovers (optional)
      /* YOUR CODE HERE*/
    }

    //handle the outputs
    /* YOUR CODE HERE*/

    // handle weights' pointer update
    /* YOUR CODE HERE*/
  }
  
  while(chan_left)
  {
    uint8_t *pB = pIn;
    uint8_t *pB2 = (pB + num_col_im2col);
    int sum = 0;
    if (pBias != NULL)
      sum = ((int) (*pBias++));    
    int sum2 = sum;

    for(int j=0; j < (num_col_im2col_w >> 2); j++)
    {
      vecA = *((v4s*) pA);
      vecB = *((v4u*) pB);
      vecB2 = *((v4u*) pB2);

      sum = SumDotp4(vecB, vecA, sum);
      sum2 = SumDotp4(vecB2, vecA, sum2);

      pA+=4;
      pB+=4;
      pB2+=4;
    }
    uint16_t col_cnt_im2col = num_col_im2col & 0x3;
    while(col_cnt_im2col)
    {
      int8_t inA = *pA++;
      uint8_t inB = *pB++;
      uint8_t inB2 = *pB2++;
      asm volatile("": : :"memory");
      sum += inA * inB;
      sum2 += inA * inB2;

      col_cnt_im2col--;
    }

    *pOut = (uint8_t) clip8(sum >> out_shift);
    pOut++;
    *pOut2 = (uint8_t) clip8(sum2 >> out_shift);
    pOut2++;

    chan_left--;
  }
  pOut+=ch_out_r;
  return pOut;
}
