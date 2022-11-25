#!/bin/sh

profout=$(echo 'circumference' | profgrep \
	| lua -e 'for c in io.stdin:lines(1) do print(c:byte()) end')
grepout=$(echo 'circumference' | grep cum \
	| lua -e 'for c in io.stdin:lines(1) do print(c:byte()) end')

if [ "$profout" = "$grepout" ]; then
	exit 0
else
	exit 2
fi

