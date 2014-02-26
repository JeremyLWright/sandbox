#include <stdexcept>
#include <iostream>
#include <functional>
#include <string>
#include <algorithm>
#include "pk11pub.h"
#include "nss.h"
#include <array>
#include <cstdint>
using namespace std;
template <typename T>
auto printDigest(T digest) -> void
{
    for(auto b : digest)
        std::cout << std::hex << (int)b << " ";
    std::cout << '\n';
}

std::string alphabet = "abcde";
size_t const pass_len = 8;

//struct rainbow_spectra {
//    std::function<
//};

class nss_sha256 {
    PK11SlotInfo *slot = 0;
    PK11Context *context = 0;
    PK11SymKey *key = 0;
    SECStatus s;
    public:
        nss_sha256():
            slot(PK11_GetInternalKeySlot()),
            context(PK11_CreateDigestContext(SEC_OID_SHA256))
        {
           if(!slot || !context)
               throw std::runtime_error("Count not initialize NSS");
        }
        ~nss_sha256()
        {
            if (context) PK11_DestroyContext(context, PR_TRUE);  /* freeit ?? */
            if (key) PK11_FreeSymKey(key);
            if (slot) PK11_FreeSlot(slot);
        }

        std::array<uint8_t, 32> operator()(uint8_t data[], unsigned int len)
        {
            uint8_t digest[32];

            s = PK11_DigestBegin(context);
            s = PK11_DigestOp(context, data, len);
            s = PK11_DigestFinal(context, digest, &len, sizeof(digest));
            std::array<uint8_t, 32> a;
            for(size_t i = 0; i < 32; ++i)
                a[i] = digest[i];
            return a;
        }
};
int main(int argc, const char *argv[])
{
    unsigned char data[80];

    /* Initialize NSS
     * If your application code has already initialized NSS, you can skip it
     * here.
     * This code uses the simplest of the Init functions, which does not
     * require a NSS database to exist
     */
    NSS_NoDB_Init(".");

    /* Initialize data */
    memset(data, 0xbc, sizeof data);
    nss_sha256 sha;
    auto digest = sha(data, sizeof(data));
    printDigest(digest);
    data[9] = '9';
    digest = sha(data, sizeof(data));
    printDigest(digest);

    return 0;
}
