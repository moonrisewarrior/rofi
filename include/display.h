/*
 * rofi
 *
 * MIT/X11 License
 * Copyright © 2013-2017 Qball Cow <qball@gmpclient.org>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 */

#ifndef ROFI_DISPLAY_H
#define ROFI_DISPLAY_H

#include <glib.h>
#include <cairo.h>
#include "widgets/widget.h"
#include "widgets/textbox.h"
#include "widgets/listview.h"
#include "helper.h"
#include "nkutils-bindings.h"

typedef struct _display_buffer_pool display_buffer_pool;

/**
 * @param main_loop The GMainLoop
 * @param bindings The bindings object
 *
 * Setup the display backend
 *
 * @returns Whether the setup succeeded or not
 */
gboolean display_setup(GMainLoop *main_loop, NkBindings *bindings);

/**
 * Do some late setup of the display backend
 *
 * @returns Whether the setup succeeded or not
 */
gboolean display_late_setup(void);

/**
 * Do some early cleanup, like unmapping the surface
 */
void display_early_cleanup(void);

/**
 * Cleanup any remaining display related stuff
 */
void display_cleanup(void);

/**
 * Dumps the display layout for -help output
 */
void display_dump_monitor_layout ( void );
void display_get_current_monitor ( int *width, int *height );
gboolean display_reversed ( widget *main_box );

/**
 * @param context The startup notification context for the application to launch
 * @param child_setup A pointer to return the child setup function
 * @param user_data A pointer to return the child setup function user_data
 *
 * Provides the needed child setup function
 */
void display_startup_notification ( RofiHelperExecuteContext *context, GSpawnChildSetupFunc *child_setup, gpointer *user_data );

display_buffer_pool *display_buffer_pool_new(gint width, gint height);
void display_buffer_pool_free(display_buffer_pool *pool);

cairo_surface_t *display_buffer_pool_get_next_buffer(display_buffer_pool *pool);
void display_surface_commit(cairo_surface_t *surface);
void display_surface_drop(cairo_surface_t *surface);

void display_trigger_paste(gboolean primary);

gint display_get_view_width ( widget *main_box );
gint display_get_view_height ( widget *main_box, listview *list_view );
void display_update_view_position ( widget *main_box, listview *list_view, gint width, gint height );


#endif