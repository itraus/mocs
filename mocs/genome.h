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

#ifndef __GENOME_H__
#define __GENOME_H__

#include <vector>

#include <mocs/gene.h>

class Genome : public vector<Gene*> {
		double dev;

	public:
		Genome();
		Genome(size_t size);
		Genome(const Genome& genome);
		virtual ~Genome();

		void init();
		void add(Gene* gene);
		double getDev() const;
		void setDev(double dev);
};

ostream& operator << (ostream& os,const Genome& genome);

#endif
