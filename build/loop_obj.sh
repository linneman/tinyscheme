#!/bin/sh
for file in $1/*.c

do
	body=`echo $file | sed 's/\.c//g'`
	printf $body'.o '
done
