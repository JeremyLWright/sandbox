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
namespace
{
    // events
    struct SystemTick 
    {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                cout << "\tSystem Tick" << endl;
            }

            void hit_ticks()
            {
                ++_ticks;
            }
            
            void reset_ticks()
            {
                _ticks = 0;
            }

            int _ticks;
    };


    // front-end: define the FSM structure 
    struct my_machine_ : public msm::front::state_machine_def<my_machine_>
    {
        // The list of FSM states
        struct RemoveBread : public msm::front::state<> 
        {
            // every (optional) entry/exit methods get the event passed.
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {std::cout << "entering: RemoveBread" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: RemoveBread" << std::endl;}
        };
        struct SpreadPB : public msm::front::state<> 
        { 
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {std::cout << "entering: SpreadPB" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: SpreadPB" << std::endl;}
        };

        struct SpreadJam : public msm::front::state<> 
        { 
            // when stopped, the CD is loaded
            template <class Event,class FSM>
            void on_entry(Event const& ,FSM&) {std::cout << "entering: SpreadJam" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: SpreadJam" << std::endl;}
        };

        struct PutHalvesTogether : public msm::front::state<>
        {
            template <class Event,class FSM>
            void on_entry(Event const&,FSM& ) {std::cout << "entering: PutHalvesTogether" << std::endl;}
            template <class Event,class FSM>
            void on_exit(Event const&,FSM& ) {std::cout << "leaving: PutHalvesTogether" << std::endl;}
        };

        // the initial state of the player SM. Must be defined
        typedef RemoveBread initial_state;

        // transition actions
        struct SpreadPBToSpreadJam 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                std::cout << "my_machine::SpreadPBToSpreadJam" << std::endl;
            }
        };
        struct SpreadJamToPutHalvesTogether 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            void operator()(EVT const& ,FSM& ,SourceState& ,TargetState& )
            {
                std::cout << "my_machine::SpreadJamToPutHalvesTogether" << std::endl;
            }
        };
        // guard conditions
        struct always_true 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
                std::cout << "always_true" << std::endl;
                return true;
            }
        };
        struct always_false 
        {
            template <class EVT,class FSM,class SourceState,class TargetState>
            bool operator()(EVT const& evt,FSM& fsm,SourceState& src,TargetState& tgt)
            {
                std::cout << "always_false" << std::endl;
                return true;
            }
        };
        
        bool check_ticks(int current, int goal)
        {
            (current < goal) ? return false : return true;
        } 
        typedef my_machine_ p; // makes transition table cleaner

        // Transition table for player
        struct transition_table : mpl::vector<
            //    Start     Event         Next      Action               Guard
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < RemoveBread   , none  , RemoveBread , &SystemTick::hit_ticks , &check_ticks  >,
            Row < RemoveBread   , none  , SpreadPB    , none , ((SystemTick::_ticks >= 5) ? true : false)  >,
            Row < SpreadPB      , none  , SpreadJam  , SpreadPBToSpreadJam                             >,
            //  +---------+-------------+---------+---------------------+----------------------+
            Row < SpreadJam  , none        , PutHalvesTogether  , SpreadJamToPutHalvesTogether      , always_true          >,
            Row < PutHalvesTogether  , hit_system_tick      , RemoveBread                                               >
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
#if 1
int main()
{
    test();
    return 0;
}
#endif
