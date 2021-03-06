#!/bin/sh
if which glibtoolize | grep -q glibtoolize
then
	echo "Found glibtool, running glibtoolize"
	glibtoolize
else
	echo "Didn't find glibtool, trying libtoolize"
	libtoolize
fi
echo "Running aclocal"
aclocal
echo "Running autoheader"
autoheader
echo "Running autoconf"
autoconf
echo "Running automake"
automake --gnu --add-missing
