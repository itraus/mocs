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

$n=0;
$ilast=-1;
while(<STDIN>) {
	chop;
	@a=split " ",$_;
	if($ilast==-1) {
		$n=1;
		@b=@a;
		$ilast=$a[0];
	} elsif($ilast==$a[0]) {
		for($i=1;$i<=$#a;$i++) {
			$b[$i]=$b[$i]+$a[$i];
		}
		$n++;
	} else {
		for($i=1;$i<=$#b;$i++) {
			$b[$i]=$b[$i]/$n;
		}
		print join(" ",@b)."\n";
		$ilast=$a[0];
		@b=@a;
		$n=1;
	}
}
if(@b>0) {
	print join(" ",@b)."\n";
}
