#!/bin/sh

str="circumference"
censor=$(echo "$str" | profgrep -i --censor=stars)

if [ "$censor" = "cir***ference" ]; then
	exit 0
else
	exit 2
fi


