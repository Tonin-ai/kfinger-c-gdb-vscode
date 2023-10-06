import pickle

tempdict=dict()

if __name__=="__main__":
    with open('./output.log', 'r') as input_file:
        file_rows = input_file.readlines()
        for row in file_rows:
            if len(row)>1:
                listainteri = list(row.split())
                valori = list(map(int, listainteri[2:]))
                tempdict[(listainteri[0], listainteri[1])] = valori
    with open('c_output_dictionary.pkl', 'wb') as f:
         pickle.dump(tempdict, f)

