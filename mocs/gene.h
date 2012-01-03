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

#ifndef __GENE_H__
#define __GENE_H__

#include <mocs/config.h>

class Gene {
	public:
		virtual Gene* newGene() const = 0;
		virtual void init() = 0;
		virtual void mutate() = 0;
		virtual void step(double x) = 0;
		virtual double getDev() const = 0;
		virtual void setDev(double dev) = 0;

		virtual Gene& operator = (const Gene& gene) = 0;
		virtual ostream& operator >> (ostream& os) = 0;
};

#endif
