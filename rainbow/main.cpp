#include <stdexcept>
#include <iostream>
#include <functional>
#include <string>

#include "pk11pub.h"
#include "nss.h"
#include <array>
#include <cstdint>
using namespace std;
    static void
printDigest(unsigned char *digest, unsigned int len)
{
    int i;

    cout << "length: " << len << endl;
    for(i = 0;i < len;i++) printf("%02x ", digest[i]);
    cout << endl;
}

std::string alphabet = "abcde";
size_t const pass_len = 8;

//struct rainbow_spectra {
//    std::function<
//};

class nss_sha256 {
    PK11SlotInfo *slot = 0;
    PK11Context *context = 0;
    SECStatus s;
    public:
        nss_sha256():
            slot(PK11_GetInternalKeySlot()),
            context(PK11_CreateDigestContext(SEC_OID_SHA256))
        {
           if(!slot || !context)
               throw std::runtime_error("Count not initialize NSS");
        }

        std::array<uint8_t, 32> operator(uint8_t[] data, size_t len)
        {
            uint8_t digest[32];

            s = PK11_DigestBegin(context);
            s = PK11_DigestOp(context, data, len);
            s = PK11_DigestFinal(context, digest, &len, sizeof(digest));
            std::array<uint8_t, 32> a(digest);
            return a;
        }
};
int main(int argc, const char *argv[])
{
     int status = 0;
    PK11SlotInfo *slot = 0;
    PK11SymKey *key = 0;
    PK11Context *context = 0;
    unsigned char data[80];
    unsigned char digest[20]; /*Is there a way to tell how large the output is?*/
    unsigned int len;
    SECStatus s;

    /* Initialize NSS
     * If your application code has already initialized NSS, you can skip it
     * here.
     * This code uses the simplest of the Init functions, which does not
     * require a NSS database to exist
     */
    NSS_NoDB_Init(".");

    /* Get a slot to use for the crypto operations */
    slot = PK11_GetInternalKeySlot();
    if (!slot)
    {
        cout << "GetInternalKeySlot failed" << endl;
        status = 1;
        goto done;
    }

    /*
     *  Part 1 - Simple hashing
     */
    cout << "Part 1 -- Simple hashing" << endl;

    /* Initialize data */
    memset(data, 0xbc, sizeof data);

    /* Create a context for hashing (digesting) */
    context = PK11_CreateDigestContext(SEC_OID_SHA256);
    if (!context) { cout << "CreateDigestContext failed" << endl; goto done; }

    s = PK11_DigestBegin(context);
    if (s != SECSuccess) { cout << "DigestBegin failed" << endl; goto done; }

    s = PK11_DigestOp(context, data, sizeof data);
    if (s != SECSuccess) { cout << "DigestUpdate failed" << endl; goto done; }

    s = PK11_DigestFinal(context, digest, &len, sizeof digest);
    if (s != SECSuccess) { cout << "DigestFinal failed" << endl; goto done; }

    /* Print digest */
    printDigest(digest, len);

    PK11_DestroyContext(context, PR_TRUE);
    context = 0;
done:  
  if (context) PK11_DestroyContext(context, PR_TRUE);  /* freeit ?? */
  if (key) PK11_FreeSymKey(key);
  if (slot) PK11_FreeSlot(slot);
    return 0;
}
