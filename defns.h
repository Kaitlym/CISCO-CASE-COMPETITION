#include<iostream>
#include <fstream>
using namespace std;

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//



struct edge;
struct vertex{
	int label;
	int edges;
	int year;
	vertex* next;
	edge* adjacent;

};

struct edge{
	int label;
	edge* next;
};


void merge(struct vertex *arr, int left, int middle, int right){
	int leftSize=middle-left+1;
	int leftIndex=0;
	
	int rightSize=right-middle;
	int rightIndex=0;
	
	struct vertex lArr[leftSize];
	struct vertex rArr[rightSize];

	
	//cout<<"\n\n"<<"left - "<<left<<"\n";
	for(int i=0; i<leftSize; i++){
		lArr[i]=arr[i+left];
		//cout<<lArr[i].label<<"\n";
	}
	
	//cout<<"right - "<<right<<"\n";
	for(int i=0; i<rightSize; i++){
		rArr[i]=arr[i+middle+1];
		//cout<<rArr[i].label<<"\n";
	}
	
	int index = left;
	while(leftIndex<leftSize && rightIndex<rightSize){
		if(lArr[leftIndex].label<=rArr[rightIndex].label){
			arr[index]=lArr[leftIndex];
			leftIndex++;
		}else{
			arr[index]=rArr[rightIndex];
			rightIndex++;
		}
		
		index++;	
	}
	
	while(leftIndex<leftSize){
		arr[index]=lArr[leftIndex];
		leftIndex++;
		index++;
	}
	while(rightIndex<rightSize){
		arr[index]=rArr[rightIndex];
		rightIndex++;
		index++;
	}
}
void mergeSort(struct vertex *arr, int left,  int right){
	int middle=(left+right)/2;
	if(left>=right){
		return;
	}
	
	mergeSort(arr, left, middle);
	mergeSort(arr, middle+1, right);
	merge(arr, left, middle, right);
}


