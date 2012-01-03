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

$prefix=$ARGV[3];
@runs=split ",",$ARGV[0];
$probs=$ARGV[1];
$algos=$ARGV[2];

sub show {
	return sprintf("%.1f",$_[0]);
}

sub stats {
	my ($prob,$algo,$type,$val,$dev,$head,$iter,@a,$i,$avg,$std,$m,$s);
	$prob=$_[0];
	$algo=$_[1];
	$type=$_[2];
	if($type eq "time") {
		$val=`grep user ${prefix}out/$prob/$algo/time | cut -f2`;
		@a=split "\n",$val;
		for($i=0,$avg=0;$i<=$#a;$i++) {
			($m,$s)=split "m",$a[$i];
			$avg+=$m*60+$s;
		}
		$avg/=$#a+1.0;
		for($i=0,$std=0;$i<=$#a;$i++) {
			($m,$s)=split "m",$a[$i];
			$std+=($m*60+$s-$avg)**2;
		}
		$std=sqrt($std/($#a+1.0));
		$val=$avg;
		$dev=$std;
	} else {
		$val=`grep $type ${prefix}out/$prob/$algo/stats | cut -f4 -d\\  `;
		$dev=`grep $type ${prefix}out/$prob/$algo/stats | cut -f5 -d\\  `;
		chop $val;
		chop $dev;
	}
	$total{$prob.$algo.$type}=$val;
	$stdev{$prob.$algo.$type}=$dev;
	return show($val).'&'.show($dev);
}

sub test {
	my ($test,@probs,$algo1,$algo2,$type,$t);
	$test=$_[0];
	@probs=split ",",$_[1];
	$algo1=$_[2];
	$algo2=$_[3];
	$type=$_[4];
	open OUT,">$test-$algo1-$algo2.tmp";
	foreach $prob (@probs) {
		print OUT $total{$prob.$algo1.$type}." ".$total{$prob.$algo2.$type}."\n";
	}
	close OUT;
	open IN,"./$test.pl < $test-$algo1-$algo2.tmp|";
	$t=0;
	while(<IN>) {
		chop $_;
		if($_=~/^# p (.*)$/) {
			$t=$1;
		}
	}
	close IN;
	unlink $test."-".$algo1."-".$algo2.".tmp";
	return $t;
}

sub cv {
	my (@probs,@algos,$algo,$prob,$n,$sumt,$meant);
	@probs=split ",",$_[0];
	@algos=split ",",$_[1];
	print '{\scriptsize\tt'."\n";
	print '\begin{tabular}{r@{ }l | ';
	map { print 'r@{$\pm$}l '; } @algos;
	print '}'."\n";
	print '\hline'."\n".'Id & Problem ';
	foreach $algo (@algos) {
		print '& \multicolumn{2}{c}{'.uc($algo).'} ';
	}
	print "\\\\\n".'\hline\hline'."\n";
	$n=0;
	foreach $prob (@probs) {
		print ''.($n+1).' & '.$prob.' ';
		foreach $algo (@algos) {
			print '& '.(stats $prob,$algo,"tba").' ';
		}
		print "\\\\\n";
		$n++;
	}
	print '\hline'."\n".'\tt & average ';
	foreach $algo (@algos) {
		$sumt=0;
		foreach $prob (@probs) {
			$sumt+=$total{$prob.$algo."tba"};
		}
		$meant=$sumt/$n;
		foreach $prob (@probs) {
			$devt+=($total{$prob.$algo."tba"}-$meant)**2;
		}
		$devt=sqrt($devt/$n);
		print '& '.show($sumt/$n).'&'.show($devt).' ';
	}
	print "\\\\\n\\hline\n".'\end{tabular}}'."\n\n";
}

sub tw {
	my ($probs,@algos,$algo,$algo2,$algo1);
	$probs=$_[0];
	@algos=split ",",$_[1];
	print '{\scriptsize\tt'."\n";
	print '\begin{tabular}{l ';
	map { print '|r r '; } @algos;
	print '}'."\n";
	print '\hline'."\n".' ';
	foreach $algo (@algos) {
		print '& \multicolumn{2}{|c}{'.uc($algo).'} ';
	}
	print "\\\\\n".'\hline\hline'."\n";
	foreach $algo2 (@algos) {
		print uc($algo2).' ';
		foreach $algo1 (@algos) {
			if($algo1 ne $algo2) {
				print '&'.show(test "student",$probs,$algo1,$algo2,"tba").'T & '.show(test "wilcoxon",$probs,$algo1,$algo2,"tba").'W ';
			} else {
				print '&& ';
			}
		}
		print "\\\\\n";
	}
	print "\\hline\n".'\end{tabular}}'."\n\n";
}

sub sm {
	my (@probs,@algos,$algo,$prob,$n,$sumt,$meant);
	@probs=split ",",$_[0];
	@algos=split ",",$_[1];
	print '{\scriptsize\tt'."\n";
	print '\begin{tabular}{r@{ }l@{ }r | ';
	map { print 'r@{$\pm$}l '; } @algos;
	print '}'."\n";
	print '\hline'."\n".'Id & Problem & ';
	foreach $algo (@algos) {
		print '& \multicolumn{2}{c}{'.uc($algo).'} ';
	}
	print "\\\\\n".'\hline\hline'."\n";
	$n=0;
	foreach $prob (@probs) {
		print ''.($n+1).' & '.$prob.' & train ';
		foreach $algo (@algos) {
			print '& '.(stats $prob,$algo,"Tba");
		}
		print "\\\\\n";
		print ' & & test ';
		foreach $algo (@algos) {
			print '& '.(stats $prob,$algo,"tba");
		}
		print "\\\\\n";
		print ' & & rules ';
		foreach $algo (@algos) {
			print '& '.(stats $prob,$algo,"rba");
		}
		print "\\\\\n";
		print ' & & time ';
		foreach $algo (@algos) {
			print '& '.(stats $prob,$algo,"time");
		}
		print "\\\\\n\\hline\n";
		$n++;
	}
	print '\hline'."\n".'& average & train ';
	foreach $algo (@algos) {
		$sum=0;
		foreach $prob (@probs) {
			$sum+=$total{$prob.$algo."Tba"};
		}
		$mean=$sum/$n;
		foreach $prob (@probs) {
			$dev+=($total{$prob.$algo."Tba"}-$mean)**2;
		}
		$dev=sqrt($dev/$n);
		print '& '.show($sum/$n).'&'.show($dev);
	}
	print '\\\\'."\n".'& & test ';
	foreach $algo (@algos) {
		$sum=0;
		foreach $prob (@probs) {
			$sum+=$total{$prob.$algo."tba"};
		}
		$mean=$sum/$n;
		foreach $prob (@probs) {
			$dev+=($total{$prob.$algo."tba"}-$mean)**2;
		}
		$dev=sqrt($dev/$n);
		print '& '.show($sum/$n).'&'.show($dev);
	}
	print '\\\\'."\n".'& & rules ';
	foreach $algo (@algos) {
		$sum=0;
		foreach $prob (@probs) {
			$sum+=$total{$prob.$algo."rba"};
		}
		$mean=$sum/$n;
		foreach $prob (@probs) {
			$dev+=($total{$prob.$algo."rba"}-$mean)**2;
		}
		$dev=sqrt($dev/$n);
		print '& '.show($sum/$n).'&'.show($dev);
	}
	print '\\\\'."\n".'& & time ';
	foreach $algo (@algos) {
		$sum=0;
		foreach $prob (@probs) {
			$sum+=$total{$prob.$algo."time"};
		}
		$mean=$sum/$n;
		foreach $prob (@probs) {
			$dev+=($total{$prob.$algo."time"}-$mean)**2;
		}
		$dev=sqrt($dev/$n);
		print '& '.show($sum/$n).'&'.show($dev);
	}
	print "\\\\\n\\hline\n".'\end{tabular}}'."\n\n";
}

sub mo {
}

if(scalar@ARGV!=3 && scalar@ARGV!=4) {
	print "usage: ./results.pl cv,mo problems algorithms [prefix]\n";
	exit;
}

print '\documentclass[10pt]{article}'."\n";
print '\usepackage{rotating}'."\n";
print '\begin{document}'."\n";

foreach $run (@runs) {
	if($run eq "cv") {
		cv $probs,$algos;
		tw $probs,$algos;
		sm $probs,$algos;
	} elsif($run eq "mo") {
		mo $probs,$algos;
	}
}

print '\end{document}'."\n";
