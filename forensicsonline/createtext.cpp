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


#include <fstream>
#include <iostream>
# include <stdlib.h>
# include<time.h>

using namespace std;

int main()
{
ofstream outputFile;
outputFile.open("data.csp",fstream::out);
float height;
float weight, bmi;
char sex;
int age;

srand(time(NULL));

outputFile<<"height,"<<rand()%100 + 100 << endl;
outputFile<<"weight," << rand()%40 + 50<<endl;
outputFile<<"bmi," << rand()%10+10<<endl;
outputFile<<"sex," <<rand()%2<<endl;
outputFile<<"age,"<<rand()%100<<endl;

outputFile.close();
cout<< "Done!\n";
}
