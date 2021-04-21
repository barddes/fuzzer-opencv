#ifndef FUZZER_OPENCV_MUTATOR_H
#define FUZZER_OPENCV_MUTATOR_H

extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize, unsigned int Seed);
extern "C" size_t LLVMFuzzerMutate(uint8_t *Data, size_t Size, size_t MaxSize);

#endif //FUZZER_OPENCV_MUTATOR_H

