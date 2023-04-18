//1190880_Qays Safa
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MAXIMUM SIZE OF FILE NAME SEGMENT.TXT = 11 size
#define FILE_SIZE 20
//MAXIMUM SIZE OF TOWN NAME 'RUSSARA' = 7 SIZE
#define TOWN_SIZE 50
//maximum line size read from the segment file
#define MAXLINE 100
//MAXIMUM INTEGER VALUE, HERE IN OUR CASE IT MEANS INFINITY
#define INT_MAX 21474836
struct ll
{
	int distance;
	char town_name[TOWN_SIZE];
};

struct graph
{
	struct ll *root;
};
/*This functions checks whether the string is an integer, that means we check if every character in the input array is a digit*/
int isDigit(char *input)
{
	for ( int i = 0 ; i < strlen(input) ; i++ )
	{
		if ( input[i] == '\n' )
		{
			return 1;
		}
		else if ( input[i] < 48 || input[i] > 57 )
		{
			return 0;
		}
	}
	return 1;
}
/*This function is for debugging, it prints the graph on the screen*/
void printGraph(struct ll **g, int total_roads)
{
	for ( int i = 0 ; i < total_roads ; i++ ) {
		for ( int j = 0 ; j < total_roads ; j++ ) {
			if ( g[i][j].distance == INT_MAX ) {
				printf("i ");
			}
			else {
				printf("%d ",g[i][j].distance);
			}
		}
		printf("\n");
	}
}
/*This function reads the segment file, get the max road number, so that we can malloc the memory of only that size, to save memory*/
int getMaxRoadNumber(char * filename )
{
	int max = 0;
	FILE *ptr = fopen(filename, "r");
	if ( ptr == NULL )
	{
		printf("File didn't open\n");
		exit(-1);
	}
	//Read file
	char *delim = " ";
	char read_line[MAXLINE];
	int start_edge, end_edge, distance;
	char town_name[TOWN_SIZE];
	//Reads a single line from the segment.txt
	while ( fgets(read_line,MAXLINE,ptr) ) {
        //Tokenize the input into word, and assign each value correctly to start, end, town and distance
		char *ptr = strtok(read_line, delim);
		int i = 0 ;
		town_name[0] = '\0';

		while(ptr != NULL) {
			if ( isDigit(ptr) == 1 ){
				if ( i == 0 ) {
					sscanf(ptr, "%d", &start_edge);
				}
				else if ( i == 1 ) {
					sscanf(ptr, "%d", &end_edge);
				}
				else {
					sscanf(ptr, "%d\n", &distance);
				}
			}
			else {
				strcat(town_name,ptr);
				if ( i != 0 ) {
					strcat(town_name," ");
				}
			}
			i++;
			ptr = strtok(NULL, delim);
		}
		town_name[strlen(town_name) - 1] = '\0';
        //Finds the max road number and saves it
		if ( start_edge > max )
		{
			max = start_edge;
		}
		if ( end_edge > max )
		{
			max = end_edge;
		}
	}
	fclose(ptr);
	return max;
}
/*This function again reads the segment file, but this time we have count of roads, so we simply insert the roads in the graph*/
void createGraph(char * filename, struct ll ***g, int max)
{
	FILE *ptr = fopen(filename, "r");
	if ( ptr == NULL )
	{
		printf("File didn't open\n");
		exit(-1);
	}
	//Read file
	char *delim = " ";
	char read_line[MAXLINE];
	int start_edge, end_edge, distance;
	char town_name[TOWN_SIZE];
	while ( fgets(read_line,MAXLINE,ptr) ) {
		char *ptr = strtok(read_line, delim);
		int i = 0 ;
		town_name[0] = '\0';

		while(ptr != NULL) {
			if ( isDigit(ptr) == 1 ){
				if ( i == 0 ) {
					sscanf(ptr, "%d", &start_edge);
				}
				else if ( i == 1 ) {
					sscanf(ptr, "%d", &end_edge);
				}
				else {
					sscanf(ptr, "%d\n", &distance);
				}
			}
			else {
				strcat(town_name,ptr);
				if ( i != 0 ) {
					strcat(town_name," ");
				}
			}
			i++;
			ptr = strtok(NULL, delim);
		}
		town_name[strlen(town_name) - 1] = '\0';
		//Bi-directional --- 2 insertions
		(*g)[start_edge - 1][end_edge - 1].distance = distance;
		strcpy((*g)[start_edge - 1][end_edge - 1].town_name, town_name);
		(*g)[end_edge - 1][start_edge - 1].distance = distance;
		strcpy((*g)[end_edge - 1][start_edge - 1].town_name, town_name);

		//printf("%d %d %s %d\n",start_edge,end_edge, town_name ,distance);
	}
	//printGraph(*g,max);
	fclose(ptr);
}
/*Prints the cities for option 2, it takes source, destination and parent array as input, starts from parent[destination] and keep printing parent town until
-1 is reached, -1 is parent of source*/
void printTown(int source, int destination, int *parent, int count, FILE *f, struct ll **g)
{

	int temp = destination;
	if ( parent[temp] != -1 ) {
		printTown(source, parent[temp],parent, count + 1, f, g);
		if ( count != 0 ) {
			if ( f == NULL ) {
				printf("%s->",g[temp][parent[temp]].town_name);
			}
			else {
				fprintf(f,"%s->",g[temp][parent[temp]].town_name);
			}
		}
		else {
			if ( f == NULL ) {
				printf("%s",g[temp][parent[temp]].town_name);
			}
			else {
				fprintf(f,"%s",g[temp][parent[temp]].town_name);
			}
		}
	}
}
/*Prints the roads for option 2, it takes source, destination and parent array as input, starts from parent[destination] and keep printing parent town until
-1 is reached, -1 is parent of source*/
void printSmallestPath(int source, int destination, int *parent, int count, FILE *f, struct ll **g)
{

	int temp = destination;
	if ( parent[temp] != -1 ) {
		printSmallestPath(source, parent[temp],parent, count + 1, f, g);
		if ( count != 0 ) {
			if ( f == NULL ) {
				printf("%d->",temp + 1);
			}
			else {
				fprintf(f,"%d->",temp + 1);
			}
		}
		else {
			if ( f == NULL ) {
				printf("%d",temp + 1);
			}
			else {
				fprintf(f,"%d",temp + 1);
			}
		}
	}
	else {
		if ( f == NULL ) {
			printf("%d->",source + 1);
		}
		else {
			fprintf(f,"%d->",source + 1);
		}
	}
}
/*Returns the minimum value index from dist_store, first it checks if dist_store is visited, then ignore that road since we have already visited that road*/
int getMinimumfromQueue(char *visited, int *dist_store, int total_roads )
{
	int getMin = INT_MAX;
	int idx = -1;
	for ( int i = 0 ; i < total_roads ; i++ )
	{
		if ( visited[i] != 'n' )
		{
			continue;
		}
		else if ( dist_store[i] <= getMin )
		{
			getMin = dist_store[i];
			idx = i;
		}
	}
	return idx;
}
/*This finds the shortest path from start to end*/
void djisktra_algorithm(struct ll **g, int total_roads, int start, int end, int f)
{
	int *dist_store = (int*) malloc(sizeof(int) * total_roads);
	char *visited = (char*) malloc(sizeof(char) * total_roads);
	int *parent_road = (int*) malloc(sizeof(int) * total_roads);

    //We set dist_store to INT_MAX since we need to find the minimum value index from dist_store
    //We set all visited to false, since none road is visited yet
    //We set parent_road of all roads to -1
	for ( int i = 0 ; i < total_roads ; i++ )
	{
		dist_store[i] = INT_MAX;
		visited[i] = 'n';
		parent_road[i] = -1;
	}
	//Now we set the value of start road to 0, so our minimum distance function return this value index
	dist_store[start - 1] = 0;

    //Now we iterate the whole dist_store arary, find the minimum value index ( minimum value index = road that is nearest to current road)
	for ( int i = 1 ; i < total_roads ; i++)
	{
		int min = getMinimumfromQueue(visited,dist_store,total_roads);
		//Set this road to visited
		visited[min] = 'y';
        //Noe check distance of all roads from min road
        //If it smaller than the current distance in graph then update the distance
        //and also update the parent
		for ( int j = 0 ; j < total_roads ; j++ )
		{
			//Valid road
			if ( min != j && g[min][j].distance != INT_MAX )
			{
				//Check if forms shortest path
				if ( dist_store[min] + g[min][j].distance < dist_store[j] )
				{
					dist_store[j] = dist_store[min] + g[min][j].distance;
					parent_road[j] = min;
				}
			}
		}
	}
	FILE *ptr = fopen("temp.txt","a");
	if ( dist_store[end - 1] == INT_MAX )
	{
		printf("Path not possible\n");
		fprintf(ptr,"Path not possible from %d to %d\n\n",start, end);
	}
	else
    {
        printf("Distance  = %d\n",dist_store[end - 1]);
        printf("Path = ");
        printSmallestPath(start - 1,end - 1,parent_road, 0, NULL,g);
        printf("\n");
        printf("The town/cities are : ");
        printTown(start - 1,end - 1,parent_road, 0, NULL,g);
        printf("\n");
        fprintf(ptr,"Distance  = %d\n",dist_store[end - 1]);
        fprintf(ptr,"Path = ");
        printSmallestPath(start - 1,end - 1,parent_road, 0, ptr, g);
        fprintf(ptr,"\n");
        fprintf(ptr,"The town/cities are : ");
        printTown(start - 1,end - 1,parent_road, 0, ptr, g);
        fprintf(ptr,"\n\n");
    }

    fclose(ptr);

	free(parent_road);
	free(dist_store);
	free(visited);
}
/*Copies the data from temp.txt to route.txt when option 3 is called*/
void copydata()
{
    FILE *read_data = fopen("temp.txt","r");
    FILE *write_data = fopen("route.txt","w");

    int line[1000];

    while ( fgets(line,1000,read_data) )
    {
        fputs(line,write_data);
    }

    fclose(read_data);
    fclose(write_data);
}
int main()
{
	struct ll **g;
	char file_name[FILE_SIZE]= "segment.txt";
	int file_read = 0;
	int total_roads = 0;
    FILE *ptr = fopen("temp.txt","w");
    fclose(ptr);
	int option = -1;
	/*Prints the menu*/
	while ( option != 0 ) {
		printf("\n\nWelcome to DJIKSTRA Program!\n");
		printf("Enter 1 to Read the segments.txt and load data\n");
		printf("Enter 2 points to compute the shortest distance between them\n");
		printf("Enter 3 to print the route of shortest distance in route.txt\n");
		printf("Enter 0 to quit!\n");
		printf("Choose the option : ");
		scanf("%d",&option);
		if ( option == 1 )
		{
			if ( file_read == 1 )
			{
				printf("File already read!\n");
				continue;
			}
			//Reads the segment file
			total_roads = getMaxRoadNumber(file_name);
			//Assign memory for the graph based on maximum number of roads
			g = (struct ll**) malloc ( sizeof(struct ll*) * total_roads);
			for ( int i = 0 ; i < total_roads ; i++ )
			{
				g[i] = (struct ll*) malloc ( sizeof(struct ll) * total_roads);
				for ( int j = 0 ; j < total_roads ; j++ )
				{
					g[i][j].distance = INT_MAX;
				}
			}
            //Creates the graph from segment file
			createGraph(file_name, &g, total_roads);
			file_read = 1;
			printf("\nFile read successfully!\n\n");
		}
		else if ( option == 2 )
		{
		    //Inputs the source and destination from the user and print the distance, path and cities
			if ( file_read != 1 )
			{
				printf("File not read yet!\n");
				continue;
			}
			int source;
			int destination;
			printf("Enter the first point: ");
			scanf("%d",&source);
			printf("Enter the second point: ");
			scanf("%d",&destination);
			if ( source <= 0 || destination <= 0 || source >= total_roads || destination >= total_roads)
			{
				printf("Invalid value for source or destination\n");
				continue;
			}
			djisktra_algorithm(g,total_roads,source,destination,1);
		}
        else if ( option == 3)
        {
            //Save the data in route.txt
            copydata();
            printf("Result are saved in route.txt\n");
        }
		else if ( option == 0 )
		{
			break;
		}
	}
	//Freeing the memory assigned
	for ( int i = 0 ; i < total_roads ; i++ )
	{
		free(g[i]);
	}
	free(g);
	remove("temp.txt");
	return 0;
}

