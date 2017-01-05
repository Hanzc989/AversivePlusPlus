/*
Copyright (c) 2015, Xenomorphales
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of Aversive++ nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/
#include "timer.hpp"

extern "C" {

#if (defined TIM8) and (defined TIM13)

void TIM8_UP_TIM13_IRQHandler(void) {
  {
    auto& h = Private::get_timer_cube_handle<8>();
    if(__HAL_TIM_GET_ITSTATUS(&h, TIM_IT_UPDATE) == SET) {
      if(Private::get_timer_irq_handler<8>()) Private::get_timer_irq_handler<8>()();
      __HAL_TIM_CLEAR_IT(&h, TIM_IT_UPDATE);
    }
  }
  {
    auto& h = Private::get_timer_cube_handle<13>();
    if(__HAL_TIM_GET_ITSTATUS(&h, TIM_IT_UPDATE) == SET) {
      if(Private::get_timer_irq_handler<13>()) Private::get_timer_irq_handler<13>()();
      __HAL_TIM_CLEAR_IT(&h, TIM_IT_UPDATE);
    }
  }
}

#endif

}

