#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#include "hash_dict.h"
#include "hash_matches_dict.h"
#include "hash_overlap_dict.h"
#include "overlap_list.h"

int stampa_risultati(hash_dict *hdict,hash_mdict *hmdict,hash_odict *hodict,olist *overlap_list,int k)
{
    int out = open("dict_occorrenze.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (-1 == out)
    {
        perror("opening cout.log");
        return 255;
    }

    int save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout)))
    {
        perror("cannot redirect stdout");
        return 255;
    }

    // printf("\nDIZIONARIO OCCORRENZE\n");
    viewHashDict(hdict, k);
    printf("\n");

    out = open("dict_match.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (-1 == out)
    {
        perror("opening cout.log");
        return 255;
    }

    save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout)))
    {
        perror("cannot redirect stdout");
        return 255;
    }
    // printf("\nDIZIONARIO MATCHES\n");
    viewHashMDict(hmdict);
    printf("\n");

    out = open("dict_overlap.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (-1 == out)
    {
        perror("opening cout.log");
        return 255;
    }

    save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout)))
    {
        perror("cannot redirect stdout");
        return 255;
    }
    // printf("\nDIZIONARIO OVERLAP\n");
    viewHashODict(hodict);
    printf("\n");

    out = open("list_overlap.log", O_RDWR | O_CREAT | O_APPEND, 0600);
    if (-1 == out)
    {
        perror("opening cout.log");
        return 255;
    }

    save_out = dup(fileno(stdout));
    if (-1 == dup2(out, fileno(stdout)))
    {
        perror("cannot redirect stdout");
        return 255;
    }
    // printf("\nLISTA OVERLAP\n");
    stampolist(overlap_list);
    printf("\n");

    /*
    if (!strcmp("-overlap_dict", argv[1]))
    {
        viewHashODict(hodict);
        printf("\n");
    }

    if (!strcmp("-overlap_list", argv[1]))
    {
        stampolist(overlap_list);
        printf("\n");
    }

    if (!strcmp("-matches_dict", argv[1]))
    {
        viewHashMDict(hmdict);
        printf("\n");
    }
    */
    
}