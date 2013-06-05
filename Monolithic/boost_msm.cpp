#include <iostream>
// back-end
#include <boost/msm/back/state_machine.hpp>
//front-end
#include <boost/msm/front/state_machine_def.hpp>
// functors
#include <boost/msm/front/functor_row.hpp>
#include <boost/msm/front/euml/common.hpp>

namespace msm = boost::msm;
namespace mpl = boost::mpl;
using namespace boost::msm::front;
using std::cout;
using std::endl;

//#define DEBUG

namespace
{
    // events
    struct SystemTick 
    {
            SystemTick():
                _ticks{0}
            {
            }
            
            int hit_ticks()
            {
#ifdef DEBUG
                cout << "\tHit Tick." << endl;
#endif
                return ++_ticks;
            }
            
            void reset_ticks()
            {
               // cout << "Reset Ticks." << endl;
                _ticks = 0;
            }

            int _ticks;
    };
    
    SystemTick g_tick;
    int eaten_sandwiches = 0;

    // front-end: define the FSM structure 
    struct my_machine_ : public msm::front::state_machine_def<my_machine_>
    {
        // The list of FSM states
        struct RemoveBread : public msm::front::state<> 
        {
            // every (optional) entry/exit methods get the event passed.
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "entering: RemoveBread" << std::endl;
#endif
                while(g_tick.hit_ticks() < 5);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG 
                std::cout << "leaving: RemoveBread" << std::endl;
#endif
            }
        };
        struct SpreadPB : public msm::front::state<> 
        { 
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) 
            {
#ifdef DEBUG
                std::cout << "entering: SpreadPB" << std::endl;
#endif
                while(g_tick.hit_ticks() < 2);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "leaving: SpreadPB" << std::endl;
#endif
            }
        };

        struct SpreadJam : public msm::front::state<> 
        { 
            // when stopped, the CD is loaded
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) 
            {
#ifdef DEBUG
                std::cout << "entering: SpreadJam" << std::endl;
#endif
                while(g_tick.hit_ticks() < 2);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "leaving: SpreadJam" << std::endl;
#endif
            }
        };

        struct PutHalvesTogether : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "entering: PutHalvesTogether" << std::endl;
#endif
                while(g_tick.hit_ticks() < 2);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "leaving: PutHalvesTogether" << std::endl;
#endif
            }
        };

        struct EatSandwich : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "entering: Eating Sandwich" << std::endl;
#endif
                while(g_tick.hit_ticks() < 10);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
                ++eaten_sandwiches;
#ifdef DEBUG
                std::cout << "leaving: Eating Sandwich" << std::endl;
#endif
            }
        };

        struct GoToWork : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "entering: Going To Work" << std::endl;
#endif
                while(g_tick.hit_ticks() < 20);
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "leaving: Going To Work" << std::endl;
#endif
            }
        };
        struct Done : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "entering: Done" << std::endl;
#endif
            }
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) 
            {
#ifdef DEBUG
                std::cout << "leaving: Done" << std::endl;
#endif
            }
        };
        // the initial state of the player SM. Must be defined
        typedef RemoveBread initial_state;

        // transition actions
        struct ResetTick
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                g_tick.reset_ticks();
            }
        };

        struct ResetSandwich
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                eaten_sandwiches = 0;
                ResetTick();
            }
        };

        
        // guard conditions
        struct user_is_full 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
#ifdef DEBUG
                std::cout << "always_true" << std::endl;
#endif
                return (eaten_sandwiches > 2) ? true : false;
            }
        };

        struct user_is_hungry 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
#ifdef DEBUG
                std::cout << "always_false" << std::endl;
#endif
                return (eaten_sandwiches <= 2) ? true : false;
            }
        };
        
        typedef my_machine_ p; // makes transition table cleaner

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action               Guard
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < RemoveBread       , none  , SpreadPB          , ResetTick, none           >,
            Row < SpreadPB          , none  , SpreadJam         , ResetTick, none           >,
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < SpreadJam         , none  , PutHalvesTogether , ResetTick, none           >,
            Row < PutHalvesTogether , none  , EatSandwich       , ResetTick, none           >,
            Row < EatSandwich       , none  , GoToWork          , ResetTick, user_is_full   >,
            Row < EatSandwich       , none  , RemoveBread       , ResetTick, user_is_hungry >,
            Row < GoToWork          , none  , Done              , ResetSandwich, none           >

            //  +---------+-------------+---------+---------------------+----------------------+
        > {};

        // Replaces the default no-transition response.
        template <class FSM,class Event>
        void no_transition(Event const& e, FSM&,int state)
        {
            std::cout << "no transition from state " << state
                << " on event " << typeid(e).name() << std::endl;
        }

    };
    // Pick a back-end
    typedef msm::back::state_machine<my_machine_> my_machine;

    //
    // Testing utilities.
    //
    static char const* const state_names[] = { "Remove Bread", "Spread Peanut Butter", "Spread Jam", "Put Halves Together", "Eat Sandwich", "Go To Work", "Done" };
    void pstate(my_machine const& p)
    {
        std::cout << " -> " << state_names[p.current_state()[0]] << std::endl;
    }

    void test()
    {        
        my_machine p;

        // needed to start the highest-level SM. This will call on_entry and mark the start of the SM
        // in this case it will also immediately trigger all anonymous transitions
        p.start(); 
        // this event will bring us back to the initial state and thus, a new "loop" will be started
        //p.process_event(system_tick());

    }
}
#if 0
int main()
{
    test();
    return 0;
}
#else
extern "C" void run_machine()
{
    test();
}
#endif
