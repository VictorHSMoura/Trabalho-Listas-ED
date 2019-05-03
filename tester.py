import os, fnmatch

os.system("make")
listOfFiles = os.listdir('Casos de Teste/')  
pattern = "*.in"  
i = 1
for entry in listOfFiles:  
    if fnmatch.fnmatch(entry, pattern):
            print ("Analisando o arquivo: ",entry)
            os.system("./trab.exe<Casos\ de\ Teste/" + entry + ">saida.txt")
            os.system("sdiff -s Casos\ de\ Teste/" + entry[0] +".out saida.txt")
