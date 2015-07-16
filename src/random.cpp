#include "random.hpp"

#include <algorithm>

unsigned int random::seed = 0;

void random::set_seed(unsigned int seed) {
   random::seed = seed;
   initialize();
}
void random::reset() {
   if (seed == 0) {
      seed = static_cast<unsigned int>(time(0));
   }
   initialize();
}
bool random::probability(double prob) {
   float r = f_range(0,1);
   return r <= prob;
}
int random::i_range(int low, int high) {
   if (high < low) {
      throw std::runtime_error("Invalid range");
   }
   int range = high - low;
   return std::rand() % range + low;
}
std::vector<int> random::i_range(int low, int high, unsigned int count, bool unique) {
   if (unique && (high-low) < count) {
      throw std::runtime_error("random vector unique but range is less than count");
   }

   std::vector<int> rand_is;
   while (rand_is.size() < count) {
      int rand_i = i_range(low, high);
      if (!unique || std::find(rand_is.begin(), rand_is.end(), rand_i) == rand_is.end()) {
         rand_is.push_back(rand_i);
      }
   }
   return rand_is;
}
float random::f_range(float low, float high) {
   if (high < low) {
      throw std::runtime_error("Invalid range");
   }
   float range = high - low;
   float r = static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
   return r * range - low;
}
void random::initialize() {
   std::srand(seed);
}
