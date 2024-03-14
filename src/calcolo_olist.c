#include "hash_overlap_dict.h"
#include "overlap_list.h"
olist *calcola_olist(hash_odict *hodict,olist *overlap_list,unsigned int hdictsize)
{
    for (unsigned int i = 0; i < hdictsize; i++)
    {

        overlap_dict *tempdict = hodict->dicts_list[i];
        if (tempdict)
        {
            for (unsigned int j = 0; j < tempdict->used; j++)
            {

                overlap_dict_entry *tempentry = tempdict->head[j];
                int *tempvalues = tempentry->value;
                // memcpy(tempvalues,tempentry->value,sizeof(int)*9);

                int strand = 0;

                int flag1 = tempvalues[0];
                int flag2 = tempvalues[1];
                int lenght1 = tempvalues[2];
                int lenght2 = tempvalues[3];
                int start1 = tempvalues[4];
                int end1 = tempvalues[5];
                int start2 = tempvalues[6];
                int end2 = tempvalues[7];

                int id1=tempdict->head[j]->reads[0];
				int id2=tempdict->head[j]->reads[1];

                /*
                if (flag1 == 1 && flag2 == 0)
                {

                    start2 = tempvalues[3] - tempvalues[7];
                    end2 = tempvalues[3] - tempvalues[6];
                    strand = 1;
                }
                else
                {

                    start1 = tempvalues[2] - tempvalues[5];
                    end1 = tempvalues[2] - tempvalues[4];
                    if (flag2 == 0)
                    {
                        start2 = tempvalues[3] - tempvalues[7];
                        end2 = tempvalues[3] - tempvalues[6];
                    }
                    else
                    {

                        strand = 1;
                    }
                }
                */

                if (flag1 == 0){
                    int temp_start1= lenght1 - end1;
                    int temp_end1 = lenght1 - start1;
                    start1=temp_start1;
                    end1=temp_end1;
                }
                if (flag2 == 0){
                    int temp_start2 = lenght2 - end2;
                    int temp_end2 = lenght2 - start2;
                    start2=temp_start2;
                    end2=temp_end2;
                }

                if(flag1!=flag2){
                    strand=1;
                }

                // add_olist_entry(overlap_list,tempentry->reads[0],tempentry->reads[1],tempvalues[2],tempvalues[3],tempvalues[4],tempvalues[5],tempvalues[6],tempvalues[7],strand);
                add_olist_entry(overlap_list, id1, flag1, id2, flag2, lenght1, lenght2, start1, end1, start2, end2, strand);
            }
        }
    }
    return overlap_list;
}