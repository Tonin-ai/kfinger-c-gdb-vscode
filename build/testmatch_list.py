import pickle

if __name__=="__main__":
    tempdict_p=dict()
    with open('./overlaplist.txt', 'r') as input_file:
        file_rows = input_file.readlines()
        for row in file_rows:
            if len(row)>1:
                listainteri = list(row.split())
                valori = list(map(int, listainteri[2:]))
            # print(str(listainteri[0]) +" "+ str(listainteri[1]))
            #tempdict[(int(listainteri[0]), int(listainteri[1]))] = valori
                tempdict_p[(listainteri[0], listainteri[1])] = valori
        #print((listainteri[0], listainteri[1]))
        #print(tempdict[('0', '1678')])
    flag = True
    tempdict = dict()
    #print(overlap_dict[('0','1678')])
    with open('./output.log', 'r') as input_file:
        file_rows = input_file.readlines()
        for row in file_rows:
            if len(row)>1:
                listainteri = list(row.split())
                valori = list(map(int, listainteri[2:]))
            # print(str(listainteri[0]) +" "+ str(listainteri[1]))
            #tempdict[(int(listainteri[0]), int(listainteri[1]))] = valori
                tempdict[(listainteri[0], listainteri[1])] = valori
            #print((listainteri[0], listainteri[1]))
    #print(tempdict[('0', '1678')])
    for (x1, x2) in tempdict_p:
        try:
            if tempdict_p[(x1, x2)] != tempdict[(x1, x2)]:
                print()
                print((x1, x2))
                print(str(tempdict_p[(x1, x2)]) + "ORIGINALE")
                print(str(tempdict[(x1, x2)])+ "IN TEST")
                flag = False
        except:
            print(str(tempdict_p.get((x1,x2),[])))
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
