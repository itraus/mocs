#!/usr/bin/perl -w

# MOCS - Multi-Objective Classifier System
# Copyright (C) 2003 by Ivan Traus
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.

while(<STDIN>) {
	chop $_;
	push @p,$_;
}

for($i=0;$i<@p;$i++) {
	@a=split " ",$p[$i];
	for($j=0,$nondom=1;$j<@p && $nondom==1;$j++) {
		@b=split " ",$p[$j];
		for($k=0,$less=0;$k<@a && $a[$k]>=$b[$k];$k++) {
			if($a[$k]>$b[$k]) {
				$less=1;
			}
		}
		if($k==@a) {
			$nondom=1-$less;
		}
	}
	if($nondom==1) {
		print $p[$i]."\n";
	}
}
