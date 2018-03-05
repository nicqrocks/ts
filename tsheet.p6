#!/usr/bin/env perl6

constant $tsloc = %*ENV<TSLOC> || $*HOME ~ "/Documents/ts";

sub USAGE() {
	print Q:c:to/END/;
	USAGE: {$*PROGRAM-NAME} [-a|--after DATE] [-b|--before DATE]
	END
}

sub MAIN(:$after is copy, :$before is copy) {
	my %info;
	my $week;

	if $after.defined  { $after  = qqx{date -d "$after"  '+%F'}.chomp; }
	if $before.defined { $before = qqx{date -d "$before" '+%F'}.chomp; }

	for $tsloc.IO.lines -> $l {
		#Split apart the line.
		my ($stat, $iso) = $l.split: ',';
		my $dt = DateTime.new: $iso;

		#Check if there are any limits.
		if $after.defined  { next unless $dt.Date > Date.new($after);  }
		if $before.defined { next unless $dt.Date < Date.new($before); }

		#Save the info.
		#say ($stat == 1 ?? "out: " !! "in:  ") ~ $dt.hh-mm-ss;
		%info{$dt.yyyy-mm-dd}[$stat] = $dt;
	}

	for %info.keys.sort -> $d {
		#FIRST { $week = Date.new($d).week[1]; }
		my @t = %info{$d}<>;

		my $diff = @t[0,1]».defined.all
			?? sprintf("%.2f", (@t[1] - @t[0]) / 3600)
			!! "?.??";

		for @t[0,1] {
			$_ = .WHAT ~~ DateTime
				?? sprintf("%02d:%02d", .hour, .minute)
				!! "??:??";
		}

		($d, |@t, $diff).join(',').say;
	}
}
