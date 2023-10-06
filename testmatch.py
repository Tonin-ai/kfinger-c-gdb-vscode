import pickle

if __name__=="__main__":
    with open('saved_dictionary.pkl', 'rb') as f:
        overlap_dict = pickle.load(f)
    flag = True
    tempdict = dict()
    #print(overlap_dict[('0','1678')])
    with open('./outputc.log', 'r') as input_file:
        file_rows = input_file.readlines()
        for row in file_rows:
            listainteri = list(row.split())
            valori = list(map(int, listainteri[2:]))
            # print(str(listainteri[0]) +" "+ str(listainteri[1]))
            #tempdict[(int(listainteri[0]), int(listainteri[1]))] = valori
            tempdict[(listainteri[0], listainteri[1])] = valori
            #print((listainteri[0], listainteri[1]))
    #print(tempdict[('0', '1678')])
    for (x1, x2) in overlap_dict:
        try:
            if overlap_dict[(x1, x2)] != tempdict[(x1, x2)]:
                print()
                print((x1, x2))
                print(overlap_dict[(x1, x2)])
                print(tempdict[(x1, x2)])
                flag = False
        except:
            print(str(overlap_dict.get((x1,x2),[])))
            print(str(tempdict[(x1, x2)]))
    """
    for (x1, x2) in tempdict:
        try:
            if overlap_dict[(x1, x2)] != tempdict[(x1, x2)]:
                print()
                print(overlap_dict[(x1, x2)])
                print(tempdict[(x1, x2)])
                flag = False
        except:
            print(str(overlap_dict.get((x1,x2),[])))
            print(str(tempdict[(x1, x2)]))
    """
    print("Pthon and C outputs are equal: " + str(flag))