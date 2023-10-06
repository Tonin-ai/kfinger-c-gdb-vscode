import re
import time
from collections import Counter
import pickle
k = 7
min_total_length = 40
min_shared_kmers = 4
max_kmer_occurrence = -1
max_diff_region_percentage = 0.0
min_region_length = 100
min_region_kmer_coverage = 0.27
min_overlap_coverage = 0.70
min_overlap_length = 600
start_time_begin = time.perf_counter()
begin_time = start_time = time.perf_counter()
with open('./inputtest.txt', 'r') as input_file:
    file_rows = input_file.readlines()
    whole_rows = [re.findall(r'[^\s|]+', row) for row in file_rows]
    read_ids = []
    fingerprint_list = []

    for row in whole_rows:
        read_ids.append(row.pop(0))
        fingerprint_list.append(list(map(int, row)))
end_time = time.perf_counter()
print('Upload the fingerprint: ', end_time-start_time)

def compute_kmer_occurrences(fingerprint_list):
    kmer_occurrences = {}

    for (j,finger) in enumerate(fingerprint_list):
        check_unique = []
        occ_kmer_list = []
        for (i,c) in enumerate(finger):        
            kmer = tuple(finger[i:i+k])                
            if len(kmer) == k:
                check_unique.append(kmer)
                occ_kmer_list.append((j,i,kmer))
               
        c = Counter(check_unique)
    
        for kmer_t in occ_kmer_list:
            #if c[kmer_t[2]] == 1: 
            if c[kmer_t[2]] >= 1: 
                cfr_kmer = kmer_t[2]                                        
                if sum(cfr_kmer) >= min_total_length:
                    cfr_kmer = '_'.join(list((map(str, cfr_kmer))))                                         
                    value = kmer_occurrences.get(cfr_kmer, [])
                    value.append((kmer_t[0], kmer_t[1]))
                    kmer_occurrences[cfr_kmer] = value
                
    for kmer in kmer_occurrences:
        kmer_occurrences[kmer] = tuple(kmer_occurrences[kmer])
        
    return kmer_occurrences

start_time = time.perf_counter()

kmer_occurrences = compute_kmer_occurrences(fingerprint_list)
end_time = time.perf_counter()
print('Computing the kmer occurrences: ', end_time-start_time)



h_kmer_occurrences = dict()
for kmer in kmer_occurrences:
    size = len(kmer_occurrences[kmer])
    if size > 1 and (max_kmer_occurrence == -1 or size <= max_kmer_occurrence):
        h_kmer_occurrences[kmer] = kmer_occurrences[kmer]
            
kmer_occurrences = h_kmer_occurrences


def compute_matches(kmer_occurrences):
    min_sharing_dict = {}
    matches_dict = {}

    for (p, kmer) in enumerate(kmer_occurrences):
        occ_list = kmer_occurrences[kmer]
        for (i, first_occ) in enumerate(occ_list):
            read1 = first_occ[0]
            for second_occ in occ_list[i+1:]:
                read2 = second_occ[0]

                min_sharing_dict[(read1, read2)] = min_sharing_dict.get((read1, read2), 0) + 1

                value = matches_dict.get((read1, read2), [-1, -1, -1, -1])

                #if read1==65 and read2==376: print("aaaaaa") 

                if value[0] == -1 or value[0] > first_occ[1]:
                    value[0] = first_occ[1]
                    value[1] = second_occ[1]

                if value[2] == -1 or value[2] < first_occ[1]:
                    value[2] = first_occ[1]
                    value[3] = second_occ[1]

                matches_dict[(read1, read2)] = value

    return (min_sharing_dict, matches_dict)

start_time = time.perf_counter()

(min_sharing_dict, matches_dict) = compute_matches(kmer_occurrences)

end_time = time.perf_counter()
print('Computing the matches: ', end_time-start_time)

overlap_dict = {}

start_time = time.perf_counter()

for (read1, read2) in matches_dict:
    if min_shared_kmers == 1 or min_sharing_dict[(read1, read2)] >= min_shared_kmers:
        (first_match1, first_match2, second_match1, second_match2) = matches_dict[(read1, read2)]

        if second_match2 >= first_match2:
            #print('here ', min_sharing_dict[(read1, read2)])
            (start1, end1, start2, end2) = (first_match1, second_match1+k, first_match2, second_match2+k)

            up1 = sum(fingerprint_list[read1][:start1])
            up2 = sum(fingerprint_list[read2][:start2])
            l1 = sum(fingerprint_list[read1][start1:end1])
            l2 = sum(fingerprint_list[read2][start2:end2])
            read1_length = sum(fingerprint_list[read1])
            read2_length = sum(fingerprint_list[read2])

            #min_region_kmer_coverage = 0.30

            min_cov_number = int(min_region_kmer_coverage * min(l1,l2) / min_total_length)
            min_cov_number = min(min_cov_number, 15)
            #print((read1, read2, min_cov_number, min_sharing_dict[(read1,read2)], min_cov_number, min_region_length))
            #print(abs(l1-l2) <= max_diff_region_percentage * max(l1,l2))
            #print(l1, ' ', l2)
            #print('here ', abs(l1-l2))
            if min_sharing_dict[(read1,read2)] >= min_cov_number and (abs(l1-l2) <= max_diff_region_percentage * max(l1,l2) and max(l1,l2) >= min_region_length):
                min_up = min(up1,up2)
                start_ov1 = up1 - min_up
                start_ov2 = up2 - min_up
                min_down = min(read1_length-(up1+l1), read2_length-(up2+l2))
                end_ov1 = up1 + l1 + min_down
                end_ov2 = up2 + l2 + min_down

                ov_length = min(end_ov1-start_ov1, end_ov2-start_ov2)
                #print((min(l1,l2)/ov_length, min(l1,l2), ov_length))
                if min(l1,l2) >= min_overlap_coverage * ov_length and ov_length >= min_overlap_length:
                    #print('OK ', (read1, read2))
                    value = overlap_dict.get((read_ids[read1][:-2], read_ids[read2][:-2]), [])
                    if value == [] or ov_length > value[-1]:
                        value = [int(read_ids[read1][-1]), int(read_ids[read2][-1]), read1_length, read2_length, start_ov1, end_ov1, start_ov2, end_ov2, ov_length]
                        overlap_dict[(read_ids[read1][:-2], read_ids[read2][:-2])] = value

end_time = time.perf_counter()
print('Computing the overlaps: ', end_time-start_time)

with open('saved_dictionary.pkl', 'wb') as f:
    pickle.dump(overlap_dict, f)

overlap_list = []

for (read1, read2) in overlap_dict:
    (flag1, flag2, length1, length2, start1, end1, start2, end2, ov_length) = overlap_dict[(read1, read2)]
    strand = 0
    if flag1 == 1:
        if flag2 == 0:
            (start2, end2) = (length2 - end2, length2 - start2)
            strand = 1
    else:
        (start1, end1) = (length1 - end1, length1 - start1)
        if flag2 == 0:
            (start2, end2) = (length2 - end2, length2 - start2)
        else:
            strand = 1

    overlap_list.append((read1, read2, length1, length2, start1, end1, start2, end2, strand))
    #print('\t'.join(map(str, [read1, read2, length1, length2, start1, end1, start2, end2, strand])))


with open('./overlaplist.txt', 'w') as ol_output:
    for x in overlap_list:
        for i in x:
            ol_output.write(str(i)+ " ");

        ol_output.write("\n");




end_time = time.perf_counter()
print('Total: ', end_time-begin_time)

read_number = len(read_ids) // 2

check_set = set(range(read_number))

cfr_set = set()

for t in overlap_dict:
    cfr_set.add(t[0])
    cfr_set.add(t[1])

cfr_set.difference(cfr_set)

