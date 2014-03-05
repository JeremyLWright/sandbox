#include <stdexcept>
#include <fstream>
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

        std::array<uint8_t, 32> operator()(uint8_t const data[], unsigned int len)
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

template <size_t PASS_LEN=3>
class hash_chain {
    nss_sha256 sha;
    public:
    hash_chain()
    {
    }

    auto hash(std::string p) -> std::array<uint8_t, 32>
    {
        uint8_t const * d = (uint8_t const *)p.c_str();
        return sha(d, p.size());
    }


    auto reduce(std::array<uint8_t, 32> h) -> std::string
    {
        auto toBase26 = [](uint8_t n){ return 'a' + n%26;};
        std::string s;
        std::transform(std::begin(h), std::begin(h)+PASS_LEN, std::back_inserter(s), toBase26);
        return s;
    }
};

int main(int argc, const char *argv[])
{

    /* Initialize NSS
     * If your application code has already initialized NSS, you can skip it
     * here.
     * This code uses the simplest of the Init functions, which does not
     * require a NSS database to exist
     */
    NSS_NoDB_Init(".");
    std::ofstream f("rainbow.3.txt");
    hash_chain<3> hc;
    std::string p = "abcde";
    while(std::next_permutation(std::begin(p), std::end(p)))
    {
        std::string o(std::begin(p), std::begin(p)+3);
        f << o << ":";
        for(int i = 0; i < 100000; ++i)
        {
            auto h = hc.hash(o);
            o = hc.reduce(h);
        }
        f << o << '\n';
    }


    return 0;
}
