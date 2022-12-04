#!/bin/bash

# Take year from command line or, if not supplied, take the current year
if [[ -z $1 ]];
then
	year=$(date +%Y)
else
	year=$1
fi

curl -b session=[PUT SESSION COOKIE HERE] https://adventofcode.com/$year/leaderboard/private/view/277686.json > $year.json

