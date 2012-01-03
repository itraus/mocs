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

#ifndef __RATTRIBUTE_H__
#define __RATTRIBUTE_H__

#include <mocs/attribute.h>

class RealAttribute : public Attribute {
		double min,max;

	public:
		RealAttribute();
		RealAttribute(double min,double max);
		virtual ~RealAttribute();

		double getMin() const;
		void setMin(double min);
		double getMax() const;
		void setMax(double max);
		void adjust(double value);
		void adjust(Attribute& att);
};

#endif
