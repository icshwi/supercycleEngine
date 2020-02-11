#ifndef CACH_HPP
#define CACH_HPP

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "cadef.h"

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <stdexcept>

#include <vector>

class CACh {
    private:
        std::string name;
        chid id;
        void caGet(int type, int val_size, void *val);
        void caPut(int type, int val_size, void *val);
        std::string msgerr = "ERROR ca_access failure at CACh::name ";
    public:
        CACh(std::string pvstr);
        CACh();
        ~CACh();
        void close();
        void init(std::string pvstr);
        std::string getName(){return name;};

        int get(int &arg);
        uint get(uint &arg);
        void get(std::string &args);

        void put(uint arg);
        void put(int arg);
        void put(std::string &args);

        void put_vec(std::vector<uint> val_vec);
        void put_vec(std::vector<int> val_vec);
};

/*
void careg_test(std::string pvstr);
void careg_test1(std::string pvstr);
*/

#endif // CACH_HPP
