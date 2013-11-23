
#include <linux/can.h>
#include <linux/can/raw.h>

// Encapsulates the flags needed for socket CAN.
/**
  * The can class contains flags necessary for CAN sockets.
  */
class Can {
     public:
         /// The type of a CAN endpoint.
         typedef boost::asio::ip::basic_endpoint<Can> endpoint;

         /// The type of a resolver query.
         typedef boost::asio::ip::basic_resolver_query<Can> resolver_query;

         /// The type of a resolver iterator.
         typedef boost::asio::ip::basic_resolver_iterator<Can> 
resolver_iterator;

         /// Construct to represent the socket CAN protocol.
         Can()
             : protocol_( CAN_RAW )
             , family_( PF_CAN )
         {
         }

         static Can v4()
         {
             return Can();
         }

         static Can v6()
         {
             return Can();
         }

         /// Obtain an identifier for the type of the protocol.
         int type() const
         {
             return SOCK_RAW;
         }

         /// Obtain an identifier for the protocol.
         int protocol() const
         {
             return protocol_;
         }

         /// Obtain an identifier for the protocol family.
         int family() const
         {
             return family_;
         }

         /// The CAN socket type.
         typedef boost::asio::basic_raw_socket<Can> socket;

         /// The CAN resolver type.
         typedef boost::asio::ip::basic_resolver<Can> resolver;

         /// Compare two protocols for equality.
         friend bool operator==(const Can& p1, const Can& p2)
         {
             return p1.protocol_ == p2.protocol_ && p1.family_ == 
p2.family_;
         }

         /// Compare two protocols for inequality.
         friend bool operator!=(const Can& p1, const Can& p2)
         {
             return p1.protocol_ != p2.protocol_ || p1.family_ != 
p2.family_;
         }

     private:
         int protocol_;
         int family_;
};

//
//That way I can create a Socket object simply by writing
//Can::socket mySkt( ios );
//However you have to call open() manually for this one.
//
//Best regards,
//Andreas
