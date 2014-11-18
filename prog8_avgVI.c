/* Program 8
Calculates the min/max/avg values from a series of binary files
should start with lots of psuedo, because i have no idea.

Tyler Jowaisas
11/13/14

*/

#include <stdio.h>
#include <stdlib.h>

FILE *openFile(char *mode);


int main()
	{
		//users file name to read
		char file_name[20];
		//pointer to resistor file information
		FILE *res_data;
		//pointer to voltage file information
		FILE *volt_data;
		//file out data
		FILE *out_file;
		//arrays that will read from the respective files
		double resArr[20] = {0};
		double voltArr[20] = {0};
		
		//counter variables
		int i = 0;
		//counts correctly read values
		int n;
		//fairly self explanatory?
		double min_volt, max_volt, avg_volt;
		double min_current, max_current, avg_current;
		double min_power, max_power, avg_power;
		
		//checked that the file can be opened,
		//stores that data.
		printf("Enter name of a file for resistor input: "); 
		res_data = openFile("rb");
		getchar();
		printf("Enter name of a file for voltage input: ");
		volt_data = openFile("rb");	
		getchar();
		printf("Enter name of a file for output: ");
		out_file = openFile("w");
		
		//stores read information in the arrays, returns number of read values	
		n = fread(resArr, sizeof(double), 20, res_data);
		fread(voltArr, sizeof(double), 20, volt_data);
		
		min_volt = voltArr[0];
		min_current = (voltArr[0] / resArr[0]);
		min_power =((voltArr[0] * voltArr[0])/ resArr[0]);
		
		max_volt = voltArr[0];
		max_current = (voltArr[0] / resArr[0]);
		max_power = ((voltArr[0] * voltArr[0])/ resArr[0]);
		
		avg_power += ((voltArr[0] * voltArr[0])/ resArr[0]);
		avg_volt += voltArr[0];
		avg_current += (voltArr[0] / resArr[0]);

		for(i = 1; i < n; i++)
			{ 
				avg_power += ((voltArr[i] * voltArr[i])/ resArr[i]);
				avg_volt += voltArr[i];
				avg_current += (voltArr[i] / resArr[i]);
				
				if(voltArr[i] < min_volt)
					min_volt = voltArr[i];
				
				if((voltArr[i] / resArr[i]) < min_current)
					min_current = (voltArr[i] / resArr[i]);
				
				if(((voltArr[i] * voltArr[i])/ resArr[i]) < min_power)
					min_power = ((voltArr[i] * voltArr[i])/ resArr[i]);
					
				if(voltArr[i] > max_volt)
					max_volt = voltArr[i];
				
				if((voltArr[i] / resArr[i]) > max_current)
					max_current = (voltArr[i] / resArr[i]);
				
				if( ((voltArr[i] * voltArr[i])/ resArr[i]) > max_power )
					max_power = ((voltArr[i] * voltArr[i])/ resArr[i]);
				//printf("\nmax power %lf, min %lf", max_power, min_power);
			}
			
			avg_power = avg_power / n;
			avg_volt = avg_volt / n;
			avg_current = avg_current /n;
		
		fprintf(out_file, "\t        \t R(ohms)      V (volts)\n");	
		for(i = 0; i < n; i++)
		{	
			if(i < 9)		
				fprintf(out_file, "RV Pair %d: \t%8.2lf \t\t %6.2lf\n", (i+1), resArr[i], voltArr[i]);
			else
				fprintf(out_file, "RV Pair %d: %8.2lf   \t %6.2lf\n", (i+1), resArr[i], voltArr[i]);
		}
		
		fprintf(out_file, "\n\n \t \t \t   Voltage \t     \t Current \t     \t Power\n");
		fprintf(out_file, "MIN \t \t %8.2lf \t \t %8.4lf \t \t %8.4lf\n", min_volt, min_current, min_power);
		fprintf(out_file, "MAX \t \t %8.2lf \t \t %8.4lf \t \t %8.4lf\n", max_volt, max_current, max_power);
		fprintf(out_file, "AVG \t \t %8.2lf \t \t %8.4lf \t \t %8.4lf\n", avg_volt, avg_current, avg_power);
		
		fclose(res_data);
		fclose(volt_data);
		fclose(out_file);
		
		return 0;
	}	

FILE *openFile(char *mode)
 {	
		char fname[50];
		FILE *fp;

	//	printf("Enter file name:  ");
		scanf("%s", fname);
		fp = fopen(fname, mode);
		
		while(fp == NULL)
			{
				getchar();
				printf("\nInvalid file name %s ;reenter file: ", fname);
				scanf("%s", fname);
				fp = fopen(fname, mode);
			}

		return fp;
	}
