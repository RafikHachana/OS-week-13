#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

//change these define statements to make the program work for any number of processes or resource types
#define P 5
#define R 3


//define IO paths here
#define INPUT "input_dl.txt"
#define OUTPUT "output_dl.txt"

int main()
{
	FILE* in = fopen(INPUT,"r");
	FILE* out = fopen(OUTPUT,"w");

	int t[R];
	int a[R];
	int used[P][R];
	int req[P][R];

	//read the input file
	for(int i=0;i<R;i++)
	{
		fscanf(in,"%d",&t[i]);
	}


	for(int i=0;i<R;i++)
	{
		fscanf(in,"%d",&a[i]);
	}

	for(int i=0;i<P;i++)
	{
		for(int j=0;j<R;j++) fscanf(in,"%d",&used[i][j]);
	}

	for(int i=0;i<P;i++)
	{
		for(int j=0;j<R;j++) fscanf(in,"%d",&req[i][j]);
	}

	bool done[P];
	for(int i=0;i<P;i++) done[i] = false;
	int found = 0;
	int rem = P;

	while(found!=-1) //look for executable processes
	{
		found = -1;
		for(int i=0;i<P;i++)
		{
			if(done[i]) continue;
			bool executable = true;
			for(int j=0;j<R;j++)
			{
				if(req[i][j]>a[j])
				{
					executable = false;
					break;
				}
			}

			if(executable)
			{
				found = i;
				break;
			}
		}
		if(found == -1 ) break;

		for(int j=0;j<R;j++)
		{
			a[j] += used[found][j];
		}

		done[found] = true;
		rem--;
	}

	//if there are still running processes at this point, it means they are in deadlock
	if(rem==0)
	{
		fprintf(out, "No deadlocks detected\n");
	}
	else
	{
		fprintf(out, "%d processes are in deadlock\n",rem);
		fprintf(out, "Process numbers:\n");
		for(int i=0;i<P;i++)
		{
			if(done[i]) continue;
			fprintf(out, "%d  ", i+1);
		}
		fprintf(out, "\n" );
	}

	fclose(in);
	fclose(out);
}