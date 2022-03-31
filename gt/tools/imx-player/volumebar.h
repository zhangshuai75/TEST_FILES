/*
 * Copyright (C) 2009-2011 Freescale Semiconductor, Inc. All rights reserved.
 *
 */

/*
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */

#ifndef VOLUMEBAR_H_
#define VOLUMEBAR_H_

#define VOLUME_BAR_W      30
#define VOLUME_BAR_H      200

typedef struct
{
  GtkWidget *volumebar;
  GtkWidget *mute;
  GtkWidget *volume;
} VolumeBar;

void volumebar_create(void *imxplayer);
void volumebar_show(VolumeBar *volumebar, gboolean show);

#endif /* VOLUMEBAR_H_ */
