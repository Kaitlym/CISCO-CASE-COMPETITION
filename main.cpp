#ifndef DEFNS
#define DEFNS
#include "defns.h"
#endif

#include "start-graph.cpp"



int main(int argc, const char* argv[]){
	//edges
	fstream edgesFile(argv[1]);
	
	
	//dates associated with vertices
	fstream datesFile(argv[2]);
	int start, end;
	
	//command
	fstream commandsFile(argv[3]);
	
	
	//vertex
	int vertexCount = 0;
	int edgeCount = 0;
	struct vertex *vertexIdentifiers;
	
	//hash
	struct vertex **vertexHash;
	int hashSize  = 0;
	int hashI = 0;
	
	//outline
	int pi, pj;
	struct vertex * piVert;
	struct vertex * pjVert;
	
	//out-degree
	int * outDegree;
	
	//line
	string line;
	string subline;
	
	//COMMANDS
	commandsFile>>line;
	while(true){
		//cout<<line<<"\n";
		
		if(line=="start-graph"){
			//start bound
			commandsFile>>line;
			start=stoi(line);
			//end bound
			commandsFile>>line;
			end=stoi(line);
			
			//command
			cout<<"Command: start-graph "<<start<<"-"<<end<<"\n";
			
			vertexCount = graphSize(argv[2], start, end);
			vertexIdentifiers = new struct vertex[vertexCount];
			
			outDegree = new int[vertexCount];
			outDegree[0] = vertexCount;
			
			hashSize = prime(3*vertexCount);
			vertexHash = new struct vertex * [hashSize];
			//vertexHash = {nullptr};
			
			//add vertex labels into array
			int vertexIndex = 0;
			while(getline(datesFile, line)){
				subline = line.substr(line.find('\t')+1, line.length()-line.find('\t'));
				//cout<<"\n"<<stoi(subline);
				
				if(inYearRange(stoi(subline), start, end)){
					struct vertex vert = {.label= stoi(line), .edges=0, .year=stoi(subline), .next=nullptr, .adjacent=nullptr};
					vertexIdentifiers[vertexIndex] = vert;
					vertexIndex++;
				}
			}

			//sort vertex labels
			mergeSort(vertexIdentifiers, 0, vertexCount-1);
			
			//add to hash
			for(int i=0; i<vertexCount; i++){
				hashI = hashFunction(vertexIdentifiers[i].label, hashSize);
				if(vertexHash[hashI]==nullptr){
					vertexHash[hashI] = &vertexIdentifiers[i];
				}else{
					struct vertex * temp;
					temp = vertexHash[hashI];
					while(temp->next!=nullptr){
						temp=temp->next;
					}
					temp->next=&vertexIdentifiers[i];
				}
				
			}
			
			/*
			for(int i=0; i<hashSize; i++){
				
				if(vertexHash[i]!=nullptr){
					cout<< vertexHash[i]->label<<"\t-\t"<<vertexHash[i]->year<<"\n";
				}
				
			}
			*/
			
			//add edges
			while(getline(edgesFile, line)){
				//pi - start
				pi = stoi(line);
				//pi = hashFunction(pi, hashSize);
				
				//pj - end
				subline = line.substr(line.find('\t')+1, line.length()-line.find('\t'));
				pj = stoi(subline);
				//pj = hashFunction(pj, hashSize);
				
				//pi vertex
				piVert = collisionSearch(vertexHash[hashFunction(pi, hashSize)], pi);
				
				//pj vertex
				pjVert = collisionSearch(vertexHash[hashFunction(pj, hashSize)], pj);
				
				if(inYearRange(piVert->year, start, end)&&inYearRange(pjVert->year, start, end)){
					addEdge(piVert, pjVert);
					edgeCount++;
					outDegree[piVert->edges-1]--;
					outDegree[piVert->edges]++;
				}
				
			}
			
			cout<<"\t|V| = "<<vertexCount<<" vertices\n";
			cout<<"\t|E| = "<<edgeCount<<" edges\n";
		}else if(line=="out-degree"){
			cout<<"Command: out-degree\n";
			
			float averageOutDegree = (float)edgeCount/vertexCount;
			averageOutDegree = floor(averageOutDegree*100)/100;
			printf("The graph G has average out-degree %d / %d = %.2f\n",edgeCount, vertexCount, averageOutDegree);
			cout<<"The out-degree distribution is:\n";
			cout<<"\tOut-Degree : Number of vertices\n";
			//cout<<"The graph G has average out-degree "<<edgeCount<<"/"<<vertexCount<<" = "<<averageOutDegree<<"\n";
			for(int i=0; i<vertexCount; i++){
				
				if(outDegree[i]!=0){
					cout<<"\t"<<i<<" : "<<outDegree[i]<<"\n";
				}
				
			}
		}else if(line=="diameter"){
			cout<<"Command: diameter\n";
			cout<<"The graph G has diameter "<<".\n";
		}else if(line=="scc"){
			cout<<"Command: scc\n";
			cout<<"The graph G has "<< "strongly connected components:\n";
			cout<<"\tSize : Number\n";
		}else if(line=="end-graph"){
			cout<<"Command: end-graph\n";
			
			
			
			break;
		}
		
		commandsFile>>line;
	}
	
	//START-GRAPH
	//startGraph(start, end);

	//adjacenty list
		//in going edges
		//out going edges
	
	
	
	return 0;
}
