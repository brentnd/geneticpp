#ifndef GENETIC_INDIVIDUAL_HPP
#define GENETIC_INDIVIDUAL_HPP

#include <string>
#include <vector>

namespace genetic {

class individual {
public:
   struct gene {
      int chromosome;

      gene();
      void mutate();
      ~gene();
      bool operator==(gene const &other) const {
         return chromosome==other.chromosome;
      }
   };

   static std::string const solution;
   static std::size_t const gene_size = 8;

   static int get_max_fitness();

   individual();

   int get_gene(int index) const;
   void set_gene(int index, int const gene);

   int get_fitness() const;

   void print_genes() const;

   std::vector<gene> const & get_genes() const {
      return genes;
   }

   void mutate(double mutation_rate);

   static individual crossover(individual a, individual b);

   bool operator==(individual const &other) const {
      return genes==other.genes;
   }

private:
   std::vector<gene> genes;
};

}

#endif //GENETIC_INDIVIDUAL_HPP