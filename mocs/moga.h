/*
 * MOCS - Multi-Objective Classifier System
 * Copyright (C) 2003 by Ivan Traus
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef __MOGA_H__
#define __MOGA_H__

#include <mocs/ffunction.h>
#include <mocs/coperator.h>
#include <mocs/moperator.h>
#include <mocs/soperator.h>
#include <mocs/ealgorithm.h>
#include <mocs/mselection.h>

class MOGA : public EvolutionaryAlgorithm {
	protected:
		struct order {
			static size_t k;

			bool operator () (const Individual* a,const Individual* b) const {
				return a->getFitness()[k]<b->getFitness()[k];
			}
		};

		FitnessFunction* func;
		MatingSelection* mating;
		MutationOperator* mutate;
		CrossoverOperator* crossOp;
		SelectionOperator* selection;
		size_t parents,population,best;
		double sharing,crossProb;
		bool elitism;

		virtual void addBest(Population& pop,Population& old);
		virtual void assignFitness(Population& pop);
		virtual Population* crossover(Population& pop);

	public:
		MOGA(Params& p);
		virtual ~MOGA();

		virtual void init(Population& pop);
		virtual Population* final(Population& pop);
		virtual Population* operator () (Population& pop);
};

#endif
