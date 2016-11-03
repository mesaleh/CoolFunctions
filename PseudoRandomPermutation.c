#include <stdio.h>
#include <stdlib.h>
/*
 This was written by herm1t as he published it in: http://vxheaven.org/forum/viewtopic.php?id=205
*/
/*
        test for the method of 'pseudo random poly decryptors
        described in the article "Advanced polymorphic engine
        construction" by The Mental Driller/29A, published in
        29A#5
        Register1 = Random(Encrypted_Data_Size)
        Register2 = InitialValue
Loop_Label:
        Decrypt [(Register1 XOR Register2)+Begin_Address_Of_Encrypted_Data]
        Register1 += Random (Encrypted_Data_Size) AND -2
        Register1 = Register1 MOD Encrypted_Data_Size
        Register2++
        Register2 = Register2 MOD Encrypted_Data_Size
        if Register2!=InitialValue GOTO Loop_Label
                GOTO Begin_Address_Of_Encrypted_Data
*/

unsigned int _random(unsigned int range)
{
        return rand() % range;
}

int main(int argc, char **argv)
{
        unsigned int    r0, r1, r2, init, ds = 16;
        unsigned char   i, test;
        unsigned char* seq;

        seq = malloc(ds * sizeof(typeof(seq)));
        
        /*      ds      - encrypted data size (must be power of 2)
                init    - init value for the counter
        */

        srand(time(0));       
        for (init = 0; init < ds; init++) {
                for (i = 0; i < ds; i++)
                        seq[i] = 0;     

                r0 = _random(ds) & ~1;
                r1 = _random(ds);
                r2 = init;
                do {
                        seq[r1 ^ r2]++;
                        printf("%2d ", r1 ^ r2);
                        r1 = (r1 + r0) % ds;
                        r2 = (r2 + 1 ) % ds;
                } while (r2 != init);
                printf("\t");

                /* test sequence, array seq must be filled with 1s */
                for (test = 1, i = 0; i < ds; i++)
                        if (seq[i] != 1)
                                test = 0;
                printf("%s", test == 1 ? "Ok\n" : "Failed\n");
        }
}
