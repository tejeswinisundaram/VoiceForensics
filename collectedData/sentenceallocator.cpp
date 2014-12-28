#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string>
#include <cstring>
#include <stack>
#include <queue>
#include <map>

typedef long long lli;
using namespace std;

int main()
{
	fstream sentencelist;
	std::vector<string> sentenceVector;
	sentencelist.open("sentenceList",fstream::in);
	string sentence;
	while(getline(sentencelist,sentence))
	{
		sentenceVector.push_back(sentence);
	}

	sentencelist.close();
	fstream allotedSents;
	allotedSents.open("allotedSentences.txt",fstream::in);

	int studentID=0;
	string outputname="";
	while(!allotedSents.eof())
	{
		outputname = "";
		studentID++;
		outputname += to_string(studentID);
		fstream file;
		file.open(outputname.c_str(),fstream::out);
		int sents;
		for (int i = 0; i < 25; ++i)
		{

			allotedSents >> sents;
			//printf("sents= %d\n",sents);
			sents--;
			file << i+1 << ". " << sentenceVector[sents] << endl;

		}
	}




	return 0;
}
