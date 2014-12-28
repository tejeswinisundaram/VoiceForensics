#!/usr/bin/env python
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


import csv
import sys
import math

if len(sys.argv) != 6:
	sys.exit("Given " + str(len(sys.argv)) + ' arguments. Expected 5')

filename2 = sys.argv[1]
labelfilename = sys.argv[2]
headerRows = sys.argv[3]
dataSetColumns = sys.argv[4]
outputfilename = sys.argv[5]
openFileObject2 = open(filename2,'r')
csvfile2 = csv.reader(openFileObject2)
outputfile = open(outputfilename,'w')
Labels = csv.reader(open(labelfilename,'r'))
idToLabel = {}
for row in Labels:
	idToLabel[int(row[0])] = (row[1])

ignoreRows = int(headerRows)
ignoreCols = int(dataSetColumns)

r2 = 0
ID = 0
for row2 in csvfile2:
	if r2<ignoreRows:
		r2+=1
		continue
	c2 = 0
	y = []
	for entry in row2:
		if c2==0:
			ID = int(entry)
			c2+=1
			continue
		outputfile.write(idToLabel[ID]+' ')
		if c2<ignoreCols:
			c2+=1
			continue
		outputfile.write(str(c2)+":"+entry)
		c2+=1
	outputfile.write('\n')
	r2+=1
openFileObject2.close()
