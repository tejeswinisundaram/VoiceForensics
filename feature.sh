#!/bin/bash
#===============================================================
#VoiceForensics
#https://github.com/utkarshp/VoiceForensics
#===============================================================
#Copyright 2014 VoiceForensics
#
#Licensed under the Apache License, Version 2.0 (the "License");
#you may not use this file except in compliance with the License.
#You may obtain a copy of the License at
#
#http://www.apache.org/licenses/LICENSE-2.0
#
#Unless required by applicable law or agreed to in writing, software
#distributed under the License is distributed on an "AS IS" BASIS,
#WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
#See the License for the specific language governing permissions and
#limitations under the License.
mkdir ../features
for i in $(find . -type d)
	do
		if [ $i != "." ]
			then
						mkdir ../features/$i-feature
						for j in {1..25}
							do
							SMILExtract -C ../config/MFCC12\_0\_D\_A_append.conf -I $i/$i-$j.wav -O opr.csv		
							python modified_height.py $i $j > ../features/$i-feature/$i-$j.csv
							cat ../features/$i-feature/$i-$j.csv >> op.csv

							done
		fi
	done


