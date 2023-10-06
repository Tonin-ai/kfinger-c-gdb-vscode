import Bio
from Bio.Seq import Seq
with open('./sampled_read-noerr.fasta', 'r') as in_sequence:
    file_seq = in_sequence.read()

file_seq = re.findall(r'[^>]+', file_seq)
file_seq = [re.findall(r'.+', seq) for seq in file_seq]
read_seq_list = [seq[1] for seq in file_seq]

with open('./output-full-raw-overlaps.txt', 'r') as cfr_sequence:
    file_rows = cfr_sequence.readlines()

old_pair_list = [(row.rstrip().split()[0], row.rstrip().split()[6], row.rstrip()) for row in file_rows]

for (i, ov) in enumerate(old_pair_list):
    if (ov[0], ov[1]) not in overlap_dict:
        print(ov)
    if i == 200:
        break

print_first = -1
which_strand = [0,1]

max_diff_length = -1
min_ov_length = -1

count = 0
min_count = 0

for r in overlap_list:
    read1 = int(r[0])
    read2 = int(r[1])
    (start1, end1, start2, end2, strand) = (r[4], r[5], r[6], r[7], r[8])
    if strand in which_strand:
        seq1 = read_seq_list[read1][start1:end1]
        seq2 = read_seq_list[read2][start2:end2]
        if (seq1 != seq2):
            print(read1, ' ', read2, ' diff ', min(len(seq1), len(seq2)))
            if max_diff_length == -1 or min(len(seq1), len(seq2)) > max_diff_length:
                max_diff_length = min(len(seq1), len(seq2))
            else:
                if min_ov_length == -1 or min(len(seq1), len(seq2)) < min_ov_length:
                    min_ov_length = min(len(seq1), len(seq2))
                
                if min(len(seq1), len(seq2)) <= min_overlap_length:
                    min_count = min_count + 1
        
        if strand == 1:
            seq2 = str(Seq(seq2).reverse_complement())
        
        chunk1 = re.findall(r'(.{,60})', seq1)
        chunk2 = re.findall(r'(.{,60})', seq2)

        if read1 == -1 and read2 == -1:
            print(r)
        
            for (i, c) in enumerate(chunk1):
                print(c)
                print(chunk2[i])
                print()
            
        count = count + 1
    
    if count == print_first:
        break
