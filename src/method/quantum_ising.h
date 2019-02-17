#pragma once
#include "../graph/sparse.h"
#include "method.h"
#include "../updater/quantum_updater.h"
#include <random>

namespace openjij {
	namespace method {
		using namespace openjij::graph;
		using namespace openjij::updater;

		using TrotterSpins = std::vector<Spins>;
		//TODO: double -> FloatType (template)
		class QuantumIsing : public Method, public QuantumUpdater{
			//general transverse-field ising model with discrete trotter slices

			private:
				TrotterSpins spins; //spins with trotter slices
				Sparse<double> interaction; //original interaction

				//random number generators
				//TODO: use MT or xorshift?
				std::mt19937 mt;
				std::uniform_int_distribution<> uid;
				std::uniform_int_distribution<> uid_trotter;
				std::uniform_real_distribution<> urd;

				//mod function for dealing trotter indices
				inline size_t mod_t(int64_t a) const;

			public:
				QuantumIsing(const Sparse<double>& interaction, size_t num_trotter_slices);

				virtual double update(double beta, double gamma, const std::string& algo = "") override;

				void simulated_quantum_annealing(double beta, double gamma_min, double gamma_max, double step_length, size_t step_num, const std::string& algo = "");

				TrotterSpins get_spins() const;

		};
	} // namespace method
} // namespace openjij

