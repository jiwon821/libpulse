#pragma once

#include <windows.h>

#include "pulse/pulseaudio.h"

// Patched functions as they were in the original foo_out_pulse sources.
// I'm not enough of a C++ programmer to know whether there's a better
// way to do this, but at least this works.
static pa_bytes_to_usec                     g_pa_bytes_to_usec;
static pa_channel_map_init_auto             g_pa_channel_map_init_auto;
static pa_context_connect                   g_pa_context_connect;
static pa_context_disconnect                g_pa_context_disconnect;
static pa_context_errno                     g_pa_context_errno;
static pa_context_get_sink_input_info       g_pa_context_get_sink_input_info;
static pa_context_get_state                 g_pa_context_get_state;
static pa_context_new_with_proplist         g_pa_context_new_with_proplist;
static pa_context_set_event_callback        g_pa_context_set_event_callback;
static pa_context_set_sink_input_volume     g_pa_context_set_sink_input_volume;
static pa_context_set_state_callback        g_pa_context_set_state_callback;
static pa_context_set_subscribe_callback    g_pa_context_set_subscribe_callback;
static pa_context_subscribe                 g_pa_context_subscribe;
static pa_context_unref                     g_pa_context_unref;
static pa_cvolume_equal                     g_pa_cvolume_equal;
static pa_cvolume_init                      g_pa_cvolume_init;
static pa_cvolume_set                       g_pa_cvolume_set;
static pa_cvolume_valid                     g_pa_cvolume_valid;
static pa_operation_get_state               g_pa_operation_get_state;
static pa_operation_unref                   g_pa_operation_unref;
static pa_proplist_free                     g_pa_proplist_free;
static pa_proplist_new                      g_pa_proplist_new;
static pa_proplist_set                      g_pa_proplist_set;
static pa_proplist_setp                     g_pa_proplist_setp;
static pa_proplist_sets                     g_pa_proplist_sets;
static pa_stream_cancel_write               g_pa_stream_cancel_write;
static pa_stream_connect_playback           g_pa_stream_connect_playback;
static pa_stream_cork                       g_pa_stream_cork;
static pa_stream_disconnect                 g_pa_stream_disconnect;
static pa_stream_drain                      g_pa_stream_drain;
static pa_stream_drop                       g_pa_stream_drop;
static pa_stream_flush                      g_pa_stream_flush;
static pa_stream_get_buffer_attr            g_pa_stream_get_buffer_attr;
static pa_stream_get_index                  g_pa_stream_get_index;
static pa_stream_get_latency                g_pa_stream_get_latency;
static pa_stream_get_sample_spec            g_pa_stream_get_sample_spec;
static pa_stream_get_state                  g_pa_stream_get_state;
static pa_stream_get_timing_info            g_pa_stream_get_timing_info;
static pa_stream_is_corked                  g_pa_stream_is_corked;
static pa_stream_new                        g_pa_stream_new;
static pa_stream_set_started_callback       g_pa_stream_set_started_callback;
static pa_stream_set_state_callback         g_pa_stream_set_state_callback;
static pa_stream_set_underflow_callback     g_pa_stream_set_underflow_callback;
static pa_stream_set_write_callback         g_pa_stream_set_write_callback;
static pa_stream_trigger                    g_pa_stream_trigger;
static pa_stream_unref                      g_pa_stream_unref;
static pa_stream_update_sample_rate         g_pa_stream_update_sample_rate;
static pa_stream_update_timing_info         g_pa_stream_update_timing_info;
static pa_stream_writable_size              g_pa_stream_writable_size;
static pa_stream_write                      g_pa_stream_write;
static pa_strerror                          g_pa_strerror;
static pa_sw_volume_from_dB                 g_pa_sw_volume_from_dB;
static pa_sw_volume_to_dB                   g_pa_sw_volume_to_dB;
static pa_threaded_mainloop_accept          g_pa_threaded_mainloop_accept;
static pa_threaded_mainloop_free            g_pa_threaded_mainloop_free;
static pa_threaded_mainloop_get_api         g_pa_threaded_mainloop_get_api;
static pa_threaded_mainloop_get_retval      g_pa_threaded_mainloop_get_retval;
static pa_threaded_mainloop_lock            g_pa_threaded_mainloop_lock;
static pa_threaded_mainloop_new             g_pa_threaded_mainloop_new;
static pa_threaded_mainloop_signal          g_pa_threaded_mainloop_signal;
static pa_threaded_mainloop_start           g_pa_threaded_mainloop_start;
static pa_threaded_mainloop_stop            g_pa_threaded_mainloop_stop;
static pa_threaded_mainloop_unlock          g_pa_threaded_mainloop_unlock;
static pa_threaded_mainloop_wait            g_pa_threaded_mainloop_wait;
static pa_usec_to_bytes                     g_pa_usec_to_bytes;

// Indicates whether the libpulse DLL has been loaded
static bool g_pa_is_loaded = false;

// Loads the libpulse DLL from the specified path
static bool g_pa_load(const std::wstring& path)
{
    HMODULE libpulse;

    if (g_pa_is_loaded)
    {
        return true;
    }

    if (!(libpulse = LoadLibraryExW(path.c_str(), NULL, LOAD_WITH_ALTERED_SEARCH_PATH)))
    {
        return false;
    }

    if (!(g_pa_bytes_to_usec = (pa_bytes_to_usec)GetProcAddress(libpulse, "pa_bytes_to_usec")) ||
        !(g_pa_channel_map_init_auto = (pa_channel_map_init_auto)GetProcAddress(libpulse, "pa_channel_map_init_auto")) ||
        !(g_pa_context_connect = (pa_context_connect)GetProcAddress(libpulse, "pa_context_connect")) ||
        !(g_pa_context_disconnect = (pa_context_disconnect)GetProcAddress(libpulse, "pa_context_disconnect")) ||
        !(g_pa_context_errno = (pa_context_errno)GetProcAddress(libpulse, "pa_context_errno")) ||
        !(g_pa_context_get_sink_input_info = (pa_context_get_sink_input_info)GetProcAddress(libpulse, "pa_context_get_sink_input_info")) ||
        !(g_pa_context_get_state = (pa_context_get_state)GetProcAddress(libpulse, "pa_context_get_state")) ||
        !(g_pa_context_new_with_proplist = (pa_context_new_with_proplist)GetProcAddress(libpulse, "pa_context_new_with_proplist")) ||
        !(g_pa_context_set_event_callback = (pa_context_set_event_callback)GetProcAddress(libpulse, "pa_context_set_event_callback")) ||
        !(g_pa_context_set_sink_input_volume = (pa_context_set_sink_input_volume)GetProcAddress(libpulse, "pa_context_set_sink_input_volume")) ||
        !(g_pa_context_set_state_callback = (pa_context_set_state_callback)GetProcAddress(libpulse, "pa_context_set_state_callback")) ||
        !(g_pa_context_set_subscribe_callback = (pa_context_set_subscribe_callback)GetProcAddress(libpulse, "pa_context_set_subscribe_callback")) ||
        !(g_pa_context_subscribe = (pa_context_subscribe)GetProcAddress(libpulse, "pa_context_subscribe")) ||
        !(g_pa_context_unref = (pa_context_unref)GetProcAddress(libpulse, "pa_context_unref")) ||
        !(g_pa_cvolume_equal = (pa_cvolume_equal)GetProcAddress(libpulse, "pa_cvolume_equal")) ||
        !(g_pa_cvolume_init = (pa_cvolume_init)GetProcAddress(libpulse, "pa_cvolume_init")) ||
        !(g_pa_cvolume_set = (pa_cvolume_set)GetProcAddress(libpulse, "pa_cvolume_set")) ||
        !(g_pa_cvolume_valid = (pa_cvolume_valid)GetProcAddress(libpulse, "pa_cvolume_valid")) ||
        !(g_pa_operation_get_state = (pa_operation_get_state)GetProcAddress(libpulse, "pa_operation_get_state")) ||
        !(g_pa_operation_unref = (pa_operation_unref)GetProcAddress(libpulse, "pa_operation_unref")) ||
        !(g_pa_proplist_free = (pa_proplist_free)GetProcAddress(libpulse, "pa_proplist_free")) ||
        !(g_pa_proplist_new = (pa_proplist_new)GetProcAddress(libpulse, "pa_proplist_new")) ||
        !(g_pa_proplist_set = (pa_proplist_set)GetProcAddress(libpulse, "pa_proplist_set")) ||
        !(g_pa_proplist_setp = (pa_proplist_setp)GetProcAddress(libpulse, "pa_proplist_setp")) ||
        !(g_pa_proplist_sets = (pa_proplist_sets)GetProcAddress(libpulse, "pa_proplist_sets")) ||
        !(g_pa_stream_cancel_write = (pa_stream_cancel_write)GetProcAddress(libpulse, "pa_stream_cancel_write")) ||
        !(g_pa_stream_connect_playback = (pa_stream_connect_playback)GetProcAddress(libpulse, "pa_stream_connect_playback")) ||
        !(g_pa_stream_cork = (pa_stream_cork)GetProcAddress(libpulse, "pa_stream_cork")) ||
        !(g_pa_stream_disconnect = (pa_stream_disconnect)GetProcAddress(libpulse, "pa_stream_disconnect")) ||
        !(g_pa_stream_drain = (pa_stream_drain)GetProcAddress(libpulse, "pa_stream_drain")) ||
        !(g_pa_stream_drop = (pa_stream_drop)GetProcAddress(libpulse, "pa_stream_drop")) ||
        !(g_pa_stream_flush = (pa_stream_flush)GetProcAddress(libpulse, "pa_stream_flush")) ||
        !(g_pa_stream_get_buffer_attr = (pa_stream_get_buffer_attr)GetProcAddress(libpulse, "pa_stream_get_buffer_attr")) ||
        !(g_pa_stream_get_index = (pa_stream_get_index)GetProcAddress(libpulse, "pa_stream_get_index")) ||
        !(g_pa_stream_get_latency = (pa_stream_get_latency)GetProcAddress(libpulse, "pa_stream_get_latency")) ||
        !(g_pa_stream_get_sample_spec = (pa_stream_get_sample_spec)GetProcAddress(libpulse, "pa_stream_get_sample_spec")) ||
        !(g_pa_stream_get_state = (pa_stream_get_state)GetProcAddress(libpulse, "pa_stream_get_state")) ||
        !(g_pa_stream_get_timing_info = (pa_stream_get_timing_info)GetProcAddress(libpulse, "pa_stream_get_timing_info")) ||
        !(g_pa_stream_is_corked = (pa_stream_is_corked)GetProcAddress(libpulse, "pa_stream_is_corked")) ||
        !(g_pa_stream_new = (pa_stream_new)GetProcAddress(libpulse, "pa_stream_new")) ||
        !(g_pa_stream_set_started_callback = (pa_stream_set_started_callback)GetProcAddress(libpulse, "pa_stream_set_started_callback")) ||
        !(g_pa_stream_set_state_callback = (pa_stream_set_state_callback)GetProcAddress(libpulse, "pa_stream_set_state_callback")) ||
        !(g_pa_stream_set_underflow_callback = (pa_stream_set_underflow_callback)GetProcAddress(libpulse, "pa_stream_set_underflow_callback")) ||
        !(g_pa_stream_set_write_callback = (pa_stream_set_write_callback)GetProcAddress(libpulse, "pa_stream_set_write_callback")) ||
        !(g_pa_stream_trigger = (pa_stream_trigger)GetProcAddress(libpulse, "pa_stream_trigger")) ||
        !(g_pa_stream_unref = (pa_stream_unref)GetProcAddress(libpulse, "pa_stream_unref")) ||
        !(g_pa_stream_update_sample_rate = (pa_stream_update_sample_rate)GetProcAddress(libpulse, "pa_stream_update_sample_rate")) ||
        !(g_pa_stream_update_timing_info = (pa_stream_update_timing_info)GetProcAddress(libpulse, "pa_stream_update_timing_info")) ||
        !(g_pa_stream_writable_size = (pa_stream_writable_size)GetProcAddress(libpulse, "pa_stream_writable_size")) ||
        !(g_pa_stream_write = (pa_stream_write)GetProcAddress(libpulse, "pa_stream_write")) ||
        !(g_pa_strerror = (pa_strerror)GetProcAddress(libpulse, "pa_strerror")) ||
        !(g_pa_sw_volume_from_dB = (pa_sw_volume_from_dB)GetProcAddress(libpulse, "pa_sw_volume_from_dB")) ||
        !(g_pa_sw_volume_to_dB = (pa_sw_volume_to_dB)GetProcAddress(libpulse, "pa_sw_volume_to_dB")) ||
        !(g_pa_threaded_mainloop_accept = (pa_threaded_mainloop_accept)GetProcAddress(libpulse, "pa_threaded_mainloop_accept")) ||
        !(g_pa_threaded_mainloop_free = (pa_threaded_mainloop_free)GetProcAddress(libpulse, "pa_threaded_mainloop_free")) ||
        !(g_pa_threaded_mainloop_get_api = (pa_threaded_mainloop_get_api)GetProcAddress(libpulse, "pa_threaded_mainloop_get_api")) ||
        !(g_pa_threaded_mainloop_get_retval = (pa_threaded_mainloop_get_retval)GetProcAddress(libpulse, "pa_threaded_mainloop_get_retval")) ||
        !(g_pa_threaded_mainloop_lock = (pa_threaded_mainloop_lock)GetProcAddress(libpulse, "pa_threaded_mainloop_lock")) ||
        !(g_pa_threaded_mainloop_new = (pa_threaded_mainloop_new)GetProcAddress(libpulse, "pa_threaded_mainloop_new")) ||
        !(g_pa_threaded_mainloop_signal = (pa_threaded_mainloop_signal)GetProcAddress(libpulse, "pa_threaded_mainloop_signal")) ||
        !(g_pa_threaded_mainloop_start = (pa_threaded_mainloop_start)GetProcAddress(libpulse, "pa_threaded_mainloop_start")) ||
        !(g_pa_threaded_mainloop_stop = (pa_threaded_mainloop_stop)GetProcAddress(libpulse, "pa_threaded_mainloop_stop")) ||
        !(g_pa_threaded_mainloop_unlock = (pa_threaded_mainloop_unlock)GetProcAddress(libpulse, "pa_threaded_mainloop_unlock")) ||
        !(g_pa_threaded_mainloop_wait = (pa_threaded_mainloop_wait)GetProcAddress(libpulse, "pa_threaded_mainloop_wait")) ||
        !(g_pa_usec_to_bytes = (pa_usec_to_bytes)GetProcAddress(libpulse, "pa_usec_to_bytes")))
    {
        return false;
    }

    g_pa_is_loaded = true;
    return true;
}
