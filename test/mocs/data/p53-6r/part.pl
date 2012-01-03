#!/usr/bin/perl

@file=<STDIN>;

for($i=0;$i<=$#file;$i++) {
	$rand[$i]=int(rand()*($#file+1)*1000);
	print($rand[$i]." ".$file[$i]);
}
