There are 3 important files,

- main.cpp

    - basic implementation of branch and bound

    - compile: `c++ main.cpp -o knap`
    
    - run: `./knap fname`, where *fname* is the instance to run  

- main_t.cpp

    - threaded implementation of branch and bound

    - compile: `c++ main_t.cpp -o knap_t`

    - run: `./knap_t fname`, where *fname* is the instance to run  

- gen.cpp

    - program to generate random test cases of a given size

    - compile: `c++ gen.cpp -o gen`

    - run: `./gen N R > fname`, where *N* is the size of the instance, *R* is the max weight of an item, and *fname* is the file you want the instance to be stored in