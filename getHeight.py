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
var1 = sys.argv[1]
var2 = sys.argv[2]
heights = csv.reader(open(var1,'r'),delimiter=',')
idToHeight = {}
for row in heights:
	idToHeight[int(row[0])] = (row[1])
with open(var2,'r') as csvfile:
	featuresReader = csv.reader(csvfile,delimiter=',')
	c = 0
	for row in featuresReader:		
		rowString = ""
		ID = row[0]	
		for value in row:
			rowString +=  value + ','
		if c==0:
			rowString+=var1
		else:
			rowString+= idToHeight[int(ID)]
		print rowString
		c += 1
