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

if length(arguments) != 4
	printf("Usage: ./splitFiles.m data-set-columns filename1 filename2 directory \n\n\
data-set-columns: the columns at the beginning of file filename1 that you need removed \n\
filename1: Name of the .csv file you want to split into training and test files\n\
filename2: Name of the .csv file which tells the program which subject-ids go into test files\n\
directory: Relative Path to the directory you want the training and test sets in\n\
");
	return
	end
dataSetColumns = str2double(arguments{1,1});
sourceFileName  = arguments{2,1};
testDataMatrix = csvread(arguments{3,1});
directory = arguments{4,1};
system(strcat("mkdir "," ./",directory));
system(strcat("mkdir "," ./",directory, "/training_sets"));
system(strcat("mkdir "," ./",directory, "/test_sets"));

firstColumn = dataSetColumns+1;
fid = fopen(sourceFileName);

%Manually creating headerFile
txt = fgetl (fid);
txt = strcat(txt,"\n");
header = fopen("headerFile","w");
idx = strchr(txt,',');

if (dataSetColumns > 0)
	fputs (header,txt(idx(dataSetColumns)+2:end) );
else
	fputs (header,txt);
end	
fclose(header);
fclose(fid);

%Splitting files based on testdatanumbers.csv

X = csvread(sourceFileName);
X = X(2:end,:);

numFolds = length(testDataMatrix(:,1));
numTestDataSets = length(testDataMatrix(1,:));


for i = (1:numFolds)
	Z = [];
	Y = X;
	for j = (1:numTestDataSets)
		fileName = testDataMatrix(i,j);
		fileRows = find(real(Y(:,1))==fileName);
		Z = [Z;Y(fileRows,:)];
		Y(fileRows,:) = [];
	end
	trainingFileName = strcat("./", directory, "/training_sets/training",num2str(i),".csv");
	testFileName = strcat("./", directory, "/test_sets/test",num2str(i),".csv");
	csvwrite(trainingFileName,real(Y(:,firstColumn:end)));
	csvwrite(testFileName,real(Z(:,firstColumn:end)));
	
	trainingFileName = strcat(" ./", directory, "/training_sets/training",num2str(i),".csv");
	testFileName = strcat(" ./", directory, "/test_sets/test",num2str(i),".csv");
	system("cp headerFile dummy ");
	system(strcat("cat ",trainingFileName," >> dummy"));
	system(strcat("mv dummy ",trainingFileName));

	system("cp headerFile dummy ");
	system(strcat("cat ",testFileName," >> dummy"));
	system(strcat("mv dummy ",testFileName));
end
