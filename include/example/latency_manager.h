/* -*- c++ -*- */
/*
 * Copyright 2019 Derek Kozel.
 *
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_EXAMPLE_LATENCY_MANAGER_H
#define INCLUDED_EXAMPLE_LATENCY_MANAGER_H

#include <example/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
  namespace example {

    /*!
     * \brief <+description of block+>
     * \ingroup example
     *
     */
    class EXAMPLE_API latency_manager : virtual public gr::sync_block
    {
     public:
      typedef boost::shared_ptr<latency_manager> sptr;

      static sptr make(int max_tags_in_flight);
    };

  } // namespace example
} // namespace gr

#endif /* INCLUDED_EXAMPLE_LATENCY_MANAGER_H */

