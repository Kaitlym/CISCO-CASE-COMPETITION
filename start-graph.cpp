#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif

#include <math.h>

int graphSize(string fileName, int start, int end){
	int size=0;
	string line;
	
	fstream file(fileName);
	
	while(getline(file, line)){
		line.erase(0, line.find('\t')+1);
		//cout<<stoi(line);
		if(start<=stoi(line) && stoi(line)<=end){
			size++;
		}
		
	}
	//cout<<size;
	return size;
}

bool TestForPrime(int val){
	int limit, factor = 2;
	limit = (long)( sqrtf( (float) val ) + 0.5f );
	while( (factor <= limit) && (val % factor) ){
		factor++;
	}
	return( factor > limit );
}


int prime(int size){
	if(TestForPrime(size)){

		return size;	

	}else{

		if(size%2==0){

			size++;

		}

		while(true){

			if(TestForPrime(size)){

				return size;
			}
			size+=2;
		}
	}
}
int hashFunction(int label, int size){
	return label%size;
}

struct vertex * collisionSearch(struct vertex * vert, int vertLabel){
	struct vertex * temp = vert;
	while(temp->label!=vertLabel){
		temp=temp->next;
	}
	return temp;
}

bool inYearRange(int year, int start, int end){
	if(start<=year && year<=end){
		return true;
	}else{
		return false;
	}
}

void addEdge(struct vertex * startVertex, struct vertex * endVertex){
	//cout<<endVertex->label;
	struct edge * newEdge = new edge();
	newEdge->label = endVertex->label;
	newEdge->next=nullptr;
	
	startVertex->edges++;
	
	//cout<<newEdge->label<<"\n";
	if(startVertex->adjacent==nullptr){
		startVertex->adjacent=newEdge;
	}else{
		struct edge * temp = startVertex->adjacent;
		while(temp->next!=nullptr){							//unordered fix later
			temp=temp->next;
		}
		temp->next=newEdge;
	}
}
