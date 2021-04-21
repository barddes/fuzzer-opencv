#if STANDALONE_TARGET
size_t LLVMFuzzerMutate(uint8_t *Data, size_t Size, size_t MaxSize) {
  assert(false && "LLVMFuzzerMutate should not be called from StandaloneFuzzTargetMain");
  return 0;
}
#endif

// extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize, unsigned int Seed) {
//   std::string s(reinterpret_cast<const char*>(Data), Size);
//   std::stringstream in(s);
//   std::stringstream out;
//   PngMutator p(in);
//   p.Mutate(LLVMFuzzerMutate, Seed);
//   p.Serialize(out);
//   const auto &str = out.str();
//   if (str.size() > MaxSize) return Size;
//   memcpy(Data, str.data(), str.size());
//   return str.size();
// }

extern "C" size_t LLVMFuzzerCustomMutator(uint8_t *Data, size_t Size, size_t MaxSize, unsigned int Seed) {
	std::vector<uint8_t> data(Data, Data+Size);

	Png png = Png(data);

}
