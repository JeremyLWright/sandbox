#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <utility>
using std::for_each;
using std::function;
using std::vector;
using std::cout;
using std::endl;

template <typename F>
class multicast_delegate : public  function<F> {
    public:
        typedef vector<typename function<F>::result_type> result_type;
        typedef typename function<F>::result_type root_result_type;
       // typedef typename function<F>::allocator_type allocator_type;

        explicit multicast_delegate() {}

        template<typename F2> multicast_delegate( function<F2> f) { l_.insert( f ); }

        void add( function<F> f) { l_.push_back(f); }
        void remove( function<F> f) { l_.erase(f); }
        
        void operator+=( function<F> f) { add(f); }
        void operator-=( function<F> f) { remove(f); }

        void swap( multicast_delegate& other ) { l_.swap(other.l_); }
        void clear() { l_.clear(); }

        bool empty() const { return l_.empty(); }
        operator bool() const { return l_.empty(); }

    template<typename... Ts>
        void operator()(Ts... vs) const {

            // GCC-Bug 41933 prevents us from placing this in a lambda.
            for(auto i = begin(l_); i != end(l_); ++i) 
            {
                    (*i)(vs...);
            }
        }
    private: 
        vector<function<F> > l_;
};

template<typename MF1, typename MF2>
void swap( multicast_delegate<MF1>& mf1, multicast_delegate<MF2>& mf2 )
{
    mf1.swap(mf2);
}

template<typename MF1, typename MF2>
bool operator==(multicast_delegate<MF1> const & mf1, multicast_delegate<MF2> const & mf2)
{
 //   for( auto aCallback = begin(mf1.l_); aCallback != end(mf1.l_); ++aCallback)
 //   {
 //       if(find(begin(mf2.l_), end(mf2.l_), *aCallback) == end(mf2.l_))
                    return false;
 //   }
 //   return true;
}

template<typename MF1, typename MF2>
bool operator!=( multicast_delegate<MF1> const & mf1, multicast_delegate<MF2> const & mf2)
{
    return !(mf1 == mf2);
}

class a
{
    public:
    int hello(int n, double, double)
    {
        cout << "Hello " << n << endl;
    }
};

int bye(int n, double, double)
{
    cout << "Bye " << n << endl;
}

int doNothing()
{
    cout << "Nothing." << endl;
}
using namespace std;
int main()
{

    auto s = a();
    //multicast_delegate<int(int,double,double)> m;
    mem_fn(&a::hello)(s,12, 2.5, 5);

    return 0;

}
