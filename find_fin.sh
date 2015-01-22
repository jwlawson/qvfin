#!/bin/bash
# Run qvfin on all sizes of quiver up to 9.
#
# This script find the mutation finite quivers up to size 9. These are stored
# as string representations in the files 3_fin, 4_fin etc and put in the
# specified directory.

sizes=(3 4 5 6 7 8 9)

suf="_fin"
dir="~/result/finite"

if [ ! -d "${dir}" ];
then
	mkdir -p ${dir}
fi

for s in ${sizes[@]};
do
	qvfin ${s} "-o ${dir}/${s}${suf}"
done

