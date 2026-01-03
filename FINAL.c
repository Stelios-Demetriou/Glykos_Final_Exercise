#include <stdio.h>
#include <string.h>

int main()
{
	char seq[1000];
	char segment[50];
	char sym[1000];
	int i, len, h;
	int in_seg, first, hphil, found;
	int count_O, count_o, last, seg_len;
	double aa, perc;

	printf("Enter the protein sequence:\n");
	while(scanf("%s", seq) ==1)
	{
	printf("\nHydropathy diagram\n");
	len=strlen(seq);
	for (i=0; i<len; i++)
		{
		if (seq[i]=='A') {aa=0.616;}
		else if (seq[i]=='C') {aa=0.680;}
		else if (seq[i]=='D') {aa=0.028;}
		else if (seq[i]=='E') {aa=0.043;}
		else if (seq[i]=='F') {aa=1.000;}
		else if (seq[i]=='G') {aa=0.501;}
		else if (seq[i]=='H') {aa=0.165;}
		else if (seq[i]=='I') {aa=0.943;}
		else if (seq[i]=='K') {aa=0.283;}
		else if (seq[i]=='L') {aa=0.943;}
		else if (seq[i]=='M') {aa=0.738;}
		else if (seq[i]=='N') {aa=0.236;}
		else if (seq[i]=='P') {aa=0.711;}
		else if (seq[i]=='Q') {aa=0.251;}
		else if (seq[i]=='R') {aa=0.000;}
		else if (seq[i]=='S') {aa=0.359;}
		else if (seq[i]=='T') {aa=0.450;}
		else if (seq[i]=='V') {aa=0.825;}
		else if (seq[i]=='W') {aa=0.878;}
		else if (seq[i]=='Y') {aa=0.880;}
		else {aa=0.00;}

		if(aa<=0.300) sym[i] = '_';
		else if(aa>0.300 && aa<=0.501) sym[i] = '.';
        else if(aa>0.501 && aa<=0.750) sym[i] = 'o';
		else if(aa>0.750) sym[i] = 'O';
		printf("%c", sym[i]);
		}
		printf("\n");

        for (i=0; i<len; i++)
		{
		if(!in_seg && (sym[i] == 'o' || sym[i] == 'O' || sym[i] == '.'))
			{
			in_seg=1;
			first=i;
			hphil=0;
			}
			if(in_seg)
            		{
                	if (sym[i] == '_')
					{
                    		hphil++;
                	}else{
                    		hphil = 0;
					}

            if (hphil ==2 || hphil == 1 || i == len)
                	{
                    last = i - hphil;
                    seg_len = last - first + 1;

                    if (seg_len >= 16 && seg_len <= 30)
                   		{
                        	count_O = 0;
							count_o = 0;

                	for (h = first; h <= last; h++)
                        		{
                            		if (sym[h] == 'O') count_O++;
									else if (sym[h] == 'o') count_o++;

                        			segment[h - first] = seq[h];
                        		}
                             	   	segment[seg_len] = '\0';

  									perc = (count_O + count_o) * 100.0 / seg_len;

                       		if (perc >= 50.0 && perc < 60.0)
                        		{
								found = 1;
                            	printf("\nPossible Transmembrane Segment - probably aliphatic a-helix: %d - %d\n",
                            	first + 1, last + 1);
                           		printf("Sequence: %s\n", segment);
                           		printf("Percentage in Hydrophobic residues: %.2f %%\n", perc);
                        		}
                        	else if (perc >= 60.0)
                        		{
								found = 1;
                           		printf("\nPossible Transmembrane Segment - probably a-helix or part of b-barrel: %d - %d\n",
                                first + 1, last + 1);
                            	printf("Sequence: %s\n", segment);
                            	printf("Percentage in Hydrophobic residues: %.2f %%\n", perc);
					}
				}
                    		in_seg = 0;
	               		}
            		}
        	}
		if(!found)
		{
		printf("\nThis Protein probably does not contain Transmembrane Segments\n");
		}
	    printf("\n");
	}
    	return 0;
}
