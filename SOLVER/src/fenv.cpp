//
//  fenv.cpp
//  AxiSEM3D
//
//  Created by Kuangdai Leng on 6/7/20.
//  Copyright © 2020 Kuangdai Leng. All rights reserved.
//

//  setup floating-point environment

#ifndef _SKIP_DISABLE_SSE_DENORMS

#if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
    #include <xmmintrin.h>
#elif defined(__arm__) || defined(__aarch64__)
    #include <arm_neon.h>
#endif

#endif

void fenv_setup() {
#ifndef _SKIP_DISABLE_SSE_DENORMS
    // Disable denormal numbers for better performance
#if defined(__x86_64__) || defined(_M_X64) || defined(__i386) || defined(_M_IX86)
    _MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#elif defined(__arm__) || defined(__aarch64__)
    // Enable flush-to-zero mode on ARM
    uint64_t fpcr;
    __asm__ __volatile__ ("mrs %0, fpcr" : "=r" (fpcr));
    fpcr |= (1 << 24);  // Set the FZ bit
    __asm__ __volatile__ ("msr fpcr, %0" : : "r" (fpcr));
#endif
#endif
}
