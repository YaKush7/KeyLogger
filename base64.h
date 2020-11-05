#ifndef BASE_64
#define BASE_64

#include <string>
#include <vector>
using namespace std;

namespace base_64
{
    const string ele = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const string s2 = "W1ldW0FdW0hdW0ZdW0JdW0JdW0FdW1NdW0RdW1NdW1ZdW0pdW0VdW1VdW1JdW0hdW0ddW01dW0FdW1NdW0VudGVyXQ";
    const string s3 = "sdjvnwioangvaionicnijcop9tiv59uybjw3j9vhqy9q0opCMcgthnvbjkbdnvzkszaewvmoyu5nslrsapewe8swl";

    string base64_encode(const string &in)
    {
        string out;

        int val = 0, valb = -6;
        for (char c : in)
        {
            val = (val << 8) + c;
            valb += 8;
            while (valb >= 0)
            {
                out.push_back(ele[(val >> valb) & 0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
            out.push_back(ele[((val << 8) >> (valb + 8)) & 0x3F]);
        while (out.size() % 4)
            out.push_back('=');
        return out;
    }

    string encrypt(const string &in)
    {
        string s = base64_encode(in);
        s.insert(20, s2);
        s = base64_encode(s);
        s.insert(45, s3);
        return base64_encode(s);
    }

    string base64_decode(const string &in)
    {
        string out;

        vector<int> T(256, -1);
        for (int i = 0; i < 64; i++)
            T[ele[i]] = i;

        int val = 0, valb = -8;
        for (char c : in)
        {
            if (T[c] == -1)
                break;
            val = (val << 6) + T[c];
            valb += 6;
            if (valb >= 0)
            {
                out.push_back(char((val >> valb) & 0xFF));
                valb -= 8;
            }
        }
        return out;
    }
} // namespace base_64

#endif