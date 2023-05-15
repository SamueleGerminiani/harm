import sys
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image


linha1 = []
linha2 = []
linha3 = []

with open(sys.argv[1]) as f:
    content = f.readlines()

content = [x.strip() for x in content] 

offset = 0
for linha in content:
    linha = linha.split(" ")
    linha = linha[offset:offset+3]
    linha1.append(linha)
    
offset = 3
for linha in content:
    linha = linha.split(" ")
    linha = linha[offset:offset+3]
    linha2.append(linha)
    
offset = 6
for linha in content:
    linha = linha.split(" ")
    linha = linha[offset:offset+3]
    linha3.append(linha)

linhas_total = []

atual = 0
for i in range(512):
    linhas_total.append(linha1[atual:atual+512])
    linhas_total.append(linha2[atual:atual+512])
    linhas_total.append(linha3[atual:atual+512])
    atual += 512

espaco = "   "
quebra_linha = "\n\n"
f = open("sobel_in_reordered.txt", "w+")
count = 1
for linha_i in range(1536):
    linha_str = ""
    
    for matrix_i in range(512):
#        print(matrix_i)
        linha_str += ' '.join(linhas_total[linha_i][matrix_i]) + espaco
        if matrix_i == 511:
            linha_str += ' '.join(linhas_total[linha_i][matrix_i]) + "\n"
    
    if count == 3:
        f.write(linha_str + quebra_linha)
        count = 0
    else:
        f.write(linha_str)
    
    count += 1
        

f.close()
#X = np.random.random((100, 100)) # sample 2D array
X = np.loadtxt("sobel_in_reordered.txt")


plt.imshow(X, cmap="gray")
plt.show()
