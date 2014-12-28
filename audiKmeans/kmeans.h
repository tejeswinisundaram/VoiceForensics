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
#include <sstream>
using namespace std;


typedef pair<int,int> Pair;

struct PairComp {
  bool operator() (const Pair& lhs, const Pair& rhs) const
  {
  	if (lhs.first != rhs.first) return lhs.first < rhs.first;
  	else return lhs.second < rhs.second;
  }
};

class CSVRow
{
	public:
		string const& operator[](std::size_t index) const
		{
			return m_data[index];
		}
		size_t size() const
		{
			return m_data.size();
		}
		void readNextRow(std::istream& str)
		{
			string line;
			getline(str,line);

			stringstream lineStream(line);
			string cell;

			m_data.clear();
			while(getline(lineStream,cell,','))
			{
				m_data.push_back(cell);
			}
		}
	private:
		std::vector<std::string> m_data;
};


class Point
{
public:
	Point(int n)
	{
		coordinates = vector<double>(n,0);
		dim = n;
		clusterIndex = -1;
		subject_id = 0;
		clip_id = 0;
	}
	Point()
	{
		coordinates.clear();
	}
	~Point()
	{
		coordinates.clear();
	}
	vector <double> coordinates;
	int dim;
	int subject_id;
	int clip_id;
	int clusterIndex;


	double dist(Point p)
	{
		assert(dim==p.dim);
		double sqdistance=0;
		for (int i = 0; i < dim; ++i)
		{
			double diff = coordinates[i]-p.coordinates[i];
			sqdistance += pow(diff,2);
		}
		return pow(sqdistance,0.5);
	}

	Point operator+(Point p)
	{
		assert(dim==p.dim);
		Point sum(dim) ;
		for (int i = 0; i < dim; ++i)
			sum.coordinates[i] = coordinates[i]+p.coordinates[i];
		return sum;
	}

	Point operator/(int divisor)
	{
		Point division(dim);
		for (int i = 0; i < dim; ++i)
			division.coordinates[i] = coordinates[i]/divisor;
		return division;
	}

	string getCoordinateString()
	{
		string coordinatestring="";
		for (std::vector<double>::iterator i = coordinates.begin(); i != coordinates.end(); ++i)
		{
			string onecoordinate = to_string(*i);
			coordinatestring += onecoordinate+'\t';
		}
		return coordinatestring;
	}
};

class Cluster
{
public:
	Cluster(vector<Point> allPoints,int i)
	{
		int ind = rand()%allPoints.size();
		centroid = allPoints[ind];
		points.clear();
		index = i;
	}
	~Cluster()
	{
		points.clear();
	}
	vector <Point> points;
	Point centroid;
	int index;

	void updateCenroid()
	{
		Point newCentroid(centroid.dim);
		for (std::vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		{
			newCentroid = newCentroid + *i;
		}
		centroid = newCentroid/points.size();
	}

	void clearPoints()
	{
		points.clear();
	}

	void assignPoint(Point &p)
	{
		points.push_back(p);
		p.clusterIndex = index;
	}

	void print()
	{
		cout << centroid.getCoordinateString() <<endl;
		// for (std::vector<Point>::iterator i = points.begin(); i != points.end(); ++i)
		// {
		// 	cout << '\t' << i->getCoordinateString() << endl;
		// }
	}

};

class Histogram
{
public:
	Histogram()
	{
		distribution.clear();
		totalNumSegments = 0;
	}
	Histogram(int K)
	{
		distribution.clear();
		distribution = vector<int> (K,0);
		totalNumSegments = 0;
	}

	vector <int> distribution;
	int totalNumSegments;

	vector <double> normalizeHistogram()
	{
		vector <double> normalized(distribution.size(),0);
		for (int i = 0; i < distribution.size(); ++i)
			normalized[i] = distribution[i]/ (totalNumSegments*1.0);
		return normalized;
	}

	void addSegment(int binIndex)
	{
//		cout << "Adding to " << binIndex << " but size is " << distribution.size() << endl;
		assert(binIndex < distribution.size());
		totalNumSegments++;
		distribution[binIndex]++;
	}

	string getNormalizedHistogramString()
	{
		string newString = "";
		vector <double> dist = normalizeHistogram();
		for (std::vector<double>::iterator i = dist.begin(); i != dist.end(); ++i)
		{
			newString += "," + to_string(*i);
		}
		return newString; 
	}
};