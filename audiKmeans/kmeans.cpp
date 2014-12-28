//
//===============================================================
//VoiceForensics
//https://github.com/utkarshp/VoiceForensics
//===============================================================
//Copyright 2014 VoiceForensics
//
//Licensed under the Apache License, Version 2.0 (the "License");
//you may not use this file except in compliance with the License.
//You may obtain a copy of the License at
//
//http://www.apache.org/licenses/LICENSE-2.0
//
//Unless required by applicable law or agreed to in writing, software
//distributed under the License is distributed on an "AS IS" BASIS,
//WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//See the License for the specific language governing permissions and
//limitations under the License.




#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>
#include <cmath>
#include <assert.h>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include "kmeans.h"

#define ITER 100
#define INFTY 1000000.0
#define FILEATTR 3
#define X 0
#define Y 1
typedef long long lli;
typedef pair<int,int> Pair;
typedef std::map< Pair, Histogram, PairComp> Map;

using namespace std;

std::istream& operator>>(std::istream& str,CSVRow& data)
{
	data.readNextRow(str);

	return str;
}
 

int main(int argc, char *argv[])
{
	int K,numPoints=0,dim;
	if (argc != 4)
	{
		cout << "Passed " << argc << " arguments. Need 4\n";
		cout << "Usage: " << argv[0] << " K dimension csv-file-name\n";
		return 1;
	}
	K = atoi(argv[1]);
	dim = atoi(argv[2]);

	srand(time(NULL));

	ifstream csvfile;
	csvfile.open(argv[3],fstream::in);
	string header;
	getline(csvfile,header);
	vector<Point> allPoints;

	CSVRow row;
	while (csvfile >> row)
	{
		numPoints++;
		Point newPoint(dim);
		string sub = row[0],clip = row[1];

		if(sub=="8") cout << "string is " << clip;


		newPoint.subject_id = atof(sub.c_str());
		newPoint.clip_id = atof(clip.c_str());
		if (sub=="8") cout << " clip is " << newPoint.clip_id << endl;
		for (int i = FILEATTR; i < row.size(); ++i)
		{
			newPoint.coordinates[i-FILEATTR] = atof(row[i].c_str());
		}
		allPoints.push_back(newPoint);
	}
	csvfile.close();
	//cout << "Input reading finished\n";
	assert(numPoints == allPoints.size());
	vector<Cluster> bin(K,Cluster(allPoints,-1));
	for (int i = 0; i < K; ++i)
	{
		bin[i] = Cluster(allPoints,i);
	}

	for (int i = 0; i < ITER; ++i)
	{
		for (std::vector<Cluster>::iterator i = bin.begin(); i != bin.end(); ++i)
			i->clearPoints();
		for (std::vector<Point>::iterator i = allPoints.begin(); i != allPoints.end(); ++i)
		{
			double min_d = INFTY;
			int min_index = -1;
			for (int j = 0; j < K; ++j)
			{
				double newdist = i->dist(bin[j].centroid);
				if (newdist<min_d)
				{
					min_d = newdist;
					min_index = j;
				}		
			}
			bin[min_index].assignPoint(*i);
		}

		for (std::vector<Cluster>::iterator i = bin.begin(); i != bin.end(); ++i)
			i->updateCenroid();
	}


	Map histogram;
	for (std::vector<Point>::iterator i = allPoints.begin(); i != allPoints.end(); ++i)
	{
		int sid = i->subject_id, cid = i->clip_id;
		Pair pair = make_pair(sid,cid);
		if (histogram.find(pair) == histogram.end())
		{
			//cout << "Initializing for pair: " << sid << " " << cid << endl;
			histogram[pair] = Histogram(K);
		}
		histogram[pair].addSegment(i->clusterIndex) ;
	}

	for (Map::iterator i = histogram.begin();i!=histogram.end();i++)
	{
		i->second.normalizeHistogram();
		cout << i->first.first << '-' << i->first.second << i->second.getNormalizedHistogramString() << endl;
	}
	
		return 0;
}
	