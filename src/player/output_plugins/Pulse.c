/**
 * Pulse.c
 *
 * Module: player
 *
 * Wrapper of the pulseaudio library C api.
 *
 * The code is a modification of the pulse.c code found at the open
 * source CMUS project. (https://github.com/cmus/cmus)
 *
 */

#include <pulse/pulseaudio.h>
#include <string.h>

#include "output_plugins/Pulse.h"


static pa_threaded_mainloop	*pa_ml;    /* Pointer to mainloop object */
static pa_context		    *pa_ctx;   /* Pointer to context object  */
static pa_stream		    *pa_s;     /* Pointer to stream object   */
static pa_channel_map		 pa_cmap;
static pa_cvolume		     pa_vol;
static pa_sample_spec		 pa_ss;

static int pa_restore_volume = 1;


/**
 * Create a pa_problist object containing the application properties
 * name and version.
 * The object must be freed after use (by calling pa_problist_free(..)).
 */
static pa_proplist *_create_app_proplist(void)
{
	/* int	rc; */

	pa_proplist *pl = pa_proplist_new();
	/* BUG_ON(!pl); */

	/* rc = */ pa_proplist_sets(pl, PA_PROP_APPLICATION_NAME, "C* Music Player");
	/* BUG_ON(rc); */

	/* rc = pa_proplist_sets(pl, PA_PROP_APPLICATION_VERSION, VERSION); */
	/* BUG_ON(rc); */

	return pl;
}



/**
 * Create property list for the stream object. Must be freed with
 * pa_proplist_free() call after use.
 */
static pa_proplist *_create_stream_proplist(void) {
	/* int	rc; */

	pa_proplist *pl = pa_proplist_new();
        /* BUG_ON(!pl); */

	/* rc = */ pa_proplist_sets(pl, PA_PROP_MEDIA_ROLE, "music");
        /* BUG_ON(rc); */

	/* rc = */ pa_proplist_sets(pl, PA_PROP_MEDIA_ICON_NAME, "audio-x-generic");
        /* BUG_ON(rc); */

	return pl;
}



/**
 * Function called when the context state changes.
 * Signals the mainloop if the context is ready, failed or terminated.
 */
static void _pa_context_running_cb(pa_context *c, void *data) {
	const pa_context_state_t cs = pa_context_get_state(c);

	/* d_print("pulse: context state has changed to %s\n", _pa_context_state_str(cs)); */

	switch (cs) {
	case PA_CONTEXT_READY:
	case PA_CONTEXT_FAILED:
	case PA_CONTEXT_TERMINATED:
		pa_threaded_mainloop_signal(pa_ml, 0);
	default:
		return;
	}
}



/**
 * Callback to get input sink information. (Volume levels ...)
 */
static void _pa_sink_input_info_cb(pa_context *c,
				   const pa_sink_input_info *i,
				   int eol,
				   void *data)
{
	if (i) {
		memcpy(&pa_vol, &i->volume, sizeof(pa_vol));
		/* notify_via_pipe(mixer_notify_in); */
	}
}



/**
 * Subscribe event to context.
 */
static void _pa_ctx_subscription_cb(pa_context *ctx, pa_subscription_event_type_t t,
		uint32_t idx, void *userdata)
{
	pa_subscription_event_type_t type = t & PA_SUBSCRIPTION_EVENT_TYPE_MASK;
	if (type != PA_SUBSCRIPTION_EVENT_CHANGE)
		return;

	if (pa_s && idx == pa_stream_get_index(pa_s))
		pa_context_get_sink_input_info(ctx, idx, _pa_sink_input_info_cb, NULL);
}



/**
 * Function called when stream state changes. If the stream is in a
 * ready, failed, or terminated state, it signals the mainloop.
 */
static void _pa_stream_running_cb(pa_stream *s, void *data) {
	const pa_stream_state_t ss = pa_stream_get_state(s);

	/* d_print("pulse: stream state has changed to %s\n", _pa_stream_state_str(ss)); */

	switch (ss) {
	case PA_STREAM_READY:
	case PA_STREAM_FAILED:
	case PA_STREAM_TERMINATED:
		pa_threaded_mainloop_signal(pa_ml, 0);
	default:
		return;
	}
}



static void _pa_stream_success_cb(pa_stream *s, int success, void *data)
{
	pa_threaded_mainloop_signal(pa_ml, 0);
}



// TODO: This may be written in C++
/**
 * Given sample format, returns a pulse audio sample format type,
 * or an invalid sample format.
 */
static pa_sample_format_t _pa_sample_format(/* sample_format_t sf */) {
    /*
	const int signed_     	= sf_get_signed(sf);
	const int big_endian	= sf_get_bigendian(sf);
	const int sample_size	= sf_get_sample_size(sf) * 8;

	if (!signed_ && sample_size == 8)
		return PA_SAMPLE_U8;

	if (signed_) {
		switch (sample_size) {
		case 16:
			return big_endian ? PA_SAMPLE_S16BE : PA_SAMPLE_S16LE;
		case 24:
			return big_endian ? PA_SAMPLE_S24BE : PA_SAMPLE_S24LE;
		case 32:
			return big_endian ? PA_SAMPLE_S32BE : PA_SAMPLE_S32LE;
		}
	}

	return PA_SAMPLE_INVALID;
    */

    return PA_SAMPLE_S16LE;
}



// TODO: This may be written in C++
/**
 * Transform form channel map to pa_channel_position_t
 */
/*
static pa_channel_position_t pulse_channel_position(channel_position_t p)
{
	switch (p) {
	RET_IF(MONO);
	RET_IF(FRONT_LEFT); RET_IF(FRONT_RIGHT); RET_IF(FRONT_CENTER);
	RET_IF(REAR_CENTER); RET_IF(REAR_LEFT); RET_IF(REAR_RIGHT);
	RET_IF(LFE);
	RET_IF(FRONT_LEFT_OF_CENTER); RET_IF(FRONT_RIGHT_OF_CENTER);
	RET_IF(SIDE_LEFT); RET_IF(SIDE_RIGHT);
	RET_IF(TOP_CENTER);
	RET_IF(TOP_FRONT_LEFT); RET_IF(TOP_FRONT_RIGHT); RET_IF(TOP_FRONT_CENTER);
	RET_IF(TOP_REAR_LEFT); RET_IF(TOP_REAR_RIGHT); RET_IF(TOP_REAR_CENTER);
	default:
		return PA_CHANNEL_POSITION_INVALID;
	}
}
*/



/**
 * Creates a new context with property list, and connects it to the
 * mainloop. Return 0 on succes, -1 otherwise.
 */
static int _pa_create_context(void) {
    /* Create new proplist and api for the context */
	pa_proplist *pl = _create_app_proplist();
	pa_mainloop_api *api = pa_threaded_mainloop_get_api(pa_ml);
        /* BUG_ON(!api); */

	pa_threaded_mainloop_lock(pa_ml);

    /* Create context, set up callbacks and connect it to server */
	pa_ctx = pa_context_new_with_proplist(api, "C* Music Player", pl);
	    /* BUG_ON(!pa_ctx); */
	pa_proplist_free(pl);

	pa_context_set_state_callback(pa_ctx, _pa_context_running_cb, NULL);

	int rc = pa_context_connect(pa_ctx, NULL, PA_CONTEXT_NOFLAGS, NULL);
	if (rc)
		goto out_fail;

    /* Check context is in READY state, wait for it if needed */
	for (;;) {
		pa_context_state_t state;
		state = pa_context_get_state(pa_ctx);
		if (state == PA_CONTEXT_READY)
			break;
		if (!PA_CONTEXT_IS_GOOD(state))
			goto out_fail_connected;
		pa_threaded_mainloop_wait(pa_ml);
	}

	pa_context_set_subscribe_callback(pa_ctx, _pa_ctx_subscription_cb, NULL);
	pa_operation *op = pa_context_subscribe(pa_ctx, PA_SUBSCRIPTION_MASK_SINK_INPUT,
			NULL, NULL);
	if (!op)
		goto out_fail_connected;
	pa_operation_unref(op);

	pa_threaded_mainloop_unlock(pa_ml);

	return 0; /* OP_ERROR_SUCCESS; */

out_fail_connected:
	pa_context_disconnect(pa_ctx);

out_fail:
	pa_context_unref(pa_ctx);
	pa_ctx = NULL;

	pa_threaded_mainloop_unlock(pa_ml);

	/* ret_pa_last_error(); */
    return -1;
}



/**
 * Given a pa_operation, and being called on a locked mainloop,
 * waits for the operation to complete, destroys the operation and
 * unlocks the mainloop.
 * Returns 0 upon succesful completion, -1 otherwise.
 */
static int _pa_wait_unlock(pa_operation *o) {
	pa_operation_state_t state;

	if (!o) {
		pa_threaded_mainloop_unlock(pa_ml);
		/* ret_pa_last_error(); */
        return -1;
	}

	while ((state = pa_operation_get_state(o)) == PA_OPERATION_RUNNING)
		pa_threaded_mainloop_wait(pa_ml);

	pa_operation_unref(o);
	pa_threaded_mainloop_unlock(pa_ml);

	if (state == PA_OPERATION_DONE)
		return 0; /* OP_ERROR_SUCCESS; */
	else
        return -1;
		/* ret_pa_last_error(); */
}



/**
 * Drain a playback stream. Use this for notification when the
 * playback buffer is empty after playing all the audio in the buffer.
 * Please note that only one drain operation per stream may be issued
 * at a time.
 */
static int _pa_stream_drain(void)
{
	pa_threaded_mainloop_lock(pa_ml);

    /* _pa_stream_success_cb will signal the mainloop */
	return _pa_wait_unlock(pa_stream_drain(pa_s, _pa_stream_success_cb, NULL));
}



/**
 * Pause (or resume) playback of this stream temporarily.
 * If pause_ is 1, then stream is paused. Otherwise, if 0 is resumed
 * Return 0 on success, -1 on failure.
 */
static int _pa_stream_cork(int pause_) {
	pa_threaded_mainloop_lock(pa_ml);

	return _pa_wait_unlock(pa_stream_cork(pa_s, pause_, _pa_stream_success_cb, NULL));
}



/**
 * Initialize pulse plugin.
 * Creates a new mainloop object, and starts. Returns specific error code
 * or 0 on success.
 * The mainloop resources have to be freed with a call to the routine
 * pa_threaded_mainloop_free(..)
 */
int pulse_init() {
	int rc = 0;

	pa_ml = pa_threaded_mainloop_new();

	rc = pa_threaded_mainloop_start(pa_ml);
	if (rc) {
		pa_threaded_mainloop_free(pa_ml);
	}

	return rc;
}



/**
 * Called after pulse_init().
 * Creates a new context and connects it to the server. Creates a new
 * stream object conecting it to an input sink.
 * On error returns -1, otherwise return 0.
 */
int pulse_open(pa_sample_spec ss) {
	int	rc;

    /*
	const pa_sample_spec ss = { // TODO
		.format		= _pa_sample_format(sf),
		.rate		= sf_get_rate(sf),
		.channels	= sf_get_channels(sf)
	};
    */

	if (!pa_sample_spec_valid(&ss))
		return -1; /* -OP_ERROR_SAMPLE_FORMAT; */

	/* pa_ss = ss; */
    /*
	if (channel_map != NULL && channel_map_valid(channel_map)) {
		pa_channel_map_init(&pa_cmap);
		pa_cmap.channels = ss.channels;
		for (i = 0; i < pa_cmap.channels; i++)
			pa_cmap.map[i] = pulse_channel_position(channel_map[i]);
        pa_cmap.channels = ss.channels;
        pa_channel_map_init_stereo(&pa_cmap);
	} else */
		pa_channel_map_init_auto(&pa_cmap, ss.channels, PA_CHANNEL_MAP_ALSA);

    /* Create a new context and connect it to server */
	rc = _pa_create_context();
	if (rc)
		return rc;

	pa_proplist *pl = _create_stream_proplist();

	pa_threaded_mainloop_lock(pa_ml);

    /* Create a new, unconnected stream with the specified name and sample
     * type, and specify the initial stream property list. */
	pa_s = pa_stream_new_with_proplist(pa_ctx, "playback", &ss, &pa_cmap, pl);
	pa_proplist_free(pl);
	if (!pa_s) {
		pa_threaded_mainloop_unlock(pa_ml);
		/* ret_pa_last_error(); */
        return -1;
	}

    /* Set the callback function that is called whenever the state of the
     * stream changes. */
	pa_stream_set_state_callback(pa_s, _pa_stream_running_cb, NULL);

    /* Connect the stream to a sink.
     * int pa_stream_connect_playback(pa_stream *s,
     *                                const char *dev,
     *                                const pa_buffer_attr *attr,  Buffering attributes, or NULL for default
     *                                pa_stream_flags_t flags,
     *                                const pa_cvolume * volume,   Initial volume, or NULL for default
     *                                pa_stream * sync_stream      Synchronize this stream with the specified one, or NULL for a standalone stream
     *                                )
     * If dev and volume are left as NULL, the sound server will have
     * the full flexibility to choose the device, volume and mute status
     * automatically. */
	rc = pa_stream_connect_playback(pa_s,
					NULL,
					NULL,
					PA_STREAM_NOFLAGS,
					pa_restore_volume ? NULL : &pa_vol,
					NULL);
	if (rc)
		goto out_fail;

	pa_threaded_mainloop_wait(pa_ml);

	if (pa_stream_get_state(pa_s) != PA_STREAM_READY)
		goto out_fail;

    /* Get information about the sink input by its index. */
	pa_context_get_sink_input_info(pa_ctx, pa_stream_get_index(pa_s),
			_pa_sink_input_info_cb, NULL);

	pa_threaded_mainloop_unlock(pa_ml);

	return 0; /* OP_ERROR_SUCCESS; */

out_fail:
	pa_stream_unref(pa_s);

	pa_threaded_mainloop_unlock(pa_ml);

	/* ret_pa_last_error(); */
    return -1;
}



/**
 * Closes the connection with the pulse audio and destroys the stream
 * object created.
 */
int pulse_close(void) {
	/*
	 * If this _pa_stream_drain() will be moved below following
	 * pa_threaded_mainloop_lock(), PulseAudio 0.9.19 will hang.
	 */
	if (pa_s)
		_pa_stream_drain();

	pa_threaded_mainloop_lock(pa_ml);

	if (pa_s) {
		pa_stream_disconnect(pa_s);
		pa_stream_unref(pa_s);
		pa_s = NULL;
	}

	if (pa_ctx) {
		pa_context_disconnect(pa_ctx);
		pa_context_unref(pa_ctx);
		pa_ctx = NULL;
	}

	pa_threaded_mainloop_unlock(pa_ml);

	return 0; /* OP_ERROR_SUCCESS; */
}



/**
 * Exit the pulseaudio plugin. Called allways after pulse_close().
 * Ends the mainloop.
 */
int pulse_exit(void) {
	if (pa_ml) {
		pa_threaded_mainloop_stop(pa_ml);
		pa_threaded_mainloop_free(pa_ml);
		pa_ml = NULL;
	}

	return 0; /* OP_ERROR_SUCCESS; */
}



/**
 * Writes count bytes from buf to the server (stream).
 * Returns count on succes, -1 otherwise.
 */
int pulse_write(const char *buf, int count) {
	int rc;

	pa_threaded_mainloop_lock(pa_ml);

    /* Write some data to the server (for playback streams).
     *
     * If free_cb is non-NULL this routine is called when all data has been written out.
     *
     * An internal reference to the specified data is kept, the data is NOT copied.
     * If NULL, the data is copied into an internal buffer.
     *
     * int pa_stream_write(pa_stream *p,         // stream to use
	 *                     const void *data,     // data to write
     *                     size_t nbytes,        // bytes of data to write from data ptr,
	 *                     pa_free_cb_t free_cb, // A cleanup routine for the data or NULL to request an internal copyu
	 *                     int64_t offset,       // Offset for seeking, must be 0 for upload streams, must be in multiples of the stream's sample spec frame size
     *          		   pa_seek_mode_t seek   //	Seek mode, must be PA_SEEK_RELATIVE for upload streams
     *                     )                     */
	rc = pa_stream_write(pa_s, buf, count, NULL, 0, PA_SEEK_RELATIVE);
	pa_threaded_mainloop_unlock(pa_ml);

	if (rc)
        return -1;
		/* ret_pa_error(rc); */
	else
		return count;
}



/**
 * Drop all data stored in streams and server buffers.
 * Returns 0 if droped succesfully, -1 otherwise.
 */
int pulse_drop(void) {
	pa_threaded_mainloop_lock(pa_ml);
	return _pa_wait_unlock(pa_stream_flush(pa_s, _pa_stream_success_cb, NULL));
}



/**
 * Pause the stream playback.
 */
int pulse_pause(void) {
	return _pa_stream_cork(1);
}



/**
 * Unpause stream playback.
 */
int pulse_unpause(void) {
	return _pa_stream_cork(0);
}


/**
 * Return the number of bytes requested by the server that have not
 * yet been written.
 */
int pulse_buffer_space(void) {
	pa_threaded_mainloop_lock(pa_ml);
	int s = (int) pa_stream_writable_size(pa_s);
	pa_threaded_mainloop_unlock(pa_ml);

	return s;
}
