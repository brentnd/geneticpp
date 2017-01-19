#pragma once

#include <algorithm> // std::min, std::swap_ranges
#include <functional> // std::function
#include <iostream>
#include <utility> // std::swap
#include <vector>

#include "random.hpp"
#include "attribute.hpp"

namespace genetic {

class individual {
public:
   individual();

   // Mating
   template <typename... Args>
   static void mating_method(void (*fcn)(individual *, individual *, Args...), Args... args) {
      mating_function = std::bind(fcn, std::placeholders::_1, std::placeholders::_2, std::forward<Args>(args)...);
   }

   // Mate two individuals using static method
   static void mate(individual * ind1, individual * ind2);
   // Mating variants for mating_method
   static void one_point_crossover(individual * ind1, individual * ind2);
   static void two_point_crossover(individual * ind1, individual * ind2);

   // Evaluate this individuals fitness
   float evaluate();
   static float eval_sum(individual const & ind);
   // Custom function for evaluation
   static void evaluation_method(std::function<int(individual const &)> && fcn);

   // Mutation
   template <typename... Args>
   static void mutation_method(void (individual::* fcn)(Args...), Args... args) {
      mutation_function = std::bind(fcn, std::placeholders::_1, std::forward<Args>(args)...);
   }
   // Mutate this individual using mutation method
   void mutate();
   // Mutation variants for mutation_method
   void uniform_int(float mutation_rate, double min, double max);
   void flip_bit(float mutation_rate);
   void shuffle_indexes(float mutation_rate);

   // Initialize the attributes by seeding them
   void seed();

   bool operator<(individual const & other) const;

   bool operator>(individual const & other) const;

   bool operator==(individual const & other) const;

   std::vector<attribute>::const_iterator begin() const;
   std::vector<attribute>::iterator begin();
   std::vector<attribute>::const_iterator end() const;
   std::vector<attribute>::iterator end();
   attribute const & at(std::size_t pos) const;
   std::size_t size() const;

   std::string to_string() const {
      std::string sol;
      for (auto const & attr : attributes) {
         char val = attr;
         if (val > ' ' && val < '~') {
            sol += static_cast<char>(attr);
         } else {
            sol += '?';
         }
      }
      return std::move(sol);
   }

   friend std::ostream& operator<<(std::ostream & stream, individual const & ind) {
      stream << "individual @ (" << static_cast<const void *>(&ind) << ") f=" << ind.fitness;

      stream << " attr=[";
      for (auto const & attr : ind.attributes) {
         stream << attr << attribute::display_delimiter;
      }
      stream << "]";
      return stream;
   }

public:
   static std::size_t attribute_count;

private:
   static std::function<float(individual const &)> evaluation_function;
   static std::function<void(individual *, individual *)> mating_function;
   static std::function<void(individual &)> mutation_function;
   void throw_if_fitness_invalid() const;

private:
   float fitness;
   bool valid_fitness;
   std::vector<attribute> attributes;
};

} // namespace genetic
