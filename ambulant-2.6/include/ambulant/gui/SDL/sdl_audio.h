/*
 * This file is part of Ambulant Player, www.ambulantplayer.org.
 *
 * Copyright (C) 2003-2015 Stichting CWI, 
 * Science Park 123, 1098 XG Amsterdam, The Netherlands.
 *
 * Ambulant Player is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 *
 * Ambulant Player is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Ambulant Player; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef AMBULANT_GUI_SDL_SDL_AUDIO_H
#define AMBULANT_GUI_SDL_SDL_AUDIO_H

#ifdef AMBULANT_PLATFORM_WIN32
// Try to hide duplicate definitions (sdl and ffmpeg) of standard
// Unix typedefs on Windows
#define int8_t _sdl_int8_t
#endif
#include "SDL.h"
#ifdef AMBULANT_PLATFORM_WIN32
#undef int8_t
#endif
#include <iostream>

#include "ambulant/common/factory.h"
#include "ambulant/lib/mtsync.h"
#include "ambulant/common/factory.h"
#include "ambulant/common/layout.h"
#include "ambulant/common/renderer_impl.h"
#include "ambulant/lib/logger.h"
#include "ambulant/gui/none/none_gui.h"
#include "ambulant/net/datasource.h"
#include "ambulant/lib/event_processor.h"
#include "ambulant/smil2/transition.h"
#include "ambulant/lib/transition_info.h"
#include "ambulant/lib/asb.h"


#define SDL_BUFFER_MAX_BYTES 819200
#define SDL_BUFFER_MIN_BYTES 20480

#define AMBULANT_MAX_CHANNELS 2

namespace ambulant {
namespace gui {
namespace sdl {

class sdl_audio_renderer : public common::renderer_playable {

  public:
	sdl_audio_renderer(
	common::playable_notification *context,
	common::playable_notification::cookie_type cookie,
	const lib::node *node,
	lib::event_processor *evp,
	common::factories *factory,
	common::playable_factory_machdep *mdp);

	sdl_audio_renderer(
	common::playable_notification *context,
	common::playable_notification::cookie_type cookie,
	const lib::node *node,
	lib::event_processor *evp,
	common::factories *factory,
	net::audio_datasource *ds);

	~sdl_audio_renderer();

//#define SDL_REFCOUNT_TRACKING
#ifdef  SDL_REFCOUNT_TRACKING
	long add_ref();
	long release();
#endif//SDL_REFCOUNT_TRACKING

	common::duration get_dur();
	void start(double where);
//	void stop();
	bool stop();
	void post_stop();
	void init_with_node(const lib::node *n);
	void preroll(double when, double where, double how_much);
	void seek(double t);
	void pause(common::pause_display d=common::display_show);
	void resume();
//	void freeze() {};
//	void speed_changed() {};

//	void set_surface(common::surface *dest) { abort(); }
//	common::surface *get_surface() { abort(); }
//	void set_alignment(common::alignment *align) { /* Ignore, for now */ }
//	void transition_freeze_end(lib::rect area) {}
	void redraw(const lib::rect &dirty, common::gui_window *window) {}
	static void sdl_callback(Uint8 *stream, size_t len);
	void set_intransition(const lib::transition_info* info);
	void start_outtransition(const lib::transition_info* info);
	static void quit();
  private:
	bool _can_be_clock_master();
	bool _can_slip();
	void _data_avail();
	bool _restart_audio_input();
	size_t _get_data(size_t bytes_wanted, Uint8 **ptr, size_t *insert_count);
	void _get_data_done(size_t size);
	net::audio_datasource *m_audio_src;
	lib::critical_section m_lock;

	bool m_is_playing;  // Invariant: m_is_playing === register_renderer() has been called.
	bool m_is_reading;	// Invariant: m_is_reading === m_audio_src->start() has been called.
	bool m_is_paused;
	bool m_is_stalled;	// True if a stalled() callback was emitted previously
	bool m_read_ptr_called;
	bool m_audio_started;
	int m_volcount;
	float m_volumes[AMBULANT_MAX_CHANNELS];
	const lib::transition_info* m_intransition;
	const lib::transition_info* m_outtransition;
	smil2::audio_transition_engine* m_transition_engine;
	net::timestamp_t m_previous_clip_position;
	lib::timer::time_type m_audio_clock;
	common::recorder* m_recorder;
	// class methods and attributes:
	static int init();
	static void register_renderer(sdl_audio_renderer *rnd);
	static void unregister_renderer(sdl_audio_renderer *rnd);
	static bool s_sdl_init;			// True when SDL has beeen initialized
	static Uint16 s_sdl_format;		// Audio format we want, in SDL terms
	static net::audio_format s_ambulant_format;	// Audio format we want, in Ambulant terms
	static size_t s_buffer_size;		// Number of samples we want SDL to process at once
	static size_t s_min_buffer_size_bytes;		// Minimum number of bytes we need for the abobe
	static lib::critical_section s_static_lock;
	static std::list<sdl_audio_renderer *>s_renderers;
	static sdl_audio_renderer *s_master_clock_renderer;
};

} // end namespace sdl
} // end namespace gui
} // end namespace ambulant


#endif // AMBULANT_GUI_SDL_SDL_AUDIO_H
