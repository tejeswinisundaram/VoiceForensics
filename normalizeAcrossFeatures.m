#! /usr/bin/octave
%===============================================================
%VoiceForensics
%https://github.com/utkarshp/VoiceForensics
%===============================================================
%Copyright 2014 VoiceForensics
%
%Licensed under the Apache License, Version 2.0 (the "License");
%you may not use this file except in compliance with the License.
%You may obtain a copy of the License at
%
%http://www.apache.org/licenses/LICENSE-2.0
%
%Unless required by applicable law or agreed to in writing, software
%distributed under the License is distributed on an "AS IS" BASIS,
%WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
%See the License for the specific language governing permissions and
%limitations under the License.


arguments = argv();

if length(arguments) != 5
	printf("Usage: ./normalizeAcrossFeatures.m data-set-columns output-columns number-of-header-rows filename outputfile \n\n\
data-set-columns: the columns at the beginning of file filename you don't want normalized \n\
outputColumns: Columns at the end that you don't want normalized\n\
number-of-header-rows: rows at the top you want removed\n\
filename: source file which you want normalized\n\
outputfile: name of the normalized file\n\
");
	return;
end
dataSetColumns = str2double(arguments{1,1}); %like filename, index, frameTime etc.
outputColumns = str2double(arguments{2,1}); %like height, weight, age etc.
lastHeaderRow = str2double(arguments{3,1});
sourceFileName = arguments{4,1};
outputFileName = arguments{5,1};


%Manually creating headerFile
fid = fopen(sourceFileName );
txt = fgetl (fid);
header = fopen("headerFile","w");

fputs (header,strcat(txt,"\n"));
fclose(header);
fclose(fid);

%Normalization code

X = real(csvread (sourceFileName));

firstRow = lastHeaderRow+1;
firstColumn = dataSetColumns + 1;
lastColumn = length (X(1,:))-outputColumns;
lastRow = length(X(:,1));

%header = X(1:lastHeaderRow,:);
%X = X(firstRow:lastRow,:);
avg = mean(X(firstRow:lastRow,firstColumn:lastColumn));
sigma = std(X(firstRow:lastRow,firstColumn:lastColumn));

Z = [];
for i = (firstColumn:lastColumn)
	Z = [Z,(X(firstRow:lastRow,i)-avg(i- dataSetColumns ))/sigma(i- dataSetColumns)];
end
Z = [floor(X(firstRow:lastRow,1:dataSetColumns)),Z,X(firstRow:lastRow, lastColumn+1:lastColumn+outputColumns)];
csvwrite(outputFileName,Z);
system(strcat("cat", " ./",outputFileName,">> headerFile"));
system(strcat("mv headerFile "," ./",outputFileName));
