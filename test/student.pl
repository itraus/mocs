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

sub normalz {
	$x=shift;
	@b=(0.319381530,-0.356563782,1.781477937,-1.821255978,1.330274429);
	$p=0.2316419;
	$t=1/(1+$p*$x);
	$fact=$t;
	$sum=0;
	for($i=0;$i<=$#b;$i++) {
		$sum+=$b[$i]*$fact;
		$fact*=$t;
	}
	return 2*$sum*exp(-$x*$x/2.0)/(sqrt(2*3.14159265358979323846));
}

$n=0;
$sum=0;
$sum2=0;
while(<STDIN>) {
	chop $_;
	($a,$b)=split " ",$_;
	if($a!=0 || $b!=0) {
		$y=$a-$b;
		$sum+=$y;
		$sum2+=$y*$y;
		$n++;
	}
}

$x=$sum/$n;
$s=sqrt(($sum2-($sum*$sum)/$n)/($n-1));

if($s==0) {
	$e=0;
	$t=0;
} else {
	$e=$s/sqrt($n);
	$t=($x-0)/$e;
}

print "# x ".$x."\n";
print "# s ".$s."\n";
print "# e ".$e."\n";
print "# t ".$t."\n";
print "# p ".100.0*(1.0-normalz(abs($t)))."\n";
