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

if len(sys.argv) != 7:
	sys.exit("Given " + str(len(sys.argv)) + ' arguments. Expected 6')

filename1 = sys.argv[1]
filename2 = sys.argv[2]
labelfilename = sys.argv[3]
headerRows = sys.argv[3+1]
dataSetColumns = sys.argv[4+1]
outputfilename = sys.argv[5+1]
openFileObject1 = open(filename1,'r')
csvfile1 = csv.reader(openFileObject1)
outputfile = open(outputfilename,'w')
Labels = csv.reader(open(labelfilename,'r'))
idToLabel = {}
for row in Labels:
	idToLabel[int(row[0])] = (row[1])

r1=0
ignoreRows = int(headerRows)
ignoreCols = int(dataSetColumns)
for row1 in csvfile1:
	if r1<ignoreRows:
		r1+=1
		continue
	c1 = 0
	x = []
	ID = 0
	for entry in row1:
		if c1==0:
			ID = int(entry)
			c1+=1
			continue
		if c1<ignoreCols:
			c1+=1
			continue
		x.append(float(entry))
	r2 = 0
	openFileObject2 = open(filename2,'r')
	csvfile2 = csv.reader(openFileObject2)
	outputfile.write(idToLabel[ID]+' ')
	outputfile.write("0:"+str(r1)+' ')
	for row2 in csvfile2:
		if r2<ignoreRows:
			r2+=1
			continue
		c2 = 0
		y = []
		for entry in row2:
			if c2<ignoreCols:
				c2+=1
				continue
			y.append(float(entry))
		chi2 = 1
		#print x,y
		for i in xrange(0,len(x)):
			if x[i]+y[i]==0:
				print i, "Dividing by zero\n"
			term = (2*((x[i]-y[i])**2))/(x[i]+y[i])
			if math.isnan(term):
				print i, "Getting Nan"
			chi2 -= term 
		outputfile.write(str(r2)+':'+str(chi2)+' ')
		r2+=1
	outputfile.write('\n')
	openFileObject2.close()
	r1 += 1
openFileObject1.close()
