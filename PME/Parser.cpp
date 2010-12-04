#include "Parser.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <QDebug>

Parser::Parser(char *file)
{
	inputFile = file;
}


int Parser::parse(void)
{
	//open the text file for reading
        ifstream in(inputFile);

	//return 0 if file can't be opened
	if(in.bad())
	{
		cerr << "Error opening file: " << inputFile <<"\n";
		return 0;
	}

	string s, word;

	//Sample samp;
	Object obj;

	vector<string> wordVec;

	//parse all lines from the text file
	while(getline(in, s))
	{
		if(!s.empty())
		{
			wordVec = parseLine(s);
			if(!wordVec.empty())
			{
				word = wordVec.at(0);

				//interpreting the command stored in word
				if(!word.compare("define"))
				{
					obj.samples.clear();

					obj = createObject(in);
					objects.push_back(obj);
				}
				else if(!word.compare("translate"))
				{

					Sample samp;
					vector<Sample> samples;

					int index = findSample(samp, samples, wordVec.at(1));
					if(index >= 0)
					{
						MyPoint point = createPoint(wordVec.at(3), wordVec.at(4), wordVec.at(5));
						Sample transSample = samp;

						for(unsigned int i = 0; i < transSample.nPlanes; i++)
						{
							for(unsigned j = 0; j < transSample.planes[i].nPoints; j++)
							{
								transSample.planes[i].points[j].x += point.x;
								transSample.planes[i].points[j].y += point.y;
								transSample.planes[i].points[j].z += point.z;
							}
						}

						transSample.time = (float)atof(wordVec.at(2).c_str());
						objects.at(index).samples.push_back(transSample);
					}
				}
				else if(!word.compare("rotate"))
				{
                                    /*Sample samp;
                                    vector<Sample> samples;

                                    int index = findSample(samp, samples, wordVec.at(1));
                                    if(index >= 0)
                                    {
                                            Sample transSample = samp;
                                            int angle = (float)atof(wordVec.at(3).c_str());

                                            for(unsigned int i = 0; i < transSample.nPlanes; i++)
                                            {
                                                if(!wordVec.at(2).compare("z"))
                                                    for(unsigned j = 0; j < transSample.planes[i].nPoints; j++)
                                                    {
                                                            transSample.planes[i].points[j].x = cos(angle) - sin(angle);
                                                            transSample.planes[i].points[j].y = sin(angle) + cos(angle);
                                                    }
                                            }

                                            transSample.time = (float)atof(wordVec.at(2).c_str());
                                            objects.at(index).samples.push_back(transSample);
                                    }*/
				}
			}
		}
	}

	in.close();
	return 1;
}


// Called when a new object is being constructed
Object Parser::createObject(ifstream &in)
{
	string s, word;

	Object obj;
	Sample samp;
	MyPlane plane;

	memset(&samp, 0, sizeof(Sample));
	obj.globalColor = false;

	vector<string> wordVec;

	while(getline(in, s))
	{
		if(!s.empty())
		{
			wordVec = parseLine(s);
			if(!wordVec.empty())
			{
				word = wordVec.at(0);

				if(!word.compare("name"))
				{
					obj.name = wordVec.at(1);
				}
				else if(!word.compare("plane"))
				{
					memset(&plane, 0, sizeof(MyPlane));
					storePoints(plane, in);
					samp.planes[samp.nPlanes++] = plane;
				}
				else if(!word.compare("color"))
				{
					obj.color = createColor(wordVec.at(1), wordVec.at(2),
											wordVec.at(3), wordVec.at(4));
					obj.globalColor = true;
				}
				else if(!word.compare("done"))
				{
					//storing sample in newly created object
					obj.samples.push_back(samp);
					return obj;
				}
			}
		}
	}
	return obj;
}


// Called when a plane is being constructed
void Parser::storePoints(MyPlane &plane, ifstream &in)
{
	MyPoint point;
	string s;

	vector<string> wordVec;

	while(getline(in, s))
	{
		if(!s.empty())
		{
			wordVec = parseLine(s);
			if(!wordVec.empty())
			{
				//done storing planes points
				if(!wordVec.at(0).compare("done"))
					break;

				point = createPoint(wordVec.at(0), wordVec.at(1), wordVec.at(2));

				//has a color
				if(wordVec.size() == 7)
				{
					Color color = createColor(wordVec.at(3), wordVec.at(4), wordVec.at(5), wordVec.at(6));
					point.color = color;
				}

				plane.points[plane.nPoints++] = point;
			}
		}
	}
}


/* ============ Getters/Setters ============ */

// Returns all parsed objects/samples
vector<Object> Parser::getObjects()
{
	return objects;
}

/* ============ General Helper Methods ============ */

// Takes three values and returns a color struct
Color Parser::createColor(string _r, string _g, string _b, string _a)
{
	Color c;

	memset(&c, 0, sizeof(Color));

	c.r = (float)atof(_r.c_str()); 
	c.g = (float)atof(_g.c_str()); 
	c.b = (float)atof(_b.c_str()); 
	c.a = (float)atof(_a.c_str()); 
	
	return c;
}

//Takes three values and returns a point struct
MyPoint Parser::createPoint(string _x, string _y, string _z)
{
	MyPoint point;

	memset(&point, 0, sizeof(MyPoint));

	point.x = (float)atof(_x.c_str());
	point.y = (float)atof(_y.c_str());
	point.z = (float)atof(_z.c_str());

	return point;
}


// Translates all points by x, y, z
Sample Parser::translateSample(Sample samp, MyPoint point)
{
	Sample transSample = samp;

	for(unsigned int i = 0; i < transSample.nPlanes; i++)
	{
		for(unsigned int j = 0; j < transSample.planes[i].nPoints; j++)
		{
			transSample.planes[i].points[j].x += point.x;
			transSample.planes[i].points[j].y += point.y;
			transSample.planes[i].points[j].z += point.z;
		}
	}

	return transSample;
}


// Places the most recently created sample of an object in samp
int Parser::findSample(Sample &samp, vector<Sample> &samples, string name)
{
	vector<Object>::iterator i;
	int count = -1;

	for(i = objects.begin(); i != objects.end(); i++)
	{
		count++;

		if(!(i->name.compare(name)))
		{
			samp = i->samples.at(i->samples.size()-1);
			samples = i->samples;
			break;
		}
	}

	return count;
}


// Prints all objects created by the parser
void Parser::printObjects()
{
	vector<Object>::iterator i;
	int count = 0;

        //Printing all objects
	for (i = objects.begin(); i != objects.end(); i++)
	{
		count = 0;

                cerr << "Object:\n{\n";
                cerr << "\tname:\t" << i->name << "\n";
		if(i->globalColor)
		{
                        cerr << "\tcolor:\t";
                        cerr << i->color.r << " ";
                        cerr << i->color.g << " ";
                        cerr << i->color.b << " ";
                        cerr << i->color.a << "\n";
		}

		vector<Sample>::iterator s;
		vector<Sample> samples;
		samples = i->samples;

		//Print all object samples
		for(s = samples.begin(); s != samples.end(); s++)
		{
                        cerr << "\tsample " << ++count << ":\n\t{\n";
                        cerr << "\t\ttime:\t" << s->time << "\n";

			for(unsigned int j = 0; j < s->nPlanes; j++)
			{
                                cerr << "\t\tPlane " << j << ":\n";

				for(unsigned int k = 0; k < s->planes[j].nPoints; k++)
				{
                                        cerr << "\t\t\t" << s->planes[j].points[k].x << " ";
                                        cerr << s->planes[j].points[k].y << " ";
                                        cerr << s->planes[j].points[k].z << " ";

					if(!(i->globalColor))
					{
                                                cerr << s->planes[j].points[k].color.r << " ";
                                                cerr << s->planes[j].points[k].color.g << " ";
                                                cerr << s->planes[j].points[k].color.b << " ";
                                                cerr << s->planes[j].points[k].color.a << " ";
					}
                                        cerr << "\n";
				}
			}
                        cerr << "\t}\n";
		}
                cerr << "}\n\n";
	}
}

/* ============ String Parsing Helpers ============ */

// Splits the string into words and returns them in
// a string vector.
vector<string> Parser::parseLine(string s)
{
	vector<string> wordVec;
	string line,word;

	stringstream ss(s);
    while (ss.good())
	{
      ss >> word;
      //strip(word);
      wordVec.push_back(word);
    }

	return wordVec;
}


// Strip leading and trailing punctuation
void Parser::strip(string &s) 
{
  string::iterator i = s.begin();
  while (ispunct(*i)) s.erase(i);
  string::reverse_iterator j = s.rbegin();
  while (ispunct(*j)) {
    s.resize(s.length()-1);
    j = s.rbegin();
  }
}

Parser::~Parser(void)
{
}
