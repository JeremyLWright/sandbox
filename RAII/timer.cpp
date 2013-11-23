//
// timer.cpp
// ~~~~~~~~~
//
// Copyright (c) 2003-2013 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include "socketcan.hpp"

#include <boost/asio/signal_set.hpp>

#include <linux/can.h>
#include <linux/can/raw.h>


void print(const boost::system::error_code& /*e*/,
    boost::asio::deadline_timer* t, int* count)
{
  if (*count < 50)
  {
    std::cout << *count << "\n";
    ++(*count);

    t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
    t->async_wait(boost::bind(print,
          boost::asio::placeholders::error, t, count));
  }
}

int main()
{
    boost::asio::io_service io;

    int count = 0;
    boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));
    t.async_wait(boost::bind(print,
                boost::asio::placeholders::error, &t, &count));
    // Register signal handlers so that the daemon may be shut down. You may
    // also want to register for other signals, such as SIGHUP to trigger a
    // re-read of a configuration file.
    boost::asio::signal_set signals(io, SIGINT, SIGTERM, SIGQUIT);
    signals.async_wait(
            boost::bind(&boost::asio::io_service::stop, &io));




    Can::socket mySkt( io );
    auto raw_fd = mySkt.native();
    struct can_filter rfilter;

    rfilter.can_id = 0x1D;
    rfilter.can_mask =  CAN_EFF_MASK;
    setsockopt(raw_fd, SOL_CAN_RAW, CAN_RAW_FILTER, &rfilter, sizeof(rfilter));

    io.run();

    std::cout << "Final count is " << count << "\n";

    return 0;
}
