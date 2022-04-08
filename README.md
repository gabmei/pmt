# Projeto 1 de IF767
Ferramenta de busca de padrão em texto
##### Dupla
- Daniel Pacheco
- Gabriel Meireles

##### Instruções de compilação

na pasta raiz do projeto execute o comando make para gerar o executavel na pasta ./bin

```
    ../pmt$ make 
```

#### instruções de uso

Usage: ./bin/pmt [options] pattern textfile [textfile...]

Search for patten in each textfile
Example: ./bin/pmt -a KMP "hello world" hello.txt

Multiple patterns can be passed through a file separated by newline
Example: ./bin/pmt -p patterns.txt hello.txt

Options:
 -e, --edit e_max                 maximum distance for approximated search
 -p, --pattern pattern_file       search for patterns in pattern_file
 -a, --algorithm algorithm_name   choose algorithm for pattern search
       exact search       :       kmp, shift_or or bruteforce
       approximated search:       sellers or ukkonen

