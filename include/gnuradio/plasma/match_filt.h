/* -*- c++ -*- */
/*
 * Copyright 2022 gr-plasma author.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_PLASMA_MATCH_FILT_H
#define INCLUDED_PLASMA_MATCH_FILT_H

#include <gnuradio/block.h>
#include <gnuradio/plasma/api.h>

namespace gr {
namespace plasma {

/*!
 * \brief <+description of block+>
 * \ingroup plasma
 *
 */
class PLASMA_API match_filt : virtual public gr::block
{
public:
    typedef std::shared_ptr<match_filt> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of plasma::match_filt.
     *
     * To avoid accidental use of raw pointers, plasma::match_filt's
     * constructor is in a private implementation
     * class. plasma::match_filt::make is the public interface for
     * creating new instances.
     */
    static sptr make(size_t num_pulse_cpi);
};

} // namespace plasma
} // namespace gr

#endif /* INCLUDED_PLASMA_MATCH_FILT_H */
